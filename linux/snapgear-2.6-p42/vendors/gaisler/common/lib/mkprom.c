/*
 * MKPROM, LEON boot-prom utility. 
 * Copyright (C) 2001 Gaisler Research
 * See <linux>/COPYING for licensing terms.
 */

#include <linux/config.h>
#include <asm/leon/lelo.h>
#include <string.h>
#include <stdlib.h> 
#include <stdio.h>
#include <elf.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define VAL(x)  strtol(x,(char **)NULL,0)
#define printf(fmt,arg...) if (verbose) printf(fmt,##arg)
int secnum = 0;
FILE *dumpfile;
int verbose = 1;
int leon = 1;
double freq = 5E7;
int comp = 1;
int flash = 0;


int main (int argc,char **argv)
{
      char cmd[512];
      char msg[128];
      int baud = CONFIG_MKPROM_BAUD;		/* 19200 baud */
      int edac = 0;
      //int par = 0;
      //double wdfreq = 0.0;
      int i;//,n;
      //int mctrl = 0x00880017;
      //int memcfg = 0;
      //int prot = 0;
      //int wrp = 0;
      int ramcs = CONFIG_MKPROM_RAMCS;
      int rambanks = 1;
      int ramsize = CONFIG_MKPROM_RAMSIZE * 1024;
      int romsize = CONFIG_MKPROM_ROMSIZE * 1024;
      //int ramws = 0;
      int ramrws = CONFIG_MKPROM_RAMRWS;
      int ramwws = CONFIG_MKPROM_RAMWWS;
      int ramwidth = 32;
      //int romwidth = 8;
      int rmw = CONFIG_MKPROM_RMW;
      //int romws = 2;
      int romrws = CONFIG_MKPROM_ROMRWS;
      int romwws = CONFIG_MKPROM_ROMWWS;
      int stack = 0;
      //int stat = 1;
      int bmsg = 1;
      //int bdinit = 0;
      //int waitcfg = 0x33330000;
      //int wdog = 1;
      //int dump = 0;
      char ofile[128] = "prom.out";
      char dfile[128] = "";
      int tmp, tmp2;
      int sdramsz = CONFIG_MKPROM_SDRAM * 1024 * 1024;
      int nosram = 0;
      int sdrambanks = CONFIG_MKPROM_SDRAMBANKS;
      int sdcas = CONFIG_MKPROM_CAS;
      int trp = CONFIG_MKPROM_TRP;
      int trfc = CONFIG_MKPROM_TRFC;
      int colsz = CONFIG_MKPROM_COLSZ;
      double refresh = 7.8;
      double ftmp;
      int refr;
      
      freq = (CONFIG_MKPROM_FREQ+500)/1000;
      freq *= 1E6;
      refresh = atof (CONFIG_MKPROM_REFRESH);
      
      dfile[0] = 0;
      if (argc == 2) {
            strcpy (dfile, argv[1]);
      } else if (argc != 1){
            printf ("Usage: %s [outputfilename]\n",argv[0]);
            exit (EXIT_FAILURE);
      }
      
      printf ("mkprom called with args\n\
      CONFIG_MKPROM_BAUD       %d\n\
      CONFIG_MKPROM_FREQ(khz)  %d\n\
      CONFIG_MKPROM_COLSZ      %d\n\
      CONFIG_MKPROM_CAS        %d\n\
      CONFIG_MKPROM_SDRAMBANKS %d\n\
      CONFIG_MKPROM_SDRAM(M)   %d\n\
      CONFIG_MKPROM_TRFC       %d\n\
      CONFIG_MKPROM_TRP        %d\n\
      CONFIG_MKPROM_REFRESH    %s\n\
      CONFIG_MKPROM_RAMSIZE(k) %d\n\
      CONFIG_MKPROM_RAMCS      %d\n\
      CONFIG_MKPROM_RAMRWS     %d\n\
      CONFIG_MKPROM_RAMWWS     %d\n\
      CONFIG_MKPROM_RMW        %d\n\
      CONFIG_MKPROM_ROMSIZE(k) %d\n\
      CONFIG_MKPROM_ROMRWS     %d\n\
      CONFIG_MKPROM_ROMWWS     %d\n",
      CONFIG_MKPROM_BAUD, CONFIG_MKPROM_FREQ, CONFIG_MKPROM_COLSZ, CONFIG_MKPROM_CAS,\
      CONFIG_MKPROM_SDRAMBANKS, CONFIG_MKPROM_SDRAM, CONFIG_MKPROM_TRFC, CONFIG_MKPROM_TRP,\
      CONFIG_MKPROM_REFRESH, CONFIG_MKPROM_RAMSIZE, CONFIG_MKPROM_RAMCS, \
      CONFIG_MKPROM_RAMRWS, CONFIG_MKPROM_RAMWWS, CONFIG_MKPROM_RMW, CONFIG_MKPROM_ROMSIZE, \
      CONFIG_MKPROM_ROMRWS, CONFIG_MKPROM_ROMWWS);
      
      if ((colsz<0) || (colsz >3)) colsz = 1;
      if ((sdcas<0) || (sdcas >1)) sdcas = 1;
      if ((sdrambanks < 1) || (sdrambanks  > 3)) sdrambanks = 1;
      
      if ((dumpfile = fopen (dfile, "w+")) == NULL) {
            if ((dumpfile = tmpfile()) == NULL) {
                  printf ("Failed to open file ]%s[\n",dfile);
                  exit (EXIT_FAILURE);
            }
      }
      
      if (dfile[0]!=0) {
            printf("Creating LEON boot register initialization: %s\n", ofile);
      }
      /*fprintf (dumpfile, "\n\t .text\n");
      fprintf (dumpfile, "\n\t.align 32\n");
      fprintf (dumpfile, "\t.global sections\n");
      fprintf (dumpfile, "sections:\n");
      fprintf (dumpfile, "\t.word\t0\n");
      
      fprintf (dumpfile,"\n\t.global _memcfg1, _memcfg2, _uart, _scaler, _ftreg \n");
      fprintf (dumpfile, "\n\t.global ramsize, _stack\n");
      fprintf (dumpfile, "\t.global freq, configmsg, bmsg\n");
      fprintf (dumpfile, "freq:\n");
      fprintf (dumpfile, "\t.word\t%d\n", (int) (freq / 1000000));
      */
      
      fprintf (dumpfile, "#define freq %d\n", (int) (freq / 1000000));

      //fprintf (dumpfile, "bmsg:\n");
      //fprintf (dumpfile, "\t.word\t%d\n", bmsg);
      
    // ################# lreg memcfg1 ################# 
      tmp = romsize;
      tmp >>= 14;
      i = 0;
      while (tmp)
      {
            i++;
            tmp >>= 1;
      }
      tmp = (i << 14) | romrws | (romwws << 4);
      //fprintf (dumpfile, "_memcfg1:\n");
      //fprintf (dumpfile, "\t.word\t0x%x\n", tmp);
      
      fprintf (dumpfile, "#define memcfg1 0x%x\n", tmp);
      
      if (dfile[0]!=0) {
            printf ("lreg memcfg1:0x%x\n", tmp);
      }
      
      // ################# lreg memcfg2 ################# 
      tmp = ramsize / ramcs;
      tmp >>= 14;
      i = 0;
      while (tmp)
      {
            i++;
            tmp >>= 1;
      }
      tmp = (i << 9) | ramrws | (ramwws << 2);
      switch (ramwidth) {
      case 8 : ramwidth = 0; break;
      case 16: ramwidth = 1; break;
      case 39: ramwidth = 3; break;
      default:ramwidth = 2;
      }
      tmp |= ramwidth << 4;
      tmp |= rmw << 6;
      
      i = 0;
      if (sdramsz) {
            tmp2 = sdramsz;
            tmp2 /= (sdrambanks * 32);
            while (tmp2) {
                  tmp2 >>=1; i++;
            }
            tmp |= 0x80004000;
      }
      tmp = (tmp & ~(3<<21)) | (colsz <<21);	/* column size */ 
      tmp = (tmp & ~(7<<23)) | (i <<23);		/* bank size */ 
      tmp = (tmp & ~(1<<26)) | (sdcas <<26); 	/* cas delay */
      if ((2.0E9/freq) < (double)trp) trp = 1; else trp = 0;
      ftmp = ((double)trfc) - (3E9/freq);
      if (ftmp > 0) trfc = 1 + (ftmp * freq)/1E9; else trfc = 0;
      if (trfc > 7) trfc = 7;
      tmp = (tmp & ~(7<<27)) | (trfc <<27);	
      tmp = (tmp & ~(1<<30)) | (trp <<30); 	/* cas delay */
      refr = (freq * refresh) / 1E6;
      if (refr > 0x7fff) refr = 0x7fff;
      if (nosram) {
            ramsize = sdramsz << 20;
            tmp |= 1<< 13;
      }
      //fprintf (dumpfile, "_memcfg2:\n");
      //fprintf (dumpfile, "\t.word\t0x%x\n", tmp);
      
      fprintf (dumpfile, "#define memcfg2 0x%x\n", tmp);
      
      if (dfile[0]!=0) {
            printf ("lreg memcfg2:0x%x\n", tmp);
      }
      else {
            printf ("      MKPROM_MEMCFG2           0x%x\n", tmp);
      }
      
      // ################# uart variable  ################# 
      tmp = (((10 * (int) freq) / (8 * baud)) + 5) / 10 - 1;
      baud = freq / (8 * (tmp + 1));
      //fprintf (dumpfile, "_uart:\n");
      //fprintf (dumpfile, "\t.word\t%d\n", tmp);
      
      fprintf (dumpfile, "#define uart 0x%x\n", tmp);

      if (dfile[0]!=0) {
            printf ( "uart:%d\n", tmp);
      }
      
      // ################# lreg ftreg ################# 
      if (edac) tmp = 0x200; else tmp = 0;
      if (sdramsz) tmp = (tmp & ~(0x7fff<<12)) | (refr <<12);
      //fprintf (dumpfile, "_ftreg:\n");
      //fprintf (dumpfile, "\t.word\t0x%x\n", tmp);
      
      fprintf (dumpfile, "#define ftreg 0x%x\n", tmp);
      
      if (dfile[0]!=0) {
            printf ( "lreg ftreg:0x%x\n", tmp);
      }

      // ################# ramsize variable ################# 
      //fprintf (dumpfile, "ramsize:\n");
      //fprintf (dumpfile, "\t.word\t0x%x\n", ramsize);
      
      fprintf (dumpfile, "#define ramsize 0x%x\n", ramsize);

      if (dfile[0]!=0) {
            printf ("ramsize:0x%x\n", ramsize);
      }
      
      // ################# stack top ################# 
      if (!stack)
            stack = 0x40000000 + ramsize - 32;
      //fprintf (dumpfile, "_stack:\n");
      //fprintf (dumpfile, "\t.word\t0x%x\n", stack);
      
      fprintf (dumpfile, "#define stack 0x%x\n", stack);

      if (dfile[0]!=0) {
            printf ( "stack:0x%x\n", stack);
      }

      // #################  kernel params ################# 
      //fprintf (dumpfile, "configmsg:\n");
      //fprintf (dumpfile, "\t.string\t\"%s\"\n", cmd);
      
      
      sprintf (cmd, " LeLo (Leon Bootloader)\\n\\r");
      sprintf (msg, " Copyright Gaisler Research 2003, all rights reserved.\\n\\r\\n\\r"); strcat (cmd, msg);
      sprintf (msg, " system clock   : %3.1f MHz\\n\\r", freq / 1E6); strcat (cmd, msg);
      sprintf (msg, " baud rate      : %d baud\\n\\r", baud); strcat (cmd, msg);
      sprintf (msg, " prom           : %d K, (%d/%d) ws (r/w)\\n\\r", romsize >> 10,romrws, romwws); strcat (cmd, msg);
      if (!nosram) {
      sprintf (msg, " sram           : %d K, %d bank(s), %d/%d ws (r/w)\\n\\r", ramsize >> 10, rambanks, ramrws,ramwws); strcat (cmd, msg);
      } else {
      sprintf (msg, " sdram          : %d M, %d bank(s), %d-bit column\\n", sdramsz, sdrambanks, colsz+8); strcat (cmd, msg);
      sprintf (msg, " sdram          : cas: %d, trp: %2.0f ns, trfc: %2.0f ns, refresh %3.1f us\\n", sdcas+2, (double)(trp+2)*1E9/freq,(double)(trfc+3)*1E9/freq, (double)(refr+1)*1E6/freq); strcat (cmd, msg);
      }
      
      fclose (dumpfile);
      exit (EXIT_SUCCESS);
}






























