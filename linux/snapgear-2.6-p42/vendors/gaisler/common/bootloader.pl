#!/usr/bin/perl
# Konrad Eisele <eiselekd@web.de>, 2003 
use Term::ANSIColor;
use File::Basename;


%boot_cfg = (
    cfg_baud => 38400,
    cfg_freq => 25000,
    cfg_colsz => 1,
    cfg_cas => 1,
    cfg_sdram_banks => 0, 
    cfg_sdram_sz => 0,
    cfg_sdram_refresh => "7.8",
    cfg_sdram_trfc => 66,
    cfg_sdram_trp => 20,
    cfg_ddr_freq => 200,
    cfg_sdram_nosram => 1,
	     
    cfg_sram_sz => 0, #8192,
    cfg_sram_cs => 0, #1,
    cfg_sram_rws => 0,
    cfg_sram_wws => 0,
    cfg_sram_rmw => 0,
    cfg_rom_sz => 1024,
    cfg_rom_rws => 2,
    cfg_rom_wws => 2,
		cfg_rom_we => 0,
    cfg_loop => "no",
    cfg_flow => 0,

    cfg_ramtype => "sdram",
    cfg_phyaddr => "0x40000000",
    cfg_phyaddr_stack => "0x40200000",
    cfg_phyaddr_set => 0	     
);

%boot_map = 
   (
    cfg_flow => [
       CONFIG_DEFAULTS_GAISLER_LEON2_UARTFLOWCTRL => 1
    ],
    
    

    cfg_ramtype => [
	CONFIG_DEFAULTS_GAISLER_LEON2_USE_SRAM => "sram",
	CONFIG_DEFAULTS_GAISLER_LEON2_USE_SDRAM => "sdram",
 	CONFIG_DEFAULTS_GAISLER_LEON2_USE_DDRSDRAM => "ddrsdram",
	CONFIG_DEFAULTS_GAISLER_LEON2_USE_DDR2SDRAM => "ddr2sdram"

        ],
  
    cfg_baud => [
	CONFIG_DEFAULTS_GAISLER_LEON2_BAUDRATE_9600 => 9600,
        CONFIG_DEFAULTS_GAISLER_LEON2_BAUDRATE_19200 => 19200,
	CONFIG_DEFAULTS_GAISLER_LEON2_BAUDRATE_38400 => 38400
	],

    cfg_loop => [
	CONFIG_DEFAULTS_GAISLER_LEON2_LOOPBACK => "yes"
    ],

    cfg_freq => [
        CONFIG_DEFAULTS_GAISLER_LEON2_FREQ_20000 => 20000,
        CONFIG_DEFAULTS_GAISLER_LEON2_FREQ_25000 => 25000,
	CONFIG_DEFAULTS_GAISLER_LEON2_FREQ_30000 => 30000,
	CONFIG_DEFAULTS_GAISLER_LEON2_FREQ_40000 => 40000,
	CONFIG_DEFAULTS_GAISLER_LEON2_FREQ_50000 => 50000,
	CONFIG_DEFAULTS_GAISLER_LEON2_FREQ_80000 => 80000, 
	CONFIG_DEFAULTS_GAISLER_LEON2_FREQ_100000 => 100000, 
	CONFIG_DEFAULTS_GAISLER_LEON2_FREQ_101000 => 101000 
	],


    cfg_colsz => [
   CONFIG_DEFAULTS_GAISLER_LEON2_SDRAMCOL_256 => 0,
   CONFIG_DEFAULTS_GAISLER_LEON2_SDRAMCOL_512 => 1,
   CONFIG_DEFAULTS_GAISLER_LEON2_SDRAMCOL_1024 => 2,
   CONFIG_DEFAULTS_GAISLER_LEON2_SDRAMCOL_2048 => 3,
   CONFIG_DEFAULTS_GAISLER_LEON2_SDRAMCOL_4096 => 4
    ],

    cfg_cas => [
   CONFIG_DEFAULTS_GAISLER_LEON2_SDRAMCAS_2 => 0,
   CONFIG_DEFAULTS_GAISLER_LEON2_SDRAMCAS_3 => 1
    ],

    cfg_sdram_banks => [
   CONFIG_DEFAULTS_GAISLER_LEON2_SDRAMBANKS_1 => 1, 
   CONFIG_DEFAULTS_GAISLER_LEON2_SDRAMBANKS_2 => 2,
	 CONFIG_DEFAULTS_GAISLER_LEON2_SDRAMBANKS_3 => 3,
	 CONFIG_DEFAULTS_GAISLER_LEON2_SDRAMBANKS_4 => 4
    ],

    cfg_sdram_sz => [
  CONFIG_DEFAULTS_GAISLER_LEON2_SDRAMSIZE_4mb   => 4,
  CONFIG_DEFAULTS_GAISLER_LEON2_SDRAMSIZE_8mb   => 8,
  CONFIG_DEFAULTS_GAISLER_LEON2_SDRAMSIZE_16mb  => 16,
  CONFIG_DEFAULTS_GAISLER_LEON2_SDRAMSIZE_32mb  => 32,
  CONFIG_DEFAULTS_GAISLER_LEON2_SDRAMSIZE_64mb  => 64, 
  CONFIG_DEFAULTS_GAISLER_LEON2_SDRAMSIZE_128mb => 128,
  CONFIG_DEFAULTS_GAISLER_LEON2_SDRAMSIZE_256mb => 256, 
  CONFIG_DEFAULTS_GAISLER_LEON2_SDRAMSIZE_512mb => 512,
  CONFIG_DEFAULTS_GAISLER_LEON2_SDRAMSIZE_1024mb => 1024
    ],

    cfg_sdram_refresh => [
  CONFIG_DEFAULTS_GAISLER_LEON2_SDRAM_refresh => sub { my ($v) = @_; return $v;}
    ],

    cfg_sdram_trfc => [
  CONFIG_DEFAULTS_GAISLER_LEON2_SDRAM_trfc => sub { my ($v) = @_; return $v;}
    ],

    cfg_sdram_trp => [
  CONFIG_DEFAULTS_GAISLER_LEON2_SDRAM_trp => sub { my ($v) = @_; return $v;}
    ],
    
    cfg_ddr_freq => [
  CONFIG_DEFAULTS_GAISLER_LEON2_DDR2SDRAM_FREQ => sub { my ($v) = @_; return $v;}
    ],
    
    cfg_sdram_nosram => [
	CONFIG_DEFAULTS_GAISLER_LEON2_SDRAM_SRAMKEEP => 0
    ],

    
    cfg_phyaddr_set => [
			CONFIG_KERNEL_PHYSICAL_ADDR_SET => 1
	],
    cfg_phyaddr => [
		    CONFIG_KERNEL_PHYSICAL_ADDR => sub { my ($v) = @_; return $v;}
    ],

    cfg_phyaddr_stack => [
		    CONFIG_KERNEL_PHYSICAL_STACK => sub { my ($v) = @_; return $v;}
    ],
    

    
    cfg_sram_sz => [
  CONFIG_DEFAULTS_GAISLER_LEON2_SRAMSIZE_8k    => 8,
  CONFIG_DEFAULTS_GAISLER_LEON2_SRAMSIZE_16k   => 16, 
  CONFIG_DEFAULTS_GAISLER_LEON2_SRAMSIZE_32k   => 32,
  CONFIG_DEFAULTS_GAISLER_LEON2_SRAMSIZE_64k   => 64, 
  CONFIG_DEFAULTS_GAISLER_LEON2_SRAMSIZE_128k  => 128,
  CONFIG_DEFAULTS_GAISLER_LEON2_SRAMSIZE_256k  => 256,
  CONFIG_DEFAULTS_GAISLER_LEON2_SRAMSIZE_512k  => 512,
  CONFIG_DEFAULTS_GAISLER_LEON2_SRAMSIZE_1mb   => 1024,
  CONFIG_DEFAULTS_GAISLER_LEON2_SRAMSIZE_2mb   => 2048,
  CONFIG_DEFAULTS_GAISLER_LEON2_SRAMSIZE_4mb   => 4096,
  CONFIG_DEFAULTS_GAISLER_LEON2_SRAMSIZE_8mb   => 8192,
  CONFIG_DEFAULTS_GAISLER_LEON2_SRAMSIZE_16mb  => 16384,
  CONFIG_DEFAULTS_GAISLER_LEON2_SRAMSIZE_32mb  => 32768,
  CONFIG_DEFAULTS_GAISLER_LEON2_SRAMSIZE_64mb  => 65536, 
  CONFIG_DEFAULTS_GAISLER_LEON2_SRAMSIZE_128mb => 131072,
  CONFIG_DEFAULTS_GAISLER_LEON2_SRAMSIZE_256mb => 262144 
    ],

    cfg_sram_cs => [
   CONFIG_DEFAULTS_GAISLER_LEON2_SRAMBANKS_1 => 1, 
   CONFIG_DEFAULTS_GAISLER_LEON2_SRAMBANKS_2 => 2,
   CONFIG_DEFAULTS_GAISLER_LEON2_SRAMBANKS_3 => 3,
   CONFIG_DEFAULTS_GAISLER_LEON2_SRAMBANKS_4 => 4
    ],

    cfg_sram_rws => [
   CONFIG_DEFAULTS_GAISLER_LEON2_SRAM_rws_0 => 0,
   CONFIG_DEFAULTS_GAISLER_LEON2_SRAM_rws_1 => 1,
   CONFIG_DEFAULTS_GAISLER_LEON2_SRAM_rws_2 => 2,
   CONFIG_DEFAULTS_GAISLER_LEON2_SRAM_rws_3 => 3
    ],

    cfg_sram_wws => [
   CONFIG_DEFAULTS_GAISLER_LEON2_SRAM_wws_0 => 0,
   CONFIG_DEFAULTS_GAISLER_LEON2_SRAM_wws_1 => 1,
   CONFIG_DEFAULTS_GAISLER_LEON2_SRAM_wws_2 => 2,
   CONFIG_DEFAULTS_GAISLER_LEON2_SRAM_wws_3 => 3
    ],

    cfg_sram_rmw => [
   CONFIG_DEFAULTS_GAISLER_LEON2_SRAM_rms_0 => 0,
   CONFIG_DEFAULTS_GAISLER_LEON2_SRAM_rms_1 => 1,
   CONFIG_DEFAULTS_GAISLER_LEON2_SRAM_rms_2 => 2,
   CONFIG_DEFAULTS_GAISLER_LEON2_SRAM_rms_3 => 3
    ],

    cfg_rom_sz => [
  CONFIG_DEFAULTS_GAISLER_LEON2_ROMSIZE_8k    => 8,
  CONFIG_DEFAULTS_GAISLER_LEON2_ROMSIZE_16k   => 16, 
  CONFIG_DEFAULTS_GAISLER_LEON2_ROMSIZE_32k   => 32,
  CONFIG_DEFAULTS_GAISLER_LEON2_ROMSIZE_64k   => 64, 
  CONFIG_DEFAULTS_GAISLER_LEON2_ROMSIZE_128k  => 128,
  CONFIG_DEFAULTS_GAISLER_LEON2_ROMSIZE_256k  => 256,
  CONFIG_DEFAULTS_GAISLER_LEON2_ROMSIZE_512k  => 512,
  CONFIG_DEFAULTS_GAISLER_LEON2_ROMSIZE_1mb   => 1024,
  CONFIG_DEFAULTS_GAISLER_LEON2_ROMSIZE_2mb   => 2048,
  CONFIG_DEFAULTS_GAISLER_LEON2_ROMSIZE_4mb   => 4096,
  CONFIG_DEFAULTS_GAISLER_LEON2_ROMSIZE_8mb   => 8192,
  CONFIG_DEFAULTS_GAISLER_LEON2_ROMSIZE_16mb  => 16384,
  CONFIG_DEFAULTS_GAISLER_LEON2_ROMSIZE_32mb  => 32768,
  CONFIG_DEFAULTS_GAISLER_LEON2_ROMSIZE_64mb  => 65536, 
  CONFIG_DEFAULTS_GAISLER_LEON2_ROMSIZE_128mb => 131072,
  CONFIG_DEFAULTS_GAISLER_LEON2_ROMSIZE_256mb => 262144 
    ],

    cfg_rom_rws => [
  CONFIG_DEFAULTS_GAISLER_LEON2_ROM_rws_0 => 0,  
  CONFIG_DEFAULTS_GAISLER_LEON2_ROM_rws_1 => 1, 
  CONFIG_DEFAULTS_GAISLER_LEON2_ROM_rws_2 => 2, 
  CONFIG_DEFAULTS_GAISLER_LEON2_ROM_rws_3 => 3, 
  CONFIG_DEFAULTS_GAISLER_LEON2_ROM_rws_4 => 4, 
  CONFIG_DEFAULTS_GAISLER_LEON2_ROM_rws_5 => 5, 
  CONFIG_DEFAULTS_GAISLER_LEON2_ROM_rws_6 => 6, 
  CONFIG_DEFAULTS_GAISLER_LEON2_ROM_rws_7 => 7, 
  CONFIG_DEFAULTS_GAISLER_LEON2_ROM_rws_8 => 8, 
  CONFIG_DEFAULTS_GAISLER_LEON2_ROM_rws_9 => 9, 
  CONFIG_DEFAULTS_GAISLER_LEON2_ROM_rws_10 => 10, 
  CONFIG_DEFAULTS_GAISLER_LEON2_ROM_rws_11 => 11,
  CONFIG_DEFAULTS_GAISLER_LEON2_ROM_rws_12 => 12, 
  CONFIG_DEFAULTS_GAISLER_LEON2_ROM_rws_13 => 13, 
  CONFIG_DEFAULTS_GAISLER_LEON2_ROM_rws_14 => 14, 
  CONFIG_DEFAULTS_GAISLER_LEON2_ROM_rws_15 => 15
    ],

    cfg_rom_wws => [
  CONFIG_DEFAULTS_GAISLER_LEON2_ROM_wws_0 => 0,  
  CONFIG_DEFAULTS_GAISLER_LEON2_ROM_wws_1 => 1, 
  CONFIG_DEFAULTS_GAISLER_LEON2_ROM_wws_2 => 2, 
  CONFIG_DEFAULTS_GAISLER_LEON2_ROM_wws_3 => 3, 
  CONFIG_DEFAULTS_GAISLER_LEON2_ROM_wws_4 => 4, 
  CONFIG_DEFAULTS_GAISLER_LEON2_ROM_wws_5 => 5, 
  CONFIG_DEFAULTS_GAISLER_LEON2_ROM_wws_6 => 6, 
  CONFIG_DEFAULTS_GAISLER_LEON2_ROM_wws_7 => 7, 
  CONFIG_DEFAULTS_GAISLER_LEON2_ROM_wws_8 => 8, 
  CONFIG_DEFAULTS_GAISLER_LEON2_ROM_wws_9 => 9, 
  CONFIG_DEFAULTS_GAISLER_LEON2_ROM_wws_10 => 10, 
  CONFIG_DEFAULTS_GAISLER_LEON2_ROM_wws_11 => 11, 
  CONFIG_DEFAULTS_GAISLER_LEON2_ROM_wws_12 => 12, 
  CONFIG_DEFAULTS_GAISLER_LEON2_ROM_wws_13 => 13, 
  CONFIG_DEFAULTS_GAISLER_LEON2_ROM_wws_14 => 14, 
  CONFIG_DEFAULTS_GAISLER_LEON2_ROM_wws_15 => 15 
    ],
		
		cfg_rom_we => [
       CONFIG_DEFAULTS_GAISLER_LEON2_ROM_WE => 1
    ]
    
);		     


$cmd = `which $0`;
$cmddn = dirname($cmd);
$BASE_DIR = $cmddn;

$cfg_image = "../../../vmlinux";
$cfg_bootloader = "<enter>";
$cfg_freq = 25;
$cfg_sram_sz = 0;
$cfg_sdram_sz = 0;

if ($#ARGV != 0) {
    die("Call: scanconfig.pl <configfile>\n");
}

%cfg = ();
$fn = $ARGV[0];
if (open(FILEH, "$fn")) {
    while (<FILEH>) {
	s/[\r\n]$//gi;
	@a = split("=",$_);
	if ($#a == 1) {
	    #print STDERR ($a[0]."=".$a[1]."\n");
	    $k = $a[0];
	    $v = $a[1];
	    $k =~ s/[^[:print:]]//gi;
	    $v =~ s/[^[:print:]]//gi;
	    $cfg{$k} = $v;
	} 
    }
    close(FILEH);
} else {
    print "opening \"$fn\": $!\n";
}

# Get the Kernel command line from .config
$cfg_kernel_command_line = "";
if (open(FILEH, "$fn")) {
   while (<FILEH>) {
      s/[\r\n]$//gi;
      $tmp = $_;
	   @a = split("=",$_);
	   if ($a[0] eq "CONFIG_KERNEL_COMMAND_LINE") {
         shift(@a);
         $cfg_kernel_command_line =join("=",@a);  
      } 
   }
      close(FILEH);
} else {
    print "opening \"$fn\": $!\n";
}


$boot_cfg = createconfig(\%boot_cfg,\%boot_map,\%cfg);
%boot_cfg = %{$boot_cfg};
boot_config_file (\%boot_cfg);

$cfg_phyaddr =~ s/"//g;
$cfg_phyaddr_stack =~ s/"//g;

print ("Basedir: $BASE_DIR\n");

    

print (" 
       5: CONFIG_MKPROM_BAUD        : $cfg_baud
       6: CONFIG_MKPROM_FREQ(khz)   : $cfg_freq
       7: CONFIG_MKPROM_COLSZ       : $cfg_colsz
       8: CONFIG_MKPROM_CAS         : $cfg_cas
       9: CONFIG_MKPROM_SDRAMBANKS  : $cfg_sdram_banks
      10: CONFIG_MKPROM_SDRAM(mb)   : $cfg_sdram_sz
      11: CONFIG_MKPROM_TRFC        : $cfg_sdram_trfc
      12: CONFIG_MKPROM_TRP         : $cfg_sdram_trp
      13: CONFIG_MKPROM_REFRESH     : $cfg_sdram_refresh
      13: CONFIG_MKPROM_NOSRAM      : $cfg_sdram_nosram
      14: CONFIG_MKPROM_RAMSIZE(k)  : $cfg_sram_sz
      15: CONFIG_MKPROM_RAMCS       : $cfg_sram_cs
      16: CONFIG_MKPROM_RAMRWS      : $cfg_sram_rws
      17: CONFIG_MKPROM_RAMWWS      : $cfg_sram_wws
      18: CONFIG_MKPROM_RMW         : $cfg_sram_rmw
      19: CONFIG_MKPROM_ROMSIZE(k)  : $cfg_rom_sz
      20: CONFIG_MKPROM_ROMRWS      : $cfg_rom_rws
      21: CONFIG_MKPROM_ROMWWS      : $cfg_rom_wws
      22: CONFIG_MKPROM_ROMWE       : $cfg_rom_we

      23: CONFIG_MKPROM_LOOP(yes/no): $cfg_loop

      24: CONFIG_MKPROM_PHYADDR     : $cfg_phyaddr
      25: CONFIG_MKPROM_CMDLINE     : $cfg_kernel_command_line

"
);

  if ( ($cfg_ramtype eq "sdram") or ($cfg_ramtype eq "ddrsdram") or ($cfg_ramtype eq "ddr2sdram") ) {
      $cfg_sram_sz = 0;
  } elsif ($cfg_ramtype eq "sram") {
      $cfg_sdram_sz = 0;
  }
  

  if ($cfg_sram_sz == 0 && $cfg_sdram_sz == 0 ) {
	    print (color("red")."Either sram, sdram, ddrsdram or ddr2sdram should be enabled (but not more than one)\n".color("reset"));
  }elsif (($cfg_ramtype eq "sdram") && ($cfg_sdram_sz>512)) {
	    print (color("red")."SDRAM controller does not support bank sizes greater than 512Mb\n".color("reset"));
  }elsif ((($cfg_ramtype eq "ddrsdram") || ($cfg_ramtype eq "ddr2sdram")) && ($cfg_sdram_sz<8)) {
	    print (color("red")."DDR SDRAM controller does not support bank sizes smaller than than 8Mb\n".color("reset"));
  }elsif ( ($cfg_ramtype eq "sdram") && ($cfg_colsz == 4) && ($cfg_sdram_sz != 512) ) {
      print (color("red")."SDRAM controller does not support column size 4k with out bank size than 512Mb\n".color("reset"));
  }elsif ( (($cfg_ramtype eq "ddr2sdram") || ($cfg_ramtype eq "ddrsdram")) && ($cfg_colsz == 0) ) {
      print (color("red")."DDR SDRAM controller does not support a column size of 256byte\n".color("reset"));  
  }else{
	    #writing configuration file
	    $cmdcf = "$cmddn/bootloader.h";
	    open HANDLE, ">$cmdcf" or die "Could not open $cmdcf";
	    print HANDLE "/* generated by bootloader.pl */\n";
	    print HANDLE "#define BOOTLOADER_FREQ_KHZ $cfg_freq\n";
	    print HANDLE "#define BOOTLOADER_SRAMSZ_KB $cfg_sram_sz\n";
	    print HANDLE "#define BOOTLOADER_SDRAMSZ_MB $cfg_sdram_sz\n";
	    print HANDLE "#define BOOTLOADER_BAUD $cfg_baud\n";
       print HANDLE "#define CONFIG_KERNEL_COMMAND_LINE $cfg_kernel_command_line\n\n";

	    $baud = $cfg_baud;
	    $edac = 0;
	    $rambanks = cfg_sram_cs;
	    $ramsize = $cfg_sram_sz * 1024;
	    $romsize = $cfg_rom_sz * 1024;
	    $ramrws = $cfg_sram_rws;
	    $ramwws = $cfg_sram_wws;
	    $ramwidth = 32;
	    $rmw = $cfg_sram_rmw;
	    $romrws = $cfg_rom_rws;
	    $romwws = $cfg_rom_wws;
			$romwe = $cfg_rom_we;
	    $stack = 0;
	    $bmsg = 1;
	    $sdramsz = $cfg_sdram_sz * 1024 * 1024;
	    $nosram = 0;
	    $sdrambanks = $cfg_sdram_banks;
	    $sdcas = $cfg_cas;
	    $trp = $cfg_sdram_trp;
	    $trfc = $cfg_sdram_trfc;
	    $colsz = $cfg_colsz;
      $ddr2spa_cfg1=0;
      $ddr2spa_cfg3=0;
      $ddrspa_cfg1=0;
      if ( ($cfg_ramtype eq "sdram") and ($colsz == 4) ){
        $colsz=3;
      }
	    if ($cfg_loop eq "yes") {
		$loop = 1;
	    } else {
		$loop = 0;
	    }
	    $cfg_sdram_refresh =~ s/"//gi;
	    
	    if ($ramsize == 0) {
		$nosram = 1;
	    }
	    $refresh = $cfg_sdram_refresh;
	    
	    $freq = ($cfg_freq + 500) / 1000;
	    $freq *= 1E6;

	    ################# lreg memcfg1 ################# 
	    $tmp = $romsize;
	    $tmp >>= 14;
	    $i = 0;
	    while ($tmp)
	    {
		$i++;
		$tmp >>= 1;
	    }
	    $tmp = ($i << 14) | $romrws | ($romwws << 4) | ($romwe << 11);
	    
	    $memcfg1 = $tmp;
	    printf ("memcfg1 :0x%x\n", $tmp);
	    
	    ################# lreg memcfg2 ################# 
	    $tmp = $ramsize;
	    $tmp >>= 14;
	    $i = 0;
	    while ($tmp)
	    {
		$i++;
		$tmp >>= 1;
	    }
	    $tmp = ($i << 9) | $ramrws | ($ramwws << 2);
	    if ($ramwidth == 8) {
		$ramwidth = 0;
	    } elsif ($ramwidth == 16) {
		$ramwidth = 1; 
	    } elsif ($ramwidth == 39) {
		$ramwidth = 3; 
	    } else {
	        $ramwidth = 2;
	    }
	    $tmp |= $ramwidth << 4;
	    $tmp |= $rmw << 6;
      
	    $i = 0;
	    if ($sdramsz) {
		$tmp2 = $cfg_sdram_sz;
		$tmp3 = 4;
		while ($tmp3 != $tmp2) {
		    $tmp3 <<=1; $i++;
		}
		$tmp |= 0x80004000;
	    }
	    $tmp = ($tmp & ~(3<<21)) | ($colsz <<21);	# column size 
	    $tmp = ($tmp & ~(7<<23)) | ($i <<23);		# bank size 
	    $tmp = ($tmp & ~(1<<26)) | ($sdcas <<26); 	# cas delay 
	    if ((2.0E9/$freq) < $trp) { $trp = 1; } else {$trp = 0;}
	    $ftmp = ($trfc) - (3E9/$freq);
	    if ($ftmp > 0) { $trfc = 1 + ($ftmp * $freq)/1E9; } else {$trfc = 0;}
	    if ($trfc > 7) {$trfc = 7;}
	    
	    #hardcoded
	    ##$trfc = 4;
	    #$trp = 1;
	    
	    $tmp = ($tmp & ~(7<<27)) | ($trfc <<27);	
	    $tmp = ($tmp & ~(1<<30)) | ($trp <<30); 	#cas delay 
		$refr = int(($freq * $refresh) / 1E6);
	    if ($refr > 0x7fff) { $refr = 0x7fff; }
	    if ($nosram) {
		$ramsize = $sdramsz << 20;
                if ($cfg_sdram_nosram) {
		    $tmp |= 1<< 13;
                }
	    }
	    
	    $memcfg2 = $tmp;
	    printf ("memcfg2 :0x%x\n", $tmp);
	    $grlibsdram = ($memcfg2 & ~0x7fff) | ($refr);
	    printf ("grsdram :0x%x\n", $grlibsdram);
      
      ################# DDR2 CFG #######################
      
      $ddr2_ref=1;
      $ddr2_OCD=0;
      $ddr2_EMR=1;
      
      $ddr2_bsize=$i-1;
      $ddr2_colsize=$cfg_colsz-1;
      $ddr2_cmd=0;
      
      $ddr2_CE=1;
      $ddr2_IN=0;
      $ddr2_PR=0;
      
      $ddr2_ref_val= int(($refresh*$cfg_ddr_freq)-0.5)-1;
      $ddr2_ref_val = $ddr2_ref_val & 0x7fff;
      
      $ddr2_RD=1;
      
      $ddr2_tWR= 4 + ($cfg_ddr_freq / 100);
      if ($ddr2_tWR < 0){
        $ddr2_tWR = 0;
      }
      if ($ddr2_tWR > 31){
        $ddr2_tWR = 31;
      }
      
      if ( $cfg_ddr_freq > 130 ) {
        $ddr2_tCD=1;
        $ddr2_tRP=1;
      }else{
        $ddr2_tCD=0;
        $ddr2_tRP=0;      
      }
      
      $ddr2_tRFC=1+((13*$cfg_ddr_freq)/100);
      $ddr2_tRFC=$ddr2_tRFC - 2;
      if ($ddr2_tRFC < 0){
        $ddr2_tRFC = 0;
      }
      if ($ddr2_tRFC > 31){
        $ddr2_tRFC = 31;
      }
      $ddr2spa_cfg1= ($ddr2_ref<<31) | ($ddr2_OCD<<30) | ($ddr2_EMR<<28) |
                     (0<<27) | ($ddr2_tCD<<26) | ($ddr2_bsize<<23) | ($ddr2_colsize<<21) |
                     ($ddr2_cmd<<18) | ($ddr2_PR<<17) | ($ddr2_IN<<16) | ($ddr2_CE<<15) |
                     ($ddr2_ref_val<<0);
      
      $ddr2spa_cfg3= ($ddr2_tRP<<28) | ($ddr2_tWR<<23) | ($ddr2_tRFC<<18) | ($ddr2_RD<<16);
      printf ("ddrfreq :%dMHz\n", $cfg_ddr_freq);
	  
	  ################# DDR CFG #######################
	  $ddr_ref=1;
     
      $ddr_bsize=$i-1;
      $ddr_colsize=$cfg_colsz-1;
      $ddr_cmd=0;
      
      $ddr_CE=1;
      $ddr_IN=0;
      $ddr_PR=0;
      
      $ddr_ref_val= int(($refresh*$cfg_ddr_freq)-0.5)-1;
      $ddr_ref_val = $ddr_ref_val & 0x7fff;
      
      if ( $cfg_ddr_freq > 100 ) {
        $ddr_tCD=1;
        $ddr_tRP=1;
      }else{
        $ddr_tCD=0;
        $ddr_tRP=0;
      }
      
      $ddr_tRFC=1+((7*$cfg_ddr_freq)/100);
      $ddr_tRFC=$ddr_tRFC - 3;
      if ($ddr_tRFC < 0){
        $ddr_tRFC = 0;
      }elsif ($ddr_tRFC > 7){
        $ddr_tRFC = 7;
      }
      $ddrspa_cfg1 = ($ddr_ref<<31) | ($ddr_tRP<<30)   | ($ddr_tRFC<<27)    |
                     ($ddr_tCD<<26) | ($ddr_bsize<<23) | ($ddr_colsize<<21) |
                     ($ddr_cmd<<18) | ($ddr_PR<<17)    | ($ddr_IN<<16)      | 
					 ($ddr_CE<<15)  | ($ddr_ref_val<<0);
      
	    ################# uart variable  ################# 
	    $baud = (((10 * (int $freq)) / (8 * $baud)) + 5) / 10 - 1;
	    $baud_real = $freq / (8 * ($baud + 1));
	    printf ("uart    :%d (baud:%d)\n", $baud,$baud_real);
	    printf ("loopback:%d \n", $loop);
	    
      
	    ################# lreg ftreg ################# 
	    if ($edac) {$tmp = 0x200;} else {$tmp = 0;}
	    if ($sdramsz) {$tmp = ($tmp & ~(0x7fff<<12)) | ($refr <<12);}
	    $ftreg = $tmp;
            printf ("ftreg   :0x%x ", $tmp);
	    print ($refresh."($refr)");
	    print ("\n");
	    
	    ################# ramsize variable ################# 
	    if ($cfg_sram_sz != 0) { $ramsize = $cfg_sram_sz * 1024 * $cfg_sram_cs; } 
	    elsif  ($cfg_sdram_sz != 0)  { $ramsize = $cfg_sdram_sz * 1024 * 1024 * $cfg_sdram_banks; }
	    printf ("ramsize :0x%x (%ik)\n", $ramsize,$ramsize/1024);
	    
	     $ramsize =  $ramsize - 4096;

            if ($cfg_phyaddr_set == 0) {
                 $cfg_phyaddr = "0x40000000";
                 if ($nosram && ($cfg_sdram_nosram == 0) ) {
                     $cfg_phyaddr = "0x60000000";
                 }
                 
            }
            print ("imageaddr:$cfg_phyaddr\n");

	    ################# stack top #################
            if ($cfg_phyaddr_set == 0) {
              if ($nosram && ($cfg_sdram_nosram == 0) ) {
                $stack = 0x60000000 + $ramsize - 32;
              } else {
	        $stack = 0x40000000 + $ramsize - 32;
              }
            } else {
              $stack = hex($cfg_phyaddr_stack);
            }
	    printf ("stack   :0x%x\n", $stack);
	    

	    printf HANDLE ("#define BOOTLOADER_memcfg1  0x%x\n", $memcfg1);
	    printf HANDLE ("#define BOOTLOADER_memcfg2  0x%x\n", $memcfg2);
	    printf HANDLE ("#define BOOTLOADER_uart     0x%x\n", $baud);
	    printf HANDLE ("#define BOOTLOADER_loopback 0x%x\n", $loop);
	    printf HANDLE ("#define BOOTLOADER_flow     0x%x\n", $cfg_flow);
	    printf HANDLE ("#define BOOTLOADER_ftreg    0x%x\n\n", $ftreg);
	    printf HANDLE ("#define BOOTLOADER_grlib_sdram 0x%x\n", $grlibsdram);
        printf HANDLE ("#define BOOTLOADER_ddr2spa_cfg1 0x%x\n", $ddr2spa_cfg1);
        printf HANDLE ("#define BOOTLOADER_ddr2spa_cfg3 0x%x\n", $ddr2spa_cfg3);
        printf HANDLE ("#define BOOTLOADER_ddrspa_cfg1 0x%x\n\n", $ddrspa_cfg1);
	    printf HANDLE ("#define BOOTLOADER_freq      %i\n\n", $freq);
	    printf HANDLE ("#define BOOTLOADER_ramsize   0x%x\n", $ramsize);
	    printf HANDLE ("#define BOOTLOADER_romsize   0x%x\n", $romsize);
	    printf HANDLE ("#define BOOTLOADER_stack     0x%x\n", $stack);



	    printf HANDLE ("\n#define BOOTLOADER_physbase  $cfg_phyaddr\n");
            
	    close HANDLE;
	    
	    $cmdcf = "$cmddn/bootloader.mk";
	    open HANDLE, ">$cmdcf" or die "Could not open $cmdcf";
	    print HANDLE "BOOTLOADER_VMLINUX = $cfg_image\n";
	    print HANDLE "BOOTLOADER_BOOTLOADER = $cfg_bootloader\n";
	    close HANDLE;
	}
  

sub getline() {

    $c=<STDIN>;
    $c =~ s/\n//g;
    return $c;
}






sub boot_config_file {
    
    my ($pericfg) = @_;
    my %pericfg = %{$pericfg};
    my $fn = "vendors/gaisler/common/bootloader.config.h";
    
    if (-f $fn) {
	print STDERR ("Making backup of $fn\n");
	`cp $fn $fn.bck`;
    }
    
    foreach $k (keys %pericfg) {
	$v = $pericfg{$k};
	$$k = $v;
	print ("$k:$v\n");
	$cache_config_file_data = cfg_replace ($k,$v,$cache_config_file_data);
    }

    if (open(FILEH, ">$fn")) {
	print FILEH $cache_config_file_data;
    } else {
	die ("opening \"$fn\": $!\n");
    }
}

sub createconfig {
    
    my ($defcfg,$map,$cfg) = @_;
    my $rkey,my $rval,my $rfound;
    my $k,my $v,my $rv;
    my %defcfg = %{$defcfg};
    my %map = %{$map};
    my %cfg = %{$cfg};
    
    foreach $k (keys %cfg) {
	$v = $cfg{$k};
	($rkey,$rval,$rfound) = resolve(\%map,$k,$v);
	
	if ($rfound == 1 && exists($defcfg{$rkey})) {
	    #print STDERR ("set $rkey:$rval\n");
	    $defcfg{$rkey} = $rval;
	} else {
	    #print STDERR ("!!!! Warning: Could not set cfiguration $k resolved to $rkey:$rval:$rfound\n");
	}
    }
    #printout_cfg(\%defcfg);
    return \%defcfg;
}

sub printout_cfg {
    my ($defcfg) = @_;
    my %defcfg = %{$defcfg};
    my $k;
    foreach $k (keys %defcfg) {
	print ("$k:".$defcfg{$k}."\n");
    }
}

sub resolve 
{
    my ($map,$entry,$value) = @_;
    my %tmp = (),my $e,my $k,my $v;
    my $key, my $val;
    my %map = %{$map};
    my $found = 0;
Found:
    foreach $k (keys %map) {
	$key = $k;
	%tmp = @{$map{$k}};
	foreach $e (keys %tmp) {
	    $val = $tmp{$e};
	    if (lc($entry) eq lc($e)) {
		$v = $tmp{$e};
		$found = 1;
		last Found;
	    }
	}
    }
    if (ref($val)) {
	$val = &$val($value);
    }
    return ($key,$val,$found);
}

sub cfg_replace {
    my ($k,$v,$l) = @_;
    my $type;
    if ($l =~ /%$k%\[(.)\]/) {
	$type = $1;
	if ($type eq "b") {
	    if ($v == 0) {
		$v = "false";
	    } else {
		$v = "true";
	    }
	    $l =~ s/%($k)%\[(.)\]/$v/gi;
	} else {
	    print STDERR ("Warning cound not resolve [$1] typedef\n");
	}
    }
    else {
	$l =~ s/%$k%/$v/gi;
    }
    return $l;
}
