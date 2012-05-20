/* vi: set sw=4 ts=4: */
/*
 * Busybox main internal header file
 *
 * Licensed under the GPL v2 or later, see the file LICENSE in this tarball.
 */
#ifndef	_BB_INTERNAL_H_
#define	_BB_INTERNAL_H_    1

#include "libbb.h"

#if ENABLE_FEATURE_INSTALLER
/* order matters: used as index into "install_dir[]" in busybox.c */
typedef enum bb_install_loc_t {
	_BB_DIR_ROOT = 0,
	_BB_DIR_BIN,
	_BB_DIR_SBIN,
	_BB_DIR_USR_BIN,
	_BB_DIR_USR_SBIN
} bb_install_loc_t;
#endif

#if ENABLE_FEATURE_SUID
typedef enum bb_suid_t {
	_BB_SUID_NEVER = 0,
	_BB_SUID_MAYBE,
	_BB_SUID_ALWAYS
} bb_suid_t;
#endif

struct bb_applet {
	const char *name;
	int (*main) (int argc, char **argv);
#if ENABLE_FEATURE_INSTALLER
	__extension__ enum bb_install_loc_t install_loc:8;
#endif
#if ENABLE_FEATURE_SUID
	__extension__ enum bb_suid_t need_suid:8;
#endif
#if ENABLE_FEATURE_PREFER_APPLETS
	/* true if instead of fork(); exec("applet"); waitpid();
	 * one can do fork(); exit(applet_main(argc,argv)); waitpid(); */
	unsigned char noexec;
	/* Even nicer */
	/* true if instead of fork(); exec("applet"); waitpid();
	 * one can simply call applet_main(argc,argv); */
	unsigned char nofork;
#endif
};


/* Defined in appletlib.c */
extern const struct bb_applet applets[];
extern const unsigned short NUM_APPLETS;

/* Length of these names has effect on size of libbusybox
 * and "individual" binaries. Keep them short.
 */
void lbb_prepare(const char *applet, char **argv) MAIN_EXTERNALLY_VISIBLE;
#if ENABLE_BUILD_LIBBUSYBOX
#if ENABLE_FEATURE_SHARED_BUSYBOX
int lbb_main(int argc, char **argv) EXTERNALLY_VISIBLE;
#else
int lbb_main(int argc, char **argv);
#endif
#endif


#endif	/* _BB_INTERNAL_H_ */
