#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <sys/utsname.h>
#include <gdbm.h>

void dump_data(int *ip, int size)
{
	do {
		printf("0x%x", *ip);
		if (size > sizeof(int))
			printf(",");
		size -= sizeof(int);
		++ip;
	} while (size > 0);
	printf("\n");
}

int base[100];

datum decode_data(char *p)
{
	datum data;
	int *value = base;

	data.dsize = 0;
	--p;

	do {
		++p;
		if ('0' <= *p && *p <= '9') {
			if (p[0] == '0') {
				if (p[1] == 'x')
					sscanf(p, "%x", value);
				else
					sscanf(p, "%o", value);
			}
			else
				sscanf(p, "%d", value);
			++value;
			data.dptr = (char *)base;
			data.dsize += sizeof(int);
		}
		else {
			data.dptr = NULL;
			break;
		}
	} while ((p = strchr(p, ',')) != (char *)0);

	return data;
}

char *progname;

int main(int argc, char **argv)
{
	GDBM_FILE dbf;
	datum key, data;
	struct utsname uts_info;
	char gdbmfile[80];
	char *p;
	int delete = 0;

	progname = argv[0];

	while (argc > 1 && argv[1][0] == '-') {
		p = &(argv[1][1]);
		while (*p) {
			switch (*p) {
			case 'd':
				delete = 1;
				break;

			default:
				fprintf(stderr, "Usage: %s [-d] key[=value[,value...]]\n", progname);
				exit(1);
			}
			++p;
		}
		++argv;
		--argc;
	}

	uname(&uts_info);
	sprintf(gdbmfile, "/lib/modules/%s/persist.gdbm", uts_info.release);

	if ((dbf = gdbm_open(gdbmfile, 0, GDBM_WRCREAT, 0600, NULL)) == NULL) {
		perror(gdbmfile);
		exit(1);
	}

	if (argc == 1) {
		key = gdbm_firstkey(dbf);
		while (key.dptr) {
			datum nextkey;

			data = gdbm_fetch(dbf, key);
			printf("%s=", key.dptr);
			dump_data((int *)(data.dptr), data.dsize);
			nextkey = gdbm_nextkey(dbf, key);
			key = nextkey;
		}
	}
	else {
		while (argc > 1) {
			char *kp = argv[1];
			if ((p = strchr(kp, '=')))
				*p++ = '\0';
			if ((*kp == '\'') || (*kp == '\"')) {
				if (strchr(kp +1, *kp)) {
					*(strchr(kp +1, *kp)) = '\0';
					++kp;
				}
			}
			key.dptr = kp;
			key.dsize = strlen(kp) +1;

			if (delete)
				gdbm_delete(dbf, key);
			else if ((p)) { /* change/insert */
				data = decode_data(p);
				if (data.dptr) {
					gdbm_store(dbf, key, data, GDBM_REPLACE);
					free(data.dptr);
				}
				else
					fprintf(stderr, "unknown '%s'\n", p);
			}
			else { /* show */
				data = gdbm_fetch(dbf, key);
				if (data.dptr) {
					printf("%s=", key.dptr);
					dump_data((int *)(data.dptr), data.dsize);
					free(data.dptr);
				}
				else
					fprintf(stderr, "'%s' not found\n", key.dptr);
			}
			++argv;
			--argc;
		}
	}
	gdbm_close(dbf);
	return 0;
}
