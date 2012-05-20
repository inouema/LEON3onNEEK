
/home/inouema/work/LEON/linux/snapgear-2.6-p42/images/image.dsu:     ファイル形式 elf32-sparc
/home/inouema/work/LEON/linux/snapgear-2.6-p42/images/image.dsu
アーキテクチャ: sparc, フラグ 0x00000112:
EXEC_P, HAS_SYMS, D_PAGED
開始アドレス 0x40000000

プログラムヘッダ:
    LOAD off    0x00010000 vaddr 0x40000000 paddr 0x40000000 align 2**16
         filesz 0x00300040 memsz 0x0031ae0c flags rwx
   STACK off    0x00000000 vaddr 0x00000000 paddr 0x00000000 align 2**2
         filesz 0x00000000 memsz 0x00000000 flags rwx

セクション:
索引名          サイズ      VMA       LMA       File off  Algn
  0 .stage2       00002800  40000000  40000000  00010000  2**3
                  CONTENTS, ALLOC, LOAD, CODE
  1 .vmlinux      002fc040  40004000  40004000  00014000  2**13
                  CONTENTS, ALLOC, LOAD, CODE
  2 .bss          0001adcc  40300040  40300040  00310040  2**5
                  ALLOC
  3 .note.GNU-stack 00000000  00000000  00000000  00310040  2**0
                  CONTENTS, READONLY, CODE
SYMBOL TABLE:
40000000 l    d  .stage2	00000000 .stage2
40004000 l    d  .vmlinux	00000000 .vmlinux
40300040 l    d  .bss	00000000 .bss
00000000 l    d  .note.GNU-stack	00000000 .note.GNU-stack
00000000 l    d  *ABS*	00000000 .shstrtab
00000000 l    d  *ABS*	00000000 .symtab
00000000 l    d  *ABS*	00000000 .strtab
00000000 l    df *ABS*	00000000 prom_stage2.c
400004f8 l     O .stage2	00000aec spi
4000017c l     F .stage2	00000030 no_nextnode
400001ac l     F .stage2	00000034 no_child
40000244 l     F .stage2	00000028 no_proplen
4000026c l     F .stage2	0000003c no_getprop
400002a8 l     F .stage2	00000008 no_setprop
400002b0 l     F .stage2	00000058 no_nextprop
40000160 l     F .stage2	00000004 leon_nbgetchar
40000164 l     F .stage2	00000018 leon_nbputchar
40000138 l     F .stage2	00000014 leon_reboot
4000014c l     F .stage2	00000014 leon_halt
400001e0 l     F .stage2	00000064 find_property
00000000 l    df *ABS*	00000000 pgt.S
40002000 l       .stage2	00000000 ctx_table
40002400 l       .stage2	00000000 pgd_table
00000000 l    df *ABS*	00000000 arch/sparc/kernel/head.S
3025400f l       .vmlinux	00000000 cputypvalend
0000000c l       *ABS*	00000000 cputypvallen
30254010 l       .vmlinux	00000000 cputypvar
30254020 l       .vmlinux	00000000 cputypvar_sun4m
3025402c l       .vmlinux	00000000 sun4_notsup
30254078 l       .vmlinux	00000000 sun4e_notsup
30008000 l       .vmlinux	00000000 t_zero
3001102c l       .vmlinux	00000000 gokernel
30008010 l       .vmlinux	00000000 t_tflt
30008020 l       .vmlinux	00000000 t_bins
30008030 l       .vmlinux	00000000 t_pins
30008040 l       .vmlinux	00000000 t_fpd
30008050 l       .vmlinux	00000000 t_wovf
30008060 l       .vmlinux	00000000 t_wunf
30008070 l       .vmlinux	00000000 t_mna
30008080 l       .vmlinux	00000000 t_fpe
30008090 l       .vmlinux	00000000 t_dflt
300080a0 l       .vmlinux	00000000 t_tio
300080b0 l       .vmlinux	00000000 t_wpt
300080c0 l       .vmlinux	00000000 t_badc
30008110 l       .vmlinux	00000000 t_irq1
30008120 l       .vmlinux	00000000 t_irq2
30008130 l       .vmlinux	00000000 t_irq3
30008140 l       .vmlinux	00000000 t_irq4
30008150 l       .vmlinux	00000000 t_irq5
30008160 l       .vmlinux	00000000 t_irq6
30008170 l       .vmlinux	00000000 t_irq7
30008180 l       .vmlinux	00000000 t_irq8
30008190 l       .vmlinux	00000000 t_irq9
300081a0 l       .vmlinux	00000000 t_irq10
300081b0 l       .vmlinux	00000000 t_irq11
300081c0 l       .vmlinux	00000000 t_irq12
300081d0 l       .vmlinux	00000000 t_irq13
300081e0 l       .vmlinux	00000000 t_irq14
30008200 l       .vmlinux	00000000 t_racc
30008210 l       .vmlinux	00000000 t_iacce
30008220 l       .vmlinux	00000000 t_bad22
30008240 l       .vmlinux	00000000 t_cpdis
30008250 l       .vmlinux	00000000 t_uflsh
30008260 l       .vmlinux	00000000 t_bad26
30008280 l       .vmlinux	00000000 t_cpexc
30008290 l       .vmlinux	00000000 t_dacce
300082a0 l       .vmlinux	00000000 t_hwdz
300082b0 l       .vmlinux	00000000 t_dserr
300082c0 l       .vmlinux	00000000 t_daccm
300082d0 l       .vmlinux	00000000 t_bad2d
30008320 l       .vmlinux	00000000 t_bad32
30008370 l       .vmlinux	00000000 t_bad37
300083c0 l       .vmlinux	00000000 t_iaccm
300083d0 l       .vmlinux	00000000 t_bad3d
30008420 l       .vmlinux	00000000 t_bad42
30008470 l       .vmlinux	00000000 t_bad47
300084c0 l       .vmlinux	00000000 t_bad4c
30008510 l       .vmlinux	00000000 t_bad51
30008560 l       .vmlinux	00000000 t_bad56
300085b0 l       .vmlinux	00000000 t_bad5b
30008600 l       .vmlinux	00000000 t_bad60
30008650 l       .vmlinux	00000000 t_bad65
300086a0 l       .vmlinux	00000000 t_bad6a
300086f0 l       .vmlinux	00000000 t_bad6f
30008740 l       .vmlinux	00000000 t_bad74
30008790 l       .vmlinux	00000000 t_bad79
300087e0 l       .vmlinux	00000000 t_bad7e
30008800 l       .vmlinux	00000000 t_sunos
30008810 l       .vmlinux	00000000 t_sbkpt
30008820 l       .vmlinux	00000000 t_divz
30008830 l       .vmlinux	00000000 t_flwin
30008840 l       .vmlinux	00000000 t_clwin
30008850 l       .vmlinux	00000000 t_rchk
30008860 l       .vmlinux	00000000 t_funal
30008870 l       .vmlinux	00000000 t_iovf
30008880 l       .vmlinux	00000000 t_slowl
30008890 l       .vmlinux	00000000 t_netbs
300088a0 l       .vmlinux	00000000 t_bad8a
300088f0 l       .vmlinux	00000000 t_bad8f
30008900 l       .vmlinux	00000000 t_linux
30008910 l       .vmlinux	00000000 t_bad91
30008960 l       .vmlinux	00000000 t_bad96
300089b0 l       .vmlinux	00000000 t_bad9b
30008a00 l       .vmlinux	00000000 t_getcc
30008a10 l       .vmlinux	00000000 t_setcc
30008a20 l       .vmlinux	00000000 t_getpsr
30008a30 l       .vmlinux	00000000 t_bada3
30008a70 l       .vmlinux	00000000 t_slowi
30008a80 l       .vmlinux	00000000 t_bada8
30008ac0 l       .vmlinux	00000000 t_badac
30008b10 l       .vmlinux	00000000 t_badb1
30008b60 l       .vmlinux	00000000 t_badb6
30008bb0 l       .vmlinux	00000000 t_badbb
30008c00 l       .vmlinux	00000000 t_badc0
30008c50 l       .vmlinux	00000000 t_badc5
30008ca0 l       .vmlinux	00000000 t_badca
30008cf0 l       .vmlinux	00000000 t_badcf
30008d40 l       .vmlinux	00000000 t_badd4
30008d90 l       .vmlinux	00000000 t_badd9
30008de0 l       .vmlinux	00000000 t_badde
30008e30 l       .vmlinux	00000000 t_bade3
30008e80 l       .vmlinux	00000000 t_bade8
30008ed0 l       .vmlinux	00000000 t_baded
30008f20 l       .vmlinux	00000000 t_badf2
30008f70 l       .vmlinux	00000000 t_badf7
30008fc0 l       .vmlinux	00000000 t_badfc
30008fe0 l       .vmlinux	00000000 dbtrap
30008ff0 l       .vmlinux	00000000 dbtrap2
30011030 l       .vmlinux	00000000 current_pc
302727fc l       .vmlinux	00000000 no_sun4u_here
30011074 l       .vmlinux	00000000 already_mapped
30011078 l       .vmlinux	00000000 copy_prom_lvl14
30011078 l       .vmlinux	00000000 copy_prom_done
3001122c l       .vmlinux	00000000 go_to_highmem
300110b0 l       .vmlinux	00000000 remap_not_a_sun4
30011188 l       .vmlinux	00000000 sun4_mutant_remap
300111cc l       .vmlinux	00000000 sun4_normal_remap
30011200 l       .vmlinux	00000000 sun4c_remap
300110c4 l       .vmlinux	00000000 srmmu_remap
3001115c l       .vmlinux	00000000 srmmu_nviking
300111ac l       .vmlinux	00000000 sun4_mutant_loop
300111e0 l       .vmlinux	00000000 sun4_normal_loop
30011214 l       .vmlinux	00000000 sun4c_remap_loop
30272000 l       .vmlinux	00000000 execute_in_high_mem
30272048 l       .vmlinux	00000000 found_version
302727b0 l       .vmlinux	00000000 sun4_init
302720b0 l       .vmlinux	00000000 got_prop
302727e0 l       .vmlinux	00000000 no_sun4e_here
30272164 l       .vmlinux	00000000 sun4m_init
30272140 l       .vmlinux	00000000 sun4d_init
3027248c l       .vmlinux	00000000 sun4c_continue_boot
3027287c l       .vmlinux	00000000 halt_me
302af0d0 l       .vmlinux	00000000 sun4u_1
302af0dc l       .vmlinux	00000000 sun4u_2
302af0e4 l       .vmlinux	00000000 sun4u_3
302af0ec l       .vmlinux	00000000 sun4u_4
302af0f4 l       .vmlinux	00000000 sun4u_5
302af0fc l       .vmlinux	00000000 sun4u_6
302af159 l       .vmlinux	00000000 sun4u_6e
302af15c l       .vmlinux	00000000 sun4u_7
302af168 l       .vmlinux	00000000 sun4u_a1
302af18c l       .vmlinux	00000000 sun4u_r1
302af190 l       .vmlinux	00000000 sun4u_a2
302af1ac l       .vmlinux	00000000 sun4u_i2
302af1cc l       .vmlinux	00000000 sun4u_r2
302af1d0 l       .vmlinux	00000000 sun4u_a3
302af1ec l       .vmlinux	00000000 sun4u_i3
302af204 l       .vmlinux	00000000 sun4u_r3
302af208 l       .vmlinux	00000000 sun4u_a4
302af220 l       .vmlinux	00000000 sun4u_r4
00000000 l    df *ABS*	00000000 init_task.c
30254cb0 l     O .vmlinux	00000020 init_fs
30254c00 l     O .vmlinux	000000b0 init_files
30254a78 l     O .vmlinux	00000188 init_signals
30254470 l     O .vmlinux	00000604 init_sighand
00000000 l    df *ABS*	00000000 main.c
302b9ee0 l     O .vmlinux	0000000c __setup_initcall_debug_setup
302af220 l     O .vmlinux	0000000f __setup_str_initcall_debug_setup
30273024 l     F .vmlinux	00000014 initcall_debug_setup
302b9eec l     O .vmlinux	0000000c __setup_rdinit_setup
302af230 l     O .vmlinux	00000008 __setup_str_rdinit_setup
30272bd0 l     F .vmlinux	00000030 rdinit_setup
302b9ef8 l     O .vmlinux	0000000c __setup_init_setup
302af238 l     O .vmlinux	00000006 __setup_str_init_setup
30272ba0 l     F .vmlinux	00000030 init_setup
302b9f04 l     O .vmlinux	0000000c __setup_loglevel
302af240 l     O .vmlinux	0000000a __setup_str_loglevel
3027291c l     F .vmlinux	00000020 loglevel
302b9f10 l     O .vmlinux	0000000c __setup_quiet_kernel
302af250 l     O .vmlinux	00000006 __setup_str_quiet_kernel
302728f4 l     F .vmlinux	00000028 quiet_kernel
302b9f1c l     O .vmlinux	0000000c __setup_debug_kernel
302af258 l     O .vmlinux	00000006 __setup_str_debug_kernel
302728cc l     F .vmlinux	00000028 debug_kernel
302b9f28 l     O .vmlinux	0000000c __setup_set_reset_devices
302af260 l     O .vmlinux	0000000e __setup_str_set_reset_devices
302728b8 l     F .vmlinux	00000014 set_reset_devices
302b9f34 l     O .vmlinux	0000000c __setup_maxcpus
302af270 l     O .vmlinux	00000009 __setup_str_maxcpus
30272898 l     F .vmlinux	00000020 maxcpus
302b9f40 l     O .vmlinux	0000000c __setup_nosmp
302af280 l     O .vmlinux	00000006 __setup_str_nosmp
30272888 l     F .vmlinux	00000010 nosmp
30254ee4 l     O .vmlinux	00000004 max_cpus
30254ee8 l     O .vmlinux	00000088 argv_init
3027293c l     F .vmlinux	00000264 unknown_bootoption
3060009c l     O .bss	00000004 panic_later
306000a0 l     O .bss	00000004 panic_param
30600094 l     O .bss	00000004 execute_command
30600098 l     O .bss	00000004 ramdisk_execute_command
30014000 l     F .vmlinux	0000002c rest_init
30273038 l     F .vmlinux	000001dc init
30272c00 l     F .vmlinux	00000094 do_early_param
302af288 l     O .vmlinux	00000004 done.0
302af290 l     O .vmlinux	00000100 tmp_cmdline.1
30600090 l     O .bss	00000004 static_command_line
302af490 l     O .vmlinux	00000004 initcall_debug
3001402c l     F .vmlinux	00000024 run_init_process
30014050 l     F .vmlinux	00000104 init_post
00000000 l    df *ABS*	00000000 version.c
00000000 l    df *ABS*	00000000 do_mounts.c
302b9f4c l     O .vmlinux	0000000c __setup_root_delay_setup
302af498 l     O .vmlinux	0000000b __setup_str_root_delay_setup
302732d4 l     F .vmlinux	00000024 root_delay_setup
302b9f58 l     O .vmlinux	0000000c __setup_fs_names_setup
302af4a8 l     O .vmlinux	0000000c __setup_str_fs_names_setup
302732c4 l     F .vmlinux	00000010 fs_names_setup
302b9f64 l     O .vmlinux	0000000c __setup_root_data_setup
302af4b8 l     O .vmlinux	0000000b __setup_str_root_data_setup
302732b4 l     F .vmlinux	00000010 root_data_setup
302b9f70 l     O .vmlinux	0000000c __setup_root_dev_setup
302af4c8 l     O .vmlinux	00000006 __setup_str_root_dev_setup
30273294 l     F .vmlinux	00000020 root_dev_setup
302b9f7c l     O .vmlinux	0000000c __setup_readwrite
302af4d0 l     O .vmlinux	00000003 __setup_str_readwrite
30273268 l     F .vmlinux	0000002c readwrite
302b9f88 l     O .vmlinux	0000000c __setup_readonly
302af4d8 l     O .vmlinux	00000003 __setup_str_readonly
3027323c l     F .vmlinux	0000002c readonly
302b9f94 l     O .vmlinux	0000000c __setup_load_ramdisk
302af4e0 l     O .vmlinux	0000000e __setup_str_load_ramdisk
30273214 l     F .vmlinux	00000028 load_ramdisk
30014154 l     F .vmlinux	000001f4 try_name
302af4f8 l     O .vmlinux	00000040 saved_root_name
302af538 l     O .vmlinux	00000004 root_mount_data
302af53c l     O .vmlinux	00000004 root_fs_names
302af540 l     O .vmlinux	00000004 root_delay
00000000 l    df *ABS*	00000000 do_mounts_rd.c
302b9fa0 l     O .vmlinux	0000000c __setup_ramdisk_start_setup
302af548 l     O .vmlinux	0000000f __setup_str_ramdisk_start_setup
302739d0 l     F .vmlinux	00000024 ramdisk_start_setup
302b9fac l     O .vmlinux	0000000c __setup_prompt_ramdisk
302af558 l     O .vmlinux	00000010 __setup_str_prompt_ramdisk
302739a8 l     F .vmlinux	00000028 prompt_ramdisk
302260a8 l     O .vmlinux	0000003c cpdext
302260e4 l     O .vmlinux	0000003c cpdist
30226120 l     O .vmlinux	0000003e cplext
3022615e l     O .vmlinux	0000003e cplens
3022619c l     O .vmlinux	00000022 mask_bits
302261c0 l     O .vmlinux	0000004c border
302739f4 l     F .vmlinux	0000002c huft_free
30273a20 l     F .vmlinux	00000524 huft_build
306000dc l     O .bss	00000004 hufts
30273f44 l     F .vmlinux	000000d8 flush_window
306000bc l     O .bss	00000004 outcnt
306000d0 l     O .bss	00000004 crd_outfd
306004e0 l     O .bss	00000004 crc
306000b0 l     O .bss	00000004 window
306000c8 l     O .bss	00000004 bytes_out
306000c4 l     O .bss	00000004 unzip_error
306000e0 l     O .bss	00000400 crc_32_tab
3027401c l     F .vmlinux	00000030 error
306000c0 l     O .bss	00000004 exit_code
3027404c l     F .vmlinux	00000078 fill_inbuf
306000ac l     O .bss	00000004 inbuf
306000cc l     O .bss	00000004 crd_infd
306000b4 l     O .bss	00000004 insize
306000b8 l     O .bss	00000004 inptr
302740c4 l     F .vmlinux	00000534 inflate_codes
306000d4 l     O .bss	00000004 bb
306000d8 l     O .bss	00000004 bk
302745f8 l     F .vmlinux	00000184 inflate_fixed
3027477c l     F .vmlinux	00000754 inflate_dynamic
30274ed0 l     F .vmlinux	00000008 gzip_release
3022620c l     O .vmlinux	00000038 p.0
00000000 l    df *ABS*	00000000 do_mounts_initrd.c
302b9fb8 l     O .vmlinux	0000000c __setup_no_initrd
302af570 l     O .vmlinux	00000009 __setup_str_no_initrd
302760e8 l     F .vmlinux	00000010 no_initrd
302af57c l     O .vmlinux	00000004 mount_initrd
30255100 l     O .vmlinux	00000008 argv.0
302760f8 l     F .vmlinux	00000074 do_linuxrc
302af580 l     O .vmlinux	00000004 old_fd
302af584 l     O .vmlinux	00000004 root_fd
00000000 l    df *ABS*	00000000 initramfs.c
302ba3b4 l     O .vmlinux	00000004 __initcall_populate_rootfsrootfs
30278b7c l     F .vmlinux	000000fc populate_rootfs
302b9fc4 l     O .vmlinux	0000000c __setup_retain_initrd_param
302af588 l     O .vmlinux	0000000e __setup_str_retain_initrd_param
30278b1c l     F .vmlinux	00000028 retain_initrd_param
302af598 l     O .vmlinux	00000020 actions
30276588 l     F .vmlinux	00000020 do_start
302765a8 l     F .vmlinux	000000a4 do_collect
3027664c l     F .vmlinux	00000258 do_header
302768a4 l     F .vmlinux	000000d0 do_skip
30276bcc l     F .vmlinux	000001f0 do_name
30276dbc l     F .vmlinux	000000d4 do_copy
30276e90 l     F .vmlinux	00000090 do_symlink
30276974 l     F .vmlinux	000000b0 do_reset
30226244 l     O .vmlinux	0000003c cpdext
30226280 l     O .vmlinux	0000003c cpdist
302262bc l     O .vmlinux	0000003e cplext
302262fa l     O .vmlinux	0000003e cplens
30226338 l     O .vmlinux	00000022 mask_bits
3022635c l     O .vmlinux	0000004c border
302764c0 l     F .vmlinux	0000001c error
302af5b8 l     O .vmlinux	00000004 message
302764dc l     F .vmlinux	00000018 malloc
302764f4 l     F .vmlinux	00000010 free
30276504 l     F .vmlinux	00000084 read_into
302af670 l     O .vmlinux	00000004 count
302af66c l     O .vmlinux	00000004 victim
302af678 l     O .vmlinux	00000008 this_header
302af664 l     O .vmlinux	00000004 state
302af68c l     O .vmlinux	00000004 collected
302af694 l     O .vmlinux	00000004 collect
302af690 l     O .vmlinux	00000004 remains
302af668 l     O .vmlinux	00000004 next_state
302af698 l     O .vmlinux	00000004 header_buf
302af688 l     O .vmlinux	00000004 dry_run
302af63c l     O .vmlinux	00000004 ino
302af658 l     O .vmlinux	00000004 uid
302af65c l     O .vmlinux	00000004 gid
302af648 l     O .vmlinux	00000004 nlink
302af640 l     O .vmlinux	00000004 major
302af644 l     O .vmlinux	00000004 minor
302af660 l     O .vmlinux	00000004 rdev
302af680 l     O .vmlinux	00000008 next_header
302af64c l     O .vmlinux	00000002 mode
302af650 l     O .vmlinux	00000004 body_len
302af654 l     O .vmlinux	00000004 name_len
302af6a0 l     O .vmlinux	00000004 name_buf
302af69c l     O .vmlinux	00000004 symlink_buf
30276a24 l     F .vmlinux	00000148 maybe_link
302af5bc l     O .vmlinux	00000080 head
30276b6c l     F .vmlinux	00000060 clean_path
302af6a4 l     O .vmlinux	00000004 wfd
30276f20 l     F .vmlinux	00000050 write_buffer
30276f70 l     F .vmlinux	0000002c huft_free
30276f9c l     F .vmlinux	00000520 huft_build
30600514 l     O .bss	00000004 hufts
302774bc l     F .vmlinux	00000134 flush_window
30600918 l     O .bss	00000004 crc
306004f8 l     O .bss	00000004 window
30600504 l     O .bss	00000004 outcnt
30600518 l     O .bss	00000400 crc_32_tab
30600508 l     O .bss	00000004 bytes_out
302775f0 l     F .vmlinux	00000438 inflate_codes
3060050c l     O .bss	00000004 bb
30600510 l     O .bss	00000004 bk
306004f4 l     O .bss	00000004 inbuf
306004fc l     O .bss	00000004 insize
30600500 l     O .bss	00000004 inptr
30277a28 l     F .vmlinux	00000184 inflate_fixed
30277bac l     F .vmlinux	00000608 inflate_dynamic
302781b4 l     F .vmlinux	00000008 gzip_release
302263a8 l     O .vmlinux	00000038 p.0
302781bc l     F .vmlinux	00000960 unpack_to_rootfs
302af6a8 l     O .vmlinux	00000004 do_retain_initrd
30278b44 l     F .vmlinux	00000038 free_initrd
00000000 l    df *ABS*	00000000 calibrate.c
302b9fd0 l     O .vmlinux	0000000c __setup_lpj_setup
302af6b0 l     O .vmlinux	00000005 __setup_str_lpj_setup
30278c78 l     F .vmlinux	00000024 lpj_setup
3060091c l     O .bss	00000004 preset_lpj
00000000 l    df *ABS*	00000000 usr/initramfs_data.S
00000000 l    df *ABS*	00000000 arch/sparc/kernel/entry.S
30255108 l       .vmlinux	00000000 in_trap_handler
300146e0 l       .vmlinux	00000000 real_irq_continue
300147f8 l       .vmlinux	00000000 mna_fromuser
3001538c l       .vmlinux	00000000 fpsave_magic
300153f4 l       .vmlinux	00000000 fpsave_catch2
300153ec l       .vmlinux	00000000 fpsave_catch
30014a90 l       .vmlinux	00000000 dfw_kernel
30014dd0 l       .vmlinux	00000000 sun4c_fault_fromuser
300150c4 l       .vmlinux	00000000 linux_sparc_ni_syscall
300150d0 l       .vmlinux	00000000 linux_fast_syscall
300150e8 l       .vmlinux	00000000 linux_syscall_trace
300151d8 l       .vmlinux	00000000 linux_syscall_trace2
300151ec l       .vmlinux	00000000 linux_syscall_for_solaris
3001548c l       .vmlinux	00000000 delay_continue
00000000 l    df *ABS*	00000000 arch/sparc/kernel/wof.S
30015634 l       .vmlinux	00000000 spwin_fromuser
3001562c l       .vmlinux	00000000 spwin_exist_uwins
300155e8 l       .vmlinux	00000000 spwin_no_userwins_from_kernel
30015640 l       .vmlinux	00000000 spwin_good_ustack
30015660 l       .vmlinux	00000000 spwin_finish_up
30015684 l       .vmlinux	00000000 spwin_user_stack_is_bolixed
30015744 l       .vmlinux	00000000 spwin_bad_ustack_from_kernel
30015834 l       .vmlinux	00000000 spwin_sun4c_onepage
300157f4 l       .vmlinux	00000000 spwin_sun4c_twopages
00000000 l    df *ABS*	00000000 arch/sparc/kernel/wuf.S
30015930 l       .vmlinux	00000000 fwin_from_user
300158ec l       .vmlinux	00000000 fwin_from_kernel
3001593c l       .vmlinux	00000000 fwin_user_stack_is_bolixed
300159d0 l       .vmlinux	00000000 fwin_user_stack_is_ok
300159f8 l       .vmlinux	00000000 fwin_user_finish_up
30015a70 l       .vmlinux	00000000 sun4c_fwin_onepage
30015a40 l       .vmlinux	00000000 sun4c_fwin_twopages
00000000 l    df *ABS*	00000000 arch/sparc/kernel/etrap.S
30015bd8 l       .vmlinux	00000000 trap_setup_from_user
30015b88 l       .vmlinux	00000000 trap_setup_kernel_spill
30015c60 l       .vmlinux	00000000 trap_setup_user_spill
30015d2c l       .vmlinux	00000000 trap_setup_user_stack_is_bolixed
30015cdc l       .vmlinux	00000000 tsetup_sun4c_onepage
30015cb4 l       .vmlinux	00000000 tsetup_sun4c_twopages
00000000 l    df *ABS*	00000000 arch/sparc/kernel/rtrap.S
30015f50 l       .vmlinux	00000000 ret_trap_kernel
30015e24 l       .vmlinux	00000000 signal_p
30015e48 l       .vmlinux	00000000 ret_trap_continue
30015e8c l       .vmlinux	00000000 ret_trap_nobufwins
30015ecc l       .vmlinux	00000000 ret_trap_userwins_ok
30015eac l       .vmlinux	00000000 ret_trap_pull_one_window
30015f20 l       .vmlinux	00000000 ret_trap_unaligned_pc
3001602c l       .vmlinux	00000000 ret_trap_user_stack_is_bolixed
300160c0 l       .vmlinux	00000000 sun4c_rett_onepage
30016088 l       .vmlinux	00000000 sun4c_rett_twopages
00000000 l    df *ABS*	00000000 traps.c
30600924 l     O .bss	00000004 init_fsr
30255110 l     O .vmlinux	00000080 init_fregs
30600928 l     O .bss	00000004 die_counter.1
3060092c l     O .bss	00000004 calls.0
30602930 l     O .bss	00000080 fake_regs
306029b0 l     O .bss	00000004 fake_fsr
306029b8 l     O .bss	00000080 fake_queue
30602a38 l     O .bss	00000004 fake_depth
00000000 l    df *ABS*	00000000 irq.c
30016aa0 l     F .vmlinux	00000024 irq_panic
00000000 l    df *ABS*	00000000 sun4m_irq.c
30602bd8 l     O .bss	00000004 dummy
302551a0 l     O .vmlinux	00000040 cpu_pil_to_imask
302551e0 l     O .vmlinux	00000020 irq_xlate
30255200 l     O .vmlinux	0000003c irq_mask
3025523c l     O .vmlinux	00000020 sun4m_pil_map
30017304 l     F .vmlinux	00000090 sun4m_disable_irq
30017394 l     F .vmlinux	000000d4 sun4m_enable_irq
30017468 l     F .vmlinux	00000028 sun4m_disable_pil_irq
30017490 l     F .vmlinux	00000028 sun4m_enable_pil_irq
300174b8 l     F .vmlinux	00000020 sun4m_clear_clock_irq
300174d8 l     F .vmlinux	00000020 sun4m_clear_profile_irq
300174f8 l     F .vmlinux	00000018 sun4m_load_profile_irq
30278ed4 l     F .vmlinux	00000238 sun4m_init_timers
00000000 l    df *ABS*	00000000 sun4c_irq.c
30255260 l     O .vmlinux	00000020 sun4c_pil_map
3001754c l     F .vmlinux	0000008c sun4c_disable_irq
300175d8 l     F .vmlinux	0000008c sun4c_enable_irq
30017664 l     F .vmlinux	0000001c sun4c_clear_clock_irq
30017680 l     F .vmlinux	00000008 sun4c_clear_profile_irq
30017688 l     F .vmlinux	00000008 sun4c_load_profile_irq
3027942c l     F .vmlinux	00000090 sun4c_init_timers
00000000 l    df *ABS*	00000000 sun4d_irq.c
30255280 l     O .vmlinux	00000020 sbus_to_pil
302552a0 l     O .vmlinux	00000040 pil_to_sbus
30602c94 l     O .bss	00000004 nsbi
30602c10 l     O .bss	00000080 irq_action
30017dc0 l     F .vmlinux	0000003c sun4d_disable_irq
30017dfc l     F .vmlinux	0000003c sun4d_enable_irq
30017e38 l     F .vmlinux	0000001c sun4d_clear_clock_irq
30017e54 l     F .vmlinux	0000001c sun4d_clear_profile_irq
30017e70 l     F .vmlinux	0000001c sun4d_load_profile_irq
302796a4 l     F .vmlinux	000000ec sun4d_init_timers
00000000 l    df *ABS*	00000000 leon_irq.c
30602ca4 l     O .bss	00000004 dummy_master_l10_counter
30602ca8 l     O .bss	00000004 dummy_master_l10_limit
00000000 l    df *ABS*	00000000 process.c
30602cb0 l     O .bss	00000000 sparc_backtrace_lock
302552e8 l     O .vmlinux	00000004 count.0
30602cb0 l     O .bss	00000004 last_jiffies.1
30602cb4 l     O .bss	00000004 last_faults.2
30602cb8 l     O .bss	00000004 fps.3
00000000 l    df *ABS*	00000000 signal.c
30018e74 l     F .vmlinux	00000068 _sigpause_common
00000000 l    df *ABS*	00000000 ioport.c
30255308 l     O .vmlinux	0000001c _sparc_dvma
30602cc4 l     O .bss	00000004 printed_full.0
3001a63c l     F .vmlinux	00000164 _sparc_alloc_io
30602cc8 l     O .bss	000001e0 xresv
3001b530 l     F .vmlinux	000000b0 _sparc_io_get_info
00000000 l    df *ABS*	00000000 setup.c
302ba37c l     O .vmlinux	00000004 __initcall_topology_init4
3027a7c4 l     F .vmlinux	00000060 topology_init
3001b7e4 l     F .vmlinux	00000024 c_start
3001b82c l     F .vmlinux	00000008 c_stop
3001b808 l     F .vmlinux	00000024 c_next
3001b6f4 l     F .vmlinux	000000f0 show_cpuinfo
302ba5c8 l     O .vmlinux	00000004 __initcall_set_preferred_console
3027a6a8 l     F .vmlinux	0000011c set_preferred_console
30255378 l     O .vmlinux	0000002c prom_debug_console
3001b6dc l     F .vmlinux	00000018 prom_console_write
30603008 l     O .bss	00000004 ncpus_probed
00000000 l    df *ABS*	00000000 idprom.c
3027a824 l     F .vmlinux	0000002c calc_idprom_cksum
30603014 l     O .bss	00000020 idprom_buffer
00000000 l    df *ABS*	00000000 sys_sparc.c
3001be90 l     F .vmlinux	000000a0 do_mmap2
30603034 l     O .bss	00000004 count.0
00000000 l    df *ABS*	00000000 arch/sparc/kernel/sunos_asm.S
00000000 l    df *ABS*	00000000 arch/sparc/kernel/systbls.S
00000000 l    df *ABS*	00000000 time.c
302ba3a4 l     O .vmlinux	00000004 __initcall_clock_init5
3027ae74 l     F .vmlinux	00000020 clock_init
302558fc l     O .vmlinux	000000c0 clock_driver
302559bc l     O .vmlinux	00000188 clock_match
3027a9ac l     F .vmlinux	000004c8 clock_probe
30603040 l     O .bss	00000004 mstk48t08_regs
30603044 l     O .bss	00000004 last_rtc_update.0
3001ca10 l     F .vmlinux	000000d0 sbus_do_settimeofday
00000000 l    df *ABS*	00000000 windows.c
00000000 l    df *ABS*	00000000 cpu.c
00000000 l    df *ABS*	00000000 devices.c
3001ccc4 l     F .vmlinux	00000028 cpu_mid_prop
3001ccec l     F .vmlinux	000000bc __cpu_find_by
3001cda8 l     F .vmlinux	00000014 cpu_instance_compare
3001cde8 l     F .vmlinux	00000054 cpu_mid_compare
00000000 l    df *ABS*	00000000 arch/sparc/kernel/sclow.S
00000000 l    df *ABS*	00000000 tadpole.c
3001cf08 l     F .vmlinux	000000c8 tsu_clockstop
30603080 l     O .bss	00000004 clk_ctrl
3060307c l     O .bss	00000004 clk_state
3001cfd0 l     F .vmlinux	0000001c swift_clockstop
00000000 l    df *ABS*	00000000 tick14.c
30603088 l     O .bss	00000004 linux_lvl14
3060308c l     O .bss	00000010 obp_lvl14
00000000 l    df *ABS*	00000000 ptrace.c
3001d248 l     F .vmlinux	00000080 pt_succ_return_linux
3001d2c8 l     F .vmlinux	00000050 pt_os_succ_return
00000000 l    df *ABS*	00000000 sys_solaris.c
3060309c l     O .bss	00000004 cnt.1
306030a0 l     O .bss	00000004 cnt.0
00000000 l    df *ABS*	00000000 unaligned.c
3001dcf8 l     F .vmlinux	000001b0 compute_effective_address
3001e124 l     F .vmlinux	00000010 unaligned_panic
306030a4 l     O .bss	00000008 zero.1
3001e3b8 l       .vmlinux	00000000 kernel_unaligned_trap_fault
306030ac l     O .bss	00000008 zero.0
3001e68c l       .vmlinux	00000000 user_unaligned_trap_fault
00000000 l    df *ABS*	00000000 muldiv.c
00000000 l    df *ABS*	00000000 semaphore.c
306030b4 l     O .bss	00000000 semaphore_lock
00000000 l    df *ABS*	00000000 prom.c
306030b4 l     O .bss	00000000 devtree_lock
306030b8 l     O .bss	00000004 allnodes
3027b244 l     F .vmlinux	00000040 prom_early_alloc
306030bc l     O .bss	00000004 prom_early_allocated
306030b4 l     O .bss	00000004 tmp.0
3027b284 l     F .vmlinux	00000154 build_one_prop
306030c0 l     O .bss	00000004 unique_id
3027b3d8 l     F .vmlinux	00000054 get_one_property
3027b42c l     F .vmlinux	0000017c create_node
3027b5a8 l     F .vmlinux	00000290 build_tree
00000000 l    df *ABS*	00000000 of_device.c
302b9fdc l     O .vmlinux	0000000c __setup_of_debug
302af6c0 l     O .vmlinux	0000000a __setup_str_of_debug
3027b8b8 l     F .vmlinux	00000038 of_debug
302ba368 l     O .vmlinux	00000004 __initcall_of_bus_driver_init2
3027c088 l     F .vmlinux	0000008c of_bus_driver_init
3001f418 l     F .vmlinux	00000034 of_platform_bus_match
3001f4a8 l     F .vmlinux	0000007c of_device_probe
3001f524 l     F .vmlinux	00000038 of_device_remove
3001f55c l     F .vmlinux	0000004c of_device_suspend
3001f5a8 l     F .vmlinux	00000040 of_device_resume
30256294 l     O .vmlinux	00000048 of_busses
3001f868 l     F .vmlinux	00000060 of_bus_pci_match
3001f8c8 l     F .vmlinux	00000028 of_bus_pci_count_cells
3001f8f0 l     F .vmlinux	000000d0 of_bus_pci_map
3001f9c0 l     F .vmlinux	00000060 of_bus_pci_get_flags
3001fa20 l     F .vmlinux	0000004c of_bus_sbus_match
3001fa6c l     F .vmlinux	00000028 of_bus_sbus_count_cells
3001fa94 l     F .vmlinux	00000010 of_bus_sbus_map
3001faa4 l     F .vmlinux	00000008 of_bus_sbus_get_flags
3001f634 l     F .vmlinux	0000003c of_bus_default_count_cells
3001f78c l     F .vmlinux	000000d4 of_bus_default_map
3001f860 l     F .vmlinux	00000008 of_bus_default_get_flags
302562dc l     O .vmlinux	00000014 dev_attr_devspec
3001fb4c l     F .vmlinux	00000024 dev_show_devspec
3001f5e8 l     F .vmlinux	00000014 node_match
3001f670 l     F .vmlinux	0000011c of_out_of_range
3001faac l     F .vmlinux	0000006c of_match_bus
306030c4 l     O .bss	00000004 of_resource_verbose
302562f0 l     O .vmlinux	00000040 pil_to_sbus.0
3027b8f0 l     F .vmlinux	00000754 scan_one_device
3027c044 l     F .vmlinux	00000044 scan_tree
00000000 l    df *ABS*	00000000 devres.c
3001fc7c l     F .vmlinux	0000001c devm_irq_release
3001fc98 l     F .vmlinux	00000030 devm_irq_match
302263e0 l     O .vmlinux	0000000e __func__.0
00000000 l    df *ABS*	00000000 leon_timer.c
306030c8 l     O .bss	00000004 freetimers
3001fdc4 l     F .vmlinux	000000d4 gptimer_leon3init
306030cc l     O .bss	00001100 timers
00000000 l    df *ABS*	00000000 leon_pmc.c
302ba3b8 l     O .vmlinux	00000004 __initcall_leon_pmc_install6
3027c114 l     F .vmlinux	00000040 leon_pmc_install
00000000 l    df *ABS*	00000000 leon_pci.c
302ba380 l     O .vmlinux	00000004 __initcall_pcic_init4
3027c154 l     F .vmlinux	0000021c pcic_init
3025638c l     O .vmlinux	00000008 pcic_ops
300208e8 l     F .vmlinux	00000100 pcic_read_config
30020a78 l     F .vmlinux	0000010c pcic_write_config
30020838 l     F .vmlinux	000000b0 pcic_read_config_dword
300209e8 l     F .vmlinux	00000090 pcic_write_config_dword
00000000 l    df *ABS*	00000000 auxio.c
306041d8 l     O .bss	00000000 auxio_lock
00000000 l    df *ABS*	00000000 apc.c
302ba3bc l     O .vmlinux	00000004 __initcall_apc_probe6
3027c7bc l     F .vmlinux	00000144 apc_probe
302b9fe8 l     O .vmlinux	0000000c __setup_apc_setup
302af6d0 l     O .vmlinux	00000005 __setup_str_apc_setup
3027c718 l     F .vmlinux	000000a4 apc_setup
302af6d8 l     O .vmlinux	00000004 apc_no_idle
30256394 l     O .vmlinux	0000001c apc_miscdev
302263f0 l     O .vmlinux	0000006c apc_fops
30020e44 l     F .vmlinux	00000228 apc_ioctl
30020e34 l     F .vmlinux	00000008 apc_open
30020e3c l     F .vmlinux	00000008 apc_release
306041d8 l     O .bss	00000004 regs
306041dc l     O .bss	00000004 apc_regsize
00000000 l    df *ABS*	00000000 pmc.c
302ba3c0 l     O .vmlinux	00000004 __initcall_pmc_probe6
3027c900 l     F .vmlinux	000000e8 pmc_probe
306041e0 l     O .bss	00000004 regs
306041e4 l     O .bss	00000004 pmc_regsize
00000000 l    df *ABS*	00000000 fault.c
3002123c l     F .vmlinux	000000b8 unhandled_fault
300213bc l     F .vmlinux	00000048 compute_si_addr
00000000 l    df *ABS*	00000000 init.c
00000000 l    df *ABS*	00000000 loadmmu.c
00000000 l    df *ABS*	00000000 generic.c
00000000 l    df *ABS*	00000000 extable.c
00000000 l    df *ABS*	00000000 btfixup.c
302af6e0 l     O .vmlinux	00000028 fca_und
302af708 l     O .vmlinux	0000003d insn_i
302af748 l     O .vmlinux	00000038 insn_a
302af780 l     O .vmlinux	00000031 insn_h
302af7b8 l     O .vmlinux	0000002f insn_s
302af7e8 l     O .vmlinux	00000031 insn_b
302af820 l     O .vmlinux	0000003a insn_f
302af860 l     O .vmlinux	0000001f wrong
302af880 l     O .vmlinux	00000030 wrong_a
302af8b0 l     O .vmlinux	00000030 wrong_h
302af8e0 l     O .vmlinux	00000030 wrong_s
302af910 l     O .vmlinux	00000033 wrong_b
302af948 l     O .vmlinux	00000033 wrong_f
302af980 l     O .vmlinux	00000007 str_iommu
302af988 l     O .vmlinux	00000009 str_iounit
302af998 l     O .vmlinux	0000000b str_srmmu
302af9a8 l     O .vmlinux	00000007 str_sun4c
302af9b0 l     O .vmlinux	00000057 version
302afa08 l     O .vmlinux	00000004 visited
302afa10 l     O .vmlinux	00000033 wrong_setaddr
3027d3b8 l     F .vmlinux	0000006c set_addr
00000000 l    df *ABS*	00000000 srmmu.c
302563bc l     O .vmlinux	00000004 leon_flush_during_switch
30604388 l     O .bss	00000000 srmmu_context_spinlock
30022888 l     F .vmlinux	0000000c srmmu_set_pte
30022894 l     F .vmlinux	00000020 srmmu_pte_pfn
300228b4 l     F .vmlinux	00000034 srmmu_pmd_page
300228e8 l     F .vmlinux	00000040 srmmu_pgd_page
30022928 l     F .vmlinux	00000014 srmmu_pte_present
3002293c l     F .vmlinux	00000010 srmmu_pte_read
3002294c l     F .vmlinux	00000010 srmmu_pte_clear
3002295c l     F .vmlinux	00000018 srmmu_pmd_bad
30022974 l     F .vmlinux	00000018 srmmu_pmd_present
3002298c l     F .vmlinux	00000024 srmmu_pmd_clear
300229b0 l     F .vmlinux	00000014 srmmu_pgd_none
300229c4 l     F .vmlinux	00000014 srmmu_pgd_bad
300229d8 l     F .vmlinux	00000014 srmmu_pgd_present
300229ec l     F .vmlinux	00000010 srmmu_pgd_clear
300229fc l     F .vmlinux	00000008 srmmu_pte_mkwrite
30022a04 l     F .vmlinux	00000008 srmmu_pte_mkdirty
30022a0c l     F .vmlinux	00000008 srmmu_pte_mkyoung
30022a14 l     F .vmlinux	00000028 srmmu_mk_pte
30022a3c l     F .vmlinux	0000000c srmmu_mk_pte_phys
30022a48 l     F .vmlinux	00000014 srmmu_mk_pte_io
30022a5c l     F .vmlinux	00000034 srmmu_pgd_set
30022a90 l     F .vmlinux	00000048 srmmu_pmd_set
30022ad8 l     F .vmlinux	00000044 srmmu_pmd_populate
30022b1c l     F .vmlinux	00000058 srmmu_pmd_offset
30022b74 l     F .vmlinux	0000003c srmmu_pte_offset
30022bb0 l     F .vmlinux	00000010 srmmu_swp_type
30022bc0 l     F .vmlinux	0000000c srmmu_swp_offset
30022bcc l     F .vmlinux	00000020 srmmu_swp_entry
30022bec l     F .vmlinux	000000c0 __srmmu_get_nocache
306043c8 l     O .bss	0000001c srmmu_nocache_map
30022e04 l     F .vmlinux	00000054 srmmu_get_pgd_fast
30022e58 l     F .vmlinux	00000014 srmmu_free_pgd_fast
30022e6c l     F .vmlinux	00000030 srmmu_pmd_alloc_one
30022e9c l     F .vmlinux	00000014 srmmu_pmd_free
30022eb0 l     F .vmlinux	0000002c srmmu_pte_alloc_one_kernel
30022edc l     F .vmlinux	00000064 srmmu_pte_alloc_one
30022f40 l     F .vmlinux	00000014 srmmu_free_pte_fast
30022f54 l     F .vmlinux	00000060 srmmu_pte_free
30022fc4 l     F .vmlinux	00000180 srmmu_switch_mm
30023144 l     F .vmlinux	000000d8 srmmu_mapiorange
3002321c l     F .vmlinux	000000bc srmmu_unmapiorange
300232f0 l     F .vmlinux	00000014 srmmu_free_thread_info
30023304 l     F .vmlinux	00000008 swift_update_mmu_cache
3002330c l     F .vmlinux	00000054 cypress_flush_cache_all
30023360 l     F .vmlinux	000000a0 cypress_flush_cache_mm
30023400 l     F .vmlinux	000000dc cypress_flush_cache_range
300234dc l     F .vmlinux	000000a4 cypress_flush_cache_page
30023580 l     F .vmlinux	00000058 cypress_flush_page_to_ram
300235d8 l     F .vmlinux	00000008 cypress_flush_page_for_dma
300235e0 l     F .vmlinux	00000008 cypress_flush_sig_insns
300235e8 l     F .vmlinux	00000010 cypress_flush_tlb_all
300235f8 l     F .vmlinux	0000002c cypress_flush_tlb_mm
30023624 l     F .vmlinux	00000058 cypress_flush_tlb_range
3002367c l     F .vmlinux	00000030 cypress_flush_tlb_page
3027e4cc l     F .vmlinux	00000038 do_large_mapping
300236ac l     F .vmlinux	0000003c srmmu_mmu_info
300236e8 l     F .vmlinux	00000008 srmmu_update_mmu_cache
300236f0 l     F .vmlinux	000000c0 srmmu_destroy_context
3027e504 l     F .vmlinux	00000104 init_vac_layout
3027e608 l     F .vmlinux	00000094 poke_hypersparc
3027e69c l     F .vmlinux	000000c0 poke_cypress
3027e75c l     F .vmlinux	0000021c init_cypress_common
3027e978 l     F .vmlinux	00000070 init_cypress_605
3027e9e8 l     F .vmlinux	00000028 poke_swift
300237b0 l     F .vmlinux	00000038 turbosparc_flush_cache_all
300237e8 l     F .vmlinux	00000048 turbosparc_flush_cache_mm
30023830 l     F .vmlinux	0000004c turbosparc_flush_cache_range
3002387c l     F .vmlinux	00000074 turbosparc_flush_cache_page
300238f0 l     F .vmlinux	00000008 turbosparc_flush_page_to_ram
300238f8 l     F .vmlinux	00000008 turbosparc_flush_sig_insns
30023900 l     F .vmlinux	00000028 turbosparc_flush_page_for_dma
30023928 l     F .vmlinux	00000010 turbosparc_flush_tlb_all
30023938 l     F .vmlinux	0000001c turbosparc_flush_tlb_mm
30023954 l     F .vmlinux	00000020 turbosparc_flush_tlb_range
30023974 l     F .vmlinux	00000020 turbosparc_flush_tlb_page
3027ea10 l     F .vmlinux	00000068 poke_turbosparc
3027ea78 l     F .vmlinux	000001c8 init_turbosparc
3027ec40 l     F .vmlinux	00000024 poke_tsunami
30604388 l     O .bss	00000004 smp_catch.0
3027ec64 l     F .vmlinux	000000b4 poke_viking
3027f42c l     F .vmlinux	00000008 poke_leonsparc
30023aec l     F .vmlinux	00000008 srmmu_check_pgt_cache
30023af4 l     F .vmlinux	0000000c srmmu_pgoff_to_pte
30023b00 l     F .vmlinux	00000008 srmmu_pte_to_pgoff
30023b08 l     F .vmlinux	00000008 srmmu_pgprot_noncached
00000000 l    df *ABS*	00000000 iommu.c
30023b10 l     F .vmlinux	000000fc iommu_flush_iotlb
306043e8 l     O .bss	00000004 viking_flush
30023c0c l     F .vmlinux	000000d0 iommu_get_one
30023cdc l     F .vmlinux	00000040 iommu_get_scsi_one
30023d1c l     F .vmlinux	00000010 iommu_get_scsi_one_noflush
30023d2c l     F .vmlinux	00000018 iommu_get_scsi_one_gflush
30023d44 l     F .vmlinux	0000003c iommu_get_scsi_one_pflush
30023d80 l     F .vmlinux	0000005c iommu_get_scsi_sgl_noflush
30023ddc l     F .vmlinux	00000064 iommu_get_scsi_sgl_gflush
30023e40 l     F .vmlinux	000000d8 iommu_get_scsi_sgl_pflush
30023f18 l     F .vmlinux	00000064 iommu_release_one
30023f7c l     F .vmlinux	00000024 iommu_release_scsi_one
30023fa0 l     F .vmlinux	00000054 iommu_release_scsi_sgl
30023ff4 l     F .vmlinux	000001b8 iommu_map_dma_area
306043f0 l     O .bss	00000004 dvma_prot
306043ec l     O .bss	00000004 ioperm_noc
300241ac l     F .vmlinux	00000078 iommu_unmap_dma_area
30024224 l     F .vmlinux	00000054 iommu_translate_dvma
30024278 l     F .vmlinux	00000008 iommu_lockarea
30024280 l     F .vmlinux	00000008 iommu_unlockarea
00000000 l    df *ABS*	00000000 io-unit.c
30024288 l     F .vmlinux	000001bc iounit_get_area
30024444 l     F .vmlinux	00000038 iounit_get_scsi_one
3002447c l     F .vmlinux	0000006c iounit_get_scsi_sgl
300244e8 l     F .vmlinux	00000070 iounit_release_scsi_one
30024558 l     F .vmlinux	000000a4 iounit_release_scsi_sgl
300245fc l     F .vmlinux	00000104 iounit_map_dma_area
30024700 l     F .vmlinux	00000008 iounit_unmap_dma_area
30024708 l     F .vmlinux	00000048 iounit_translate_dvma
30024750 l     F .vmlinux	00000008 iounit_lockarea
30024758 l     F .vmlinux	00000008 iounit_unlockarea
00000000 l    df *ABS*	00000000 arch/sparc/mm/hypersparc.S
300249e4 l       .vmlinux	00000000 hypersparc_flush_cache_mm_out
30024b0c l       .vmlinux	00000000 hypersparc_flush_cache_range_out
30024bcc l       .vmlinux	00000000 hypersparc_flush_cache_page_out
30024c8c l       .vmlinux	00000000 hypersparc_flush_tlb_mm_out
30024cd0 l       .vmlinux	00000000 hypersparc_flush_tlb_range_out
30024cfc l       .vmlinux	00000000 hypersparc_flush_tlb_page_out
302808a8 l       .vmlinux	00000000 hypersparc_bzero_1page
30280900 l       .vmlinux	00000000 hypersparc_copy_1page
00000000 l    df *ABS*	00000000 arch/sparc/mm/viking.S
30024e24 l       .vmlinux	00000000 viking_flush_cache_out
00000000 l    df *ABS*	00000000 arch/sparc/mm/tsunami.S
30024f2c l       .vmlinux	00000000 tsunami_flush_cache_out
30024f6c l       .vmlinux	00000000 tsunami_flush_tlb_out
30024fac l       .vmlinux	00000000 tsunami_flush_tlb_page_out
00000000 l    df *ABS*	00000000 arch/sparc/mm/swift.S
30025150 l       .vmlinux	00000000 swift_flush_tlb_all_out
3002517c l       .vmlinux	00000000 swift_flush_tlb_page_out
00000000 l    df *ABS*	00000000 highmem.c
00000000 l    df *ABS*	00000000 sun4c.c
30025330 l     F .vmlinux	00000018 sun4c_flush_context_hw
30025348 l     F .vmlinux	0000002c sun4c_flush_segment_hw
30025374 l     F .vmlinux	00000020 sun4c_flush_page_hw
30025394 l     F .vmlinux	0000005c sun4c_flush_context_sw
300253f0 l     F .vmlinux	00000074 sun4c_flush_segment_sw
30025464 l     F .vmlinux	0000007c sun4c_flush_page_sw
3002551c l     F .vmlinux	0000006c sun4c_map_dma_area
30025588 l     F .vmlinux	00000030 sun4c_translate_dvma
300255b8 l     F .vmlinux	00000008 sun4c_unmap_dma_area
30280bdc l     F .vmlinux	00000134 sun4c_init_lock_area
30604418 l     O .bss	00001800 mmu_entry_pool
300255c0 l     F .vmlinux	00000024 add_ring
300255e4 l     F .vmlinux	00000014 remove_lru
300255f8 l     F .vmlinux	00000050 free_user_entry
30605c18 l     O .bss	000001c0 sun4c_context_ring
30605dd8 l     O .bss	0000001c sun4c_ufree_ring
30025648 l     F .vmlinux	0000003c free_kernel_entry
30025684 l     F .vmlinux	0000007c sun4c_kernel_unmap
30025700 l     F .vmlinux	0000009c sun4c_demap_context
3002579c l     F .vmlinux	00000170 sun4c_user_strategy
30605e48 l     O .bss	00000004 sun4c_user_taken_entries
30605df4 l     O .bss	0000001c sun4c_ulru_ring
30605e4c l     O .bss	00000004 max_user_taken_entries
3002597c l     F .vmlinux	000000b4 get_locked_segment
30025a30 l     F .vmlinux	00000078 free_locked_segment
30025aa8 l     F .vmlinux	0000013c sun4c_alloc_thread_info
30606650 l     O .bss	00000004 sun4c_lowbucket_avail
30025be4 l     F .vmlinux	000000e4 sun4c_free_thread_info
30025cc8 l     F .vmlinux	000001d8 sun4c_lockarea
30606660 l     O .bss	00000004 sun4c_iobuffer_map
30606664 l     O .bss	00000004 iobuffer_map_size
30606654 l     O .bss	00000004 sun4c_iobuffer_start
3060665c l     O .bss	00000004 sun4c_iobuffer_high
30025ea0 l     F .vmlinux	00000140 sun4c_unlockarea
30025fe0 l     F .vmlinux	00000044 sun4c_get_scsi_one
30026024 l     F .vmlinux	00000058 sun4c_get_scsi_sgl
3002607c l     F .vmlinux	0000002c sun4c_release_scsi_one
300260a8 l     F .vmlinux	00000044 sun4c_release_scsi_sgl
300260ec l     F .vmlinux	000000d0 sun4c_flush_cache_all
300261bc l     F .vmlinux	000000e4 sun4c_flush_cache_mm
300262a0 l     F .vmlinux	00000188 sun4c_flush_cache_range
30026428 l     F .vmlinux	0000006c sun4c_flush_cache_page
30026494 l     F .vmlinux	00000024 sun4c_flush_page_to_ram
300264b8 l     F .vmlinux	00000008 sun4c_flush_sig_insns
300264c0 l     F .vmlinux	000000dc sun4c_flush_tlb_all
3002659c l     F .vmlinux	000000c4 sun4c_flush_tlb_mm
30026660 l     F .vmlinux	0000012c sun4c_flush_tlb_range
3002678c l     F .vmlinux	0000007c sun4c_flush_tlb_page
30026808 l     F .vmlinux	00000058 sun4c_mapiorange
30026860 l     F .vmlinux	00000034 sun4c_unmapiorange
30026894 l     F .vmlinux	0000015c sun4c_switch_mm
300269f0 l     F .vmlinux	00000088 sun4c_destroy_context
30026a78 l     F .vmlinux	000000d8 sun4c_mmu_info
30026b50 l     F .vmlinux	00000008 sun4c_set_pte
30026b58 l     F .vmlinux	00000008 sun4c_pgd_set
30026b60 l     F .vmlinux	0000000c sun4c_pmd_set
30026b6c l     F .vmlinux	0000002c sun4c_pmd_populate
30026b98 l     F .vmlinux	00000014 sun4c_pte_present
30026bac l     F .vmlinux	00000008 sun4c_pte_clear
30026bb4 l     F .vmlinux	0000000c sun4c_pte_read
30026bc0 l     F .vmlinux	00000044 sun4c_pmd_bad
30026c04 l     F .vmlinux	0000000c sun4c_pmd_present
30026c10 l     F .vmlinux	0000001c sun4c_pmd_clear
30026c2c l     F .vmlinux	00000008 sun4c_pgd_none
30026c34 l     F .vmlinux	00000008 sun4c_pgd_bad
30026c3c l     F .vmlinux	00000008 sun4c_pgd_present
30026c44 l     F .vmlinux	00000008 sun4c_pgd_clear
30026c4c l     F .vmlinux	00000024 sun4c_pte_mkwrite
30026c70 l     F .vmlinux	00000024 sun4c_pte_mkdirty
30026c94 l     F .vmlinux	00000024 sun4c_pte_mkyoung
30026cb8 l     F .vmlinux	00000024 sun4c_mk_pte
30026cdc l     F .vmlinux	0000000c sun4c_mk_pte_phys
30026ce8 l     F .vmlinux	00000014 sun4c_mk_pte_io
30026cfc l     F .vmlinux	00000010 sun4c_pte_pfn
30026d0c l     F .vmlinux	0000000c sun4c_pgoff_to_pte
30026d18 l     F .vmlinux	0000000c sun4c_pte_to_pgoff
30026d24 l     F .vmlinux	00000038 sun4c_pmd_page
30026d5c l     F .vmlinux	00000008 sun4c_pgd_page
30026d64 l     F .vmlinux	00000008 sun4c_pmd_offset
30026d98 l     F .vmlinux	0000000c sun4c_swp_type
30026da4 l     F .vmlinux	00000010 sun4c_swp_offset
30026db4 l     F .vmlinux	00000020 sun4c_swp_entry
30026dd4 l     F .vmlinux	00000084 sun4c_get_pgd_fast
30026e58 l     F .vmlinux	00000024 sun4c_free_pgd_fast
30026e7c l     F .vmlinux	0000006c sun4c_pte_alloc_one_kernel
30026ee8 l     F .vmlinux	00000040 sun4c_pte_alloc_one
30026f28 l     F .vmlinux	00000024 sun4c_free_pte_fast
30026f4c l     F .vmlinux	00000034 sun4c_pte_free
30026f80 l     F .vmlinux	00000004 sun4c_pmd_alloc_one
30026f84 l     F .vmlinux	00000008 sun4c_free_pmd_fast
30026f8c l     F .vmlinux	000000ac sun4c_check_pgt_cache
30606658 l     O .bss	00000004 sun4c_iobuffer_end
30027228 l     F .vmlinux	0000000c sun4c_pgprot_noncached
00000000 l    df *ABS*	00000000 leon.c
00000000 l    df *ABS*	00000000 math.c
30027ff8 l     F .vmlinux	000088ec do_one_mathemu
00000000 l    df *ABS*	00000000 sched.c
30226460 l     O .vmlinux	00000008 stat_nam
30030a80 l     F .vmlinux	00000060 static_prio_timeslice
30030ae0 l     F .vmlinux	00000018 task_rq_lock
30606788 l     O .bss	00000930 per_cpu__runqueues
30030af8 l     F .vmlinux	0000008c dequeue_task
30030b84 l     F .vmlinux	00000074 enqueue_task
30030bf8 l     F .vmlinux	00000044 requeue_task
30030c3c l     F .vmlinux	0000007c set_load_weight
30030cb8 l     F .vmlinux	000000a4 effective_prio
30030d5c l     F .vmlinux	00000048 __activate_task
30030da4 l     F .vmlinux	00000134 recalc_task_prio
30030ed8 l     F .vmlinux	00000038 deactivate_task
30030f44 l     F .vmlinux	00000184 try_to_wake_up
30031518 l     F .vmlinux	0000028c task_running_tick
30226468 l     O .vmlinux	0000000f __func__.0
30114ec8 l       .vmlinux	00000000 here
30031a54 l     F .vmlinux	0000006c __wake_up_common
300321b8 l     F .vmlinux	000000a0 do_sched_setscheduler
3003266c l     F .vmlinux	00000038 __cond_resched
00000000 l    df *ABS*	00000000 fork.c
306070dc l     O .bss	00000004 task_struct_cachep
30226478 l     O .vmlinux	00000012 __func__.1
306070c0 l     O .bss	00000000 __key.0
30032b54 l     F .vmlinux	0000009c mm_init
306070e4 l     O .bss	00000004 mm_cachep
30032f00 l     F .vmlinux	00000208 dup_fd
30033108 l     F .vmlinux	00000060 copy_files
306070e0 l     O .bss	00000004 signal_cachep
3003322c l     F .vmlinux	00000df0 copy_process
300341ec l     F .vmlinux	0000000c sighand_ctor
00000000 l    df *ABS*	00000000 exec_domain.c
30034894 l     F .vmlinux	00000074 default_handler
302563f4 l     O .vmlinux	00000080 ident_map
30256474 l     O .vmlinux	00000004 exec_domains
306070e8 l     O .bss	00000000 exec_domains_lock
00000000 l    df *ABS*	00000000 panic.c
302b9ff4 l     O .vmlinux	0000000c __setup_pause_on_oops_setup
302afa50 l     O .vmlinux	0000000f __setup_str_pause_on_oops_setup
30282960 l     F .vmlinux	00000024 pause_on_oops_setup
302ba000 l     O .vmlinux	0000000c __setup_panic_setup
302afa60 l     O .vmlinux	00000007 __setup_str_panic_setup
3028293c l     F .vmlinux	00000024 panic_setup
306070ec l     O .bss	00000000 pause_on_oops_lock
300349b4 l     F .vmlinux	00000008 no_blink
306070f0 l     O .bss	00000400 buf.2
306074f0 l     O .bss	00000014 buf.1
30607518 l     O .bss	00000004 pause_on_oops
30034c24 l     F .vmlinux	00000038 spin_msec
30607504 l     O .bss	00000004 spin_counter.0
30034c5c l     F .vmlinux	000000c0 do_oops_enter_exit
3060751c l     O .bss	00000004 pause_on_oops_flag
00000000 l    df *ABS*	00000000 printk.c
302ba00c l     O .vmlinux	0000000c __setup_console_setup
302afa68 l     O .vmlinux	00000009 __setup_str_console_setup
30282a78 l     F .vmlinux	0000016c console_setup
302ba018 l     O .vmlinux	0000000c __setup_printk_time_setup
302afa78 l     O .vmlinux	00000005 __setup_str_printk_time_setup
30282984 l     F .vmlinux	00000028 printk_time_setup
30252e58 l     O .vmlinux	00000014 __param_printk_time
30256480 l     O .vmlinux	00000013 __param_str_printk_time
30607520 l     O .bss	00000004 printk_time
302ba024 l     O .vmlinux	0000000c __setup_ignore_loglevel_setup
302afa80 l     O .vmlinux	00000010 __setup_str_ignore_loglevel_setup
30282d98 l     F .vmlinux	00000024 ignore_loglevel_setup
302ba030 l     O .vmlinux	0000000c __setup_log_buf_len_setup
302afa90 l     O .vmlinux	0000000d __setup_str_log_buf_len_setup
30282be4 l     F .vmlinux	000001b4 log_buf_len_setup
302564ac l     O .vmlinux	00000004 log_buf
306079d8 l     O .bss	00004000 __log_buf
30607524 l     O .bss	00000000 logbuf_lock
302564b0 l     O .vmlinux	00000004 log_buf_len
302564b4 l     O .vmlinux	00000004 selected_console
302564b8 l     O .vmlinux	00000004 preferred_console
302564bc l     O .vmlinux	00000010 console_sem
302564cc l     O .vmlinux	00000010 secondary_console_sem
302564dc l     O .vmlinux	00000004 printk_cpu
30607944 l     O .bss	00000004 log_start
3060794c l     O .bss	00000004 log_end
3060b9d8 l     O .bss	00000004 logged_chars
300351b4 l     F .vmlinux	00000084 __call_console_drivers
30035238 l     F .vmlinux	000000a0 _call_console_drivers
3060b9dc l     O .bss	00000004 ignore_loglevel
300352d8 l     F .vmlinux	00000088 emit_log_char
30607948 l     O .bss	00000004 con_start
30607950 l     O .bss	00000080 console_cmdline
30607940 l     O .bss	00000004 console_suspended
306079d0 l     O .bss	00000004 console_may_schedule
3060793c l     O .bss	00000004 console_locked
302564e0 l     O .vmlinux	00000004 msg_level.4
30607528 l     O .bss	00000400 printk_buf.5
302564e4 l     O .vmlinux	00000004 log_level_unknown.6
30607928 l     O .bss	00000004 oops_timestamp.7
3060792c l     O .bss	00000000 ratelimit_lock.0
302564e8 l     O .vmlinux	00000004 toks.1
3060792c l     O .bss	00000004 last_msg.2
30607930 l     O .bss	00000004 missed.3
00000000 l    df *ABS*	00000000 profile.c
302ba3c4 l     O .vmlinux	00000004 __initcall_create_proc_profile6
30283020 l     F .vmlinux	00000064 create_proc_profile
302ba03c l     O .vmlinux	0000000c __setup_profile_setup
302afaa0 l     O .vmlinux	00000009 __setup_str_profile_setup
30282dbc l     F .vmlinux	000001f8 profile_setup
30226490 l     O .vmlinux	0000006c proc_profile_operations
3003635c l     F .vmlinux	00000140 read_profile
3003649c l     F .vmlinux	00000024 write_profile
302564f0 l     O .vmlinux	00000004 prof_cpu_mask
3060b9e8 l     O .bss	00000004 prof_buffer
3060b9f0 l     O .bss	00000004 prof_shift
3060b9ec l     O .bss	00000004 prof_len
302afab0 l     O .vmlinux	00000009 schedstr.0
302afac0 l     O .vmlinux	00000006 sleepstr.1
302afac8 l     O .vmlinux	00000004 kvmstr.2
30036294 l     F .vmlinux	00000048 prof_cpu_mask_read_proc
300362dc l     F .vmlinux	00000034 prof_cpu_mask_write_proc
00000000 l    df *ABS*	00000000 exit.c
300364c0 l     F .vmlinux	00000030 delayed_put_task_struct
30036854 l     F .vmlinux	00000090 will_become_orphaned_pgrp
30036904 l     F .vmlinux	00000044 has_stopped_jobs
30036da4 l     F .vmlinux	000000e8 exit_mm
300370d8 l     F .vmlinux	000001b8 reparent_thread
30226500 l     O .vmlinux	00000008 __func__.0
30037bf8 l     F .vmlinux	000000fc eligible_child
30037cf4 l     F .vmlinux	000001ac wait_noreap_copyout
30037ea0 l     F .vmlinux	00000dd8 do_wait
00000000 l    df *ABS*	00000000 itimer.c
30038d54 l     F .vmlinux	0000009c itimer_get_remtime
302564f4 l     O .vmlinux	00000004 warnlimit.0
30038fe8 l     F .vmlinux	000000c8 fixup_timeval
00000000 l    df *ABS*	00000000 time.c
302564f8 l     O .vmlinux	00000004 firsttime.0
00000000 l    df *ABS*	00000000 softirq.c
302afad0 l     O .vmlinux	0000000c cpu_nfb
302830b4 l     F .vmlinux	00000094 cpu_callback
3060ba00 l     O .bss	00000004 per_cpu__tasklet_hi_vec
3060ba04 l     O .bss	00000004 per_cpu__tasklet_vec
30226508 l     O .vmlinux	00000012 __func__.5
3060ba08 l     O .bss	00000004 __warned.6
3060ba0c l     O .bss	00000004 __warned.7
30226520 l     O .vmlinux	00000011 __func__.2
3060ba10 l     O .bss	00000004 __warned.3
3060ba14 l     O .bss	00000004 __warned.4
3060ba40 l     O .bss	00000100 softirq_vec
3060bb40 l     O .bss	00000004 per_cpu__ksoftirqd
30226538 l     O .vmlinux	00000010 __func__.0
3060ba18 l     O .bss	00000004 __warned.1
3003a8a8 l     F .vmlinux	000000a4 tasklet_action
3003a94c l     F .vmlinux	000000a4 tasklet_hi_action
3003aa98 l     F .vmlinux	000000d0 ksoftirqd
00000000 l    df *ABS*	00000000 resource.c
302ba048 l     O .vmlinux	0000000c __setup_reserve_setup
302afae0 l     O .vmlinux	00000009 __setup_str_reserve_setup
302831ec l     F .vmlinux	000000f4 reserve_setup
302ba3c8 l     O .vmlinux	00000004 __initcall_ioresources_init6
30283188 l     F .vmlinux	00000064 ioresources_init
30226548 l     O .vmlinux	0000006c proc_iomem_operations
3003ad44 l     F .vmlinux	00000034 iomem_open
302265b4 l     O .vmlinux	0000006c proc_ioports_operations
3003ad10 l     F .vmlinux	00000034 ioports_open
30226620 l     O .vmlinux	00000010 resource_op
3003abc0 l     F .vmlinux	00000094 r_start
3003ac54 l     F .vmlinux	00000008 r_stop
3003ab68 l     F .vmlinux	00000058 r_next
3003ac5c l     F .vmlinux	000000b4 r_show
3060bb60 l     O .bss	00000000 resource_lock
3003ad78 l     F .vmlinux	0000007c __request_resource
3003b31c l     F .vmlinux	0000001c devm_region_release
3003b338 l     F .vmlinux	00000044 devm_region_match
30226630 l     O .vmlinux	00000016 __func__.2
3060bb60 l     O .bss	00000004 reserved.0
3060bb64 l     O .bss	00000070 reserve.1
00000000 l    df *ABS*	00000000 sysctl.c
302ba348 l     O .vmlinux	00000004 __initcall_sysctl_init1
302832e0 l     F .vmlinux	0000001c sysctl_init
30256534 l     O .vmlinux	00000108 root_table
30256bf4 l     O .vmlinux	00000478 kern_table
302568a8 l     O .vmlinux	00000344 vm_table
3025663c l     O .vmlinux	00000268 fs_table
3060bc00 l     O .bss	0000002c debug_table
3060bbd4 l     O .bss	0000002c dev_table
3060bc2c l     O .bss	00000004 minolduid
302568a4 l     O .vmlinux	00000004 maxolduid
3060bc30 l     O .bss	00000004 zero
30256bf0 l     O .vmlinux	00000004 one_hundred
30256bec l     O .vmlinux	00000004 min_percpu_pagelist_fract
3003c3bc l     F .vmlinux	00000064 proc_dointvec_taint
3003cc1c l     F .vmlinux	000000a4 proc_do_cad_pid
3025706c l     O .vmlinux	00000004 ngroups_max
3060bc2c l     O .bss	00000000 sysctl_lock
30257070 l     O .vmlinux	00000014 root_table_header
3003b478 l     F .vmlinux	0000003c unuse_table
3003b9bc l     F .vmlinux	00000074 sysctl_set_parent
3003bd64 l     F .vmlinux	00000054 do_proc_dointvec_conv
3003bdb8 l     F .vmlinux	0000047c __do_proc_dointvec
3003c234 l     F .vmlinux	0000003c do_proc_dointvec
3003c2a0 l     F .vmlinux	000000a8 do_proc_dointvec_bset_conv
3003c420 l     F .vmlinux	000000a0 do_proc_dointvec_minmax_conv
3003c514 l     F .vmlinux	0000048c do_proc_doulongvec_minmax
3003ca0c l     F .vmlinux	00000090 do_proc_dointvec_jiffies_conv
3003ca9c l     F .vmlinux	0000006c do_proc_dointvec_userhz_jiffies_conv
3003cb08 l     F .vmlinux	0000006c do_proc_dointvec_ms_jiffies_conv
00000000 l    df *ABS*	00000000 capability.c
3060bc38 l     O .bss	00000000 task_capability_lock
00000000 l    df *ABS*	00000000 ptrace.c
3003d964 l     F .vmlinux	000000e0 may_attach
00000000 l    df *ABS*	00000000 timer.c
302ba3cc l     O .vmlinux	00000004 __initcall_timekeeping_init_device6
3028343c l     F .vmlinux	00000038 timekeeping_init_device
30257090 l     O .vmlinux	00000044 device_timer
302570d4 l     O .vmlinux	00000064 timekeeping_sysclass
3003e4b8 l     F .vmlinux	00000050 timekeeping_suspend
3003e400 l     F .vmlinux	000000b8 timekeeping_resume
302afaf0 l     O .vmlinux	0000000c timers_nb
30283474 l     F .vmlinux	00000118 timer_cpu_notify
30257138 l     O .vmlinux	00000004 per_cpu__tvec_bases
3003e0c0 l     F .vmlinux	000000c8 internal_add_timer
3003e188 l     F .vmlinux	0000004c lock_timer_base
3003e34c l     F .vmlinux	00000074 cascade
3060cc7c l     O .bss	00000004 clock
3060cc84 l     O .bss	00000004 timekeeping_suspend_time
3060cc80 l     O .bss	00000004 timekeeping_suspended
3003e508 l     F .vmlinux	000001b0 run_timer_softirq
3025713c l     O .vmlinux	00000004 count.2
3003eea8 l     F .vmlinux	00000010 process_timeout
302afb00 l     O .vmlinux	00000001 tvec_base_done.0
3060bc44 l     O .bss	00000001 boot_done.1
3060cc88 l     O .bss	00000000 base_lock_keys
00000000 l    df *ABS*	00000000 user.c
302ba3d0 l     O .vmlinux	00000004 __initcall_uid_cache_init6
302835cc l     F .vmlinux	00000088 uid_cache_init
3060cc90 l     O .bss	00000000 uidhash_lock
3060cc94 l     O .bss	00000800 uidhash_table
3060cc90 l     O .bss	00000004 uid_cachep
00000000 l    df *ABS*	00000000 signal.c
3003f3f0 l     F .vmlinux	00000098 sig_ignored
3003f524 l     F .vmlinux	00000094 __sigqueue_alloc
3060d494 l     O .bss	00000004 sigqueue_cachep
3003f5b8 l     F .vmlinux	00000048 __sigqueue_free
3003f770 l     F .vmlinux	00000270 __dequeue_signal
3003fb70 l     F .vmlinux	000000cc rm_from_queue_full
3003fc3c l     F .vmlinux	00000094 rm_from_queue
3003fcd0 l     F .vmlinux	000000cc check_kill_permission
3003fd9c l     F .vmlinux	00000164 send_signal
3003ff00 l     F .vmlinux	000000bc specific_send_sig_info
30040080 l     F .vmlinux	00000304 __group_complete_signal
300406c4 l     F .vmlinux	0000010c do_notify_parent_cldstop
300407d0 l     F .vmlinux	00000194 handle_stop_signal
30040f0c l     F .vmlinux	00000108 ptrace_stop
30041088 l     F .vmlinux	00000048 finish_stop
30041d70 l     F .vmlinux	000000e0 do_tkill
00000000 l    df *ABS*	00000000 sys.c
30257218 l     O .vmlinux	00000010 reboot_notifier_list
300425a0 l     F .vmlinux	00000054 notifier_chain_register
300425f4 l     F .vmlinux	00000050 notifier_chain_unregister
30042644 l     F .vmlinux	00000050 notifier_call_chain
3060d498 l     O .bss	00000000 __key.1
30042990 l     F .vmlinux	0000009c set_one_prio
300430ec l     F .vmlinux	00000014 deferred_cad
30257228 l     O .vmlinux	00000010 cad_work.0
30043350 l     F .vmlinux	000000ac set_user
00000000 l    df *ABS*	00000000 kmod.c
30044e84 l     F .vmlinux	00000108 ____call_usermodehelper
30044f8c l     F .vmlinux	000000b8 wait_for_helper
30045044 l     F .vmlinux	0000008c __call_usermodehelper
3060d49c l     O .bss	00000004 khelper_wq
00000000 l    df *ABS*	00000000 workqueue.c
30257238 l     O .vmlinux	0000000c workqueue_mutex
30257244 l     O .vmlinux	00000008 workqueues
300453a8 l     F .vmlinux	0000007c __queue_work
30226648 l     O .vmlinux	0000000e __func__.0
300455d8 l     F .vmlinux	0000015c run_workqueue
30045734 l     F .vmlinux	00000170 worker_thread
300458a4 l     F .vmlinux	000000e4 flush_cpu_workqueue
300459d4 l     F .vmlinux	000000ac create_workqueue_thread
30045a80 l     F .vmlinux	00000038 cleanup_workqueue_thread
3060d4a0 l     O .bss	00000004 singlethread_cpu
3060d4a4 l     O .bss	00000004 keventd_wq
00000000 l    df *ABS*	00000000 pid.c
3060d4a8 l     O .bss	00000000 pidmap_lock
3060d4b0 l     O .bss	00000004 pid_cachep
30045f18 l     F .vmlinux	00000014 delayed_put_pid
3060d4ac l     O .bss	00000004 pidhash_shift
3060d4a8 l     O .bss	00000004 pid_hash
00000000 l    df *ABS*	00000000 rcupdate.c
30252e6c l     O .vmlinux	00000014 __param_qlowmark
30257278 l     O .vmlinux	00000012 __param_str_qlowmark
30257270 l     O .vmlinux	00000004 qlowmark
30252e80 l     O .vmlinux	00000014 __param_qhimark
30257290 l     O .vmlinux	00000011 __param_str_qhimark
3025728c l     O .vmlinux	00000004 qhimark
30252e94 l     O .vmlinux	00000014 __param_blimit
302572a8 l     O .vmlinux	00000010 __param_str_blimit
302572a4 l     O .vmlinux	00000004 blimit
302afb08 l     O .vmlinux	0000000c rcu_nb
3028386c l     F .vmlinux	00000060 rcu_cpu_notify
3060d52c l     O .bss	00000014 per_cpu__rcu_tasklet
302572b8 l     O .vmlinux	00000014 rcu_bh_ctrlblk
302572cc l     O .vmlinux	00000014 rcu_ctrlblk
302572e0 l     O .vmlinux	0000000c rcu_barrier_mutex
300467a4 l     F .vmlinux	00000038 rcu_barrier_callback
3060d540 l     O .bss	00000004 rcu_barrier_cpu_count
3060d544 l     O .bss	0000000c rcu_barrier_completion
3004686c l     F .vmlinux	00000058 rcu_start_batch
300468c4 l     F .vmlinux	00000240 __rcu_process_callbacks
30046b04 l     F .vmlinux	00000030 rcu_process_callbacks
30046b34 l     F .vmlinux	00000084 __rcu_pending
30046d20 l     F .vmlinux	0000004c rcu_init_percpu_data
30046d6c l     F .vmlinux	00000014 wakeme_after_rcu
00000000 l    df *ABS*	00000000 extable.c
00000000 l    df *ABS*	00000000 params.c
302ba384 l     O .vmlinux	00000004 __initcall_param_sysfs_init4
30283a84 l     F .vmlinux	000001e8 param_sysfs_init
30257358 l     O .vmlinux	0000000c module_ktype
3025734c l     O .vmlinux	0000000c module_uevent_ops
300479f0 l     F .vmlinux	0000003c uevent_filter
30257364 l     O .vmlinux	00000008 module_sysfs_ops
30047984 l     F .vmlinux	00000034 module_attr_show
300479b8 l     F .vmlinux	00000038 module_attr_store
300478f0 l     F .vmlinux	00000058 param_attr_show
30047948 l     F .vmlinux	0000003c param_attr_store
30283910 l     F .vmlinux	00000174 kernel_param_sysfs_setup
00000000 l    df *ABS*	00000000 posix-timers.c
302ba3d4 l     O .vmlinux	00000004 __initcall_init_posix_timers6
30283c6c l     F .vmlinux	000000b0 init_posix_timers
3060d550 l     O .bss	00000000 idr_lock
30047a2c l     F .vmlinux	00000014 posix_ktime_get_ts
3060d564 l     O .bss	00000280 posix_clocks
3060d550 l     O .bss	00000004 posix_timers_cache
3060d554 l     O .bss	00000010 posix_timers_id
30047bb0 l     F .vmlinux	000000ac posix_timer_fn
30047c5c l     F .vmlinux	00000094 release_posix_timer
30048080 l     F .vmlinux	00000088 lock_timer
3004820c l     F .vmlinux	00000180 common_timer_get
00000000 l    df *ABS*	00000000 kthread.c
302ba34c l     O .vmlinux	00000004 __initcall_helper_init1
30283d1c l     F .vmlinux	00000030 helper_init
3025736c l     O .vmlinux	0000000c kthread_stop_lock
3060d7e8 l     O .bss	00000014 kthread_stop_info
30048f3c l     F .vmlinux	00000108 kthread
30049044 l     F .vmlinux	0000005c keventd_create_kthread
3060d7e4 l     O .bss	00000004 helper_wq
00000000 l    df *ABS*	00000000 wait.c
00000000 l    df *ABS*	00000000 kfifo.c
00000000 l    df *ABS*	00000000 sys_ni.c
00000000 l    df *ABS*	00000000 posix-cpu-timers.c
302ba3d8 l     O .vmlinux	00000004 __initcall_init_posix_cpu_timers6
30283d4c l     F .vmlinux	000000dc init_posix_cpu_timers
30049804 l     F .vmlinux	00000090 check_clock
30049894 l     F .vmlinux	000000a8 sample_to_timespec
3004993c l     F .vmlinux	000001e0 bump_cpu_timer
30049b7c l     F .vmlinux	0000008c cpu_clock_sample
30049c08 l     F .vmlinux	00000120 cpu_clock_sample_group_locked
30049d28 l     F .vmlinux	00000038 cpu_clock_sample_group
3004a008 l     F .vmlinux	00000194 cleanup_timers
3004a20c l     F .vmlinux	000001f4 process_timer_rebalance
3004a400 l     F .vmlinux	00000078 clear_dead_task
3004a478 l     F .vmlinux	00000290 arm_timer
3004a844 l     F .vmlinux	00000088 cpu_timer_fire
3060d7fc l     O .bss	00000010 zero_it.0
3004b848 l     F .vmlinux	00000148 do_cpu_nanosleep
3004bb40 l     F .vmlinux	00000014 process_cpu_clock_getres
3004bb54 l     F .vmlinux	00000014 process_cpu_clock_get
3004bb68 l     F .vmlinux	00000018 process_cpu_timer_create
3004bb80 l     F .vmlinux	00000014 process_cpu_nsleep
3004bb94 l     F .vmlinux	00000008 process_cpu_nsleep_restart
3004bb9c l     F .vmlinux	00000014 thread_cpu_clock_getres
3004bbb0 l     F .vmlinux	00000014 thread_cpu_clock_get
3004bbc4 l     F .vmlinux	00000018 thread_cpu_timer_create
3004bbdc l     F .vmlinux	00000008 thread_cpu_nsleep
3004bbe4 l     F .vmlinux	00000008 thread_cpu_nsleep_restart
00000000 l    df *ABS*	00000000 mutex.c
30115f30 l     F .vmlinux	00000090 __mutex_lock_slowpath
30115fc0 l     F .vmlinux	0000003c __mutex_unlock_slowpath
30116034 l     F .vmlinux	000000b8 __mutex_lock_interruptible_slowpath
3004bc10 l     F .vmlinux	00000050 __mutex_trylock_slowpath
00000000 l    df *ABS*	00000000 hrtimer.c
302afb14 l     O .vmlinux	0000000c hrtimers_nb
30283e28 l     F .vmlinux	0000003c hrtimer_cpu_notify
3004c090 l     F .vmlinux	000000e8 enqueue_hrtimer
3004c178 l     F .vmlinux	00000038 __remove_hrtimer
3004c618 l     F .vmlinux	00000028 hrtimer_wakeup
30116100 l     F .vmlinux	0000008c do_nanosleep
00000000 l    df *ABS*	00000000 rwsem.c
00000000 l    df *ABS*	00000000 latency.c
302ba3dc l     O .vmlinux	00000004 __initcall_latency_init6
30283e88 l     F .vmlinux	00000034 latency_init
302573c8 l     O .vmlinux	00000010 latency_notifier
302573d8 l     O .vmlinux	00000008 latency_list
3060d80c l     O .bss	00000000 latency_lock
3060d80c l     O .bss	00000004 current_max_latency
00000000 l    df *ABS*	00000000 nsproxy.c
00000000 l    df *ABS*	00000000 srcu.c
3060d810 l     O .bss	00000000 __key.1
3004ce68 l     F .vmlinux	00000010 srcu_readers_active_idx
30226670 l     O .vmlinux	00000014 __func__.0
00000000 l    df *ABS*	00000000 ntp.c
30257408 l     O .vmlinux	00000004 time_constant
3060d810 l     O .bss	00000004 time_state
3004cfe0 l     F .vmlinux	00000108 ntp_update_frequency
3060d828 l     O .bss	00000008 tick_length_base
3060d820 l     O .bss	00000008 tick_length
3060d830 l     O .bss	00000008 time_offset
3060d838 l     O .bss	00000004 time_reftime
00000000 l    df *ABS*	00000000 clocksource.c
302ba054 l     O .vmlinux	0000000c __setup_boot_override_clock
302afb20 l     O .vmlinux	00000007 __setup_str_boot_override_clock
30283f88 l     F .vmlinux	0000004c boot_override_clock
302ba060 l     O .vmlinux	0000000c __setup_boot_override_clocksource
302afb28 l     O .vmlinux	0000000d __setup_str_boot_override_clocksource
30283f48 l     F .vmlinux	00000040 boot_override_clocksource
302ba3e0 l     O .vmlinux	00000004 __initcall_init_clocksource_sysfs6
30283ed0 l     F .vmlinux	00000078 init_clocksource_sysfs
302ba3a8 l     O .vmlinux	00000004 __initcall_clocksource_done_booting5
30283ebc l     F .vmlinux	00000014 clocksource_done_booting
3025740c l     O .vmlinux	00000014 attr_available_clocksource
3004df04 l     F .vmlinux	00000070 sysfs_show_available_clocksources
30257420 l     O .vmlinux	00000014 attr_current_clocksource
3004ddb0 l     F .vmlinux	00000050 sysfs_show_current_clocksources
3004de00 l     F .vmlinux	00000104 sysfs_override_clocksource
30257434 l     O .vmlinux	00000044 device_clocksource
30257478 l     O .vmlinux	00000064 clocksource_sysclass
302574dc l     O .vmlinux	00000008 clocksource_list
3060d840 l     O .bss	00000000 clocksource_lock
302574e4 l     O .vmlinux	00000004 curr_clocksource
3060d868 l     O .bss	00000004 finished_booting
3060d840 l     O .bss	00000004 next_clocksource
3004dbdc l     F .vmlinux	00000050 select_clocksource
3060d844 l     O .bss	00000004 clocksource_override
3004dc2c l     F .vmlinux	000000bc clocksource_enqueue
3060d848 l     O .bss	00000020 override_name
00000000 l    df *ABS*	00000000 jiffies.c
302ba350 l     O .vmlinux	00000004 __initcall_init_jiffies_clocksource1
30283fd4 l     F .vmlinux	00000018 init_jiffies_clocksource
3004df74 l     F .vmlinux	00000014 jiffies_read
00000000 l    df *ABS*	00000000 timer_list.c
302ba3e4 l     O .vmlinux	00000004 __initcall_init_timer_list_procfs6
30283fec l     F .vmlinux	0000003c init_timer_list_procfs
30257540 l     O .vmlinux	0000006c timer_list_fops
3004e47c l     F .vmlinux	00000020 timer_list_open
3004df88 l     F .vmlinux	00000044 print_name_offset
3004dfcc l     F .vmlinux	00000498 timer_list_show
00000000 l    df *ABS*	00000000 futex.c
302ba3e8 l     O .vmlinux	00000004 __initcall_init6
30284028 l     F .vmlinux	00000074 init
302575ac l     O .vmlinux	00000020 futex_fs_type
30050318 l     F .vmlinux	00000024 futexfs_get_sb
30226688 l     O .vmlinux	0000006c futex_fops
3004f484 l     F .vmlinux	00000060 futex_poll
3004f464 l     F .vmlinux	00000020 futex_close
3004e4c0 l     F .vmlinux	000000cc hash_futex
3060d874 l     O .bss	00000800 futex_queues
3004e58c l     F .vmlinux	00000118 get_futex_key
3004e6a4 l     F .vmlinux	00000058 drop_key_refs
3004e6fc l     F .vmlinux	000000ac futex_handle_fault
302266f8 l     O .vmlinux	00000013 __func__.7
3004e8d0 l     F .vmlinux	0000005c wake_futex
3004e92c l     F .vmlinux	000000ec futex_wake
3004ea18 l     F .vmlinux	00000250 futex_requeue
30226710 l     O .vmlinux	0000000b __func__.0
3004ec68 l     F .vmlinux	000000b0 unqueue_me
30226720 l     O .vmlinux	0000000e __func__.6
3004ed18 l     F .vmlinux	00000120 unqueue_me_pi
30226730 l     O .vmlinux	0000000e __func__.3
30226740 l     O .vmlinux	00000010 __func__.4
30226750 l     O .vmlinux	0000000f __func__.5
3004ee38 l     F .vmlinux	0000062c futex_lock_pi
3060d870 l     O .bss	00000004 printk_interval.1
30226760 l     O .vmlinux	0000000e __func__.2
3060e074 l     O .bss	00000004 futex_mnt
00000000 l    df *ABS*	00000000 rtmutex.c
3005033c l     F .vmlinux	00000020 rt_mutex_set_owner
3005035c l     F .vmlinux	00000028 fixup_rt_mutex_waiters
300503c0 l     F .vmlinux	00000030 __rt_mutex_adjust_prio
300503f0 l     F .vmlinux	00000024 rt_mutex_adjust_prio
3060e078 l     O .bss	00000004 prev_max.2
30050414 l     F .vmlinux	000002c4 rt_mutex_adjust_prio_chain
300506d8 l     F .vmlinux	0000010c try_to_take_rt_mutex
30226770 l     O .vmlinux	0000000e __func__.3
301162cc l     F .vmlinux	00000408 rt_mutex_slowlock
30050848 l     F .vmlinux	0000003c rt_mutex_slowtrylock
30226780 l     O .vmlinux	00000013 __func__.1
301166d4 l     F .vmlinux	00000180 rt_mutex_slowunlock
30226798 l     O .vmlinux	00000011 __func__.0
00000000 l    df *ABS*	00000000 dma.c
302ba3ec l     O .vmlinux	00000004 __initcall_proc_dma_init6
3028409c l     F .vmlinux	00000034 proc_dma_init
302267b0 l     O .vmlinux	0000006c proc_dma_operations
30050a88 l     F .vmlinux	00000020 proc_dma_open
302575d0 l     O .vmlinux	00000040 dma_chan_busy
30050a24 l     F .vmlinux	00000064 proc_dma_show
00000000 l    df *ABS*	00000000 uid16.c
00000000 l    df *ABS*	00000000 acct.c
30600000 l     O .vmlinux	00000024 acct_globals
30051324 l     F .vmlinux	00000018 acct_timeout
3005133c l     F .vmlinux	00000068 encode_comp_t
300513a4 l     F .vmlinux	00000610 do_acct_process
300519b4 l     F .vmlinux	000000d8 acct_file_reopen
00000000 l    df *ABS*	00000000 ksysfs.c
302ba354 l     O .vmlinux	00000004 __initcall_ksysfs_init1
302840d0 l     F .vmlinux	00000040 ksysfs_init
30257678 l     O .vmlinux	00000008 kernel_attr_group
3060e080 l     O .bss	00000004 kernel_attrs
00000000 l    df *ABS*	00000000 softlockup.c
30257680 l     O .vmlinux	0000000c panic_block
30051e00 l     F .vmlinux	00000014 softlock_panic
302afb38 l     O .vmlinux	0000000c cpu_nfb
30284110 l     F .vmlinux	000000a8 cpu_callback
3060e084 l     O .bss	00000004 did_panic
3060e088 l     O .bss	00000000 print_lock
3060e088 l     O .bss	00000004 per_cpu__touch_timestamp
3060e08c l     O .bss	00000004 per_cpu__print_timestamp
3060e090 l     O .bss	00000004 per_cpu__watchdog_task
30051edc l     F .vmlinux	00000068 watchdog
00000000 l    df *ABS*	00000000 utsname_sysctl.c
302ba3f0 l     O .vmlinux	00000004 __initcall_utsname_sysctl_init6
30284208 l     F .vmlinux	00000018 utsname_sysctl_init
3025768c l     O .vmlinux	00000058 uts_root_table
302576e4 l     O .vmlinux	00000108 uts_kern_table
30051fb4 l     F .vmlinux	00000068 proc_do_uts_string
3005201c l     F .vmlinux	00000084 sysctl_uts_string
30051f44 l     F .vmlinux	0000003c get_uts
30051f80 l     F .vmlinux	00000034 put_uts
00000000 l    df *ABS*	00000000 bootmem.c
302577ec l     O .vmlinux	00000008 bdata_list
30284234 l     F .vmlinux	00000024 get_mapsize
30284258 l     F .vmlinux	000000c4 init_bootmem_core
3028431c l     F .vmlinux	00000088 reserve_bootmem_core
302843a4 l     F .vmlinux	0000009c free_bootmem_core
302847cc l     F .vmlinux	00000204 free_all_bootmem_core
00000000 l    df *ABS*	00000000 filemap.c
300521ac l     F .vmlinux	0000005c sync_page
300522c4 l     F .vmlinux	00000014 filemap_fdatawrite_range
30052414 l     F .vmlinux	00000018 __sleep_on_page_lock
3005242c l     F .vmlinux	0000006c page_waitqueue
30052f64 l     F .vmlinux	0000001c shrink_readahead_size_eio
30053804 l     F .vmlinux	00000100 page_cache_read
30054e6c l     F .vmlinux	00000180 generic_file_direct_IO
30055124 l     F .vmlinux	000005f4 __generic_file_aio_write_nolock
00000000 l    df *ABS*	00000000 mempool.c
30055b14 l     F .vmlinux	00000028 add_element
30055b3c l     F .vmlinux	00000024 remove_element
30055b60 l     F .vmlinux	0000004c free_pool
00000000 l    df *ABS*	00000000 oom_kill.c
3025780c l     O .vmlinux	00000010 oom_notify_list
30226820 l     O .vmlinux	00000010 __func__.0
30056248 l     F .vmlinux	000000dc __oom_kill_task
30056324 l     F .vmlinux	00000138 oom_kill_task
3005645c l     F .vmlinux	000000a0 oom_kill_process
00000000 l    df *ABS*	00000000 fadvise.c
00000000 l    df *ABS*	00000000 page_alloc.c
302ba3f4 l     O .vmlinux	00000004 __initcall_init_per_zone_pages_min6
30285520 l     F .vmlinux	00000054 init_per_zone_pages_min
3060e0b8 l     O .bss	00000020 contig_bootmem_data
30226830 l     O .vmlinux	0000000c zone_names
300569b0 l     F .vmlinux	000000a0 bad_page
30056a50 l     F .vmlinux	000000a4 destroy_compound_page
30056af4 l     F .vmlinux	00000340 __free_pages_ok
30056e34 l     F .vmlinux	00000014 free_compound_page
30056e48 l     F .vmlinux	00000130 __rmqueue
30056f78 l     F .vmlinux	00000390 free_hot_cold_page
300574a8 l     F .vmlinux	00000360 get_page_from_freelist
30057c38 l     F .vmlinux	0000005c nr_free_zone_pages
30284cb8 l     F .vmlinux	00000064 build_zonelists_node
30284d1c l     F .vmlinux	00000120 __build_all_zonelists
302afb50 l     O .vmlinux	00000004 dma_reserve
30058060 l     F .vmlinux	000000b0 calculate_totalreserve_pages
30058110 l     F .vmlinux	000000e4 setup_per_zone_lowmem_reserve
00000000 l    df *ABS*	00000000 page-writeback.c
302afb54 l     O .vmlinux	0000000c ratelimit_nb
30285940 l     F .vmlinux	00000018 ratelimit_handler
30257c74 l     O .vmlinux	00000018 wb_timer
30058be0 l     F .vmlinux	00000040 wb_timer_fn
30257c8c l     O .vmlinux	00000004 ratelimit_pages
30257c90 l     O .vmlinux	00000018 laptop_mode_wb_timer
30058c30 l     F .vmlinux	0000001c laptop_timer_fn
30058498 l     F .vmlinux	00000120 get_dirty_limits
3060e0d8 l     O .bss	00000004 per_cpu__ratelimits.0
3060e0e4 l     O .bss	00000004 dirty_exceeded
300588d4 l     F .vmlinux	00000110 background_writeout
30058a1c l     F .vmlinux	00000164 wb_kupdate
30058c20 l     F .vmlinux	00000010 laptop_flush
00000000 l    df *ABS*	00000000 pdflush.c
302ba3f8 l     O .vmlinux	00000004 __initcall_pdflush_init6
30285990 l     F .vmlinux	00000020 pdflush_init
30257ca8 l     O .vmlinux	00000008 pdflush_list
3060e0ec l     O .bss	00000000 pdflush_lock
3060e0ec l     O .bss	00000004 last_empty_jifs
3005982c l     F .vmlinux	0000003c start_one_pdflush_thread
30059868 l     F .vmlinux	000001bc pdflush
00000000 l    df *ABS*	00000000 readahead.c
30059b50 l     F .vmlinux	00000268 __do_page_cache_readahead
30059e94 l     F .vmlinux	000000b4 blockable_page_cache_readahead
30059f48 l     F .vmlinux	000000d8 make_ahead_window
00000000 l    df *ABS*	00000000 swap.c
3060e0f0 l     O .bss	00000040 per_cpu__lru_add_active_pvecs
3060e130 l     O .bss	00000040 per_cpu__lru_add_pvecs
3005a354 l     F .vmlinux	00000038 put_compound_page
00000000 l    df *ABS*	00000000 truncate.c
3005ae8c l     F .vmlinux	00000074 truncate_complete_page
00000000 l    df *ABS*	00000000 vmscan.c
302ba3fc l     O .vmlinux	00000004 __initcall_kswapd_init6
302859d8 l     F .vmlinux	00000030 kswapd_init
30257cd0 l     O .vmlinux	00000008 shrinker_list
30257cd8 l     O .vmlinux	0000000c shrinker_rwsem
30226840 l     O .vmlinux	0000000c __func__.1
3005ba94 l     F .vmlinux	000000bc isolate_lru_pages
30226850 l     O .vmlinux	00000008 __func__.0
3005bb50 l     F .vmlinux	00000f4c shrink_zone
3005cd28 l     F .vmlinux	00000448 kswapd
00000000 l    df *ABS*	00000000 prio_tree.c
00000000 l    df *ABS*	00000000 util.c
00000000 l    df *ABS*	00000000 mmzone.c
00000000 l    df *ABS*	00000000 vmstat.c
3005da34 l     F .vmlinux	000000ac vmstat_start
3005db6c l     F .vmlinux	00000018 vmstat_stop
3005dae0 l     F .vmlinux	00000054 vmstat_next
3005db34 l     F .vmlinux	00000038 vmstat_show
3005d6f0 l     F .vmlinux	0000005c frag_start
3005d770 l     F .vmlinux	00000008 frag_stop
3005d74c l     F .vmlinux	00000024 frag_next
3005d840 l     F .vmlinux	000001f4 zoneinfo_show
3005d778 l     F .vmlinux	000000c8 frag_show
30226888 l     O .vmlinux	000000b4 vmstat_text
00000000 l    df *ABS*	00000000 backing-dev.c
30257ce4 l     O .vmlinux	00000010 congestion_wqh
00000000 l    df *ABS*	00000000 fremap.c
3005dd98 l     F .vmlinux	000000e0 zap_pte
00000000 l    df *ABS*	00000000 highmem.c
30257cf4 l     O .vmlinux	00000008 pkmap_map_wait
3060e22c l     O .bss	00000000 kmap_lock
3005e23c l     F .vmlinux	00000040 page_slot
3060f240 l     O .bss	00000400 page_address_htable
3060f238 l     O .bss	00000008 page_address_pool
3060e234 l     O .bss	00001000 pkmap_count
3060f234 l     O .bss	00000004 last_pkmap_nr
3060f640 l     O .bss	00004000 page_address_maps
3060f240 l     O .bss	00000000 pool_lock
00000000 l    df *ABS*	00000000 madvise.c
00000000 l    df *ABS*	00000000 memory.c
302ba06c l     O .vmlinux	0000000c __setup_disable_randmaps
302afb60 l     O .vmlinux	0000000b __setup_str_disable_randmaps
30285a88 l     F .vmlinux	00000010 disable_randmaps
3005fbf4 l     F .vmlinux	000004a8 do_wp_page
3006009c l     F .vmlinux	000000a4 unmap_mapping_range_vma
300605e8 l     F .vmlinux	000000e0 do_no_pfn
00000000 l    df *ABS*	00000000 mincore.c
30062104 l     F .vmlinux	00000038 mincore_page
30226940 l     O .vmlinux	0000000b __func__.0
00000000 l    df *ABS*	00000000 mlock.c
30613654 l     O .bss	00000000 shmlock_user_lock
30062534 l     F .vmlinux	00000140 mlock_fixup
30062674 l     F .vmlinux	00000108 do_mlock
300628a0 l     F .vmlinux	00000094 do_mlockall
00000000 l    df *ABS*	00000000 mmap.c
30257d08 l     O .vmlinux	00000018 special_mapping_vmops
30064f84 l     F .vmlinux	00000008 special_mapping_close
30064ef8 l     F .vmlinux	0000008c special_mapping_nopage
30062cb0 l     F .vmlinux	00000088 __remove_shared_vm_struct
30062d64 l     F .vmlinux	00000068 remove_vma
30062dcc l     F .vmlinux	00000098 find_vma_prepare
30062e90 l     F .vmlinux	00000060 __vma_link
30062ef0 l     F .vmlinux	000000ec vma_link
30063374 l     F .vmlinux	00000094 can_vma_merge_before
30063408 l     F .vmlinux	000000a8 can_vma_merge_after
30063cc4 l     F .vmlinux	000000e4 unmap_region
00000000 l    df *ABS*	00000000 mprotect.c
00000000 l    df *ABS*	00000000 mremap.c
30065684 l     F .vmlinux	000002c8 move_page_tables
00000000 l    df *ABS*	00000000 msync.c
00000000 l    df *ABS*	00000000 rmap.c
30066228 l     F .vmlinux	00000024 anon_vma_ctor
3006624c l     F .vmlinux	00000030 page_lock_anon_vma
3006627c l     F .vmlinux	00000008 page_unlock_anon_vma
30066400 l     F .vmlinux	000000bc page_referenced_one
300664bc l     F .vmlinux	000000b0 page_referenced_file
30066800 l     F .vmlinux	0000007c __page_set_anon_rmap
30066a68 l     F .vmlinux	000001a0 try_to_unmap_one
00000000 l    df *ABS*	00000000 vmalloc.c
30226950 l     O .vmlinux	00000011 __func__.2
30226968 l     O .vmlinux	0000000f __func__.1
300674d4 l     F .vmlinux	0000021c __get_vm_area_node
30067740 l     F .vmlinux	00000030 __find_vm_area
30226978 l     O .vmlinux	00000009 __func__.0
30067b00 l     F .vmlinux	00000054 __vmalloc_node
00000000 l    df *ABS*	00000000 bounce.c
302ba400 l     O .vmlinux	00000004 __initcall_init_emergency_pool6
30285ad0 l     F .vmlinux	00000068 init_emergency_pool
306136a8 l     O .bss	00000004 page_pool
30067ea0 l     F .vmlinux	00000014 mempool_alloc_pages_isa
306136ac l     O .bss	00000004 isa_page_pool
30067f0c l     F .vmlinux	000000e4 bounce_end_io
30067ff0 l     F .vmlinux	00000034 bounce_end_io_write
30068024 l     F .vmlinux	00000034 bounce_end_io_write_isa
30068058 l     F .vmlinux	000000d0 __bounce_end_io_read
30068128 l     F .vmlinux	00000034 bounce_end_io_read
3006815c l     F .vmlinux	00000034 bounce_end_io_read_isa
00000000 l    df *ABS*	00000000 shmem.c
302ba404 l     O .vmlinux	00000004 __initcall_init_tmpfs6
30285b38 l     F .vmlinux	000000ec init_tmpfs
30257d20 l     O .vmlinux	00000020 tmpfs_fs_type
3006a120 l     F .vmlinux	0000001c shmem_get_sb
30226988 l     O .vmlinux	0000004c shmem_ops
3006a0b0 l     F .vmlinux	0000002c shmem_alloc_inode
3006a0dc l     F .vmlinux	0000001c shmem_destroy_inode
300691e4 l     F .vmlinux	000000f0 shmem_delete_inode
30069f94 l     F .vmlinux	00000018 shmem_put_super
306136b0 l     O .bss	00000000 shmem_swaplist_lock
302269d4 l     O .vmlinux	00000054 shmem_dir_inode_operations
30226a28 l     O .vmlinux	0000006c shmem_file_operations
30069d98 l     F .vmlinux	00000034 shmem_mmap
30226a94 l     O .vmlinux	00000054 shmem_inode_operations
300691c4 l     F .vmlinux	00000020 shmem_truncate
300699fc l     F .vmlinux	00000124 shmem_notify_change
30068a14 l     F .vmlinux	000007b0 shmem_truncate_range
30226ae8 l     O .vmlinux	00000054 shmem_special_inode_operations
30257d40 l     O .vmlinux	0000001c shmem_backing_dev_info
30226b3c l     O .vmlinux	0000003c shmem_aops
300695a8 l     F .vmlinux	00000034 shmem_writepage
30257d5c l     O .vmlinux	00000008 shmem_swaplist
30257d64 l     O .vmlinux	00000018 shmem_vm_ops
30069b20 l     F .vmlinux	000000a4 shmem_nopage
30069bc4 l     F .vmlinux	0000013c shmem_populate
3006852c l     F .vmlinux	00000014 shmem_dir_map
30068540 l     F .vmlinux	00000014 shmem_swp_map
30068554 l     F .vmlinux	00000038 shmem_free_blocks
3006858c l     F .vmlinux	00000070 shmem_recalc_inode
300685fc l     F .vmlinux	0000015c shmem_swp_entry
30068758 l     F .vmlinux	00000054 shmem_swp_set
300687ac l     F .vmlinux	0000022c shmem_swp_alloc
300689d8 l     F .vmlinux	0000003c shmem_free_swp
300695dc l     F .vmlinux	00000420 shmem_getpage
30069dcc l     F .vmlinux	000001c8 shmem_get_inode
30069fac l     F .vmlinux	00000104 shmem_fill_super
306136b0 l     O .bss	00000004 shmem_inode_cachep
3006a0f8 l     F .vmlinux	00000028 init_once
306136b4 l     O .bss	00000004 shm_mnt
00000000 l    df *ABS*	00000000 slab.c
3006c2d0 l     F .vmlinux	000000f0 s_start
3006c3f4 l     F .vmlinux	00000018 s_stop
3006c3c0 l     F .vmlinux	00000034 s_next
3006c40c l     F .vmlinux	00000268 s_show
302ba408 l     O .vmlinux	00000004 __initcall_cpucache_init6
30285ca0 l     F .vmlinux	00000014 cpucache_init
302ba078 l     O .vmlinux	0000000c __setup_noaliencache_setup
302afb70 l     O .vmlinux	0000000d __setup_str_noaliencache_setup
30285c24 l     F .vmlinux	00000010 noaliencache_setup
30257e3c l     O .vmlinux	00000004 use_alien_caches
30257e40 l     O .vmlinux	0000000c cache_chain_mutex
30257e4c l     O .vmlinux	00000054 cache_cache
30257ea0 l     O .vmlinux	00000004 slab_early_init
306136b8 l     O .bss	00000004 slab_break_gfp_order
30257ea4 l     O .vmlinux	00000014 initarray_generic
302afb80 l     O .vmlinux	0000000c cpucache_notifier
30285cb4 l     F .vmlinux	00000318 cpuup_callback
302afb8c l     O .vmlinux	00000080 cache_names
302afc0c l     O .vmlinux	00000014 initarray_cache
3006a370 l     F .vmlinux	00000040 kmem_list3_init
306136c4 l     O .bss	00000004 g_cpucache_up
3006a3c8 l     F .vmlinux	00000018 slab_mgmt_size
3006a3e0 l     F .vmlinux	000000b4 cache_estimate
30285c34 l     F .vmlinux	0000006c start_cpu_timer
306136c8 l     O .bss	00000028 per_cpu__reap_work
3006c1a8 l     F .vmlinux	00000128 cache_reap
3006a494 l     F .vmlinux	00000144 kmem_freepages
3006a5d8 l     F .vmlinux	00000064 set_up_list3s
3006aae0 l     F .vmlinux	000000b4 cache_flusharray
3006a7b8 l     F .vmlinux	000000cc slab_destroy
3006ad54 l     F .vmlinux	00000040 kmem_rcu_free
3006a884 l     F .vmlinux	00000174 free_block
3006a9f8 l     F .vmlinux	000000e8 drain_array
3006ab94 l     F .vmlinux	000000b4 drain_freelist
3006ac48 l     F .vmlinux	000000c0 __cache_shrink
3006ad94 l     F .vmlinux	0000005c __kmem_cache_destroy
30226b88 l     O .vmlinux	00000013 __func__.0
306136bc l     O .bss	00000008 cache_chain
3006af3c l     F .vmlinux	000005f0 cache_alloc_refill
3006b75c l     F .vmlinux	00000038 alloc_arraycache
3006b794 l     F .vmlinux	0000010c init_list
3006b8b0 l     F .vmlinux	000002f4 do_tune_cpucache
3006bba4 l     F .vmlinux	000000b0 enable_cpucache
30226ba0 l     O .vmlinux	00000012 __func__.1
00000000 l    df *ABS*	00000000 open.c
3006c8b0 l     F .vmlinux	00000134 vfs_statfs_native
3006c9e4 l     F .vmlinux	00000054 vfs_statfs64
3006cd1c l     F .vmlinux	00000208 do_sys_truncate
3006cf44 l     F .vmlinux	000001c4 do_sys_ftruncate
3006d5c8 l     F .vmlinux	000000dc chown_common
3006d7e0 l     F .vmlinux	000001b0 __dentry_open
3006d9e0 l     F .vmlinux	0000005c do_filp_open
3006dc20 l     F .vmlinux	00000040 __put_unused_fd
00000000 l    df *ABS*	00000000 read_write.c
3006e44c l     F .vmlinux	0000004c wait_on_retry_sync_kiocb
3006ed64 l     F .vmlinux	000001a0 do_readv_writev
3006f0a4 l     F .vmlinux	0000025c do_sendfile
00000000 l    df *ABS*	00000000 file_table.c
3006f48c l     F .vmlinux	0000001c file_free_rcu
3006f4a8 l     F .vmlinux	0000000c get_nr_files
306136f8 l     O .bss	00000008 nr_files
306136f4 l     O .bss	00000004 old_max.0
00000000 l    df *ABS*	00000000 super.c
30613701 l     O .bss	00000000 unnamed_dev_lock
3006fa1c l     F .vmlinux	00000010 put_super
30613704 l     O .bss	0000004c default_op.1
30613750 l     O .bss	00000000 __key.2
30613750 l     O .bss	00000000 __key.3
30613750 l     O .bss	00000000 __key.4
30613750 l     O .bss	00000000 __key.5
30613750 l     O .bss	00000000 __key.6
30613750 l     O .bss	00000000 __key.7
30257ecc l     O .vmlinux	0000000c mutex.0
30070508 l     F .vmlinux	0000009c do_emergency_remount
30613750 l     O .bss	00000010 unnamed_dev_idr
300706b0 l     F .vmlinux	00000014 set_bdev_super
300706c4 l     F .vmlinux	00000014 test_bdev_super
300706d8 l     F .vmlinux	00000008 bdev_uevent
300708f4 l     F .vmlinux	00000008 compare_single
00000000 l    df *ABS*	00000000 char_dev.c
30257ef4 l     O .vmlinux	0000000c chrdevs_lock
30257f00 l     O .vmlinux	0000000c ktype_cdev_default
300711d8 l     F .vmlinux	00000010 cdev_default_release
30613760 l     O .bss	00000000 cdev_lock
30257f0c l     O .vmlinux	0000000c ktype_cdev_dynamic
300711e8 l     F .vmlinux	00000018 cdev_dynamic_release
30613764 l     O .bss	000003fc chrdevs
30070b64 l     F .vmlinux	000001d4 __register_chrdev_region
30070d38 l     F .vmlinux	000000c8 __unregister_chrdev_region
30070f60 l     F .vmlinux	00000014 cdev_get
30613760 l     O .bss	00000004 cdev_map
300710c0 l     F .vmlinux	00000048 cdev_purge
30071108 l     F .vmlinux	00000008 exact_match
30071110 l     F .vmlinux	0000001c exact_lock
30071374 l     F .vmlinux	00000008 base_probe
00000000 l    df *ABS*	00000000 stat.c
30071550 l     F .vmlinux	000001d0 cp_new_stat
30071898 l     F .vmlinux	00000138 cp_new_stat64
00000000 l    df *ABS*	00000000 exec.c
30613b64 l     O .bss	00000000 binfmt_lock
30613b68 l     O .bss	00000004 formats
30071dd0 l     F .vmlinux	00000080 count
30071e50 l     F .vmlinux	00000338 copy_strings
300730ac l     F .vmlinux	00000074 zap_process
00000000 l    df *ABS*	00000000 pipe.c
302ba3ac l     O .vmlinux	00000004 __initcall_init_pipe_fs5
30286398 l     F .vmlinux	00000054 init_pipe_fs
30073bc4 l     F .vmlinux	00000468 pipe_read
3007402c l     F .vmlinux	00000510 pipe_write
300745f0 l     F .vmlinux	000000d0 pipe_poll
3007454c l     F .vmlinux	000000a4 pipe_ioctl
30074840 l     F .vmlinux	00000064 pipe_rdwr_open
30074a50 l     F .vmlinux	00000030 pipe_rdwr_release
30074768 l     F .vmlinux	00000078 pipe_rdwr_fasync
3007453c l     F .vmlinux	00000008 bad_pipe_r
30074810 l     F .vmlinux	00000030 pipe_write_open
30074a2c l     F .vmlinux	00000024 pipe_write_release
30074714 l     F .vmlinux	00000054 pipe_write_fasync
30074544 l     F .vmlinux	00000008 bad_pipe_w
300747e0 l     F .vmlinux	00000030 pipe_read_open
30074a08 l     F .vmlinux	00000024 pipe_read_release
300746c0 l     F .vmlinux	00000054 pipe_read_fasync
30226dd4 l     O .vmlinux	0000001c anon_pipe_buf_ops
30073988 l     F .vmlinux	0000005c anon_pipe_buf_release
30257f98 l     O .vmlinux	00000020 pipe_fs_type
30074dcc l     F .vmlinux	00000024 pipefs_get_sb
30226df0 l     O .vmlinux	0000006c read_pipe_fops
30226e5c l     O .vmlinux	0000006c write_pipe_fops
30257fb8 l     O .vmlinux	00000018 pipefs_dentry_operations
30074a80 l     F .vmlinux	00000014 pipefs_delete_dentry
30226ec8 l     O .vmlinux	0000006c rdwr_pipe_fops
30073814 l     F .vmlinux	000000d0 pipe_iov_copy_from_user
300738e4 l     F .vmlinux	000000a4 iov_fault_in_pages_read
30074970 l     F .vmlinux	00000098 pipe_release
30613b6c l     O .bss	00000004 pipe_mnt
00000000 l    df *ABS*	00000000 namei.c
30075314 l     F .vmlinux	000000b0 __follow_mount
300753c4 l     F .vmlinux	000000a8 follow_mount
300754e8 l     F .vmlinux	000001e8 do_lookup
300756e8 l     F .vmlinux	00000154 __emul_lookup_dentry
3007583c l     F .vmlinux	00000ef8 __link_path_walk
30076838 l     F .vmlinux	00000208 do_path_lookup
30076b1c l     F .vmlinux	00000088 __path_lookup_intent_open
30076c14 l     F .vmlinux	00000168 __lookup_hash
30076d7c l     F .vmlinux	00000020 lookup_hash
30076eac l     F .vmlinux	0000013c may_delete
30078178 l     F .vmlinux	000000ec do_rmdir
30078338 l     F .vmlinux	00000140 do_unlinkat
30079110 l     F .vmlinux	000000e4 page_getlink
00000000 l    df *ABS*	00000000 fcntl.c
302ba40c l     O .vmlinux	00000004 __initcall_fasync_init6
302863ec l     F .vmlinux	00000034 fasync_init
30613b70 l     O .bss	00000000 fasync_lock
30226f98 l     O .vmlinux	00000018 band_table
30079574 l     F .vmlinux	00000130 dupfd
300797e8 l     F .vmlinux	00000064 f_modown
30079908 l     F .vmlinux	00000320 do_fcntl
30613b70 l     O .bss	00000004 fasync_cache
00000000 l    df *ABS*	00000000 ioctl.c
3007a0a0 l     F .vmlinux	00000078 do_ioctl
00000000 l    df *ABS*	00000000 readdir.c
3007a5cc l     F .vmlinux	000000f4 fillonedir
3007a71c l     F .vmlinux	00000154 filldir
3007a934 l     F .vmlinux	00000154 filldir64
00000000 l    df *ABS*	00000000 select.c
3007abf4 l     F .vmlinux	000000f4 __pollwait
3007ab4c l     F .vmlinux	00000020 free_poll_entry
3007b144 l     F .vmlinux	0000033c core_sys_select
00000000 l    df *ABS*	00000000 fifo.c
3007c130 l     F .vmlinux	000002b4 fifo_open
3007c0d0 l     F .vmlinux	00000040 wait_for_partner
3007c110 l     F .vmlinux	00000020 wake_up_partner
00000000 l    df *ABS*	00000000 locks.c
302ba358 l     O .vmlinux	00000004 __initcall_filelock_init1
30286420 l     F .vmlinux	00000038 filelock_init
30257fd8 l     O .vmlinux	00000008 file_lock_list
30257fe0 l     O .vmlinux	00000008 blocked_list
30257fe8 l     O .vmlinux	0000001c lease_manager_ops
3007c9b4 l     F .vmlinux	0000002c lease_release_private_callback
3007c994 l     F .vmlinux	00000020 lease_break_callback
3007c9e0 l     F .vmlinux	00000018 lease_mylease_callback
3007c440 l     F .vmlinux	0000001c locks_alloc_lock
30613b74 l     O .bss	00000004 filelock_cache
3007c45c l     F .vmlinux	00000078 locks_release_private
3007c4d4 l     F .vmlinux	00000054 locks_free_lock
3007c588 l     F .vmlinux	00000028 init_once
3007c5b0 l     F .vmlinux	00000084 locks_copy_private
3007c634 l     F .vmlinux	00000040 __locks_copy_lock
3007c6b0 l     F .vmlinux	00000024 assign_type
3007c6d4 l     F .vmlinux	00000140 flock_to_posix_lock
3007c814 l     F .vmlinux	00000180 flock64_to_posix_lock
3007c9f8 l     F .vmlinux	0000007c lease_init
3007ca74 l     F .vmlinux	00000068 posix_same_owner
3007cadc l     F .vmlinux	00000040 __locks_delete_block
3007cb1c l     F .vmlinux	00000010 locks_delete_block
3007cb2c l     F .vmlinux	00000060 locks_insert_block
3007cb8c l     F .vmlinux	00000080 locks_wake_up_blocks
3007cc0c l     F .vmlinux	00000064 locks_insert_lock
3007cc70 l     F .vmlinux	000000b4 locks_delete_lock
3007cd24 l     F .vmlinux	0000002c locks_conflict
3007cd50 l     F .vmlinux	000000a4 posix_locks_conflict
3007ce74 l     F .vmlinux	000005c8 __posix_lock_file_conf
3007d764 l     F .vmlinux	000000bc time_out_leases
3007dc38 l     F .vmlinux	000001ec __setlease
3007f06c l     F .vmlinux	000003b0 lock_get_status
3007f41c l     F .vmlinux	00000070 move_lock_status
00000000 l    df *ABS*	00000000 dcache.c
302ba084 l     O .vmlinux	0000000c __setup_set_dhash_entries
302afcc0 l     O .vmlinux	0000000f __setup_str_set_dhash_entries
30286458 l     F .vmlinux	00000038 set_dhash_entries
30258020 l     O .vmlinux	00000008 dentry_unused
30613b7c l     O .bss	00000004 rename_lock
3007f794 l     F .vmlinux	00000044 __d_free
30613b88 l     O .bss	00000004 dentry_cache
3007f7d8 l     F .vmlinux	00000014 d_callback
3007f7ec l     F .vmlinux	0000005c d_free
3007f848 l     F .vmlinux	000000ac dentry_iput
3007fafc l     F .vmlinux	00000138 __d_find_alias
3007fd40 l     F .vmlinux	000000b4 prune_one_dentry
3007fdf4 l     F .vmlinux	000001c4 prune_dcache
300800d0 l     F .vmlinux	000002d0 shrink_dcache_for_umount_subtree
30080678 l     F .vmlinux	0000004c shrink_dcache_memory
3008089c l     F .vmlinux	000000d8 __d_instantiate_unique
3022701c l     O .vmlinux	0000000c name.1
30227028 l     O .vmlinux	0000000c anonstring.0
30613b90 l     O .bss	00000004 d_hash_shift
30613b8c l     O .bss	00000004 d_hash_mask
30613b94 l     O .bss	00000004 dentry_hashtable
30080ee0 l     F .vmlinux	00000034 __d_rehash
30080f14 l     F .vmlinux	0000005c _d_rehash
30080f80 l     F .vmlinux	00000088 switch_names
30081008 l     F .vmlinux	000001f0 d_move_locked
300815bc l     F .vmlinux	00000154 __d_path
302afcd0 l     O .vmlinux	00000004 dhash_entries
00000000 l    df *ABS*	00000000 inode.c
302ba090 l     O .vmlinux	0000000c __setup_set_ihash_entries
302afcd8 l     O .vmlinux	0000000f __setup_str_set_ihash_entries
302866d4 l     F .vmlinux	00000038 set_ihash_entries
30258038 l     O .vmlinux	0000000c iprune_mutex
30613b9c l     O .bss	0000003c empty_aops.0
30613bd8 l     O .bss	00000054 empty_iops.1
30613c2c l     O .bss	0000006c empty_fops.2
30081ac0 l     F .vmlinux	0000012c alloc_inode
30613cc8 l     O .bss	00000004 inode_cachep
30613c98 l     O .bss	00000000 __key.5
30613c98 l     O .bss	00000000 __key.6
30613c98 l     O .bss	00000000 __key.7
30081d08 l     F .vmlinux	00000028 init_once
30613c98 l     O .bss	00000004 last_ino.4
30081f58 l     F .vmlinux	0000004c hash
30613cc0 l     O .bss	00000004 i_hash_shift
30613cbc l     O .bss	00000004 i_hash_mask
30613cc4 l     O .bss	00000004 inode_hashtable
300823dc l     F .vmlinux	000000a0 __wait_on_freeing_inode
3008247c l     F .vmlinux	0000007c find_inode_fast
300824f8 l     F .vmlinux	00000060 ifind_fast
30613c9c l     O .bss	00000004 counter.3
30082738 l     F .vmlinux	00000088 find_inode
300827c0 l     F .vmlinux	0000006c ifind
300829f4 l     F .vmlinux	000000f4 dispose_list
30082ae8 l     F .vmlinux	00000238 shrink_icache_memory
302afce8 l     O .vmlinux	00000004 ihash_entries
00000000 l    df *ABS*	00000000 attr.c
00000000 l    df *ABS*	00000000 bad_inode.c
30227034 l     O .vmlinux	00000054 bad_inode_ops
300838c0 l     F .vmlinux	00000008 bad_inode_create
300838c8 l     F .vmlinux	00000008 bad_inode_lookup
300838d0 l     F .vmlinux	00000008 bad_inode_link
300838d8 l     F .vmlinux	00000008 bad_inode_unlink
300838e0 l     F .vmlinux	00000008 bad_inode_symlink
300838e8 l     F .vmlinux	00000008 bad_inode_mkdir
300838f0 l     F .vmlinux	00000008 bad_inode_rmdir
300838f8 l     F .vmlinux	00000008 bad_inode_mknod
30083900 l     F .vmlinux	00000008 bad_inode_rename
30083908 l     F .vmlinux	00000008 bad_inode_readlink
30083910 l     F .vmlinux	00000008 bad_inode_permission
30083920 l     F .vmlinux	00000008 bad_inode_setattr
30083918 l     F .vmlinux	00000008 bad_inode_getattr
30083928 l     F .vmlinux	00000008 bad_inode_setxattr
30083930 l     F .vmlinux	00000008 bad_inode_getxattr
30083938 l     F .vmlinux	00000008 bad_inode_listxattr
30083940 l     F .vmlinux	00000008 bad_inode_removexattr
30227088 l     O .vmlinux	0000006c bad_file_ops
300837ec l     F .vmlinux	0000000c bad_file_llseek
300837f8 l     F .vmlinux	00000008 bad_file_read
30083800 l     F .vmlinux	00000008 bad_file_write
30083808 l     F .vmlinux	00000008 bad_file_aio_read
30083810 l     F .vmlinux	00000008 bad_file_aio_write
30083818 l     F .vmlinux	00000008 bad_file_readdir
30083820 l     F .vmlinux	00000008 bad_file_poll
30083828 l     F .vmlinux	00000008 bad_file_ioctl
30083830 l     F .vmlinux	00000008 bad_file_unlocked_ioctl
30083838 l     F .vmlinux	00000008 bad_file_compat_ioctl
30083840 l     F .vmlinux	00000008 bad_file_mmap
30083848 l     F .vmlinux	00000008 bad_file_open
30083850 l     F .vmlinux	00000008 bad_file_flush
30083858 l     F .vmlinux	00000008 bad_file_release
30083860 l     F .vmlinux	00000008 bad_file_fsync
30083868 l     F .vmlinux	00000008 bad_file_aio_fsync
30083870 l     F .vmlinux	00000008 bad_file_fasync
30083878 l     F .vmlinux	00000008 bad_file_lock
30083880 l     F .vmlinux	00000008 bad_file_sendfile
30083888 l     F .vmlinux	00000008 bad_file_sendpage
30083890 l     F .vmlinux	00000008 bad_file_get_unmapped_area
30083898 l     F .vmlinux	00000008 bad_file_check_flags
300838a0 l     F .vmlinux	00000008 bad_file_dir_notify
300838a8 l     F .vmlinux	00000008 bad_file_flock
300838b0 l     F .vmlinux	00000008 bad_file_splice_write
300838b8 l     F .vmlinux	00000008 bad_file_splice_read
00000000 l    df *ABS*	00000000 file.c
300839bc l     F .vmlinux	00000088 free_fdtable_work
30613ccc l     O .bss	00000014 per_cpu__fdtable_defer_list
00000000 l    df *ABS*	00000000 filesystems.c
30613ce0 l     O .bss	00000000 file_systems_lock
30083dc0 l     F .vmlinux	00000050 find_filesystem
30613ce0 l     O .bss	00000004 file_systems
00000000 l    df *ABS*	00000000 namespace.c
30084798 l     F .vmlinux	0000006c m_start
30084838 l     F .vmlinux	00000018 m_stop
30084804 l     F .vmlinux	00000034 m_next
300849ec l     F .vmlinux	00000104 show_vfsstat
30084850 l     F .vmlinux	0000019c show_vfsmnt
30613cf8 l     O .bss	00000004 mnt_cache
30613cf4 l     O .bss	00000004 hash_bits
30613cf0 l     O .bss	00000004 hash_mask
30613cec l     O .bss	00000004 mount_hashtable
30084290 l     F .vmlinux	00000048 touch_mnt_namespace
30613ce8 l     O .bss	00000004 event
300842d8 l     F .vmlinux	00000064 detach_mnt
30084398 l     F .vmlinux	00000090 attach_mnt
30084428 l     F .vmlinux	00000104 commit_tree
3008452c l     F .vmlinux	00000048 next_mnt
30084574 l     F .vmlinux	00000168 clone_mnt
30613cfc l     O .bss	0000000c namespace_sem
302580c0 l     O .vmlinux	00000020 fs_info.0
302580e0 l     O .vmlinux	00000038 mnt_info.1
3008515c l     F .vmlinux	00000144 attach_recursive_mnt
300852a0 l     F .vmlinux	000000e4 graft_tree
300854a4 l     F .vmlinux	00000160 expire_mount_list
302270f8 l     O .vmlinux	00000009 __func__.2
30613ce5 l     O .bss	00000000 __key.3
00000000 l    df *ABS*	00000000 aio.c
302ba410 l     O .vmlinux	00000004 __initcall_aio_setup6
30286ad0 l     F .vmlinux	00000078 aio_setup
3025811c l     O .vmlinux	00000010 fput_work
30086cac l     F .vmlinux	00000148 aio_fput_routine
3025812c l     O .vmlinux	00000008 fput_head
30613d08 l     O .bss	00000000 fput_lock
30613d08 l     O .bss	00000000 aio_nr_lock
30613d0c l     O .bss	00000004 kiocb_cachep
30613d10 l     O .bss	00000004 kioctx_cachep
30613d14 l     O .bss	00000004 aio_wq
300867c8 l     F .vmlinux	000000b4 aio_free_ring
3008687c l     F .vmlinux	000000a0 aio_cancel_all
3008691c l     F .vmlinux	000000bc wait_for_all_aios
30086ba0 l     F .vmlinux	0000010c __aio_get_req
30086df4 l     F .vmlinux	00000160 __aio_put_req
30086fdc l     F .vmlinux	0000003c aio_queue_work
30087190 l     F .vmlinux	0000011c aio_run_iocb
300872ac l     F .vmlinux	000000ac __aio_run_iocbs
30087358 l     F .vmlinux	000000dc aio_kick_handler
3008750c l     F .vmlinux	000000c0 aio_read_evt
300875cc l     F .vmlinux	0000001c timeout_func
300875e8 l     F .vmlinux	000000ec io_destroy
30087a80 l     F .vmlinux	0000022c aio_rw_vect_retry
30087cac l     F .vmlinux	00000038 aio_fdsync
30087ce4 l     F .vmlinux	00000038 aio_fsync
30087d1c l     F .vmlinux	0000004c aio_setup_vectored_rw
30087d68 l     F .vmlinux	0000002c aio_setup_single_vector
30087d94 l     F .vmlinux	00000030 aio_wake_function
00000000 l    df *ABS*	00000000 seq_file.c
30613d18 l     O .bss	00000000 __key.0
300890ac l     F .vmlinux	00000020 single_start
300890cc l     F .vmlinux	00000018 single_next
300890e4 l     F .vmlinux	00000008 single_stop
00000000 l    df *ABS*	00000000 xattr.c
30089254 l     F .vmlinux	00000310 xattr_permission
300898d8 l     F .vmlinux	0000013c setxattr
30089b00 l     F .vmlinux	0000015c getxattr
30089d3c l     F .vmlinux	000000e4 listxattr
30089ef4 l     F .vmlinux	00000098 removexattr
3008a054 l     F .vmlinux	0000009c xattr_resolve_name
00000000 l    df *ABS*	00000000 libfs.c
30613d18 l     O .bss	00000000 pin_fs_lock
302271c8 l     O .vmlinux	0000004c simple_super_operations
3008a31c l     F .vmlinux	00000008 simple_delete_dentry
30258134 l     O .vmlinux	00000018 simple_dentry_operations.3
3025814c l     O .vmlinux	0000000c cursor_name.2
30613d18 l     O .bss	00000000 simple_transaction_lock.1
30613d18 l     O .bss	00000000 __key.0
00000000 l    df *ABS*	00000000 fs-writeback.c
30227218 l     O .vmlinux	00000019 __func__.0
3008b3d4 l     F .vmlinux	0000038c __writeback_single_inode
3008b780 l     F .vmlinux	00000034 set_sb_syncing
3008b97c l     F .vmlinux	000002e8 sync_sb_inodes
3008bd04 l     F .vmlinux	000000b0 __sync_inodes
00000000 l    df *ABS*	00000000 pnode.c
3008c08c l     F .vmlinux	00000074 propagation_next
00000000 l    df *ABS*	00000000 drop_caches.c
00000000 l    df *ABS*	00000000 splice.c
30227238 l     O .vmlinux	0000001c user_page_pipe_buf_ops
3008c6d8 l     F .vmlinux	00000020 page_cache_pipe_buf_release
3008c784 l     F .vmlinux	00000028 user_page_pipe_buf_steal
30227254 l     O .vmlinux	0000001c page_cache_pipe_buf_ops
3008c6f8 l     F .vmlinux	0000008c page_cache_pipe_buf_pin
3008c5d8 l     F .vmlinux	00000100 page_cache_pipe_buf_steal
30227270 l     O .vmlinux	0000001a __func__.0
3008c7ac l     F .vmlinux	00000280 splice_to_pipe
3008cf34 l     F .vmlinux	00000090 pipe_to_sendpage
3008cfc4 l     F .vmlinux	000002a8 pipe_to_file
3008d748 l     F .vmlinux	00000088 do_splice_from
3008d7d0 l     F .vmlinux	000000ec do_splice_to
00000000 l    df *ABS*	00000000 sync.c
3008e3ac l     F .vmlinux	00000080 do_sync
3008e554 l     F .vmlinux	0000003c __do_fsync
00000000 l    df *ABS*	00000000 utimes.c
00000000 l    df *ABS*	00000000 stack.c
00000000 l    df *ABS*	00000000 buffer.c
30613d1c l     O .bss	00000008 per_cpu__bh_accounting
30613d24 l     O .bss	00000020 per_cpu__bh_lrus
30227290 l     O .vmlinux	00000009 __func__.8
3008ed08 l     F .vmlinux	00000064 sync_buffer
3008ed88 l     F .vmlinux	00000038 buffer_io_error
3008f040 l     F .vmlinux	0000010c __find_get_block_slow
3008f14c l     F .vmlinux	00000078 free_more_memory
3008f1c4 l     F .vmlinux	00000118 end_buffer_async_read
3008f2dc l     F .vmlinux	00000128 end_buffer_async_write
302272a0 l     O .vmlinux	00000015 __func__.1
3008f7a8 l     F .vmlinux	0000008c init_page_buffers
3008fcd4 l     F .vmlinux	000000d8 __block_commit_write
3008fdac l     F .vmlinux	00000148 __generic_cont_expand
30090008 l     F .vmlinux	00000038 end_buffer_read_nobh
300901f8 l     F .vmlinux	00000070 end_bio_bh_io_sync
302272b8 l     O .vmlinux	00000012 __func__.2
30090944 l     F .vmlinux	00000150 drop_buffers
30613d44 l     O .bss	00000004 msg_count.0
30090b68 l     F .vmlinux	00000050 recalc_bh_state
30613d50 l     O .bss	00000004 max_buffer_heads
30613d4c l     O .bss	00000004 bh_cachep
302272d0 l     O .vmlinux	00000018 __func__.3
30091260 l     F .vmlinux	000003e0 __block_write_full_page
302272e8 l     O .vmlinux	00000014 __func__.4
30227300 l     O .vmlinux	00000016 __func__.5
30091a2c l     F .vmlinux	000004a4 __block_prepare_write
30227318 l     O .vmlinux	00000015 __func__.6
30227330 l     O .vmlinux	0000000d __func__.7
300927d0 l     F .vmlinux	00000034 init_buffer_head
00000000 l    df *ABS*	00000000 bio.c
302ba388 l     O .vmlinux	00000004 __initcall_init_bio4
30286bb4 l     F .vmlinux	00000144 init_bio
30258158 l     O .vmlinux	00000048 bvec_slabs
302581a0 l     O .vmlinux	00000010 bio_dirty_work
3009385c l     F .vmlinux	00000054 bio_dirty_fn
30613d54 l     O .bss	00000000 bio_dirty_lock
3009287c l     F .vmlinux	00000018 bio_fs_destructor
30613d5c l     O .bss	00000004 fs_bio_set
30092cd8 l     F .vmlinux	00000264 __bio_add_page
30092f8c l     F .vmlinux	00000018 bio_free_map_data
30093658 l     F .vmlinux	0000002c bio_map_kern_endio
30613d60 l     O .bss	00000004 bio_dirty_list
30227340 l     O .vmlinux	0000000a __func__.0
30093a64 l     F .vmlinux	0000003c bio_pair_end_1
30093aa0 l     F .vmlinux	00000040 bio_pair_end_2
30613d58 l     O .bss	00000004 bio_slab
00000000 l    df *ABS*	00000000 block_dev.c
300940a8 l     F .vmlinux	000000e4 block_llseek
30095034 l     F .vmlinux	0000002c block_ioctl
30094f74 l     F .vmlinux	00000084 blkdev_open
30094ff8 l     F .vmlinux	0000003c blkdev_close
3009418c l     F .vmlinux	0000001c block_fsync
30094030 l     F .vmlinux	0000001c blkdev_writepage
3009404c l     F .vmlinux	0000001c blkdev_readpage
30094068 l     F .vmlinux	00000024 blkdev_prepare_write
3009408c l     F .vmlinux	0000001c blkdev_commit_write
30093fe0 l     F .vmlinux	00000050 blkdev_direct_IO
30613d64 l     O .bss	00000000 bdev_lock
302581b0 l     O .vmlinux	00000008 all_bdevs
302581b8 l     O .vmlinux	00000020 bd_type
300942dc l     F .vmlinux	00000028 bd_get_sb
302273f8 l     O .vmlinux	0000004c bdev_sops
300941a8 l     F .vmlinux	0000002c bdev_alloc_inode
300941d4 l     F .vmlinux	00000020 bdev_destroy_inode
3009427c l     F .vmlinux	00000060 bdev_clear_inode
30093d44 l     F .vmlinux	00000048 max_block
30093d8c l     F .vmlinux	00000028 kill_bdev
30093ee8 l     F .vmlinux	0000004c blkdev_get_block
30093f34 l     F .vmlinux	000000ac blkdev_get_blocks
30613d68 l     O .bss	00000004 bdev_cachep
30613d64 l     O .bss	00000000 __key.0
300941f4 l     F .vmlinux	00000088 init_once
30613d6c l     O .bss	00000004 bd_mnt
30094304 l     F .vmlinux	00000018 bdev_test
3009431c l     F .vmlinux	00000010 bdev_set
3009447c l     F .vmlinux	0000008c bd_acquire
3009463c l     F .vmlinux	00000034 add_symlink
30094670 l     F .vmlinux	00000038 del_symlink
300946a8 l     F .vmlinux	00000010 free_bd_holder
30094a80 l     F .vmlinux	00000134 __blkdev_put
30094bb4 l     F .vmlinux	000002ec do_open
30094ea0 l     F .vmlinux	00000058 __blkdev_get
00000000 l    df *ABS*	00000000 direct-io.c
300952e8 l     F .vmlinux	0000017c dio_get_page
30095464 l     F .vmlinux	00000120 dio_complete
30095584 l     F .vmlinux	0000007c dio_bio_end_io
30095600 l     F .vmlinux	00000064 dio_bio_submit
30095664 l     F .vmlinux	00000068 dio_cleanup
300956cc l     F .vmlinux	000000e4 dio_bio_complete
300957b0 l     F .vmlinux	000000bc dio_bio_end_aio
3009586c l     F .vmlinux	0000010c dio_new_bio
30095978 l     F .vmlinux	000000a4 dio_bio_add_page
30095a1c l     F .vmlinux	000000c8 dio_send_cur_page
30095ae4 l     F .vmlinux	000000e8 submit_page_section
30095bcc l     F .vmlinux	000000a0 dio_zero_block
00000000 l    df *ABS*	00000000 mpage.c
3009682c l     F .vmlinux	00000098 mpage_end_io_read
300968c4 l     F .vmlinux	000000c4 mpage_end_io_write
30096988 l     F .vmlinux	00000034 mpage_bio_submit
300969bc l     F .vmlinux	0000007c mpage_alloc
30096a38 l     F .vmlinux	0000048c do_mpage_readpage
30097078 l     F .vmlinux	0000053c __mpage_writepage
00000000 l    df *ABS*	00000000 ioprio.c
30097a60 l     F .vmlinux	00000064 set_task_ioprio
30097ce8 l     F .vmlinux	00000008 get_task_ioprio
00000000 l    df *ABS*	00000000 inotify.c
302ba414 l     O .vmlinux	00000004 __initcall_inotify_setup6
30286d84 l     F .vmlinux	0000001c inotify_setup
30227448 l     O .vmlinux	00000017 __func__.0
30097fe0 l     F .vmlinux	00000134 set_dentry_child_flags
30098114 l     F .vmlinux	00000038 inode_find_handle
3009814c l     F .vmlinux	0000008c remove_watch_no_event
30227460 l     O .vmlinux	00000016 __func__.2
30613d70 l     O .bss	00000004 inotify_cookie
30613d70 l     O .bss	00000000 __key.1
00000000 l    df *ABS*	00000000 inotify_user.c
302ba418 l     O .vmlinux	00000004 __initcall_inotify_user_setup6
30286da0 l     F .vmlinux	000000d4 inotify_user_setup
30613d8c l     O .bss	00000004 zero
30258288 l     O .vmlinux	00000020 inotify_fs_type
30099524 l     F .vmlinux	00000024 inotify_get_sb
30227478 l     O .vmlinux	0000006c inotify_fops
30098e2c l     F .vmlinux	00000214 inotify_read
30098db0 l     F .vmlinux	0000007c inotify_poll
300990d4 l     F .vmlinux	00000054 inotify_ioctl
30099040 l     F .vmlinux	00000094 inotify_release
302274e4 l     O .vmlinux	00000008 inotify_user_ops
30098bec l     F .vmlinux	00000158 inotify_dev_queue_event
30098a7c l     F .vmlinux	00000078 free_inotify_user_watch
30613d74 l     O .bss	00000004 watch_cachep
30098af4 l     F .vmlinux	000000f8 kernel_event
30613d78 l     O .bss	00000004 event_cachep
30098d44 l     F .vmlinux	0000006c remove_kevent
30613d74 l     O .bss	00000000 __key.0
30613d74 l     O .bss	00000000 __key.1
30613d7c l     O .bss	00000004 inotify_mnt
00000000 l    df *ABS*	00000000 binfmt_script.c
302ba35c l     O .vmlinux	00000004 __initcall_init_script_binfmt1
30286e74 l     F .vmlinux	00000018 init_script_binfmt
302582a8 l     O .vmlinux	0000001c script_format
30099548 l     F .vmlinux	000002d8 load_script
00000000 l    df *ABS*	00000000 binfmt_elf.c
302ba360 l     O .vmlinux	00000004 __initcall_init_elf_binfmt1
30286e8c l     F .vmlinux	00000018 init_elf_binfmt
302582c4 l     O .vmlinux	0000001c elf_format
300999a4 l     F .vmlinux	000015b8 load_elf_binary
3009af5c l     F .vmlinux	00000240 load_elf_library
3009b628 l     F .vmlinux	00000cb4 elf_core_dump
30099820 l     F .vmlinux	0000007c set_brk
3009989c l     F .vmlinux	00000068 padzero
30099904 l     F .vmlinux	000000a0 elf_map
3009b19c l     F .vmlinux	00000034 dump_write
3009b1d0 l     F .vmlinux	000000fc dump_seek
3009b2cc l     F .vmlinux	00000060 maydump
3009b32c l     F .vmlinux	0000002c notesize
302274f0 l     O .vmlinux	00000004 buf.0
3009b358 l     F .vmlinux	000000a8 alignfile
3009b400 l     F .vmlinux	000000e4 writenote
3009b4e4 l     F .vmlinux	00000014 fill_note
3009b4f8 l     F .vmlinux	000000ec fill_prstatus
3009b5e4 l     F .vmlinux	00000020 first_vma
3009b604 l     F .vmlinux	00000024 next_vma
00000000 l    df *ABS*	00000000 mmu.c
00000000 l    df *ABS*	00000000 task_mmu.c
3009cdac l     F .vmlinux	00000018 smaps_open
3009cd94 l     F .vmlinux	00000018 maps_open
302582e0 l     O .vmlinux	00000010 proc_pid_maps_op
3009cadc l     F .vmlinux	0000014c m_start
3009ccd8 l     F .vmlinux	00000050 m_stop
3009cc68 l     F .vmlinux	00000070 m_next
3009c878 l     F .vmlinux	00000014 show_map
302582f0 l     O .vmlinux	00000010 proc_pid_smaps_op
3009c88c l     F .vmlinux	00000250 show_smap
3009c5f0 l     F .vmlinux	0000003c pad_len_spaces
3009c62c l     F .vmlinux	0000024c show_map_internal
3009cc28 l     F .vmlinux	00000040 vma_stop
3009cd28 l     F .vmlinux	0000006c do_maps_open
00000000 l    df *ABS*	00000000 inode.c
302275d0 l     O .vmlinux	0000004c proc_sops
3009cea8 l     F .vmlinux	00000060 proc_alloc_inode
3009cf08 l     F .vmlinux	0000001c proc_destroy_inode
3009ce7c l     F .vmlinux	0000002c proc_read_inode
3009ce38 l     F .vmlinux	00000044 proc_delete_inode
3009cf4c l     F .vmlinux	00000014 proc_remount
3009cdc4 l     F .vmlinux	00000074 de_put
30613d94 l     O .bss	00000004 proc_inode_cachep
3009cf24 l     F .vmlinux	00000028 init_once
30227620 l     O .vmlinux	0000000f __func__.0
00000000 l    df *ABS*	00000000 root.c
3022769c l     O .vmlinux	00000054 proc_root_inode_operations
30227630 l     O .vmlinux	0000006c proc_root_operations
3009d1fc l     F .vmlinux	00000050 proc_root_readdir
3009d1cc l     F .vmlinux	00000030 proc_root_lookup
3009d1a0 l     F .vmlinux	0000002c proc_root_getattr
30258358 l     O .vmlinux	00000020 proc_fs_type
3009d144 l     F .vmlinux	0000005c proc_get_sb
00000000 l    df *ABS*	00000000 base.c
30258378 l     O .vmlinux	00000018 proc_base_stuff
302276f0 l     O .vmlinux	00000054 proc_self_inode_operations
3009eea8 l     F .vmlinux	0000003c proc_self_readlink
3009eee4 l     F .vmlinux	00000034 proc_self_follow_link
30258390 l     O .vmlinux	00000018 proc_base_dentry_operations
3009ef18 l     F .vmlinux	00000098 proc_base_revalidate
3009e390 l     F .vmlinux	00000018 pid_delete_dentry
302583a8 l     O .vmlinux	00000018 pid_dentry_operations
3009e290 l     F .vmlinux	00000100 pid_revalidate
30227744 l     O .vmlinux	0000006c proc_tgid_base_operations
3009f0b4 l     F .vmlinux	0000001c proc_tgid_base_readdir
302277b0 l     O .vmlinux	00000054 proc_tgid_base_inode_operations
3009f0d0 l     F .vmlinux	0000001c proc_tgid_base_lookup
3009d6a4 l     F .vmlinux	00000050 proc_setattr
3009e21c l     F .vmlinux	00000074 pid_getattr
302583c0 l     O .vmlinux	000001b0 tgid_base_stuff
30227ba0 l     O .vmlinux	00000054 proc_task_inode_operations
30227b34 l     O .vmlinux	0000006c proc_task_operations
30227ae0 l     O .vmlinux	00000054 proc_fd_inode_operations
30227a74 l     O .vmlinux	0000006c proc_fd_operations
30227a08 l     O .vmlinux	0000006c proc_info_file_operations
3009d42c l     F .vmlinux	00000088 proc_pid_environ
3009d5b0 l     F .vmlinux	00000070 proc_pid_auxv
3009d4b4 l     F .vmlinux	000000fc proc_pid_cmdline
3022799c l     O .vmlinux	0000006c proc_mem_operations
30227948 l     O .vmlinux	00000054 proc_pid_link_inode_operations
3009d2ac l     F .vmlinux	000000c0 proc_cwd_link
3009d36c l     F .vmlinux	000000c0 proc_root_link
302278dc l     O .vmlinux	0000006c proc_mounts_operations
30227870 l     O .vmlinux	0000006c proc_mountstats_operations
3009d620 l     F .vmlinux	00000034 proc_oom_score
30227804 l     O .vmlinux	0000006c proc_oom_adjust_operations
3009dd10 l     F .vmlinux	0000013c oom_adjust_read
3009de4c l     F .vmlinux	0000018c oom_adjust_write
3009d8c4 l     F .vmlinux	000000c0 mountstats_open
3009d810 l     F .vmlinux	00000044 mounts_release
3009d854 l     F .vmlinux	00000070 mounts_poll
3009d6f4 l     F .vmlinux	0000011c mounts_open
3009e028 l     F .vmlinux	0000011c proc_pid_readlink
3009dfd8 l     F .vmlinux	00000050 proc_pid_follow_link
3009dcd0 l     F .vmlinux	00000040 mem_lseek
3009da6c l     F .vmlinux	00000264 mem_read
3009da58 l     F .vmlinux	00000014 mem_open
3009d984 l     F .vmlinux	000000d4 proc_info_read
3009e974 l     F .vmlinux	000001f4 proc_readfd
3009e8f8 l     F .vmlinux	0000007c proc_lookupfd
3009f830 l     F .vmlinux	00000368 proc_task_readdir
3009f740 l     F .vmlinux	000000f0 proc_task_lookup
3009fb98 l     F .vmlinux	0000006c proc_task_getattr
30227bf4 l     O .vmlinux	0000006c proc_tid_base_operations
3009f670 l     F .vmlinux	0000001c proc_tid_base_readdir
30227c60 l     O .vmlinux	00000054 proc_tid_base_inode_operations
3009f68c l     F .vmlinux	0000001c proc_tid_base_lookup
30258570 l     O .vmlinux	00000180 tid_base_stuff
302586f0 l     O .vmlinux	00000018 tid_fd_dentry_operations
3009e684 l     F .vmlinux	00000154 tid_fd_revalidate
30227cb4 l     O .vmlinux	00000054 proc_def_inode_operations
3009d24c l     F .vmlinux	00000028 get_fs_struct
3009d274 l     F .vmlinux	00000038 get_nr_threads
3009d654 l     F .vmlinux	00000050 proc_fd_access_allowed
3009e144 l     F .vmlinux	00000030 task_dumpable
3009e174 l     F .vmlinux	000000a8 proc_pid_make_inode
3009e3a8 l     F .vmlinux	00000158 proc_fill_cache
3009e500 l     F .vmlinux	00000088 name_to_int
3009e588 l     F .vmlinux	000000fc proc_fd_link
3009e7d8 l     F .vmlinux	00000120 proc_fd_instantiate
3009eb68 l     F .vmlinux	000000b8 proc_pident_instantiate
3009ec20 l     F .vmlinux	000000d0 proc_pident_lookup
3009ecf0 l     F .vmlinux	000001b8 proc_pident_readdir
3009efb0 l     F .vmlinux	00000104 proc_base_instantiate
3009f290 l     F .vmlinux	00000098 proc_pid_instantiate
3009f464 l     F .vmlinux	00000068 next_tgid
3009f6a8 l     F .vmlinux	00000098 proc_task_instantiate
00000000 l    df *ABS*	00000000 generic.c
30258708 l     O .vmlinux	00000018 proc_dentry_operations
300a012c l     F .vmlinux	00000008 proc_delete_dentry
30613db0 l     O .bss	00000010 proc_inum_idr
30613dc0 l     O .bss	00000000 proc_inum_lock
30227d08 l     O .vmlinux	00000054 proc_dir_inode_operations
3009ffe8 l     F .vmlinux	00000060 proc_notify_change
300a0048 l     F .vmlinux	00000040 proc_getattr
30227d5c l     O .vmlinux	0000006c proc_dir_operations
30227dc8 l     O .vmlinux	00000054 proc_file_inode_operations
30227e1c l     O .vmlinux	0000006c proc_file_operations
3009ff80 l     F .vmlinux	00000068 proc_file_lseek
3009fc38 l     F .vmlinux	00000308 proc_file_read
3009ff40 l     F .vmlinux	00000040 proc_file_write
30227e88 l     O .vmlinux	00000054 proc_link_inode_operations
300a0108 l     F .vmlinux	00000024 proc_follow_link
3009fc04 l     F .vmlinux	00000034 proc_match
300a0088 l     F .vmlinux	00000080 xlate_proc_name
300a0378 l     F .vmlinux	0000015c proc_register
300a04d4 l     F .vmlinux	000000c8 proc_create
30227ee0 l     O .vmlinux	00000012 __func__.0
00000000 l    df *ABS*	00000000 array.c
30258720 l     O .vmlinux	0000001c task_state_array
300a09dc l     F .vmlinux	000000f8 render_sigset_t
300a0ad4 l     F .vmlinux	0000007c collect_sigign_sigcatch
300a0f94 l     F .vmlinux	00000460 do_task_stat
00000000 l    df *ABS*	00000000 proc_tty.c
30227ef8 l     O .vmlinux	0000006c proc_tty_drivers_operations
300a186c l     F .vmlinux	0000001c tty_drivers_open
3025873c l     O .vmlinux	00000010 tty_drivers_op
300a17d8 l     F .vmlinux	00000058 t_start
300a1864 l     F .vmlinux	00000008 t_stop
300a1830 l     F .vmlinux	00000034 t_next
300a162c l     F .vmlinux	000001ac show_tty_driver
300a14a4 l     F .vmlinux	00000188 show_tty_range
300a1888 l     F .vmlinux	000000d4 tty_ldiscs_read_proc
30613dc4 l     O .bss	00000004 proc_tty_driver
30613dc0 l     O .bss	00000004 proc_tty_ldisc
00000000 l    df *ABS*	00000000 proc_misc.c
30227f64 l     O .vmlinux	0000006c proc_diskstats_operations
300a1f50 l     F .vmlinux	0000001c diskstats_open
30227fd0 l     O .vmlinux	0000006c proc_zoneinfo_file_operations
300a1d84 l     F .vmlinux	0000001c zoneinfo_open
3022803c l     O .vmlinux	0000006c proc_vmstat_file_operations
300a1f18 l     F .vmlinux	0000001c vmstat_open
302280a8 l     O .vmlinux	0000006c fragmentation_file_operations
300a1d68 l     F .vmlinux	0000001c fragmentation_open
30228114 l     O .vmlinux	0000006c proc_slabinfo_operations
300a1f6c l     F .vmlinux	0000001c slabinfo_open
30228180 l     O .vmlinux	0000006c proc_interrupts_operations
300a2428 l     F .vmlinux	0000001c interrupts_open
302281ec l     O .vmlinux	0000006c proc_stat_operations
300a2338 l     F .vmlinux	00000070 stat_open
30228258 l     O .vmlinux	0000006c proc_partitions_operations
300a1f34 l     F .vmlinux	0000001c partitions_open
302282c4 l     O .vmlinux	0000006c proc_cpuinfo_operations
300a1ddc l     F .vmlinux	0000001c cpuinfo_open
30228330 l     O .vmlinux	0000006c proc_devinfo_operations
300a1efc l     F .vmlinux	0000001c devinfo_open
3025874c l     O .vmlinux	00000010 devinfo_ops
300a1e7c l     F .vmlinux	00000030 devinfo_start
300a1ef4 l     F .vmlinux	00000008 devinfo_stop
300a1eac l     F .vmlinux	00000048 devinfo_next
300a1df8 l     F .vmlinux	00000084 devinfo_show
3025875c l     O .vmlinux	00000010 int_seq_ops
300a23a8 l     F .vmlinux	00000030 int_seq_start
300a2420 l     F .vmlinux	00000008 int_seq_stop
300a23d8 l     F .vmlinux	00000048 int_seq_next
300a1a0c l     F .vmlinux	0000003c proc_calc_metrics
300a1a48 l     F .vmlinux	000000c4 loadavg_read_proc
300a1b0c l     F .vmlinux	00000090 uptime_read_proc
300a1b9c l     F .vmlinux	000001cc meminfo_read_proc
300a1da0 l     F .vmlinux	0000003c version_read_proc
300a1f88 l     F .vmlinux	000003b0 show_stat
300a2444 l     F .vmlinux	00000018 filesystems_read_proc
300a245c l     F .vmlinux	00000028 cmdline_read_proc
300a2484 l     F .vmlinux	00000030 locks_read_proc
300a24b4 l     F .vmlinux	00000018 execdomains_read_proc
30613dc8 l     O .bss	00000004 p.0
3025876c l     O .vmlinux	00000048 simple_ones.1
00000000 l    df *ABS*	00000000 proc_sysctl.c
3022839c l     O .vmlinux	0000006c proc_sys_file_operations
300a27b0 l     F .vmlinux	00000094 proc_sys_read
300a2844 l     F .vmlinux	00000094 proc_sys_write
300a28d8 l     F .vmlinux	0000039c proc_sys_readdir
302587b4 l     O .vmlinux	00000054 proc_sys_inode_operations
300a2740 l     F .vmlinux	00000070 proc_sys_lookup
300a2c74 l     F .vmlinux	000000c0 proc_sys_permission
300a2d34 l     F .vmlinux	00000050 proc_sys_setattr
30258808 l     O .vmlinux	00000018 proc_sys_dentry_operations
300a2d84 l     F .vmlinux	0000003c proc_sys_revalidate
300a24f8 l     F .vmlinux	00000054 proc_sys_refresh_inode
300a254c l     F .vmlinux	00000084 proc_sys_make_inode
300a25d0 l     F .vmlinux	00000080 proc_sys_lookup_table_one
300a2650 l     F .vmlinux	0000007c proc_sys_lookup_table
300a26cc l     F .vmlinux	00000074 do_proc_sys_lookup
30613dd0 l     O .bss	00000004 proc_sys_root
00000000 l    df *ABS*	00000000 kcore.c
300a2eec l     F .vmlinux	00000730 read_kcore
300a2e08 l     F .vmlinux	0000001c open_kcore
30613dd4 l     O .bss	00000000 kclist_lock
30613dd4 l     O .bss	00000004 kclist
300a2e40 l     F .vmlinux	0000002c notesize
300a2e6c l     F .vmlinux	00000080 storenote
00000000 l    df *ABS*	00000000 kmsg.c
300a3654 l     F .vmlinux	00000048 kmsg_read
300a369c l     F .vmlinux	0000004c kmsg_poll
300a361c l     F .vmlinux	0000001c kmsg_open
300a3638 l     F .vmlinux	0000001c kmsg_release
00000000 l    df *ABS*	00000000 check.c
300a3928 l     F .vmlinux	00000014 part_release
302588a8 l     O .vmlinux	00000008 part_sysfs_ops
3025882c l     O .vmlinux	00000018 default_attrs
30258894 l     O .vmlinux	00000014 part_attr_uevent
30258880 l     O .vmlinux	00000014 part_attr_dev
3025886c l     O .vmlinux	00000014 part_attr_start
30258858 l     O .vmlinux	00000014 part_attr_size
30258844 l     O .vmlinux	00000014 part_attr_stat
300a38dc l     F .vmlinux	0000004c part_stat_read
300a38b4 l     F .vmlinux	00000028 part_size_read
300a388c l     F .vmlinux	00000028 part_start_read
300a3848 l     F .vmlinux	00000044 part_dev_read
300a3840 l     F .vmlinux	00000008 part_uevent_store
300a37dc l     F .vmlinux	00000030 part_attr_show
300a380c l     F .vmlinux	00000034 part_attr_store
302588b4 l     O .vmlinux	0000000c check_part
302588c0 l     O .vmlinux	0000000c addpartattr.1
302588cc l     O .vmlinux	00000004 block_str.0
300a3af4 l     F .vmlinux	00000078 make_block_name
00000000 l    df *ABS*	00000000 msdos.c
302588d0 l     O .vmlinux	00000040 subtypes
300a41a0 l     F .vmlinux	00000008 parse_freebsd
300a41a8 l     F .vmlinux	00000008 parse_netbsd
300a41b0 l     F .vmlinux	00000008 parse_openbsd
300a41c0 l     F .vmlinux	00000008 parse_minix
300a41b8 l     F .vmlinux	00000008 parse_unixware
300a4198 l     F .vmlinux	00000008 parse_solaris_x86
00000000 l    df *ABS*	00000000 sun.c
00000000 l    df *ABS*	00000000 inode.c
302284e0 l     O .vmlinux	00000054 sysfs_inode_operations
30258910 l     O .vmlinux	0000001c sysfs_backing_dev_info
30228534 l     O .vmlinux	0000003c sysfs_aops
30613dd8 l     O .bss	00000000 sysfs_inode_imutex_key
00000000 l    df *ABS*	00000000 file.c
300a5590 l     F .vmlinux	000001e8 sysfs_read_file
300a5778 l     F .vmlinux	0000017c sysfs_write_file
300a5b84 l     F .vmlinux	0000007c sysfs_poll
300a58f4 l     F .vmlinux	000001ec sysfs_open_file
300a5ae0 l     F .vmlinux	000000a4 sysfs_release
3025892c l     O .vmlinux	00000008 subsys_sysfs_ops
300a552c l     F .vmlinux	00000030 subsys_attr_show
300a555c l     F .vmlinux	00000034 subsys_attr_store
302285e0 l     O .vmlinux	00000010 __func__.0
300a5c00 l     F .vmlinux	0000008c step_down
300a60f0 l     F .vmlinux	0000002c sysfs_schedule_callback_work
00000000 l    df *ABS*	00000000 dir.c
300a7230 l     F .vmlinux	00000160 sysfs_dir_lseek
300a7010 l     F .vmlinux	00000220 sysfs_readdir
300a6f2c l     F .vmlinux	00000058 sysfs_dir_open
300a6f84 l     F .vmlinux	0000008c sysfs_dir_close
300a6734 l     F .vmlinux	000002c0 sysfs_lookup
30258940 l     O .vmlinux	00000018 sysfs_dentry_ops
300a620c l     F .vmlinux	00000088 sysfs_d_iput
300a6294 l     F .vmlinux	00000064 __sysfs_new_dirent
300a62f8 l     F .vmlinux	0000002c __sysfs_list_dirent
302286b0 l     O .vmlinux	0000000a __func__.0
300a638c l     F .vmlinux	00000090 __sysfs_make_dirent
300a645c l     F .vmlinux	0000002c init_dir
300a6488 l     F .vmlinux	00000020 init_file
300a64a8 l     F .vmlinux	00000014 init_symlink
300a64bc l     F .vmlinux	000001d8 create_dir
300a69f4 l     F .vmlinux	00000108 remove_dir
300a6b0c l     F .vmlinux	00000134 __sysfs_remove_dir
00000000 l    df *ABS*	00000000 symlink.c
300a7634 l     F .vmlinux	000001e8 sysfs_follow_link
300a781c l     F .vmlinux	00000038 sysfs_put_link
30228718 l     O .vmlinux	00000016 __func__.0
00000000 l    df *ABS*	00000000 mount.c
30258958 l     O .vmlinux	00000020 sysfs_fs_type
300a7948 l     F .vmlinux	0000001c sysfs_get_sb
30258978 l     O .vmlinux	0000002c sysfs_root
30228730 l     O .vmlinux	0000004c sysfs_ops
300a7854 l     F .vmlinux	00000014 sysfs_clear_inode
30228780 l     O .vmlinux	00000011 __func__.0
300a7868 l     F .vmlinux	000000e0 sysfs_fill_super
00000000 l    df *ABS*	00000000 bin.c
300a7964 l     F .vmlinux	00000168 read
300a7acc l     F .vmlinux	00000158 write
300a7c24 l     F .vmlinux	00000048 mmap
300a7c6c l     F .vmlinux	00000108 open
300a7d74 l     F .vmlinux	0000002c release
30228808 l     O .vmlinux	00000016 __func__.0
00000000 l    df *ABS*	00000000 group.c
300a7e1c l     F .vmlinux	00000060 remove_files
00000000 l    df *ABS*	00000000 inode.c
302ba41c l     O .vmlinux	00000004 __initcall_init_devpts_fs6
30287338 l     F .vmlinux	00000044 init_devpts_fs
302589a4 l     O .vmlinux	00000020 devpts_fs_type
300a8254 l     F .vmlinux	0000001c devpts_get_sb
30228820 l     O .vmlinux	0000004c devpts_sops
300a8030 l     F .vmlinux	00000138 devpts_remount
302589c4 l     O .vmlinux	00000020 tokens
302589e4 l     O .vmlinux	00000014 config
300a8168 l     F .vmlinux	000000ec devpts_fill_super
30613de8 l     O .bss	00000004 devpts_root
300a8270 l     F .vmlinux	00000048 get_node
30613de4 l     O .bss	00000004 devpts_mnt
00000000 l    df *ABS*	00000000 balloc.c
300a8584 l     F .vmlinux	000000c4 read_block_bitmap
300a8648 l     F .vmlinux	00000030 release_blocks
300a8678 l     F .vmlinux	00000074 group_reserve_blocks
300a86ec l     F .vmlinux	00000074 group_release_blocks
30228870 l     O .vmlinux	00000011 __func__.0
300a8b70 l     F .vmlinux	000001a0 grab_block
300a9534 l     F .vmlinux	000000a8 ext2_group_sparse
00000000 l    df *ABS*	00000000 dir.c
300a9b24 l     F .vmlinux	00000460 ext2_readdir
302589f8 l     O .vmlinux	00000008 ext2_filetype_table
30258a00 l     O .vmlinux	0000000f ext2_type_by_mode
300a9670 l     F .vmlinux	00000024 ext2_last_byte
300a9694 l     F .vmlinux	00000084 ext2_commit_chunk
300a9718 l     F .vmlinux	0000040c ext2_get_page
302288f8 l     O .vmlinux	0000000d __func__.0
30228908 l     O .vmlinux	00000010 __func__.4
30228918 l     O .vmlinux	0000000e __func__.3
30228928 l     O .vmlinux	00000012 __func__.2
30228950 l     O .vmlinux	0000000f __func__.1
00000000 l    df *ABS*	00000000 file.c
300aafec l     F .vmlinux	00000024 ext2_release_file
00000000 l    df *ABS*	00000000 fsync.c
00000000 l    df *ABS*	00000000 ialloc.c
300ab064 l     F .vmlinux	000000c4 read_inode_bitmap
00000000 l    df *ABS*	00000000 inode.c
300acd14 l     F .vmlinux	0000001c ext2_nobh_writepage
300acc8c l     F .vmlinux	0000001c ext2_readpage
300acd9c l     F .vmlinux	00000018 ext2_writepages
300acca8 l     F .vmlinux	00000024 ext2_readpages
300accf0 l     F .vmlinux	00000024 ext2_nobh_prepare_write
300acd30 l     F .vmlinux	00000018 ext2_bmap
300acd48 l     F .vmlinux	00000054 ext2_direct_IO
300acc70 l     F .vmlinux	0000001c ext2_writepage
300acccc l     F .vmlinux	00000024 ext2_prepare_write
300ac12c l     F .vmlinux	000000ac ext2_alloc_block
300ac1d8 l     F .vmlinux	00000148 ext2_block_to_path
300ac320 l     F .vmlinux	00000144 ext2_get_branch
300acdb4 l     F .vmlinux	000001e0 ext2_free_branches
300acf94 l     F .vmlinux	00000178 ext2_get_inode
300ad7a4 l     F .vmlinux	0000065c ext2_update_inode
00000000 l    df *ABS*	00000000 ioctl.c
00000000 l    df *ABS*	00000000 namei.c
300ae8e4 l     F .vmlinux	000000d4 ext2_create
300ae7a8 l     F .vmlinux	00000098 ext2_lookup
300aebb4 l     F .vmlinux	000000bc ext2_link
300aedc0 l     F .vmlinux	00000064 ext2_unlink
300aea4c l     F .vmlinux	00000168 ext2_symlink
300aec70 l     F .vmlinux	00000150 ext2_mkdir
300aee24 l     F .vmlinux	00000080 ext2_rmdir
300ae9b8 l     F .vmlinux	00000094 ext2_mknod
300aeea4 l     F .vmlinux	000002fc ext2_rename
00000000 l    df *ABS*	00000000 super.c
302ba420 l     O .vmlinux	00000004 __initcall_init_ext2_fs6
3028737c l     F .vmlinux	00000078 init_ext2_fs
30258a10 l     O .vmlinux	00000020 ext2_fs_type
300b1408 l     F .vmlinux	0000001c ext2_get_sb
30258a30 l     O .vmlinux	00000018 ext2_export_ops
300af3a0 l     F .vmlinux	00000114 ext2_get_dentry
30228b80 l     O .vmlinux	0000004c ext2_sops
300af2d4 l     F .vmlinux	00000034 ext2_alloc_inode
300af308 l     F .vmlinux	0000001c ext2_destroy_inode
300af768 l     F .vmlinux	000000c0 ext2_put_super
300b0f84 l     F .vmlinux	00000484 ext2_statfs
300b0d44 l     F .vmlinux	00000240 ext2_remount
300af364 l     F .vmlinux	00000008 ext2_clear_inode
300af36c l     F .vmlinux	00000034 ext2_show_options
30258a48 l     O .vmlinux	000000e8 tokens
30228bd0 l     O .vmlinux	00000018 __func__.2
30613dec l     O .bss	00000004 ext2_inode_cachep
300af324 l     F .vmlinux	00000028 init_once
300af34c l     F .vmlinux	00000018 destroy_inodecache
300af4b4 l     F .vmlinux	000001f0 parse_options
300af6a4 l     F .vmlinux	000000c4 ext2_sync_super
300af97c l     F .vmlinux	0000024c ext2_setup_super
30228be8 l     O .vmlinux	00000010 __func__.0
300afccc l     F .vmlinux	00001078 ext2_fill_super
30228bf8 l     O .vmlinux	0000000d __func__.1
00000000 l    df *ABS*	00000000 symlink.c
300b1424 l     F .vmlinux	00000020 ext2_follow_link
00000000 l    df *ABS*	00000000 inode.c
302ba424 l     O .vmlinux	00000004 __initcall_init_ramfs_fs6
302873f4 l     F .vmlinux	00000018 init_ramfs_fs
30258b30 l     O .vmlinux	00000020 ramfs_fs_type
30258b50 l     O .vmlinux	00000020 rootfs_fs_type
300b17fc l     F .vmlinux	00000024 rootfs_get_sb
30228cb0 l     O .vmlinux	0000004c ramfs_ops
30228cfc l     O .vmlinux	00000054 ramfs_dir_inode_operations
300b1660 l     F .vmlinux	0000001c ramfs_create
300b167c l     F .vmlinux	000000cc ramfs_symlink
300b1624 l     F .vmlinux	0000003c ramfs_mkdir
300b1564 l     F .vmlinux	000000c0 ramfs_mknod
30258b70 l     O .vmlinux	0000001c ramfs_backing_dev_info
300b1748 l     F .vmlinux	00000098 ramfs_fill_super
00000000 l    df *ABS*	00000000 file-mmu.c
00000000 l    df *ABS*	00000000 inode.c
302ba428 l     O .vmlinux	00000004 __initcall_init_romfs_fs6
30287424 l     F .vmlinux	00000078 init_romfs_fs
30258b90 l     O .vmlinux	00000020 romfs_fs_type
300b23fc l     F .vmlinux	0000001c romfs_get_sb
30228e4c l     O .vmlinux	0000004c romfs_ops
300b2360 l     F .vmlinux	0000002c romfs_alloc_inode
300b238c l     F .vmlinux	0000001c romfs_destroy_inode
300b21b0 l     F .vmlinux	000001b0 romfs_read_inode
300b19fc l     F .vmlinux	0000004c romfs_statfs
300b23e8 l     F .vmlinux	00000014 romfs_remount
30228e98 l     O .vmlinux	0000003c romfs_aops
300b1fac l     F .vmlinux	00000204 romfs_readpage
30228ed4 l     O .vmlinux	0000006c romfs_dir_operations
300b1c80 l     F .vmlinux	00000150 romfs_readdir
30228f40 l     O .vmlinux	00000054 romfs_dir_inode_operations
300b1dd0 l     F .vmlinux	000001dc romfs_lookup
30258bb0 l     O .vmlinux	00000010 romfs_modemap
30258bc0 l     O .vmlinux	00000008 romfs_dtype_table
300b1820 l     F .vmlinux	000001dc romfs_fill_super
300b1a48 l     F .vmlinux	00000124 romfs_strnlen
300b1b6c l     F .vmlinux	00000114 romfs_copyfrom
30613df0 l     O .bss	00000004 romfs_inode_cachep
300b23a8 l     F .vmlinux	00000028 init_once
300b23d0 l     F .vmlinux	00000018 destroy_inodecache
00000000 l    df *ABS*	00000000 commoncap.c
00000000 l    df *ABS*	00000000 elevator.c
302ba09c l     O .vmlinux	0000000c __setup_elevator_setup
302afcf0 l     O .vmlinux	0000000a __setup_str_elevator_setup
3028749c l     F .vmlinux	0000009c elevator_setup
30258bc8 l     O .vmlinux	00000008 elv_list
30613df8 l     O .bss	00000000 elv_list_lock
30258bd0 l     O .vmlinux	0000000c elv_ktype
300b2d3c l     F .vmlinux	0000001c elevator_release
30258bdc l     O .vmlinux	00000008 elv_sysfs_ops
300b3c9c l     F .vmlinux	00000068 elv_attr_show
300b3d04 l     F .vmlinux	0000006c elv_attr_store
300b2b00 l     F .vmlinux	0000003c elv_iosched_allow_merge
300b2bbc l     F .vmlinux	00000054 elevator_find
300b2c10 l     F .vmlinux	00000008 elevator_put
300b2c18 l     F .vmlinux	00000028 elevator_get
300b2c40 l     F .vmlinux	0000001c elevator_init_queue
300b2c5c l     F .vmlinux	0000000c elevator_attach
30613e00 l     O .bss	00000010 chosen_elevator
30613df8 l     O .bss	00000000 __key.0
300b2c68 l     F .vmlinux	000000d4 elevator_alloc
300b2eb4 l     F .vmlinux	00000038 elv_rqhash_del
300b2eec l     F .vmlinux	0000007c elv_rqhash_add
300b2f68 l     F .vmlinux	00000040 elv_rqhash_reposition
30613df8 l     O .bss	00000004 printed.1
300b34cc l     F .vmlinux	0000007c elv_drain_elevator
30228f98 l     O .vmlinux	0000000b __func__.3
30228fa8 l     O .vmlinux	00000011 __func__.2
300b3de8 l     F .vmlinux	00000014 __elv_unregister_queue
00000000 l    df *ABS*	00000000 ll_rw_blk.c
302afd00 l     O .vmlinux	0000000c blk_cpu_notifier
300b7da0 l     F .vmlinux	0000005c blk_cpu_notify
30258be4 l     O .vmlinux	0000000c queue_ktype
300b8608 l     F .vmlinux	00000084 blk_release_queue
30258c6c l     O .vmlinux	00000008 queue_sysfs_ops
30258bf0 l     O .vmlinux	00000018 default_attrs
30258c58 l     O .vmlinux	00000014 queue_requests_entry
30258c44 l     O .vmlinux	00000014 queue_ra_entry
30258c30 l     O .vmlinux	00000014 queue_max_hw_sectors_entry
30258c1c l     O .vmlinux	00000014 queue_max_sectors_entry
30258c08 l     O .vmlinux	00000014 queue_iosched_entry
300b8a98 l     F .vmlinux	00000018 queue_max_sectors_show
300b8ab0 l     F .vmlinux	0000007c queue_max_sectors_store
300b8b2c l     F .vmlinux	00000018 queue_max_hw_sectors_show
300b8a4c l     F .vmlinux	00000018 queue_ra_show
300b8a64 l     F .vmlinux	00000034 queue_ra_store
300b8880 l     F .vmlinux	00000014 queue_requests_show
300b8894 l     F .vmlinux	000001b8 queue_requests_store
300b8b44 l     F .vmlinux	0000006c queue_attr_show
300b8bb0 l     F .vmlinux	00000070 queue_attr_store
300b4258 l     F .vmlinux	00000044 blk_queue_congestion_threshold
30228fc0 l     O .vmlinux	0000001c __func__.13
30228fe0 l     O .vmlinux	0000001a __func__.12
30229000 l     O .vmlinux	00000016 __func__.14
300b43b4 l     F .vmlinux	00000060 rq_init
300b45ec l     F .vmlinux	0000006c queue_flush
300b83f4 l     F .vmlinux	00000024 pre_flush_end_io
300b83d0 l     F .vmlinux	00000024 post_flush_end_io
300b4658 l     F .vmlinux	0000009c flush_dry_bio_endio
300b46f4 l     F .vmlinux	00000070 ordered_bio_endio
300b5b38 l     F .vmlinux	00000020 blk_unplug_work
300b85c4 l     F .vmlinux	00000014 blk_unplug_timeout
30229018 l     O .vmlinux	0000001b __func__.11
30229038 l     O .vmlinux	0000001b __func__.10
300b4a30 l     F .vmlinux	00000064 __blk_free_tags
30229058 l     O .vmlinux	0000000d __func__.9
300b4ac8 l     F .vmlinux	000000a4 init_tag_map
300b4b6c l     F .vmlinux	00000070 __blk_queue_init_tags
30229068 l     O .vmlinux	00000012 __func__.8
30229080 l     O .vmlinux	00000014 __func__.7
30229098 l     O .vmlinux	0000001a __func__.6
300b531c l     F .vmlinux	000000d4 blk_phys_contig_segment
300b53f0 l     F .vmlinux	000000f0 blk_hw_contig_segment
300b5650 l     F .vmlinux	00000168 init_request_from_bio
302290b8 l     O .vmlinux	00000010 __func__.5
302290c8 l     O .vmlinux	00000010 __func__.4
300b5b08 l     F .vmlinux	00000030 blk_backing_dev_unplug
30613e10 l     O .bss	00000000 __key.2
30613e1c l     O .bss	00000004 requestq_cachep
30613e18 l     O .bss	00000004 request_cachep
300b6ef0 l     F .vmlinux	000005e4 __make_request
300b5e00 l     F .vmlinux	0000005c ioc_set_batching
300b5e5c l     F .vmlinux	000000ac __freed_request
300b5f08 l     F .vmlinux	00000068 freed_request
300b5f70 l     F .vmlinux	0000006c current_io_context
30613e20 l     O .bss	00000004 iocontext_cachep
300b5fdc l     F .vmlinux	00000290 get_request
300b626c l     F .vmlinux	00000118 get_request_wait
300b6450 l     F .vmlinux	00000040 __blk_rq_unmap_user
302290d8 l     O .vmlinux	00000016 __func__.1
300b6af4 l     F .vmlinux	00000068 drive_stat_acct
300b6ce4 l     F .vmlinux	0000020c attempt_merge
300b74d4 l     F .vmlinux	00000090 handle_bad_sector
302290f0 l     O .vmlinux	00000019 __func__.0
300b77e8 l     F .vmlinux	000004c8 __end_that_request_first
300b7cd4 l     F .vmlinux	000000cc blk_done_softirq
30613e28 l     O .bss	00000008 per_cpu__blk_cpu_done
30229110 l     O .vmlinux	0000000f __func__.15
300b8418 l     F .vmlinux	00000024 bar_end_io
30613e24 l     O .bss	00000004 kblockd_workqueue
30229120 l     O .vmlinux	00000010 __func__.3
300b883c l     F .vmlinux	00000020 queue_var_show
300b885c l     F .vmlinux	00000024 queue_var_store
00000000 l    df *ABS*	00000000 ioctl.c
300b8ce4 l     F .vmlinux	00000034 put_int
00000000 l    df *ABS*	00000000 genhd.c
300b9f38 l     F .vmlinux	0000006c diskstats_start
300b9fd8 l     F .vmlinux	00000018 diskstats_stop
300b9fa4 l     F .vmlinux	00000034 diskstats_next
300b9ff0 l     F .vmlinux	00000174 diskstats_show
30258cec l     O .vmlinux	0000000c ktype_block
30258ce0 l     O .vmlinux	0000000c block_uevent_ops
300b9e60 l     F .vmlinux	00000054 block_uevent_filter
300b9eb4 l     F .vmlinux	00000084 block_uevent
300b9e3c l     F .vmlinux	00000024 disk_release
30258d8c l     O .vmlinux	00000008 disk_sysfs_ops
30258cf8 l     O .vmlinux	0000001c default_attrs
30258d78 l     O .vmlinux	00000014 disk_attr_uevent
30258d64 l     O .vmlinux	00000014 disk_attr_dev
30258d50 l     O .vmlinux	00000014 disk_attr_range
30258d3c l     O .vmlinux	00000014 disk_attr_removable
30258d28 l     O .vmlinux	00000014 disk_attr_size
30258d14 l     O .vmlinux	00000014 disk_attr_stat
300b9da0 l     F .vmlinux	0000009c disk_stats_read
300b9d78 l     F .vmlinux	00000028 disk_size_read
300b9d54 l     F .vmlinux	00000024 disk_removable_read
300b9d30 l     F .vmlinux	00000024 disk_range_read
300b9cf8 l     F .vmlinux	00000038 disk_dev_read
300b9cf0 l     F .vmlinux	00000008 disk_uevent_store
300b9c8c l     F .vmlinux	00000030 disk_attr_show
300b9cbc l     F .vmlinux	00000034 disk_attr_store
302ba38c l     O .vmlinux	00000004 __initcall_genhd_device_init4
30287640 l     F .vmlinux	00000060 genhd_device_init
300b9a7c l     F .vmlinux	0000006c part_start
300b9b1c l     F .vmlinux	00000018 part_stop
300b9ae8 l     F .vmlinux	00000034 part_next
300b9b34 l     F .vmlinux	00000150 show_partition
30258da4 l     O .vmlinux	0000000c block_subsys_lock
30613e30 l     O .bss	000003fc major_names
3061422c l     O .bss	00000004 bdev_map
300b9978 l     F .vmlinux	00000008 exact_match
300b99ac l     F .vmlinux	0000001c exact_lock
300b9c84 l     F .vmlinux	00000008 base_probe
30229130 l     O .vmlinux	00000012 __func__.0
00000000 l    df *ABS*	00000000 scsi_ioctl.c
30258db0 l     O .vmlinux	00000100 cmd_type.1
300ba33c l     F .vmlinux	0000009c verify_command
300ba3d8 l     F .vmlinux	000003d4 sg_io
300bab70 l     F .vmlinux	0000007c __blk_send_generic
30229150 l     O .vmlinux	00000004 sg_version_num.0
00000000 l    df *ABS*	00000000 noop-iosched.c
302ba42c l     O .vmlinux	00000004 __initcall_noop_init6
302876a0 l     F .vmlinux	00000018 noop_init
30258eb0 l     O .vmlinux	00000068 elevator_noop
300bb11c l     F .vmlinux	0000001c noop_merged_requests
300bb138 l     F .vmlinux	0000004c noop_dispatch
300bb184 l     F .vmlinux	00000020 noop_add_request
300bb1a4 l     F .vmlinux	0000001c noop_queue_empty
300bb1c0 l     F .vmlinux	00000024 noop_former_request
300bb1e4 l     F .vmlinux	00000024 noop_latter_request
300bb208 l     F .vmlinux	00000034 noop_init_queue
300bb23c l     F .vmlinux	00000020 noop_exit_queue
00000000 l    df *ABS*	00000000 cfq-iosched.c
302ba430 l     O .vmlinux	00000004 __initcall_cfq_init6
302876b8 l     F .vmlinux	000000d4 cfq_init
30258f18 l     O .vmlinux	00000068 iosched_cfq
300bc4dc l     F .vmlinux	0000009c cfq_merge
300bbbc0 l     F .vmlinux	00000094 cfq_merged_request
300bb804 l     F .vmlinux	0000006c cfq_merged_requests
300bc44c l     F .vmlinux	00000090 cfq_allow_merge
300bbce0 l     F .vmlinux	00000590 cfq_dispatch_requests
300bca68 l     F .vmlinux	000003f8 cfq_insert_request
300bb5a4 l     F .vmlinux	00000038 cfq_activate_request
300bb5dc l     F .vmlinux	00000058 cfq_deactivate_request
300bb25c l     F .vmlinux	00000018 cfq_queue_empty
300bce60 l     F .vmlinux	00000268 cfq_completed_request
300bd25c l     F .vmlinux	00000380 cfq_set_request
300bd1f8 l     F .vmlinux	00000064 cfq_put_request
300bd0c8 l     F .vmlinux	00000130 cfq_may_queue
300bd7d8 l     F .vmlinux	00000178 cfq_init_queue
300bd750 l     F .vmlinux	00000088 cfq_exit_queue
300bc578 l     F .vmlinux	00000084 cfq_free_io_context
30258f80 l     O .vmlinux	000000c8 cfq_attrs
300bd9e0 l     F .vmlinux	00000018 cfq_quantum_show
300bdacc l     F .vmlinux	0000003c cfq_quantum_store
300bd9f8 l     F .vmlinux	0000001c cfq_fifo_expire_sync_show
300bdb08 l     F .vmlinux	00000044 cfq_fifo_expire_sync_store
300bda14 l     F .vmlinux	0000001c cfq_fifo_expire_async_show
300bdb4c l     F .vmlinux	00000044 cfq_fifo_expire_async_store
300bda30 l     F .vmlinux	00000018 cfq_back_seek_max_show
300bdb90 l     F .vmlinux	00000028 cfq_back_seek_max_store
300bda48 l     F .vmlinux	00000018 cfq_back_seek_penalty_show
300bdbb8 l     F .vmlinux	0000003c cfq_back_seek_penalty_store
300bda7c l     F .vmlinux	0000001c cfq_slice_sync_show
300bdc24 l     F .vmlinux	00000044 cfq_slice_sync_store
300bda98 l     F .vmlinux	0000001c cfq_slice_async_show
300bdc68 l     F .vmlinux	00000044 cfq_slice_async_store
300bdab4 l     F .vmlinux	00000018 cfq_slice_async_rq_show
300bdcac l     F .vmlinux	0000003c cfq_slice_async_rq_store
300bda60 l     F .vmlinux	0000001c cfq_slice_idle_show
300bdbf4 l     F .vmlinux	00000030 cfq_slice_idle_store
30614230 l     O .bss	00000004 cfq_slice_idle
30259048 l     O .vmlinux	00000004 cfq_slice_async
30229158 l     O .vmlinux	00000008 cfq_fifo_expire
300bb274 l     F .vmlinux	000001c4 cfq_choose_req
300bb438 l     F .vmlinux	0000016c cfq_resort_rr_list
30229160 l     O .vmlinux	00000017 __func__.6
30229178 l     O .vmlinux	00000013 __func__.7
300bb634 l     F .vmlinux	000001d0 cfq_remove_request
300bb870 l     F .vmlinux	000000bc __cfq_slice_expired
30229190 l     O .vmlinux	00000014 __func__.5
300bb92c l     F .vmlinux	0000010c cfq_arm_slice_timer
300bba38 l     F .vmlinux	000000a0 cfq_dispatch_insert
300bbad8 l     F .vmlinux	000000e8 cfq_add_rq_rb
300bbc54 l     F .vmlinux	0000008c cfq_forced_dispatch_cfqqs
302291a8 l     O .vmlinux	00000012 __func__.8
300bc270 l     F .vmlinux	0000010c cfq_put_queue
30614234 l     O .bss	00000004 cfq_pool
300bc37c l     F .vmlinux	0000008c __cfq_find_cfq_hash
300bc408 l     F .vmlinux	00000044 cfq_find_cfq_hash
30614238 l     O .bss	00000004 cfq_ioc_pool
3061423c l     O .bss	00000004 per_cpu__ioc_count
30614240 l     O .bss	00000004 ioc_gone
300bc5fc l     F .vmlinux	0000005c cfq_exit_cfqq
300bc658 l     F .vmlinux	0000007c __cfq_exit_single_io_context
300bc6d4 l     F .vmlinux	00000060 cfq_exit_io_context
302291c0 l     O .vmlinux	0000000c __func__.0
300bc734 l     F .vmlinux	0000010c cfq_init_prio_data
302291d0 l     O .vmlinux	0000000e __func__.2
300bc840 l     F .vmlinux	000001b4 cfq_get_queue
302291e0 l     O .vmlinux	00000012 __func__.1
300bc9f4 l     F .vmlinux	00000074 cfq_drop_dead_cic
302291f8 l     O .vmlinux	00000016 __func__.3
30229210 l     O .vmlinux	00000012 __func__.4
300bd5dc l     F .vmlinux	00000024 cfq_kick_queue
300bd600 l     F .vmlinux	000000c4 cfq_idle_slice_timer
300bd6c4 l     F .vmlinux	00000068 cfq_idle_class_timer
300bd72c l     F .vmlinux	00000024 cfq_shutdown_timer_wq
300bd950 l     F .vmlinux	0000004c cfq_slab_kill
300bd99c l     F .vmlinux	00000020 cfq_var_show
300bd9bc l     F .vmlinux	00000024 cfq_var_store
00000000 l    df *ABS*	00000000 bitmap.c
300be954 l     F .vmlinux	0000009c bitmap_pos_to_ord
300be9f0 l     F .vmlinux	000000ac bitmap_ord_to_pos
300bec94 l     F .vmlinux	0000011c __reg_op
00000000 l    df *ABS*	00000000 cmdline.c
00000000 l    df *ABS*	00000000 ctype.c
00000000 l    df *ABS*	00000000 dec_and_lock.c
00000000 l    df *ABS*	00000000 div64.c
00000000 l    df *ABS*	00000000 find_next_bit.c
00000000 l    df *ABS*	00000000 idr.c
300bf704 l     F .vmlinux	00000048 alloc_layer
300bf74c l     F .vmlinux	0000001c __free_layer
300bf768 l     F .vmlinux	00000028 free_layer
30614244 l     O .bss	00000004 idr_layer_cache
300bf7f4 l     F .vmlinux	0000035c idr_get_new_above_int
300bff68 l     F .vmlinux	0000001c idr_cache_ctor
00000000 l    df *ABS*	00000000 int_sqrt.c
00000000 l    df *ABS*	00000000 irq_regs.c
00000000 l    df *ABS*	00000000 kobject.c
30259150 l     O .vmlinux	0000000c dir_ktype
300c0760 l     F .vmlinux	00000010 dir_release
30229228 l     O .vmlinux	0000000f __func__.2
300c0318 l     F .vmlinux	00000014 kobject_release
300c032c l     F .vmlinux	00000038 unlink
30229238 l     O .vmlinux	00000013 __func__.1
3061424c l     O .bss	00000000 __key.0
00000000 l    df *ABS*	00000000 kref.c
30229250 l     O .vmlinux	00000009 __func__.1
30229260 l     O .vmlinux	00000009 __func__.0
00000000 l    df *ABS*	00000000 prio_tree.c
300c0b58 l     F .vmlinux	00000054 get_index
3061424c l     O .bss	00000080 index_bits_to_maxindex
300c106c l     F .vmlinux	000000d8 prio_tree_left
300c1144 l     F .vmlinux	00000108 prio_tree_right
300c124c l     F .vmlinux	00000084 prio_tree_parent
00000000 l    df *ABS*	00000000 radix-tree.c
300c149c l     F .vmlinux	00000068 radix_tree_node_alloc
30614308 l     O .bss	00000004 radix_tree_node_cachep
300c1504 l     F .vmlinux	0000001c radix_tree_node_rcu_free
306142ec l     O .bss	0000001c height_to_maxindex
300c21a0 l     F .vmlinux	0000001c radix_tree_node_ctor
00000000 l    df *ABS*	00000000 rbtree.c
300c21bc l     F .vmlinux	00000078 __rb_rotate_left
300c2234 l     F .vmlinux	00000078 __rb_rotate_right
00000000 l    df *ABS*	00000000 reciprocal_div.c
00000000 l    df *ABS*	00000000 rwsem-spinlock.c
00000000 l    df *ABS*	00000000 string.c
00000000 l    df *ABS*	00000000 vsprintf.c
300c3be4 l     F .vmlinux	00000064 skip_atoi
30229270 l     O .vmlinux	00000025 small_digits.2
30229298 l     O .vmlinux	00000025 large_digits.3
300c3c48 l     F .vmlinux	00000328 number
302292c0 l     O .vmlinux	0000000a __func__.0
3025915c l     O .vmlinux	00000004 warn.1
00000000 l    df *ABS*	00000000 bootstr.c
30614310 l     O .bss	00000100 barg_buf
302afd0c l     O .vmlinux	00000001 fetched
00000000 l    df *ABS*	00000000 console.c
30259160 l     O .vmlinux	0000000a con_name_jmc
30614410 l     O .bss	00000001 inc.1
30614411 l     O .bss	00000001 outc.0
00000000 l    df *ABS*	00000000 init.c
00000000 l    df *ABS*	00000000 memory.c
30287a9c l     F .vmlinux	00000110 prom_sortmemlist
00000000 l    df *ABS*	00000000 misc.c
00000000 l    df *ABS*	00000000 printf.c
30615348 l     O .bss	00000400 ppbuf
00000000 l    df *ABS*	00000000 ranges.c
300c580c l     F .vmlinux	000000c0 prom_adjust_regs
00000000 l    df *ABS*	00000000 segment.c
00000000 l    df *ABS*	00000000 tree.c
30615890 l     O .bss	00000004 intprop.1
30615898 l     O .bss	00000080 namebuf.0
30615918 l     O .bss	00000080 promlib_buf
00000000 l    df *ABS*	00000000 devops.c
00000000 l    df *ABS*	00000000 arch/sparc/lib/ashldi3.S
00000000 l    df *ABS*	00000000 arch/sparc/lib/ashrdi3.S
00000000 l    df *ABS*	00000000 arch/sparc/lib/atomic.S
00000000 l    df *ABS*	00000000 bitext.c
00000000 l    df *ABS*	00000000 arch/sparc/lib/blockops.S
00000000 l    df *ABS*	00000000 arch/sparc/lib/checksum.S
300c6a78 l       .vmlinux	00000000 csum_partial_end_cruft
300c6af4 l       .vmlinux	00000000 csum_partial_fix_alignment
300c6d14 l       .vmlinux	00000000 cpte
300c6b6c l       .vmlinux	00000000 cpa
300c6c64 l       .vmlinux	00000000 cptbl
300c6d1c l       .vmlinux	00000000 cpout
300c6d24 l       .vmlinux	00000000 cc_end_cruft
300c6dc0 l       .vmlinux	00000000 cc_dword_align
300c7110 l       .vmlinux	00000000 ccte
300c7240 l       .vmlinux	00000000 ccslow
300c7120 l       .vmlinux	00000000 ccdbl
300c6fc8 l       .vmlinux	00000000 ccmerge
300c6ff0 l       .vmlinux	00000000 cctbl
00000000 l    df *ABS*	00000000 arch/sparc/lib/copy_user.S
300c7490 l       .vmlinux	00000000 dword_align
300c77ec l       .vmlinux	00000000 cannot_optimize
300c79b4 l       .vmlinux	00000000 short_aligned_end
300c7734 l       .vmlinux	00000000 ldd_std
300c76d0 l       .vmlinux	00000000 copy_user_table_end
300c7628 l       .vmlinux	00000000 copy_user_table
300c76ec l       .vmlinux	00000000 copy_user_last7
3026bdac l       .vmlinux	00000000 fixupretl
300c790c l       .vmlinux	00000000 short_end
300c787c l       .vmlinux	00000000 byte_chunk
300c799c l       .vmlinux	00000000 short_table_end
00000000 l    df *ABS*	00000000 arch/sparc/lib/divdi3.S
00000000 l    df *ABS*	00000000 arch/sparc/lib/lshrdi3.S
00000000 l    df *ABS*	00000000 arch/sparc/lib/memcmp.S
300c7e24 l       .vmlinux	00000000 L3
300c7df4 l       .vmlinux	00000000 L5
00000000 l    df *ABS*	00000000 arch/sparc/lib/memcpy.S
00000000 l    df *ABS*	00000000 arch/sparc/lib/memscan.S
300c8558 l       .vmlinux	00000000 mzero_scan_word
300c8524 l       .vmlinux	00000000 mzero_still_not_word_aligned
300c8564 l       .vmlinux	00000000 mzero_next_word
300c8568 l       .vmlinux	00000000 mzero_next_word_preloaded
300c856c l       .vmlinux	00000000 mzero_next_word_preloaded_next
300c8594 l       .vmlinux	00000000 mzero_byte_zero
300c8578 l       .vmlinux	00000000 mzero_check_out_of_fuel
300c85ac l       .vmlinux	00000000 mzero_byte_one
300c85c4 l       .vmlinux	00000000 mzero_byte_two_and_three
300c85ec l       .vmlinux	00000000 mzero_found_it
00000000 l    df *ABS*	00000000 arch/sparc/lib/memset.S
00000000 l    df *ABS*	00000000 arch/sparc/lib/mul.S
300c8858 l       .vmlinux	00000000 Lmul_shortway
00000000 l    df *ABS*	00000000 arch/sparc/lib/muldi3.S
00000000 l    df *ABS*	00000000 arch/sparc/lib/rem.S
300c8c1c l       .vmlinux	00000000 Lgot_result
300c8a78 l       .vmlinux	00000000 Lnot_really_big
300c8a18 l       .vmlinux	00000000 Lnot_too_big
300c8a2c l       .vmlinux	00000000 Ldo_single_div
300c8c08 l       .vmlinux	00000000 Lend_regular_divide
300c8a68 l       .vmlinux	00000000 Lend_single_divloop
300c8a48 l       .vmlinux	00000000 Lsingle_divloop
300c8a94 l       .vmlinux	00000000 Ldivloop
300c8b54 l       .vmlinux	00000000 L.1.16
300c8b00 l       .vmlinux	00000000 L.2.17
300c8adc l       .vmlinux	00000000 L.3.19
300c8ad0 l       .vmlinux	00000000 L.4.23
300c8af4 l       .vmlinux	00000000 L.4.21
300c8b30 l       .vmlinux	00000000 L.3.17
300c8b24 l       .vmlinux	00000000 L.4.19
300c8b48 l       .vmlinux	00000000 L.4.17
300c8bb4 l       .vmlinux	00000000 L.2.15
300c8b90 l       .vmlinux	00000000 L.3.15
300c8b84 l       .vmlinux	00000000 L.4.15
300c8ba8 l       .vmlinux	00000000 L.4.13
300c8be4 l       .vmlinux	00000000 L.3.13
300c8bd8 l       .vmlinux	00000000 L.4.11
300c8bfc l       .vmlinux	00000000 L.4.9
00000000 l    df *ABS*	00000000 arch/sparc/lib/sdiv.S
300c8ef4 l       .vmlinux	00000000 Lgot_result
300c8d50 l       .vmlinux	00000000 Lnot_really_big
300c8cf0 l       .vmlinux	00000000 Lnot_too_big
300c8d04 l       .vmlinux	00000000 Ldo_single_div
300c8ee0 l       .vmlinux	00000000 Lend_regular_divide
300c8d40 l       .vmlinux	00000000 Lend_single_divloop
300c8d20 l       .vmlinux	00000000 Lsingle_divloop
300c8d6c l       .vmlinux	00000000 Ldivloop
300c8e2c l       .vmlinux	00000000 L.1.16
300c8dd8 l       .vmlinux	00000000 L.2.17
300c8db4 l       .vmlinux	00000000 L.3.19
300c8da8 l       .vmlinux	00000000 L.4.23
300c8dcc l       .vmlinux	00000000 L.4.21
300c8e08 l       .vmlinux	00000000 L.3.17
300c8dfc l       .vmlinux	00000000 L.4.19
300c8e20 l       .vmlinux	00000000 L.4.17
300c8e8c l       .vmlinux	00000000 L.2.15
300c8e68 l       .vmlinux	00000000 L.3.15
300c8e5c l       .vmlinux	00000000 L.4.15
300c8e80 l       .vmlinux	00000000 L.4.13
300c8ebc l       .vmlinux	00000000 L.3.13
300c8eb0 l       .vmlinux	00000000 L.4.11
300c8ed4 l       .vmlinux	00000000 L.4.9
00000000 l    df *ABS*	00000000 arch/sparc/lib/strlen.S
00000000 l    df *ABS*	00000000 arch/sparc/lib/strlen_user.S
00000000 l    df *ABS*	00000000 arch/sparc/lib/strncmp.S
00000000 l    df *ABS*	00000000 arch/sparc/lib/strncpy_from_user.S
00000000 l    df *ABS*	00000000 arch/sparc/lib/udiv.S
300c94d4 l       .vmlinux	00000000 Lgot_result
300c9330 l       .vmlinux	00000000 Lnot_really_big
300c92d0 l       .vmlinux	00000000 Lnot_too_big
300c92e4 l       .vmlinux	00000000 Ldo_single_div
300c94c0 l       .vmlinux	00000000 Lend_regular_divide
300c9320 l       .vmlinux	00000000 Lend_single_divloop
300c9300 l       .vmlinux	00000000 Lsingle_divloop
300c934c l       .vmlinux	00000000 Ldivloop
300c940c l       .vmlinux	00000000 L.1.16
300c93b8 l       .vmlinux	00000000 L.2.17
300c9394 l       .vmlinux	00000000 L.3.19
300c9388 l       .vmlinux	00000000 L.4.23
300c93ac l       .vmlinux	00000000 L.4.21
300c93e8 l       .vmlinux	00000000 L.3.17
300c93dc l       .vmlinux	00000000 L.4.19
300c9400 l       .vmlinux	00000000 L.4.17
300c946c l       .vmlinux	00000000 L.2.15
300c9448 l       .vmlinux	00000000 L.3.15
300c943c l       .vmlinux	00000000 L.4.15
300c9460 l       .vmlinux	00000000 L.4.13
300c949c l       .vmlinux	00000000 L.3.13
300c9490 l       .vmlinux	00000000 L.4.11
300c94b4 l       .vmlinux	00000000 L.4.9
00000000 l    df *ABS*	00000000 arch/sparc/lib/udivdi3.S
00000000 l    df *ABS*	00000000 arch/sparc/lib/umul.S
300c98ec l       .vmlinux	00000000 Lmul_shortway
00000000 l    df *ABS*	00000000 arch/sparc/lib/urem.S
300c9bb8 l       .vmlinux	00000000 Lgot_result
300c9a14 l       .vmlinux	00000000 Lnot_really_big
300c99b4 l       .vmlinux	00000000 Lnot_too_big
300c99c8 l       .vmlinux	00000000 Ldo_single_div
300c9ba4 l       .vmlinux	00000000 Lend_regular_divide
300c9a04 l       .vmlinux	00000000 Lend_single_divloop
300c99e4 l       .vmlinux	00000000 Lsingle_divloop
300c9a30 l       .vmlinux	00000000 Ldivloop
300c9af0 l       .vmlinux	00000000 L.1.16
300c9a9c l       .vmlinux	00000000 L.2.17
300c9a78 l       .vmlinux	00000000 L.3.19
300c9a6c l       .vmlinux	00000000 L.4.23
300c9a90 l       .vmlinux	00000000 L.4.21
300c9acc l       .vmlinux	00000000 L.3.17
300c9ac0 l       .vmlinux	00000000 L.4.19
300c9ae4 l       .vmlinux	00000000 L.4.17
300c9b50 l       .vmlinux	00000000 L.2.15
300c9b2c l       .vmlinux	00000000 L.3.15
300c9b20 l       .vmlinux	00000000 L.4.15
300c9b44 l       .vmlinux	00000000 L.4.13
300c9b80 l       .vmlinux	00000000 L.3.13
300c9b74 l       .vmlinux	00000000 L.4.11
300c9b98 l       .vmlinux	00000000 L.4.9
00000000 l    df *ABS*	00000000 sort.c
300c9be0 l     F .vmlinux	00000014 u32_swap
300c9bf4 l     F .vmlinux	0000002c generic_swap
00000000 l    df *ABS*	00000000 parser.c
300ca01c l     F .vmlinux	00000090 match_number
00000000 l    df *ABS*	00000000 halfmd4.c
00000000 l    df *ABS*	00000000 debug_locks.c
00000000 l    df *ABS*	00000000 random32.c
302ba480 l     O .vmlinux	00000004 __initcall_random32_reseed7
30288070 l     F .vmlinux	00000028 random32_reseed
302ba364 l     O .vmlinux	00000004 __initcall_random32_init1
3028804c l     F .vmlinux	00000024 random32_init
300ca574 l     F .vmlinux	00000070 __random32
300ca5e4 l     F .vmlinux	000000cc __set_random32
3061599c l     O .bss	0000000c per_cpu__net_rand_state
00000000 l    df *ABS*	00000000 bust_spinlocks.c
00000000 l    df *ABS*	00000000 iomap_copy.c
00000000 l    df *ABS*	00000000 devres.c
300ca768 l     F .vmlinux	00000014 devm_ioremap_release
300ca77c l     F .vmlinux	00000014 devm_ioremap_match
302292d0 l     O .vmlinux	0000000d __func__.2
300ca8d8 l     F .vmlinux	00000014 devm_ioport_map_release
300ca8ec l     F .vmlinux	00000014 devm_ioport_map_match
302292e0 l     O .vmlinux	00000012 __func__.1
300ca9d8 l     F .vmlinux	00000040 pcim_iomap_release
302292f8 l     O .vmlinux	0000000d __func__.0
00000000 l    df *ABS*	00000000 hweight.c
00000000 l    df *ABS*	00000000 plist.c
30229308 l     O .vmlinux	0000000a __func__.0
00000000 l    df *ABS*	00000000 bitrev.c
00000000 l    df *ABS*	00000000 crc32.c
30229418 l     O .vmlinux	00000400 crc32table_be
30229818 l     O .vmlinux	00000400 crc32table_le
00000000 l    df *ABS*	00000000 iomap.c
00000000 l    df *ABS*	00000000 atomic32.c
306159a8 l     O .bss	00000000 dummy
00000000 l    df *ABS*	00000000 access.c
30259288 l     O .vmlinux	00000008 pci_ucfg_wait
306159c0 l     O .bss	00000000 pci_lock
300cb584 l     F .vmlinux	000000ac pci_wait_ucfg
30229c18 l     O .vmlinux	0000001c __func__.0
00000000 l    df *ABS*	00000000 bus.c
00000000 l    df *ABS*	00000000 probe.c
302ba36c l     O .vmlinux	00000004 __initcall_pcibus_class_init2
30288298 l     F .vmlinux	00000018 pcibus_class_init
300cbbb4 l     F .vmlinux	0000003c pci_bus_show_cpuaffinity
302592b4 l     O .vmlinux	000000b8 pcibus_class
300cbbf0 l     F .vmlinux	00000034 release_pcibus_dev
300cbc24 l     F .vmlinux	00000048 pci_size
300cbc6c l     F .vmlinux	0000046c pci_read_bases
3028856c l     F .vmlinux	00000044 pci_alloc_bus
302886e4 l     F .vmlinux	00000008 pci_fixup_parent_subordinate_busnr
300cc0d8 l     F .vmlinux	00000054 pci_read_irq
300cc12c l     F .vmlinux	00000014 pci_release_dev
300cc1e0 l     F .vmlinux	00000010 pci_release_bus_bridge_dev
30289310 l     F .vmlinux	00000050 pci_sort_bf_cmp
00000000 l    df *ABS*	00000000 remove.c
300cc1f0 l     F .vmlinux	00000074 pci_stop_dev
00000000 l    df *ABS*	00000000 pci.c
302ba434 l     O .vmlinux	00000004 __initcall_pci_init6
30289588 l     F .vmlinux	0000003c pci_init
302ba0a8 l     O .vmlinux	0000000c __setup_pci_setup
302afd10 l     O .vmlinux	00000004 __setup_str_pci_setup
302895c4 l     F .vmlinux	000001dc pci_setup
300cc434 l     F .vmlinux	000000a0 __pci_find_next_cap_ttl
300cc4d4 l     F .vmlinux	0000002c __pci_find_next_cap
300cc524 l     F .vmlinux	00000050 __pci_bus_find_cap_start
300cc6c0 l     F .vmlinux	000000c4 __pci_find_next_ht_cap
30229c38 l     O .vmlinux	00000014 __func__.2
300ccfa4 l     F .vmlinux	00000068 do_pci_enable_device
300cd098 l     F .vmlinux	00000038 find_pci_dr
300cd59c l     F .vmlinux	000000bc pcim_release
30229c50 l     O .vmlinux	00000013 __func__.1
30229c68 l     O .vmlinux	00000010 __func__.0
00000000 l    df *ABS*	00000000 quirks.c
30252880 l     O .vmlinux	00000008 __pci_fixup_resumePCI_VENDOR_ID_NVIDIAPCI_DEVICE_ID_NVIDIA_CK804_PCIEquirk_nvidia_ck804_pcie_aer_ext_cap
300ce6d0 l     F .vmlinux	00000060 quirk_nvidia_ck804_pcie_aer_ext_cap
30252688 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_NVIDIAPCI_DEVICE_ID_NVIDIA_CK804_PCIEquirk_nvidia_ck804_pcie_aer_ext_cap
30252690 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTEL0x1460quirk_p64h2_1k_io_fix_iobl
3028a984 l     F .vmlinux	000000a8 quirk_p64h2_1k_io_fix_iobl
30252458 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTEL0x1460quirk_p64h2_1k_io
3028a8f0 l     F .vmlinux	00000094 quirk_p64h2_1k_io
30252460 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_NCRPCI_DEVICE_ID_NCR_53C810fixup_rev1_53c810
3028a8c0 l     F .vmlinux	00000030 fixup_rev1_53c810
30252418 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_ANY_IDquirk_e100_interrupt
3028a6d4 l     F .vmlinux	000001ec quirk_e100_interrupt
30252468 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_NETMOSPCI_ANY_IDquirk_netmos
3028a600 l     F .vmlinux	000000d4 quirk_netmos
30252470 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_TOSHIBA_2PCI_DEVICE_ID_TOSHIBA_TC86C001_IDEquirk_tc86c001_ide
3028a5dc l     F .vmlinux	00000024 quirk_tc86c001_ide
30252698 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTEL0x260bquirk_intel_pcie_pm
300ce5b0 l     F .vmlinux	00000020 quirk_intel_pcie_pm
302526a0 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTEL0x260aquirk_intel_pcie_pm
302526a8 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTEL0x2609quirk_intel_pcie_pm
302526b0 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTEL0x2608quirk_intel_pcie_pm
302526b8 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTEL0x2607quirk_intel_pcie_pm
302526c0 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTEL0x2606quirk_intel_pcie_pm
302526c8 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTEL0x2605quirk_intel_pcie_pm
302526d0 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTEL0x2604quirk_intel_pcie_pm
302526d8 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTEL0x2603quirk_intel_pcie_pm
302526e0 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTEL0x2602quirk_intel_pcie_pm
302526e8 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTEL0x2601quirk_intel_pcie_pm
302526f0 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTEL0x25faquirk_intel_pcie_pm
302526f8 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTEL0x25f9quirk_intel_pcie_pm
30252700 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTEL0x25f8quirk_intel_pcie_pm
30252708 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTEL0x25f7quirk_intel_pcie_pm
30252710 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTEL0x25e7quirk_intel_pcie_pm
30252718 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTEL0x25e6quirk_intel_pcie_pm
30252720 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTEL0x25e5quirk_intel_pcie_pm
30252728 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTEL0x25e4quirk_intel_pcie_pm
30252730 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTEL0x25e3quirk_intel_pcie_pm
30252738 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTEL0x25e2quirk_intel_pcie_pm
30252420 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_PXHVquirk_pcie_pxh
3028a5b0 l     F .vmlinux	0000002c quirk_pcie_pxh
30252428 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_PXH_1quirk_pcie_pxh
30252430 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_PXH_0quirk_pcie_pxh
30252438 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_PXHD_1quirk_pcie_pxh
30252440 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_PXHD_0quirk_pcie_pxh
30252740 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_E7525_MCHquirk_pcie_mch
3028a5a0 l     F .vmlinux	00000010 quirk_pcie_mch
30252748 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_E7320_MCHquirk_pcie_mch
30252750 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_E7520_MCHquirk_pcie_mch
302ba0b4 l     O .vmlinux	0000000c __setup_combined_setup
302afd18 l     O .vmlinux	0000000f __setup_str_combined_setup
3028a48c l     F .vmlinux	00000114 combined_setup
30252888 l     O .vmlinux	00000008 __pci_fixup_resumePCI_VENDOR_ID_VIAPCI_DEVICE_ID_VIA_8237asus_hides_ac97_lpc
300ce4fc l     F .vmlinux	000000b4 asus_hides_ac97_lpc
30252478 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_VIAPCI_DEVICE_ID_VIA_8237asus_hides_ac97_lpc
30252890 l     O .vmlinux	00000008 __pci_fixup_resumePCI_VENDOR_ID_SIPCI_DEVICE_ID_SI_503quirk_sis_503
300ce460 l     F .vmlinux	0000009c quirk_sis_503
30252480 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_SIPCI_DEVICE_ID_SI_503quirk_sis_503
30252898 l     O .vmlinux	00000008 __pci_fixup_resumePCI_VENDOR_ID_SIPCI_DEVICE_ID_SI_LPCquirk_sis_96x_smbus
300ce404 l     F .vmlinux	0000005c quirk_sis_96x_smbus
302528a0 l     O .vmlinux	00000008 __pci_fixup_resumePCI_VENDOR_ID_SIPCI_DEVICE_ID_SI_963quirk_sis_96x_smbus
302528a8 l     O .vmlinux	00000008 __pci_fixup_resumePCI_VENDOR_ID_SIPCI_DEVICE_ID_SI_962quirk_sis_96x_smbus
302528b0 l     O .vmlinux	00000008 __pci_fixup_resumePCI_VENDOR_ID_SIPCI_DEVICE_ID_SI_961quirk_sis_96x_smbus
30252488 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_SIPCI_DEVICE_ID_SI_LPCquirk_sis_96x_smbus
30252490 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_SIPCI_DEVICE_ID_SI_963quirk_sis_96x_smbus
30252498 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_SIPCI_DEVICE_ID_SI_962quirk_sis_96x_smbus
302524a0 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_SIPCI_DEVICE_ID_SI_961quirk_sis_96x_smbus
302528b8 l     O .vmlinux	00000008 __pci_fixup_resumePCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_ICH6_1asus_hides_smbus_lpc_ich6
300ce330 l     F .vmlinux	000000d4 asus_hides_smbus_lpc_ich6
302524a8 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_ICH6_1asus_hides_smbus_lpc_ich6
302528c0 l     O .vmlinux	00000008 __pci_fixup_resumePCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82801EB_0asus_hides_smbus_lpc
300ce28c l     F .vmlinux	000000a4 asus_hides_smbus_lpc
302528c8 l     O .vmlinux	00000008 __pci_fixup_resumePCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82801DB_12asus_hides_smbus_lpc
302528d0 l     O .vmlinux	00000008 __pci_fixup_resumePCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82801CA_12asus_hides_smbus_lpc
302528d8 l     O .vmlinux	00000008 __pci_fixup_resumePCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82801CA_0asus_hides_smbus_lpc
302528e0 l     O .vmlinux	00000008 __pci_fixup_resumePCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82801BA_0asus_hides_smbus_lpc
302528e8 l     O .vmlinux	00000008 __pci_fixup_resumePCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82801DB_0asus_hides_smbus_lpc
302524b0 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82801EB_0asus_hides_smbus_lpc
302524b8 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82801DB_12asus_hides_smbus_lpc
302524c0 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82801CA_12asus_hides_smbus_lpc
302524c8 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82801CA_0asus_hides_smbus_lpc
302524d0 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82801BA_0asus_hides_smbus_lpc
302524d8 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82801DB_0asus_hides_smbus_lpc
302524e0 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82915GM_HBasus_hides_smbus_hostbridge
3028a140 l     F .vmlinux	0000034c asus_hides_smbus_hostbridge
302524e8 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82855GM_HBasus_hides_smbus_hostbridge
302524f0 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82855PM_HBasus_hides_smbus_hostbridge
302524f8 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_E7501_MCHasus_hides_smbus_hostbridge
30252500 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_7205_0asus_hides_smbus_hostbridge
30252508 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82865_HBasus_hides_smbus_hostbridge
30252510 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82850_HBasus_hides_smbus_hostbridge
30252518 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82845G_HBasus_hides_smbus_hostbridge
30252520 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82845_HBasus_hides_smbus_hostbridge
302528f0 l     O .vmlinux	00000008 __pci_fixup_resumePCI_VENDOR_ID_VIAPCI_DEVICE_ID_VIA_8237k8t_sound_hostbridge
300ce1d8 l     F .vmlinux	000000b4 k8t_sound_hostbridge
30252528 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_VIAPCI_DEVICE_ID_VIA_8237k8t_sound_hostbridge
30252530 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82375quirk_eisa_bridge
3028a130 l     F .vmlinux	00000010 quirk_eisa_bridge
30252448 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82801CA_10quirk_ide_samemode
3028a0a4 l     F .vmlinux	0000008c quirk_ide_samemode
30252450 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_SERVERWORKSPCI_DEVICE_ID_SERVERWORKS_CSB5IDEquirk_svwks_csb5ide
3028a04c l     F .vmlinux	00000058 quirk_svwks_csb5ide
30252538 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_ATIPCI_DEVICE_ID_ATI_IXP600_SATAquirk_sb600_sata
30289fb8 l     F .vmlinux	00000094 quirk_sb600_sata
302528f8 l     O .vmlinux	00000008 __pci_fixup_resumePCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82454NXquirk_disable_pxb
300ce15c l     F .vmlinux	0000007c quirk_disable_pxb
30252758 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82454NXquirk_disable_pxb
30252900 l     O .vmlinux	00000008 __pci_fixup_resumePCI_VENDOR_ID_CYRIXPCI_DEVICE_ID_CYRIX_PCI_MASTERquirk_mediagx_master
300ce100 l     F .vmlinux	0000005c quirk_mediagx_master
30252760 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_CYRIXPCI_DEVICE_ID_CYRIX_PCI_MASTERquirk_mediagx_master
30252540 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_TOSHIBA0x605quirk_transparent_bridge
30289fa4 l     F .vmlinux	00000014 quirk_transparent_bridge
30252548 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82380FBquirk_transparent_bridge
30252550 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_DUNORDPCI_DEVICE_ID_DUNORD_I3000quirk_dunord
30289f90 l     F .vmlinux	00000014 quirk_dunord
30252908 l     O .vmlinux	00000008 __pci_fixup_resumePCI_VENDOR_ID_AMDPCI_DEVICE_ID_AMD_FE_GATE_700Cquirk_amd_ordering
300ce06c l     F .vmlinux	00000094 quirk_amd_ordering
30252768 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_AMDPCI_DEVICE_ID_AMD_FE_GATE_700Cquirk_amd_ordering
30252910 l     O .vmlinux	00000008 __pci_fixup_resumePCI_ANY_IDPCI_ANY_IDquirk_cardbus_legacy
300ce030 l     F .vmlinux	0000003c quirk_cardbus_legacy
30252770 l     O .vmlinux	00000008 __pci_fixup_PCI_ANY_IDPCI_ANY_IDquirk_cardbus_legacy
30252558 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_VIAPCI_DEVICE_ID_VIA_82C597_0quirk_vt82c598_id
30289f5c l     F .vmlinux	00000034 quirk_vt82c598_id
30252878 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_VIAPCI_ANY_IDquirk_via_vlink
300cdf60 l     F .vmlinux	000000d0 quirk_via_vlink
30252560 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_VIAPCI_DEVICE_ID_VIA_8237Aquirk_via_bridge
300cde7c l     F .vmlinux	000000e4 quirk_via_bridge
30252568 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_VIAPCI_DEVICE_ID_VIA_8237quirk_via_bridge
30252570 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_VIAPCI_DEVICE_ID_VIA_8235quirk_via_bridge
30252578 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_VIAPCI_DEVICE_ID_VIA_8233C_0quirk_via_bridge
30252580 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_VIAPCI_DEVICE_ID_VIA_8233Aquirk_via_bridge
30252588 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_VIAPCI_DEVICE_ID_VIA_8233_0quirk_via_bridge
30252590 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_VIAPCI_DEVICE_ID_VIA_8231quirk_via_bridge
30252598 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_VIAPCI_DEVICE_ID_VIA_82C686quirk_via_bridge
302525a0 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_VIAPCI_DEVICE_ID_VIA_82C686_4quirk_via_acpi
30289f10 l     F .vmlinux	0000004c quirk_via_acpi
302525a8 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_VIAPCI_DEVICE_ID_VIA_82C586_3quirk_via_acpi
302525b0 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_VIAPCI_DEVICE_ID_VIA_8235quirk_vt8235_acpi
30289e80 l     F .vmlinux	00000090 quirk_vt8235_acpi
302525b8 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_VIAPCI_DEVICE_ID_VIA_82C686_4quirk_vt82c686_acpi
30289df0 l     F .vmlinux	00000090 quirk_vt82c686_acpi
302525c0 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_VIAPCI_DEVICE_ID_VIA_82C586_3quirk_vt82c586_acpi
30289d88 l     F .vmlinux	00000068 quirk_vt82c586_acpi
302525c8 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_ICH8_3quirk_ich6_lpc_acpi
30289d14 l     F .vmlinux	00000074 quirk_ich6_lpc_acpi
302525d0 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_ICH8_2quirk_ich6_lpc_acpi
302525d8 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_ICH8_0quirk_ich6_lpc_acpi
302525e0 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_ICH7_31quirk_ich6_lpc_acpi
302525e8 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_ICH7_1quirk_ich6_lpc_acpi
302525f0 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_ICH7_0quirk_ich6_lpc_acpi
302525f8 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_ICH6_1quirk_ich6_lpc_acpi
30252600 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_ICH6_0quirk_ich6_lpc_acpi
30252608 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_ESB_1quirk_ich4_lpc_acpi
30289ca0 l     F .vmlinux	00000074 quirk_ich4_lpc_acpi
30252610 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82801EB_0quirk_ich4_lpc_acpi
30252618 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82801DB_12quirk_ich4_lpc_acpi
30252620 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82801DB_0quirk_ich4_lpc_acpi
30252628 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82801CA_12quirk_ich4_lpc_acpi
30252630 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82801CA_0quirk_ich4_lpc_acpi
30252638 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82801BA_10quirk_ich4_lpc_acpi
30252640 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82801BA_0quirk_ich4_lpc_acpi
30252648 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82801AB_0quirk_ich4_lpc_acpi
30252650 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82801AA_0quirk_ich4_lpc_acpi
30252658 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82443MX_3quirk_piix4_acpi
30289b10 l     F .vmlinux	00000190 quirk_piix4_acpi
30252660 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82371AB_3quirk_piix4_acpi
30252668 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_ALPCI_DEVICE_ID_AL_M7101quirk_ali7101_acpi
30289a9c l     F .vmlinux	00000074 quirk_ali7101_acpi
30252778 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_ATIPCI_DEVICE_ID_ATI_RS100quirk_ati_exploding_mce
30289a58 l     F .vmlinux	00000044 quirk_ati_exploding_mce
30252670 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_S3PCI_DEVICE_ID_S3_968quirk_s3_64M
30289994 l     F .vmlinux	0000003c quirk_s3_64M
30252678 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_S3PCI_DEVICE_ID_S3_868quirk_s3_64M
30252680 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_IBMPCI_DEVICE_ID_IBM_CITRINEquirk_citrine
30289988 l     F .vmlinux	0000000c quirk_citrine
30252780 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82443BX_2quirk_natoma
30289950 l     F .vmlinux	00000038 quirk_natoma
30252788 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82443BX_1quirk_natoma
30252790 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82443BX_0quirk_natoma
30252798 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82443LX_1quirk_natoma
302527a0 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82443LX_0quirk_natoma
302527a8 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82441quirk_natoma
302527b0 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_ALPCI_DEVICE_ID_AL_M1651quirk_alimagik
30289918 l     F .vmlinux	00000038 quirk_alimagik
302527b8 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_ALPCI_DEVICE_ID_AL_M1647quirk_alimagik
302527c0 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_VIAPCI_DEVICE_ID_VIA_82C576quirk_vsfx
302898e0 l     F .vmlinux	00000038 quirk_vsfx
302527c8 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_VIAPCI_DEVICE_ID_VIA_82C597_0quirk_viaetbf
302898a8 l     F .vmlinux	00000038 quirk_viaetbf
30252918 l     O .vmlinux	00000008 __pci_fixup_resumePCI_VENDOR_ID_VIAPCI_DEVICE_ID_VIA_8361quirk_vialatency
300cdc98 l     F .vmlinux	000000e8 quirk_vialatency
30252920 l     O .vmlinux	00000008 __pci_fixup_resumePCI_VENDOR_ID_VIAPCI_DEVICE_ID_VIA_8371_1quirk_vialatency
30252928 l     O .vmlinux	00000008 __pci_fixup_resumePCI_VENDOR_ID_VIAPCI_DEVICE_ID_VIA_8363_0quirk_vialatency
302527d0 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_VIAPCI_DEVICE_ID_VIA_8361quirk_vialatency
302527d8 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_VIAPCI_DEVICE_ID_VIA_8371_1quirk_vialatency
302527e0 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_VIAPCI_DEVICE_ID_VIA_8363_0quirk_vialatency
302527e8 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82439TXquirk_triton
30289870 l     F .vmlinux	00000038 quirk_triton
302527f0 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82439quirk_triton
302527f8 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82437VXquirk_triton
30252800 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82437quirk_triton
30252808 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_AMDPCI_DEVICE_ID_AMD_8151_0quirk_nopciamd
30289824 l     F .vmlinux	0000004c quirk_nopciamd
30252810 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_SIPCI_DEVICE_ID_SI_496quirk_nopcipci
302897ec l     F .vmlinux	00000038 quirk_nopcipci
30252818 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_SIPCI_DEVICE_ID_SI_5597quirk_nopcipci
30252820 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_NECPCI_DEVICE_ID_NEC_CBUS_3quirk_isa_dma_hangs
302897b4 l     F .vmlinux	00000038 quirk_isa_dma_hangs
30252828 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_NECPCI_DEVICE_ID_NEC_CBUS_2quirk_isa_dma_hangs
30252830 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_NECPCI_DEVICE_ID_NEC_CBUS_1quirk_isa_dma_hangs
30252838 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_ALPCI_DEVICE_ID_AL_M1533quirk_isa_dma_hangs
30252840 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82371SB_0quirk_isa_dma_hangs
30252848 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_VIAPCI_DEVICE_ID_VIA_82C596quirk_isa_dma_hangs
30252850 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_VIAPCI_DEVICE_ID_VIA_82C586_0quirk_isa_dma_hangs
30252930 l     O .vmlinux	00000008 __pci_fixup_resumePCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82441quirk_passive_release
300cdc10 l     F .vmlinux	00000088 quirk_passive_release
30252858 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_INTELPCI_DEVICE_ID_INTEL_82441quirk_passive_release
30252860 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_MELLANOXPCI_DEVICE_ID_MELLANOX_TAVOR_BRIDGEquirk_mellanox_tavor
302897a0 l     F .vmlinux	00000014 quirk_mellanox_tavor
30252868 l     O .vmlinux	00000008 __pci_fixup_PCI_VENDOR_ID_MELLANOXPCI_DEVICE_ID_MELLANOX_TAVORquirk_mellanox_tavor
3025937c l     O .vmlinux	00000004 via_vlink_dev_hi
30259380 l     O .vmlinux	00000004 via_vlink_dev_lo
302899d0 l     F .vmlinux	00000088 quirk_io_region
300cdd80 l     F .vmlinux	00000080 piix4_io_quirk
300cde00 l     F .vmlinux	0000007c piix4_mem_quirk
306159d4 l     O .bss	00000004 asus_hides_smbus
306159d8 l     O .bss	00000004 combined_mode
00000000 l    df *ABS*	00000000 pci-driver.c
302ba370 l     O .vmlinux	00000004 __initcall_pci_driver_init2
3028aa2c l     F .vmlinux	00000018 pci_driver_init
300cecac l     F .vmlinux	00000020 pci_bus_match
300ced84 l     F .vmlinux	00000090 pci_device_probe
300ced18 l     F .vmlinux	0000006c pci_device_remove
300ceac4 l     F .vmlinux	0000003c pci_device_shutdown
300ce950 l     F .vmlinux	0000006c pci_device_suspend
300ce9bc l     F .vmlinux	00000048 pci_device_suspend_late
300cea7c l     F .vmlinux	00000048 pci_device_resume_early
300cea04 l     F .vmlinux	00000078 pci_device_resume
30252ea8 l     O .vmlinux	00000014 __param_pci_multithread_probe
302594e8 l     O .vmlinux	00000016 __param_str_pci_multithread_probe
306159dc l     O .bss	00000004 pci_multithread_probe
30259500 l     O .vmlinux	000000e4 pci_compat_driver
302595e4 l     O .vmlinux	0000000c pci_driver_kobj_type
302595f0 l     O .vmlinux	00000008 pci_driver_sysfs_ops
300ceb00 l     F .vmlinux	0000005c pci_driver_attr_show
300ceb5c l     F .vmlinux	00000060 pci_driver_attr_store
00000000 l    df *ABS*	00000000 search.c
300cee1c l     F .vmlinux	00000054 pci_do_find_bus
30229c78 l     O .vmlinux	00000012 __func__.6
30229c90 l     O .vmlinux	0000000d __func__.5
30229ca0 l     O .vmlinux	00000010 __func__.4
30229cb0 l     O .vmlinux	0000000f __func__.3
30229cc0 l     O .vmlinux	00000017 __func__.2
30229cd8 l     O .vmlinux	0000000e __func__.1
30229ce8 l     O .vmlinux	00000011 __func__.0
00000000 l    df *ABS*	00000000 pci-sysfs.c
302ba438 l     O .vmlinux	00000004 __initcall_pci_sysfs_init6
3028aa44 l     F .vmlinux	0000004c pci_sysfs_init
300cf8a4 l     F .vmlinux	00000088 resource_show
300cf704 l     F .vmlinux	00000024 vendor_show
300cf728 l     F .vmlinux	00000024 device_show
300cf74c l     F .vmlinux	00000024 subsystem_vendor_show
300cf770 l     F .vmlinux	00000024 subsystem_device_show
300cf794 l     F .vmlinux	00000024 class_show
300cf7b8 l     F .vmlinux	00000024 irq_show
300cf860 l     F .vmlinux	00000044 local_cpus_show
300cf92c l     F .vmlinux	00000050 modalias_show
300cfa04 l     F .vmlinux	00000024 is_enabled_show
300cf97c l     F .vmlinux	00000088 is_enabled_store
300cf7dc l     F .vmlinux	00000028 broken_parity_status_show
300cf804 l     F .vmlinux	0000005c broken_parity_status_store
300cfa28 l     F .vmlinux	00000038 msi_bus_show
300cfa60 l     F .vmlinux	000000ac msi_bus_store
30259708 l     O .vmlinux	00000020 pcie_config_attr
300cfb0c l     F .vmlinux	00000204 pci_read_config
300cfd10 l     F .vmlinux	000001c4 pci_write_config
30259728 l     O .vmlinux	00000020 pci_config_attr
300cfed4 l     F .vmlinux	00000044 pci_write_rom
300cff18 l     F .vmlinux	000000d8 pci_read_rom
306159e0 l     O .bss	00000004 sysfs_initialized
00000000 l    df *ABS*	00000000 rom.c
300d0224 l     F .vmlinux	00000040 pci_disable_rom
00000000 l    df *ABS*	00000000 setup-res.c
00000000 l    df *ABS*	00000000 proc.c
302ba43c l     O .vmlinux	00000004 __initcall_pci_proc_init6
3028acec l     F .vmlinux	00000088 pci_proc_init
30229d00 l     O .vmlinux	0000006c proc_bus_pci_dev_operations
300d1214 l     F .vmlinux	0000001c proc_bus_pci_dev_open
30259748 l     O .vmlinux	00000010 proc_bus_pci_devices_op
300d0f24 l     F .vmlinux	0000004c pci_seq_start
300d0f9c l     F .vmlinux	00000024 pci_seq_stop
300d0f70 l     F .vmlinux	0000002c pci_seq_next
300d0fc0 l     F .vmlinux	0000010c show_device
30229d6c l     O .vmlinux	0000006c proc_bus_pci_operations
300d09e4 l     F .vmlinux	000000c4 proc_bus_pci_lseek
300d0aa8 l     F .vmlinux	00000244 proc_bus_pci_read
300d0cec l     F .vmlinux	00000218 proc_bus_pci_write
300d0f04 l     F .vmlinux	00000020 proc_bus_pci_ioctl
306159e4 l     O .bss	00000004 proc_initialized
306159e8 l     O .bss	00000004 proc_bus_pci_dir
00000000 l    df *ABS*	00000000 setup-bus.c
3028ad74 l     F .vmlinux	00000090 find_free_bus_resource
3028ae04 l     F .vmlinux	0000027c pbus_size_mem
00000000 l    df *ABS*	00000000 syscall.c
00000000 l    df *ABS*	00000000 fb_notify.c
30259758 l     O .vmlinux	00000010 fb_notifier_list
00000000 l    df *ABS*	00000000 fbmem.c
302ba0c0 l     O .vmlinux	0000000c __setup_video_setup
302afd28 l     O .vmlinux	00000007 __setup_str_video_setup
3028b9a0 l     F .vmlinux	000000f8 video_setup
302ba390 l     O .vmlinux	00000004 __initcall_fbmem_init4
3028b8c0 l     F .vmlinux	000000e0 fbmem_init
30229dd8 l     O .vmlinux	0000006c fb_fops
300d252c l     F .vmlinux	00000230 fb_read
300d275c l     F .vmlinux	00000244 fb_write
300d2d7c l     F .vmlinux	0000044c fb_ioctl
300d31c8 l     F .vmlinux	00000074 fb_mmap
300d323c l     F .vmlinux	00000074 fb_open
300d32b0 l     F .vmlinux	0000002c fb_release
30615a74 l     O .bss	00000014 fb_logo
30229e48 l     O .vmlinux	00000009 mask.0
300d2490 l     F .vmlinux	0000009c fbmem_read_proc
30615b0c l     O .bss	00000004 ofonly
30615a8c l     O .bss	00000080 video_options
00000000 l    df *ABS*	00000000 fbmon.c
00000000 l    df *ABS*	00000000 fbcmap.c
30259768 l     O .vmlinux	00000020 blue16
30259788 l     O .vmlinux	00000020 green16
302597a8 l     O .vmlinux	00000020 red16
302597c8 l     O .vmlinux	00000010 blue8
302597d8 l     O .vmlinux	00000010 green8
302597e8 l     O .vmlinux	00000010 red8
302597f8 l     O .vmlinux	00000008 blue4
30259800 l     O .vmlinux	00000008 green4
30259808 l     O .vmlinux	00000008 red4
30259810 l     O .vmlinux	00000004 blue2
30259814 l     O .vmlinux	00000004 green2
30259818 l     O .vmlinux	00000004 red2
30229e58 l     O .vmlinux	00000018 default_16_colors
30229e70 l     O .vmlinux	00000018 default_8_colors
30229e88 l     O .vmlinux	00000018 default_4_colors
30229ea0 l     O .vmlinux	00000018 default_2_colors
00000000 l    df *ABS*	00000000 fbsysfs.c
3025981c l     O .vmlinux	000000f0 device_attrs
300d45fc l     F .vmlinux	00000028 show_bpp
300d45a8 l     F .vmlinux	00000054 store_bpp
300d47e8 l     F .vmlinux	00000008 show_blank
300d477c l     F .vmlinux	0000006c store_blank
300d47f8 l     F .vmlinux	00000008 show_console
300d47f0 l     F .vmlinux	00000008 store_console
300d4808 l     F .vmlinux	00000008 show_cursor
300d4800 l     F .vmlinux	00000008 store_cursor
300d4440 l     F .vmlinux	0000002c show_mode
300d4378 l     F .vmlinux	000000c8 store_mode
300d4564 l     F .vmlinux	00000044 show_modes
300d446c l     F .vmlinux	000000f8 store_modes
300d48a8 l     F .vmlinux	0000002c show_pan
300d4810 l     F .vmlinux	00000098 store_pan
300d4728 l     F .vmlinux	0000002c show_virtual
300d46a0 l     F .vmlinux	00000088 store_virtual
300d48d4 l     F .vmlinux	00000028 show_name
300d4754 l     F .vmlinux	00000028 show_stride
300d4678 l     F .vmlinux	00000028 show_rotate
300d4624 l     F .vmlinux	00000054 store_rotate
300d4940 l     F .vmlinux	00000028 show_fbstate
300d48fc l     F .vmlinux	00000044 store_fbstate
300d429c l     F .vmlinux	00000050 activate
300d42ec l     F .vmlinux	0000008c mode_string
00000000 l    df *ABS*	00000000 modedb.c
30229eb8 l     O .vmlinux	00000c40 modedb
300d4b7c l     F .vmlinux	00000038 my_atoi
300d4bb4 l     F .vmlinux	000000c0 fb_try_mode
00000000 l    df *ABS*	00000000 fbcvt.c
3022aaf8 l     O .vmlinux	00000008 fb_cvt_vbi_tab
00000000 l    df *ABS*	00000000 dummycon.c
300d60ec l     F .vmlinux	0000000c dummycon_startup
300d60f8 l     F .vmlinux	0000003c dummycon_init
300d6134 l     F .vmlinux	00000008 dummycon_dummy
00000000 l    df *ABS*	00000000 fbcon.c
302ba440 l     O .vmlinux	00000004 __initcall_fb_console_init6
3028bf70 l     F .vmlinux	0000017c fb_console_init
302ba0cc l     O .vmlinux	0000000c __setup_fb_console_setup
302afd30 l     O .vmlinux	00000007 __setup_str_fb_console_setup
3028ba98 l     F .vmlinux	000004d8 fb_console_setup
3025990c l     O .vmlinux	00000004 fbcon_is_default
30259910 l     O .vmlinux	00000004 last_fb_vc
30259914 l     O .vmlinux	00000004 fbcon_softback_size
30259918 l     O .vmlinux	0000000c fbcon_event_notifier
300dbb50 l     F .vmlinux	00000efc fbcon_event_notify
30615b18 l     O .bss	00000004 scrollback_max
30615b1c l     O .bss	00000004 scrollback_current
30615b20 l     O .bss	00000004 scrollback_phys_max
30259924 l     O .vmlinux	00000004 logo_shown
30259928 l     O .vmlinux	00000018 palette_cmap
30617890 l     O .bss	00000020 palette_red
306178b0 l     O .bss	00000020 palette_green
306178d0 l     O .bss	00000020 palette_blue
30259940 l     O .vmlinux	00000004 info_idx
3022ab64 l     O .vmlinux	00000064 fb_con
300d6ea4 l     F .vmlinux	000002c0 fbcon_startup
300d7164 l     F .vmlinux	000004a0 fbcon_init
300d7604 l     F .vmlinux	0000023c fbcon_deinit
300d7840 l     F .vmlinux	0000015c fbcon_clear
300d7cc0 l     F .vmlinux	0000002c fbcon_putc
300d799c l     F .vmlinux	00000324 fbcon_putcs
300d9a14 l     F .vmlinux	00000340 fbcon_cursor
300d9f78 l     F .vmlinux	00000d80 fbcon_scroll
300d87e0 l     F .vmlinux	000000cc fbcon_bmove
300db3ec l     F .vmlinux	00000764 fbcon_switch
300d9d54 l     F .vmlinux	00000224 fbcon_blank
300db1e0 l     F .vmlinux	0000020c fbcon_set_font
300d8d74 l     F .vmlinux	000001d4 fbcon_get_font
300db140 l     F .vmlinux	000000a0 fbcon_set_def_font
300db0e8 l     F .vmlinux	00000058 fbcon_copy_font
300d88ac l     F .vmlinux	000004c8 fbcon_resize
300d8f48 l     F .vmlinux	00000164 fbcon_set_palette
300d93b4 l     F .vmlinux	00000634 fbcon_scrolldelta
300d99e8 l     F .vmlinux	0000002c fbcon_set_origin
300d92ac l     F .vmlinux	00000108 fbcon_invert_region
300d90ac l     F .vmlinux	0000009c fbcon_screen_pos
300d9148 l     F .vmlinux	00000164 fbcon_getxy
30259944 l     O .vmlinux	00000028 class_device_attrs
300dcb5c l     F .vmlinux	00000090 show_rotate
300dca4c l     F .vmlinux	00000088 store_rotate
300dcad4 l     F .vmlinux	00000088 store_rotate_all
300d6274 l     F .vmlinux	0000005c fbcon_update_softback
30617838 l     O .bss	00000004 softback_buf
30617848 l     O .bss	00000004 softback_end
30617844 l     O .bss	00000004 softback_top
300d62d0 l     F .vmlinux	0000034c fb_flashcursor
306177b0 l     O .bss	0000003f con2fb_map
3061784c l     O .bss	00000004 softback_lines
300d661c l     F .vmlinux	00000028 cursor_timer_handler
300d6644 l     F .vmlinux	000000b4 fbcon_add_cursor_timer
300d66f8 l     F .vmlinux	00000048 fbcon_del_cursor_timer
30617858 l     O .bss	00000028 fontname
30617850 l     O .bss	00000004 first_fb_vc
30617880 l     O .bss	00000004 rotate
306177f0 l     O .bss	0000003f con2fb_map_boot
300d6740 l     F .vmlinux	00000058 search_fb_in_map
300d6798 l     F .vmlinux	000000d8 fbcon_takeover
300d6870 l     F .vmlinux	00000074 fbcon_clear_margins
300d68e4 l     F .vmlinux	00000350 fbcon_prepare_logo
30617830 l     O .bss	00000004 logo_height
30617834 l     O .bss	00000004 logo_lines
300d6c34 l     F .vmlinux	00000054 set_blitting_type
30615b24 l     O .bss	00001c8c fb_display
300d6c88 l     F .vmlinux	000000d4 var_to_display
300d6d5c l     F .vmlinux	00000088 fbcon_preset_disp
300d6de4 l     F .vmlinux	000000c0 display_to_var
30617840 l     O .bss	00000004 softback_in
3061783c l     O .bss	00000004 softback_curr
30617854 l     O .bss	00000004 fbcon_has_exited
300d7cec l     F .vmlinux	000002b4 fbcon_set_disp
300d7fa0 l     F .vmlinux	000003e4 set_con2fb_map
300d8384 l     F .vmlinux	00000118 fbcon_redraw_move
300d849c l     F .vmlinux	000001c0 fbcon_redraw
300d865c l     F .vmlinux	00000184 fbcon_bmove_rec
30617888 l     O .bss	00000004 vbl_cursor_cnt
300dacf8 l     F .vmlinux	000003f0 fbcon_do_set_font
3061788c l     O .bss	00000004 fbcon_class_device
30617884 l     O .bss	00000004 fbcon_has_sysfs
00000000 l    df *ABS*	00000000 bitblit.c
300dcc04 l     F .vmlinux	0000008c bit_bmove
300dcc90 l     F .vmlinux	0000009c bit_clear
300dcd2c l     F .vmlinux	000005a0 bit_putcs
300dd2cc l     F .vmlinux	00000110 bit_clear_margins
300dd3dc l     F .vmlinux	000005b8 bit_cursor
300dd994 l     F .vmlinux	00000034 bit_update_start
00000000 l    df *ABS*	00000000 fonts.c
3025996c l     O .vmlinux	00000004 fonts
00000000 l    df *ABS*	00000000 font_8x16.c
3022abe0 l     O .vmlinux	00001000 fontdata_8x16
00000000 l    df *ABS*	00000000 softcursor.c
00000000 l    df *ABS*	00000000 logo.c
00000000 l    df *ABS*	00000000 logo_linux_mono.c
302afd50 l     O .vmlinux	00000320 logo_linux_mono_data
00000000 l    df *ABS*	00000000 logo_linux_vga16.c
302b0088 l     O .vmlinux	00000c80 logo_linux_vga16_data
00000000 l    df *ABS*	00000000 logo_linux_clut224.c
302b2620 l     O .vmlinux	00000231 logo_linux_clut224_clut
302b0d20 l     O .vmlinux	00001900 logo_linux_clut224_data
00000000 l    df *ABS*	00000000 logo_sun_clut224.c
302b4170 l     O .vmlinux	00000297 logo_sun_clut224_clut
302b2870 l     O .vmlinux	00001900 logo_sun_clut224_data
00000000 l    df *ABS*	00000000 grvga.c
302ba444 l     O .vmlinux	00000004 __initcall_grvga_init6
30259970 l     O .vmlinux	00000150 grvga_device
300de5bc l     F .vmlinux	00000008 grvga_platform_release
30259ac0 l     O .vmlinux	000000a0 grvga_driver
3028c728 l     F .vmlinux	000002f4 grvga_probe
300de5c4 l     F .vmlinux	0000002c grvga_remove
306178f0 l     O .bss	00000004 running
30259b60 l     O .vmlinux	00000058 grvga_ops
300dddfc l     F .vmlinux	00000268 grvga_check_var
300de064 l     F .vmlinux	00000270 grvga_set_par
300de2d4 l     F .vmlinux	00000198 grvga_setcolreg
300de5b4 l     F .vmlinux	00000008 grvga_fb_blank
300de46c l     F .vmlinux	000000ac grvga_pan_display
300de518 l     F .vmlinux	0000009c grvga_mmap
306178f4 l     O .bss	00000001 fb_hard
302b4408 l     O .vmlinux	000000a0 m800x480
302b44a8 l     O .vmlinux	000000a0 m800x600x72
302b4548 l     O .vmlinux	000000a0 m800x600x60
302b45e8 l     O .vmlinux	000000a0 m1024x768
302b4688 l     O .vmlinux	00000044 grvga_fix
302b46cc l     O .vmlinux	000000a0 m640x480
300dddd8 l     F .vmlinux	00000024 get_line_length
306178f8 l     O .bss	00000004 mem_size
30617900 l     O .bss	000000a0 screendata
306179a0 l     O .bss	00000044 screeninfo
306178fc l     O .bss	00000004 fb_addr
00000000 l    df *ABS*	00000000 cfbfillrect.c
300de674 l     F .vmlinux	00000144 bitfill_aligned
300de7b8 l     F .vmlinux	00000160 bitfill_unaligned
300de918 l     F .vmlinux	00000160 bitfill_aligned_rev
300dea78 l     F .vmlinux	0000016c bitfill_unaligned_rev
00000000 l    df *ABS*	00000000 cfbcopyarea.c
00000000 l    df *ABS*	00000000 cfbimgblt.c
3022bbe0 l     O .vmlinux	00000008 cfb_tab32
3022bbe8 l     O .vmlinux	00000010 cfb_tab16
3022bbf8 l     O .vmlinux	00000040 cfb_tab8
00000000 l    df *ABS*	00000000 amba.c
30259bb8 l     O .vmlinux	00000004 allocate_child.0
00000000 l    df *ABS*	00000000 amba_driver.c
00000000 l    df *ABS*	00000000 amba_proc.c
302ba448 l     O .vmlinux	00000004 __initcall_amba_proc_init6
3028cab8 l     F .vmlinux	0000004c amba_proc_init
00000000 l    df *ABS*	00000000 apbuart.c
302ba44c l     O .vmlinux	00000004 __initcall_gaisler_apbuart_init6
3028cd38 l     F .vmlinux	00000308 gaisler_apbuart_init
302ba5cc l     O .vmlinux	00000004 __initcall_leonuart_console_init
3028cd14 l     F .vmlinux	00000024 leonuart_console_init
30259bbc l     O .vmlinux	0000002c leon_console
300e195c l     F .vmlinux	000000cc leonuart_console_write
3028cbf0 l     F .vmlinux	00000124 leonuart_console_setup
30259be8 l     O .vmlinux	00000024 leon_reg
30259c0c l     O .vmlinux	00000050 leon_pops
300e16dc l     F .vmlinux	00000018 leonuart_tx_empty
300e16fc l     F .vmlinux	00000008 leonuart_set_mctrl
300e16f4 l     F .vmlinux	00000008 leonuart_get_mctrl
300e12dc l     F .vmlinux	0000001c leonuart_stop_tx
300e13f8 l     F .vmlinux	00000044 leonuart_start_tx
300e143c l     F .vmlinux	0000001c leonuart_stop_rx
300e1458 l     F .vmlinux	00000008 leonuart_enable_ms
300e1704 l     F .vmlinux	00000008 leonuart_break_ctl
300e170c l     F .vmlinux	00000050 leonuart_startup
300e175c l     F .vmlinux	0000002c leonuart_shutdown
300e1788 l     F .vmlinux	00000134 leonuart_set_termios
300e18bc l     F .vmlinux	00000020 leonuart_type
300e18dc l     F .vmlinux	00000008 leonuart_release_port
300e18e4 l     F .vmlinux	00000008 leonuart_request_port
300e18ec l     F .vmlinux	00000018 leonuart_config_port
300e1904 l     F .vmlinux	00000058 leonuart_verify_port
30618158 l     O .bss	00000004 _apbuart_init_bases_done
3028cb04 l     F .vmlinux	000000ec _apbuart_init_bases
3061815c l     O .bss	00000420 leon_ports
00000000 l    df *ABS*	00000000 mem.c
302ba3b0 l     O .vmlinux	00000004 __initcall_chr_dev_init5
3028d040 l     F .vmlinux	0000009c chr_dev_init
3022bc38 l     O .vmlinux	00000090 devlist
3022bf50 l     O .vmlinux	0000006c mem_fops
3022bee4 l     O .vmlinux	0000006c kmem_fops
3022be78 l     O .vmlinux	0000006c null_fops
3022be0c l     O .vmlinux	0000006c port_fops
3022bda0 l     O .vmlinux	0000006c zero_fops
3022bd34 l     O .vmlinux	0000006c full_fops
3022bcc8 l     O .vmlinux	0000006c kmsg_fops
300e2978 l     F .vmlinux	000000b8 kmsg_write
300e28c4 l     F .vmlinux	00000018 null_lseek
300e262c l     F .vmlinux	0000024c read_zero
300e28bc l     F .vmlinux	00000008 write_full
300e2604 l     F .vmlinux	00000008 write_null
300e2878 l     F .vmlinux	00000044 mmap_zero
300e28dc l     F .vmlinux	00000080 memory_lseek
300e249c l     F .vmlinux	000000ac read_port
300e2548 l     F .vmlinux	000000b4 write_port
300e295c l     F .vmlinux	0000001c open_port
300e25fc l     F .vmlinux	00000008 read_null
300e2614 l     F .vmlinux	00000018 splice_write_null
300e1f94 l     F .vmlinux	00000278 read_kmem
300e220c l     F .vmlinux	00000290 write_kmem
300e1f34 l     F .vmlinux	00000060 mmap_kmem
300e1bd8 l     F .vmlinux	00000184 read_mem
300e1d5c l     F .vmlinux	00000144 write_mem
300e1ea0 l     F .vmlinux	00000094 mmap_mem
3022bfbc l     O .vmlinux	0000006c memory_fops
300e2a30 l     F .vmlinux	00000124 memory_open
30259c60 l     O .vmlinux	0000001c zero_bdi
300e260c l     F .vmlinux	00000008 pipe_to_null
30618580 l     O .bss	00000004 mem_class
00000000 l    df *ABS*	00000000 random.c
302ba484 l     O .vmlinux	00000004 __initcall_seqgen_init7
3028d10c l     F .vmlinux	00000014 seqgen_init
30259e14 l     O .vmlinux	00000004 sysctl_poolsize
30259dc4 l     O .vmlinux	00000020 input_pool
30259dc0 l     O .vmlinux	00000004 random_read_wakeup_thresh
30259dbc l     O .vmlinux	00000004 min_read_thresh
30259db8 l     O .vmlinux	00000004 max_read_thresh
30259db4 l     O .vmlinux	00000004 random_write_wakeup_thresh
30618938 l     O .bss	00000004 min_write_thresh
30259db0 l     O .vmlinux	00000004 max_write_thresh
30618940 l     O .bss	00000010 sysctl_bootid
300e3b1c l     F .vmlinux	000000f0 proc_do_uuid
300e3c0c l     F .vmlinux	00000144 uuid_strategy
30259de4 l     O .vmlinux	00000030 poolinfo_table
306185a8 l     O .bss	00000200 input_pool_data
300e36d8 l     F .vmlinux	00000018 urandom_read
300e37a0 l     F .vmlinux	00000118 random_write
300e38b8 l     F .vmlinux	0000022c random_ioctl
300e352c l     F .vmlinux	000001ac random_read
300e36f0 l     F .vmlinux	000000b0 random_poll
302ba450 l     O .vmlinux	00000004 __initcall_rand_initialize6
3028d0dc l     F .vmlinux	00000030 rand_initialize
30259e18 l     O .vmlinux	00000020 nonblocking_pool
30618828 l     O .bss	00000080 nonblocking_pool_data
30259e38 l     O .vmlinux	00000020 blocking_pool
306187a8 l     O .bss	00000080 blocking_pool_data
30259e58 l     O .vmlinux	00000008 random_write_wait
30259e60 l     O .vmlinux	00000008 random_read_wait
30259e68 l     O .vmlinux	00000028 rekey_work
300e3d50 l     F .vmlinux	00000060 rekey_seq_generator
306185a0 l     O .bss	00000004 per_cpu__trickle_count
30259e90 l     O .vmlinux	00000004 trickle_thresh
3022c100 l     O .vmlinux	00000020 twist_table.0
300e2b54 l     F .vmlinux	00000180 __add_entropy_words
300e2cd4 l     F .vmlinux	00000054 credit_entropy_store
300e2d28 l     F .vmlinux	000001a4 add_timer_randomness
306185a4 l     O .bss	00000001 last_value.1
306188a8 l     O .bss	00000010 input_timer_state
306188b8 l     O .bss	00000080 irq_timer_state
300e2fa0 l     F .vmlinux	000000e0 account
300e3080 l     F .vmlinux	0000010c extract_buf
300e318c l     F .vmlinux	00000088 extract_entropy
300e3214 l     F .vmlinux	000000ec xfer_secondary_pool
300e3300 l     F .vmlinux	00000110 extract_entropy_user
300e343c l     F .vmlinux	00000060 init_std_data
306189e0 l     O .bss	00000004 ip_cnt
30618960 l     O .bss	00000080 ip_keydata
00000000 l    df *ABS*	00000000 tty_io.c
302ba454 l     O .vmlinux	00000004 __initcall_tty_init6
3028d1a4 l     F .vmlinux	000001dc tty_init
302ba374 l     O .vmlinux	00000004 __initcall_tty_class_init2
3028d170 l     F .vmlinux	00000034 tty_class_init
3022c120 l     O .vmlinux	0000006c ptmx_fops
300e4ae0 l     F .vmlinux	000000c4 tty_read
300e4ba4 l     F .vmlinux	0000021c tty_write
300e4fc4 l     F .vmlinux	00000084 tty_poll
300e7c00 l     F .vmlinux	00000234 ptmx_open
300e5ccc l     F .vmlinux	00000014 tty_release
300e5048 l     F .vmlinux	000000e0 tty_fasync
3022c18c l     O .vmlinux	0000006c console_fops
300e7888 l     F .vmlinux	00000378 tty_open
3022c1f8 l     O .vmlinux	0000006c tty_fops
3022c264 l     O .vmlinux	0000006c hung_up_tty_fops
300e479c l     F .vmlinux	00000008 hung_up_tty_read
300e47a4 l     F .vmlinux	00000008 hung_up_tty_write
300e47ac l     F .vmlinux	00000008 hung_up_tty_poll
300e47b4 l     F .vmlinux	00000020 hung_up_tty_ioctl
30618a00 l     O .bss	00000000 redirect_lock
30259ed8 l     O .vmlinux	00000008 tty_ldisc_wait
30618a00 l     O .bss	00000010 allocated_ptys
30259ee0 l     O .vmlinux	00000010 allocated_ptys_lock
30618a10 l     O .bss	00000000 tty_ldisc_lock
30259ef0 l     O .vmlinux	00000011 ptychar
300e3e64 l     F .vmlinux	0000001c alloc_tty_struct
300e3e80 l     F .vmlinux	00000050 tty_buffer_free_all
300e3f90 l     F .vmlinux	0000009c check_tty_count
300e4364 l     F .vmlinux	00000024 tty_set_termios_ldisc
30618a14 l     O .bss	000004c8 tty_ldiscs
300e450c l     F .vmlinux	00000020 tty_ldisc_assign
300e452c l     F .vmlinux	00000044 tty_ldisc_try
300e46d4 l     F .vmlinux	0000002c tty_ldisc_enable
300e48e4 l     F .vmlinux	00000040 session_clear_tty
3022c2d0 l     O .vmlinux	00000010 __func__.4
30618a10 l     O .bss	00000004 __warned.5
30618edc l     O .bss	00000004 redirect
300e4e20 l     F .vmlinux	0000002c tty_line_name
300e4e4c l     F .vmlinux	000000c0 release_one_tty
300e4f0c l     F .vmlinux	00000034 release_tty
300e4f40 l     F .vmlinux	00000084 __proc_set_tty
300e5128 l     F .vmlinux	000003dc do_tty_hangup
300e569c l     F .vmlinux	00000630 release_dev
300e5d0c l     F .vmlinux	000000ac send_break
300e6fb8 l     F .vmlinux	00000014 do_SAK_work
3022c2e0 l     O .vmlinux	00000010 __func__.3
300e6ff4 l     F .vmlinux	00000174 flush_to_ldisc
30618a14 l     O .bss	00000000 __key.0
30618a14 l     O .bss	00000000 __key.1
30618a14 l     O .bss	00000000 __key.2
300e71c0 l     F .vmlinux	00000130 initialize_tty_struct
300e72f0 l     F .vmlinux	00000598 init_dev
300e7e34 l     F .vmlinux	0000002c tty_default_put_char
30618ee0 l     O .bss	00000004 tty_class
30618ee4 l     O .bss	00000054 tty_cdev
30618f38 l     O .bss	00000054 console_cdev
30618f8c l     O .bss	00000054 ptmx_cdev
30618fe0 l     O .bss	00000054 vc0_cdev
00000000 l    df *ABS*	00000000 n_tty.c
300e9e9c l     F .vmlinux	00000094 n_tty_open
300e9e6c l     F .vmlinux	00000030 n_tty_close
300e862c l     F .vmlinux	0000005c n_tty_flush_buffer
300e8688 l     F .vmlinux	00000064 n_tty_chars_in_buffer
300ea010 l     F .vmlinux	00000664 read_chan
300ea674 l     F .vmlinux	000003d4 write_chan
300e9a8c l     F .vmlinux	000003e0 n_tty_set_termios
300eaa48 l     F .vmlinux	000001a0 normal_poll
300e89d4 l     F .vmlinux	0000105c n_tty_receive_buf
300e8990 l     F .vmlinux	00000044 n_tty_write_wakeup
300e84d8 l     F .vmlinux	00000044 n_tty_set_room
300e851c l     F .vmlinux	00000040 put_tty_queue_nolock
300e855c l     F .vmlinux	00000028 put_tty_queue
300e8584 l     F .vmlinux	00000054 check_unthrottle
300e85d8 l     F .vmlinux	00000054 reset_buffer_flags
300e86ec l     F .vmlinux	00000214 opost
300e8900 l     F .vmlinux	00000090 echo_char
300e9f30 l     F .vmlinux	000000e0 copy_from_read_buf
00000000 l    df *ABS*	00000000 tty_ioctl.c
3022c2f0 l     O .vmlinux	00000064 baud_table
30259f50 l     O .vmlinux	00000004 n_baud_table
300eadd8 l     F .vmlinux	00000380 change_termios
300eb158 l     F .vmlinux	00000404 set_termios
300eb55c l     F .vmlinux	000000dc send_prio_char
00000000 l    df *ABS*	00000000 pty.c
302ba458 l     O .vmlinux	00000004 __initcall_pty_init6
3028d380 l     F .vmlinux	00000508 pty_init
30619034 l     O .bss	00000004 pty_limit_min
30259fd8 l     O .vmlinux	00000004 pty_limit_max
3022c354 l     O .vmlinux	0000005c pty_ops
300ec9b0 l     F .vmlinux	00000084 pty_open
300ec670 l     F .vmlinux	00000140 pty_close
300ec7ec l     F .vmlinux	00000054 pty_write
300ec840 l     F .vmlinux	0000002c pty_write_room
300ec86c l     F .vmlinux	00000064 pty_chars_in_buffer
300eca34 l     F .vmlinux	00000024 pty_set_termios
300ec7b0 l     F .vmlinux	0000003c pty_unthrottle
300ec93c l     F .vmlinux	00000074 pty_flush_buffer
300ec8d0 l     F .vmlinux	0000006c pty_set_lock
300eca58 l     F .vmlinux	00000028 pty_bsd_ioctl
300eca80 l     F .vmlinux	00000074 pty_unix98_ioctl
30619040 l     O .bss	00000004 pty_driver
30619044 l     O .bss	00000004 pty_slave_driver
3061903c l     O .bss	00000004 pts_driver
00000000 l    df *ABS*	00000000 misc.c
302ba394 l     O .vmlinux	00000004 __initcall_misc_init4
3028d888 l     F .vmlinux	000000a0 misc_init
3022c3b0 l     O .vmlinux	0000006c misc_fops
300ecc48 l     F .vmlinux	00000168 misc_open
3022c41c l     O .vmlinux	0000006c misc_proc_fops
300ecc2c l     F .vmlinux	0000001c misc_seq_open
30259fe0 l     O .vmlinux	00000010 misc_seq_ops
300ecaf4 l     F .vmlinux	000000a4 misc_seq_start
300ecbcc l     F .vmlinux	0000002c misc_seq_stop
300ecb98 l     F .vmlinux	00000034 misc_seq_next
300ecbf8 l     F .vmlinux	00000034 misc_seq_show
30259ff0 l     O .vmlinux	00000008 misc_list
30259ff8 l     O .vmlinux	00000010 misc_sem
30619048 l     O .bss	00000008 misc_minors
30619050 l     O .bss	00000004 misc_class
00000000 l    df *ABS*	00000000 vt_ioctl.c
3025a008 l     O .vmlinux	00000008 vt_activate_queue
300ed340 l     F .vmlinux	000000f8 complete_change_console
00000000 l    df *ABS*	00000000 vc_screen.c
3022c488 l     O .vmlinux	0000006c vcs_fops
300ef418 l     F .vmlinux	0000010c vcs_lseek
300ef524 l     F .vmlinux	00000394 vcs_read
300ef8b8 l     F .vmlinux	00000500 vcs_write
300efdb8 l     F .vmlinux	00000038 vcs_open
300ef39c l     F .vmlinux	0000007c vcs_size
3061905c l     O .bss	00000004 vc_class
00000000 l    df *ABS*	00000000 consolemap.c
3025a010 l     O .vmlinux	00000800 translations
300f0034 l     F .vmlinux	000000a8 set_inverse_transl
30619060 l     O .bss	000000fc inv_translate
300f015c l     F .vmlinux	00000074 update_user_maps
300f037c l     F .vmlinux	0000008c con_release_unimap
3061915c l     O .bss	00000004 dflt
300f0454 l     F .vmlinux	00000178 con_unify_unimap
300f05cc l     F .vmlinux	000000e4 con_insert_unipair
00000000 l    df *ABS*	00000000 consolemap_deftbl.c
00000000 l    df *ABS*	00000000 selection.c
3025ab68 l     O .vmlinux	00000004 sel_start
3025ab6c l     O .vmlinux	00000020 inwordLut
300f0c58 l     F .vmlinux	00000030 sel_pos
30619164 l     O .bss	00000004 sel_end
3061916c l     O .bss	00000004 sel_buffer
30619168 l     O .bss	00000004 sel_buffer_lth
00000000 l    df *ABS*	00000000 keyboard.c
300f2ccc l     F .vmlinux	00000178 kbd_bh
30252ebc l     O .vmlinux	00000014 __param_brl_nbchords
3025aba8 l     O .vmlinux	00000016 __param_str_brl_nbchords
3025aba4 l     O .vmlinux	00000004 brl_nbchords
30252ed0 l     O .vmlinux	00000014 __param_brl_timeout
3025abc8 l     O .vmlinux	00000015 __param_str_brl_timeout
3025abc0 l     O .vmlinux	00000004 brl_timeout
3025abe0 l     O .vmlinux	00000038 kbd_handler
300f2e44 l     F .vmlinux	00000670 kbd_event
300f34b4 l     F .vmlinux	000000ac kbd_connect
300f3560 l     F .vmlinux	00000018 kbd_disconnect
300f3578 l     F .vmlinux	00000094 kbd_start
3022c538 l     O .vmlinux	00000180 kbd_ids
3025ac18 l     O .vmlinux	00000001 ledstate
3025ac1c l     O .vmlinux	00000004 kbd
3025ac20 l     O .vmlinux	00000040 k_handler
300f2480 l     F .vmlinux	0000001c k_self
300f2508 l     F .vmlinux	00000068 k_fn
300f22f4 l     F .vmlinux	00000080 k_spec
300f25b8 l     F .vmlinux	0000016c k_pad
300f24b8 l     F .vmlinux	00000028 k_dead
300f24e0 l     F .vmlinux	00000028 k_cons
300f2570 l     F .vmlinux	00000048 k_cur
300f2724 l     F .vmlinux	00000138 k_shift
300f285c l     F .vmlinux	00000060 k_meta
300f28bc l     F .vmlinux	0000006c k_ascii
300f2928 l     F .vmlinux	00000040 k_lock
300f2374 l     F .vmlinux	00000018 k_lowercase
300f2968 l     F .vmlinux	000000a0 k_slock
300f249c l     F .vmlinux	0000001c k_dead2
300f2a94 l     F .vmlinux	000001a4 k_brl
300f22ec l     F .vmlinux	00000008 k_ignore
3061917c l     O .bss	00000004 sparc_l1_a_state
3025ac60 l     O .vmlinux	00000004 npadch
3025ac64 l     O .vmlinux	00000050 fn_handler
300f22dc l     F .vmlinux	00000010 fn_null
300f1e34 l     F .vmlinux	00000098 fn_enter
300f1f4c l     F .vmlinux	0000002c fn_show_ptregs
300f2224 l     F .vmlinux	00000010 fn_show_mem
300f2234 l     F .vmlinux	00000014 fn_show_state
300f2148 l     F .vmlinux	000000b4 fn_send_intr
300f2050 l     F .vmlinux	00000018 fn_lastcons
300f1ecc l     F .vmlinux	00000040 fn_caps_toggle
300f2018 l     F .vmlinux	00000038 fn_num
300f1f78 l     F .vmlinux	00000060 fn_hold
300f21fc l     F .vmlinux	00000014 fn_scroll_forw
300f2210 l     F .vmlinux	00000014 fn_scroll_back
300f2248 l     F .vmlinux	00000010 fn_boot_it
300f1f0c l     F .vmlinux	00000040 fn_caps_on
300f2258 l     F .vmlinux	00000010 fn_compose
300f22ac l     F .vmlinux	00000030 fn_SAK
300f2068 l     F .vmlinux	0000007c fn_dec_console
300f20e4 l     F .vmlinux	00000064 fn_inc_console
300f2268 l     F .vmlinux	00000044 fn_spawn_con
300f1fd8 l     F .vmlinux	00000040 fn_bare_num
3022c6b8 l     O .vmlinux	00000200 x86_keycodes
3025acb4 l     O .vmlinux	00000018 kd_mksound_timer
300f177c l     F .vmlinux	000000d0 kd_nosound
300f19cc l     F .vmlinux	000000b0 put_queue
300f1a7c l     F .vmlinux	000000e0 puts_queue
3025acd0 l     O .vmlinux	00000004 buf.6
300f1b5c l     F .vmlinux	00000038 applkey
300f1b94 l     F .vmlinux	00000064 to_utf8
30619310 l     O .bss	00000009 shift_down
306192d0 l     O .bss	00000040 key_down
300f1d14 l     F .vmlinux	00000120 handle_diacr
30619320 l     O .bss	00000004 diacr
30619324 l     O .bss	00000001 rep
3061931c l     O .bss	00000004 dead_key_next
300f238c l     F .vmlinux	000000a0 k_unicode
300f242c l     F .vmlinux	00000054 k_deadunicode
3022c8b8 l     O .vmlinux	00000006 ret_diacr.7
3022c8c0 l     O .vmlinux	00000005 cur_chars.5
3022c8c8 l     O .vmlinux	00000016 pad_chars.8
3022c8e0 l     O .vmlinux	00000016 app_map.9
30619180 l     O .bss	00000004 chords.3
30619184 l     O .bss	00000004 committed.4
300f2a08 l     F .vmlinux	0000008c k_brlcommit
30619188 l     O .bss	00000004 pressed.0
3061918c l     O .bss	00000004 committing.1
30619190 l     O .bss	00000004 releasestart.2
30619325 l     O .bss	00000001 ledioctl
30619328 l     O .bss	00000024 ledptrs
3061934c l     O .bss	00000004 sysrq_alt
00000000 l    df *ABS*	00000000 vt.c
302ba378 l     O .vmlinux	00000004 __initcall_vtconsole_class_init2
3028de9c l     F .vmlinux	000000e4 vtconsole_class_init
302ba5d0 l     O .vmlinux	00000004 __initcall_con_init
3028dab4 l     F .vmlinux	000002c0 con_init
3025adbc l     O .vmlinux	0000002c vt_console_driver
300f5d24 l     F .vmlinux	00000354 vt_console_print
300f6078 l     F .vmlinux	00000028 vt_console_device
3025ade8 l     O .vmlinux	00000018 console_timer
300f9148 l     F .vmlinux	0000004c blank_screen_t
3025ae00 l     O .vmlinux	00000004 blankinterval
3025ae04 l     O .vmlinux	00000010 console_work
300f7190 l     F .vmlinux	00000138 console_callback
3025ae14 l     O .vmlinux	00000028 device_attrs
300f6900 l     F .vmlinux	0000002c show_bind
300f68a4 l     F .vmlinux	0000001c store_bind
300f692c l     F .vmlinux	00000044 show_name
3022c8f8 l     O .vmlinux	0000005c con_ops
300f6508 l     F .vmlinux	000000ac con_open
300f624c l     F .vmlinux	0000006c con_close
300f8e30 l     F .vmlinux	00000030 con_write
300f8df4 l     F .vmlinux	0000003c con_put_char
300f60a0 l     F .vmlinux	00000058 con_flush_chars
300f60f8 l     F .vmlinux	0000001c con_write_room
300f6114 l     F .vmlinux	00000008 con_chars_in_buffer
300f611c l     F .vmlinux	00000008 con_throttle
300f6124 l     F .vmlinux	00000024 con_unthrottle
300f6148 l     F .vmlinux	0000008c con_stop
300f61d4 l     F .vmlinux	00000078 con_start
300f39b4 l     F .vmlinux	00000120 scrup
300f3ad4 l     F .vmlinux	000000fc scrdown
300f3bd0 l     F .vmlinux	000001b8 do_update_region
300f3d88 l     F .vmlinux	0000011c build_attr
300f3ea4 l     F .vmlinux	00000080 update_attr
3022c958 l     O .vmlinux	0000000e __func__.18
3022c968 l     O .vmlinux	0000000f __func__.13
3025ae3c l     O .vmlinux	00000004 old_offset.14
30619350 l     O .bss	00000002 old.15
30619352 l     O .bss	00000002 oldx.16
30619354 l     O .bss	00000002 oldy.17
300f42ec l     F .vmlinux	0000011c insert_char
300f4408 l     F .vmlinux	000000cc add_softcursor
3061ab48 l     O .bss	00000004 softcursor_original
300f44d4 l     F .vmlinux	0000009c hide_cursor
300f4570 l     F .vmlinux	000000b0 set_cursor
3022c978 l     O .vmlinux	0000000e __func__.19
3022c988 l     O .vmlinux	0000000b __func__.1
300f46cc l     F .vmlinux	000000f4 set_origin
300f47c0 l     F .vmlinux	00000058 clear_buffer_attributes
3022c998 l     O .vmlinux	0000000c __func__.3
300f4818 l     F .vmlinux	00000090 set_palette
3022c9a8 l     O .vmlinux	0000000e __func__.12
3022c9b8 l     O .vmlinux	0000000c __func__.2
300f4b1c l     F .vmlinux	000000c8 visual_init
3061aa28 l     O .bss	000000fc con_driver_map
3061ab34 l     O .bss	00000004 master_display_fg
300f4be4 l     F .vmlinux	000000b8 gotoxy
300f4c9c l     F .vmlinux	000000a8 save_cur
3022c9c8 l     O .vmlinux	0000000a __func__.10
3022c9d8 l     O .vmlinux	0000000e __func__.9
300f5220 l     F .vmlinux	00000030 gotoxay
3061ab38 l     O .bss	00000004 scrollback_delta
300f52b0 l     F .vmlinux	0000006c lf
300f531c l     F .vmlinux	000001b8 csi_J
300f54d4 l     F .vmlinux	0000003c default_attr
300f5510 l     F .vmlinux	000000d4 respond_string
300f5668 l     F .vmlinux	000002cc set_mode
300f59b8 l     F .vmlinux	000000e4 restore_cur
300f5a9c l     F .vmlinux	00000218 reset_terminal
30619358 l     O .bss	00000004 printing.0
3061ab24 l     O .bss	00000004 printable
300f62b8 l     F .vmlinux	000000cc vc_init
3022c9e8 l     O .vmlinux	0000000c __func__.11
3022c9f8 l     O .vmlinux	00000010 __func__.7
3061ab40 l     O .bss	00000004 blank_state
3061ab2c l     O .bss	00000004 vesa_blank_mode
3061ab44 l     O .bss	00000004 blank_timer_expired
3061ab30 l     O .bss	00000004 vesa_off_interval
3061a868 l     O .bss	000001c0 registered_con_driver
300f6970 l     F .vmlinux	000000a0 vtconsole_init_device
3061ab50 l     O .bss	00000004 vtconsole_class
3022ca08 l     O .vmlinux	00000012 __func__.6
3061ab28 l     O .bss	00000004 ignore_poke
3022ca20 l     O .vmlinux	00000015 __func__.5
3061935c l     O .bss	00000004 error.8
300f72c8 l     F .vmlinux	00001b2c do_con_write
3022ca38 l     O .vmlinux	0000000d __func__.4
300f9194 l     F .vmlinux	0000026c set_get_cmap
00000000 l    df *ABS*	00000000 defkeymap.c
00000000 l    df *ABS*	00000000 serial_core.c
3025c7f0 l     O .vmlinux	0000000c port_mutex
3022ca48 l     O .vmlinux	0000005c uart_ops
300fb710 l     F .vmlinux	000004c0 uart_open
300fb474 l     F .vmlinux	000001ec uart_close
300fa1e8 l     F .vmlinux	00000104 uart_write
300fa164 l     F .vmlinux	00000074 uart_put_char
300fa1d8 l     F .vmlinux	00000010 uart_flush_chars
300fa2ec l     F .vmlinux	00000020 uart_write_room
300fa30c l     F .vmlinux	0000001c uart_chars_in_buffer
300fa6c8 l     F .vmlinux	00000a8c uart_ioctl
300fb154 l     F .vmlinux	000001dc uart_set_termios
300fa408 l     F .vmlinux	000000a0 uart_throttle
300fa4a8 l     F .vmlinux	000000ac uart_unthrottle
300f9b44 l     F .vmlinux	00000030 uart_stop
300f9bd0 l     F .vmlinux	00000024 uart_start
300fb660 l     F .vmlinux	000000b0 uart_hangup
300fa678 l     F .vmlinux	00000050 uart_break_ctl
300fa328 l     F .vmlinux	00000070 uart_flush_buffer
300fb374 l     F .vmlinux	00000100 uart_wait_until_sent
300fa398 l     F .vmlinux	00000070 uart_send_xchar
300fbc10 l     F .vmlinux	00000538 uart_read_proc
300fa554 l     F .vmlinux	00000080 uart_tiocmget
300fa5d4 l     F .vmlinux	000000a4 uart_tiocmset
3022caa4 l     O .vmlinux	00000060 baud_rates
300f9b74 l     F .vmlinux	0000005c __uart_start
300f9bf4 l     F .vmlinux	00000018 uart_tasklet_action
300f9c0c l     F .vmlinux	000000bc uart_change_speed
300f9cc8 l     F .vmlinux	0000019c uart_startup
300f9e64 l     F .vmlinux	00000110 uart_shutdown
3022cb08 l     O .vmlinux	0000000b __func__.2
3022cb18 l     O .vmlinux	00000012 __func__.1
300fb330 l     F .vmlinux	00000044 uart_change_pm
300fbbd0 l     F .vmlinux	00000040 uart_type
3061ab5c l     O .bss	00000000 __key.0
3061ab5c l     O .bss	00000000 port_lock_key
00000000 l    df *ABS*	00000000 suncore.c
302ba45c l     O .vmlinux	00000004 __initcall_suncore_init6
3028e1a0 l     F .vmlinux	00000008 suncore_init
3025c800 l     O .vmlinux	00000030 mouse_baud_table
3061ab5c l     O .bss	00000004 mouse_got_break.0
3061ab60 l     O .bss	00000004 ctr.1
00000000 l    df *ABS*	00000000 core.c
3025c898 l     O .vmlinux	0000000c ktype_device
3025c88c l     O .vmlinux	0000000c device_uevent_ops
300fd16c l     F .vmlinux	00000068 dev_uevent_filter
300fd1d4 l     F .vmlinux	00000034 dev_uevent_name
300fd208 l     F .vmlinux	00000140 dev_uevent
300fd0c4 l     F .vmlinux	000000a8 device_release
3025c8a4 l     O .vmlinux	00000008 dev_sysfs_ops
300fd058 l     F .vmlinux	00000034 dev_attr_show
300fd08c l     F .vmlinux	00000038 dev_attr_store
3022cb30 l     O .vmlinux	0000000f __func__.0
3022cb40 l     O .vmlinux	0000000b __func__.1
300fd348 l     F .vmlinux	00000008 store_uevent
300fd350 l     F .vmlinux	0000005c device_remove_groups
300fd3ac l     F .vmlinux	0000002c show_dev
300fd49c l     F .vmlinux	000000c0 device_remove_attrs
300fd5c8 l     F .vmlinux	00000014 klist_children_get
300fd5dc l     F .vmlinux	00000014 klist_children_put
300fd670 l     F .vmlinux	00000028 get_device_parent
300fe03c l     F .vmlinux	00000024 next_device
3022cb50 l     O .vmlinux	00000016 __func__.2
300fe130 l     F .vmlinux	00000010 device_create_release
300fe3d8 l     F .vmlinux	000000c0 device_move_class_links
00000000 l    df *ABS*	00000000 sys.c
3025c8ac l     O .vmlinux	0000005c system_subsys
3025c908 l     O .vmlinux	0000000c ktype_sysdev_class
3025c914 l     O .vmlinux	00000008 sysfs_class_ops
300fe744 l     F .vmlinux	00000030 sysdev_class_show
300fe774 l     F .vmlinux	00000034 sysdev_class_store
3025c91c l     O .vmlinux	00000008 sysdev_drivers
3025c924 l     O .vmlinux	00000010 sysdev_drivers_lock
3025c934 l     O .vmlinux	0000000c ktype_sysdev
3025c940 l     O .vmlinux	00000008 sysfs_ops
300fe6b8 l     F .vmlinux	00000030 sysdev_show
300fe6e8 l     F .vmlinux	00000034 sysdev_store
300fed7c l     F .vmlinux	000000cc __sysdev_resume
00000000 l    df *ABS*	00000000 bus.c
3025c948 l     O .vmlinux	0000005c bus_subsys
3025c9a4 l     O .vmlinux	0000000c ktype_bus
3025c9b0 l     O .vmlinux	00000008 bus_sysfs_ops
300ff320 l     F .vmlinux	00000030 bus_attr_show
300ff350 l     F .vmlinux	00000034 bus_attr_store
3025c9b8 l     O .vmlinux	0000000c ktype_driver
300ff30c l     F .vmlinux	00000014 driver_release
3025c9c4 l     O .vmlinux	00000008 driver_sysfs_ops
300ff2a8 l     F .vmlinux	00000030 drv_attr_show
300ff2d8 l     F .vmlinux	00000034 drv_attr_store
300ff44c l     F .vmlinux	00000024 next_device
300ff604 l     F .vmlinux	00000054 device_remove_attrs
3022cb68 l     O .vmlinux	0000000f __func__.1
300ffa90 l     F .vmlinux	000000a8 bus_rescan_devices_helper
300ffbd8 l     F .vmlinux	00000014 klist_devices_get
300ffbec l     F .vmlinux	00000014 klist_devices_put
3061ab6c l     O .bss	00000000 __key.0
00000000 l    df *ABS*	00000000 dd.c
3025c9cc l     O .vmlinux	00000008 probe_waitqueue
3061ab6c l     O .bss	00000004 probe_count
3022cb78 l     O .vmlinux	0000000d __func__.1
300ffec4 l     F .vmlinux	00000070 driver_bound
300fff34 l     F .vmlinux	0000006c driver_sysfs_add
300fffa0 l     F .vmlinux	0000003c driver_sysfs_remove
3022cb88 l     O .vmlinux	0000000d __func__.0
30100008 l     F .vmlinux	000001a8 really_probe
3022cb98 l     O .vmlinux	00000012 __func__.2
301002ac l     F .vmlinux	00000010 __device_attach
30100350 l     F .vmlinux	000000d0 __driver_attach
30100444 l     F .vmlinux	000000c8 __device_release_driver
00000000 l    df *ABS*	00000000 driver.c
301007e4 l     F .vmlinux	00000024 next_device
00000000 l    df *ABS*	00000000 class.c
3025c9d4 l     O .vmlinux	0000005c class_obj_subsys
3025ca3c l     O .vmlinux	0000000c ktype_class_device
3025ca30 l     O .vmlinux	0000000c class_uevent_ops
30101000 l     F .vmlinux	00000054 class_uevent_filter
30101054 l     F .vmlinux	0000000c class_uevent_name
301010d4 l     F .vmlinux	00000088 class_uevent
30100f78 l     F .vmlinux	00000088 class_dev_release
3025ca48 l     O .vmlinux	00000008 class_dev_sysfs_ops
30100f14 l     F .vmlinux	00000030 class_device_attr_show
30100f44 l     F .vmlinux	00000034 class_device_attr_store
3025ca50 l     O .vmlinux	0000005c class_subsys
3025caac l     O .vmlinux	0000000c ktype_class
30100b40 l     F .vmlinux	0000002c class_release
3025cab8 l     O .vmlinux	00000008 class_sysfs_ops
30100adc l     F .vmlinux	00000030 class_attr_show
30100b0c l     F .vmlinux	00000034 class_attr_store
30100bc0 l     F .vmlinux	00000040 class_get
30100c00 l     F .vmlinux	00000028 class_put
3022cbb0 l     O .vmlinux	00000015 __func__.4
30100db4 l     F .vmlinux	00000010 class_create_release
3022cbc8 l     O .vmlinux	0000001c __func__.3
30100dc4 l     F .vmlinux	00000010 class_device_create_release
3022cbe8 l     O .vmlinux	0000001b __func__.2
30100dd4 l     F .vmlinux	00000008 class_device_create_uevent
3022cc08 l     O .vmlinux	00000012 __func__.0
3022cc20 l     O .vmlinux	0000000d __func__.1
3010115c l     F .vmlinux	00000058 class_device_remove_attrs
301011b4 l     F .vmlinux	0000005c class_device_remove_groups
30101210 l     F .vmlinux	0000002c show_dev
3010123c l     F .vmlinux	00000008 store_uevent
00000000 l    df *ABS*	00000000 platform.c
3025cc20 l     O .vmlinux	00000028 platform_dev_attrs
301024e4 l     F .vmlinux	00000090 platform_match
301024bc l     F .vmlinux	00000028 platform_uevent
30102574 l     F .vmlinux	00000048 platform_suspend
301025bc l     F .vmlinux	0000004c platform_suspend_late
30102608 l     F .vmlinux	00000040 platform_resume_early
30102648 l     F .vmlinux	0000003c platform_resume
30102488 l     F .vmlinux	00000034 modalias_show
30101eec l     F .vmlinux	00000024 platform_device_release
3010232c l     F .vmlinux	0000001c platform_drv_probe
30102348 l     F .vmlinux	00000008 platform_drv_probe_fail
30102350 l     F .vmlinux	0000001c platform_drv_remove
3010236c l     F .vmlinux	00000020 platform_drv_shutdown
3010238c l     F .vmlinux	00000028 platform_drv_suspend
301023b4 l     F .vmlinux	0000001c platform_drv_resume
00000000 l    df *ABS*	00000000 cpu.c
3061ab70 l     O .bss	00000004 cpu_sys_devices
00000000 l    df *ABS*	00000000 firmware.c
3025cdec l     O .vmlinux	0000005c firmware_subsys
00000000 l    df *ABS*	00000000 init.c
00000000 l    df *ABS*	00000000 map.c
00000000 l    df *ABS*	00000000 dmapool.c
3025ce48 l     O .vmlinux	00000014 dev_attr_pools
30102bc4 l     F .vmlinux	00000108 show_pools
3025ce5c l     O .vmlinux	00000010 pools_lock
301033e4 l     F .vmlinux	00000014 dmam_pool_release
301033f8 l     F .vmlinux	00000014 dmam_pool_match
3022cc30 l     O .vmlinux	00000012 __func__.0
00000000 l    df *ABS*	00000000 dma-mapping.c
301035b4 l     F .vmlinux	00000020 dmam_coherent_release
301035d4 l     F .vmlinux	00000020 dmam_noncoherent_release
3022cc48 l     O .vmlinux	0000000b __func__.1
301035f4 l     F .vmlinux	00000084 dmam_match
3022cc58 l     O .vmlinux	00000013 __func__.2
3022cc70 l     O .vmlinux	00000016 __func__.0
00000000 l    df *ABS*	00000000 devres.c
30103888 l     F .vmlinux	00000008 group_open_release
30103890 l     F .vmlinux	00000008 group_close_release
30103898 l     F .vmlinux	00000038 node_to_group
301038d0 l     F .vmlinux	00000028 add_dr
301039a0 l     F .vmlinux	00000074 find_dr
30103b58 l     F .vmlinux	00000194 release_nodes
30103db8 l     F .vmlinux	00000084 find_group
3022cc88 l     O .vmlinux	00000013 __func__.3
3022cca0 l     O .vmlinux	00000014 __func__.2
3022ccb8 l     O .vmlinux	00000015 __func__.1
30103fe8 l     F .vmlinux	00000008 devm_kzalloc_release
30103ff0 l     F .vmlinux	00000010 devm_kzalloc_match
3022ccd0 l     O .vmlinux	0000000b __func__.0
00000000 l    df *ABS*	00000000 attribute_container.c
3025ce6c l     O .vmlinux	00000010 attribute_container_mutex
301040c4 l     F .vmlinux	00000014 internal_container_klist_get
301040d8 l     F .vmlinux	00000014 internal_container_klist_put
3061ab74 l     O .bss	00000008 attribute_container_list
30104204 l     F .vmlinux	0000001c attribute_container_release
00000000 l    df *ABS*	00000000 transport_class.c
301049f4 l     F .vmlinux	00000008 anon_transport_dummy_function
30104a4c l     F .vmlinux	00000030 transport_setup_classdev
30104a94 l     F .vmlinux	0000003c transport_add_class_device
30104b48 l     F .vmlinux	00000074 transport_remove_classdev
30104b00 l     F .vmlinux	00000030 transport_configure
30104bbc l     F .vmlinux	00000034 transport_destroy_classdev
00000000 l    df *ABS*	00000000 shutdown.c
00000000 l    df *ABS*	00000000 rd.c
30252ee4 l     O .vmlinux	00000014 __param_rd_blocksize
3025ce88 l     O .vmlinux	00000010 __param_str_rd_blocksize
3025ce80 l     O .vmlinux	00000004 rd_blocksize
30252ef8 l     O .vmlinux	00000014 __param_rd_size
3025ce98 l     O .vmlinux	0000000b __param_str_rd_size
302ba0d8 l     O .vmlinux	0000000c __setup_ramdisk_blocksize
302b4770 l     O .vmlinux	00000013 __setup_str_ramdisk_blocksize
3028e5cc l     F .vmlinux	00000024 ramdisk_blocksize
302ba0e4 l     O .vmlinux	0000000c __setup_ramdisk_size2
302b4788 l     O .vmlinux	0000000e __setup_str_ramdisk_size2
3028e5bc l     F .vmlinux	00000010 ramdisk_size2
302ba0f0 l     O .vmlinux	0000000c __setup_ramdisk_size
302b4798 l     O .vmlinux	00000009 __setup_str_ramdisk_size
3028e598 l     F .vmlinux	00000024 ramdisk_size
302ba460 l     O .vmlinux	00000004 __initcall_rd_init6
3028e3d4 l     F .vmlinux	000001c4 rd_init
3025cea8 l     O .vmlinux	00000028 rd_bd_op
30105130 l     F .vmlinux	000000fc rd_open
301050c0 l     F .vmlinux	00000070 rd_ioctl
3025ced0 l     O .vmlinux	0000001c rd_file_backing_dev_info
3025ceec l     O .vmlinux	0000001c rd_backing_dev_info
3022cce0 l     O .vmlinux	0000003c ramdisk_aops
30104dd4 l     F .vmlinux	0000005c ramdisk_writepage
30104d70 l     F .vmlinux	0000002c ramdisk_readpage
30104e30 l     F .vmlinux	00000008 ramdisk_writepages
30104e38 l     F .vmlinux	00000020 ramdisk_set_page_dirty
30104d9c l     F .vmlinux	00000024 ramdisk_prepare_write
30104dc0 l     F .vmlinux	00000014 ramdisk_commit_write
30104ccc l     F .vmlinux	000000a4 make_page_uptodate
30104e58 l     F .vmlinux	00000268 rd_make_request
3061abbc l     O .bss	00000040 rd_bdev
3061ab7c l     O .bss	00000040 rd_disks
3061abfc l     O .bss	00000040 rd_queue
00000000 l    df *ABS*	00000000 loop.c
302ba0fc l     O .vmlinux	0000000c __setup_max_loop_setup
302b47a8 l     O .vmlinux	0000000a __setup_str_max_loop_setup
3028e898 l     F .vmlinux	00000024 max_loop_setup
30106dec l     F .vmlinux	000000b4 loop_exit
302ba464 l     O .vmlinux	00000004 __initcall_loop_init6
3028e5f0 l     F .vmlinux	000002a8 loop_init
30252f0c l     O .vmlinux	00000014 __param_max_loop
3025cf10 l     O .vmlinux	0000000e __param_str_max_loop
3025cf08 l     O .vmlinux	00000004 max_loop
3025cf20 l     O .vmlinux	00000028 lo_fops
30106c6c l     F .vmlinux	00000038 lo_open
30106ca4 l     F .vmlinux	00000038 lo_release
301062ec l     F .vmlinux	00000980 lo_ioctl
3025cf48 l     O .vmlinux	00000018 none_funcs
30105248 l     F .vmlinux	0000007c transfer_none
3025cf60 l     O .vmlinux	00000050 xfer_funcs
3025cfb0 l     O .vmlinux	00000018 xor_funcs
301052c4 l     F .vmlinux	000000b0 transfer_xor
30105374 l     F .vmlinux	00000018 xor_init
3010538c l     F .vmlinux	00000088 get_loop_size
30105414 l     F .vmlinux	000001ec do_lo_send_aops
30105600 l     F .vmlinux	0000007c __do_lo_send_write
3010567c l     F .vmlinux	00000108 do_lo_send_direct_write
30105784 l     F .vmlinux	000000ac do_lo_send_write
30105830 l     F .vmlinux	000000c0 lo_read_actor
301058f0 l     F .vmlinux	000000c8 loop_make_request
301059b8 l     F .vmlinux	0000005c loop_unplug
30105a14 l     F .vmlinux	00000504 loop_thread
30105f18 l     F .vmlinux	00000048 loop_release_xfer
30105f60 l     F .vmlinux	00000234 loop_set_status
3061ac40 l     O .bss	00000004 disks
30106194 l     F .vmlinux	00000158 loop_get_status
3061ac3c l     O .bss	00000004 loop_dev
3061ac3c l     O .bss	00000000 __key.0
00000000 l    df *ABS*	00000000 mtdcore.c
302ba468 l     O .vmlinux	00000004 __initcall_init_mtd6
3028e8bc l     F .vmlinux	0000003c init_mtd
3025cfd4 l     O .vmlinux	00000008 mtd_notifiers
30107438 l     F .vmlinux	000000f4 mtd_read_proc
3061acc4 l     O .bss	00000004 proc_mtd
00000000 l    df *ABS*	00000000 chipreg.c
3025cfdc l     O .vmlinux	00000008 chip_drvs_list
3061acc8 l     O .bss	00000000 chip_drvs_lock
30107580 l     F .vmlinux	00000054 get_mtd_chip_driver
00000000 l    df *ABS*	00000000 sbus.c
302ba398 l     O .vmlinux	00000004 __initcall_sbus_init4
3028eca0 l     F .vmlinux	00000288 sbus_init
3025cfe4 l     O .vmlinux	00000014 dev_attr_obppath
30107644 l     F .vmlinux	00000028 show_sbusobppath_attr
3028e8f8 l     F .vmlinux	00000154 fill_sbus_device
3028ea4c l     F .vmlinux	000000a8 __apply_ranges_to_regs
3028eaf4 l     F .vmlinux	000000fc sbus_fixup_all_regs
3028ebf0 l     F .vmlinux	00000038 sdev_insert
3028ec28 l     F .vmlinux	00000078 walk_children
00000000 l    df *ABS*	00000000 dvma.c
3061accc l     O .bss	00000004 num_dma.0
00000000 l    df *ABS*	00000000 pci-quirks.c
30252870 l     O .vmlinux	00000008 __pci_fixup_PCI_ANY_IDPCI_ANY_IDquirk_usb_early_handoff
3028f22c l     F .vmlinux	000004f0 quirk_usb_early_handoff
3028f1d0 l     F .vmlinux	0000005c mmio_resource_enabled
00000000 l    df *ABS*	00000000 serio.c
302ba39c l     O .vmlinux	00000004 __initcall_serio_init4
3028f71c l     F .vmlinux	000000b0 serio_init
3025cff8 l     O .vmlinux	00000160 serio_bus
3025d194 l     O .vmlinux	00000064 serio_device_attrs
3025d158 l     O .vmlinux	0000003c serio_driver_attrs
301086f8 l     F .vmlinux	0000003c serio_bus_match
30108734 l     F .vmlinux	00000008 serio_uevent
30108228 l     F .vmlinux	0000001c serio_driver_probe
30108244 l     F .vmlinux	00000014 serio_driver_remove
30108258 l     F .vmlinux	0000003c serio_shutdown
30108160 l     F .vmlinux	00000030 serio_driver_show_description
30108190 l     F .vmlinux	00000038 serio_driver_show_bind_mode
301081c8 l     F .vmlinux	00000060 serio_driver_set_bind_mode
30107ad4 l     F .vmlinux	00000024 serio_show_description
30107af8 l     F .vmlinux	00000030 serio_show_modalias
30107f58 l     F .vmlinux	00000164 serio_rebind_driver
30107bb8 l     F .vmlinux	0000003c serio_show_bind_mode
30107bf4 l     F .vmlinux	00000060 serio_set_bind_mode
3025d1f8 l     O .vmlinux	0000000c serio_mutex
3025d204 l     O .vmlinux	00000008 serio_id_attr_group
3025d20c l     O .vmlinux	00000014 serio_device_id_attrs
3025d25c l     O .vmlinux	00000014 dev_attr_type
3025d248 l     O .vmlinux	00000014 dev_attr_proto
3025d234 l     O .vmlinux	00000014 dev_attr_id
3025d220 l     O .vmlinux	00000014 dev_attr_extra
30107b94 l     F .vmlinux	00000024 serio_show_id_extra
30107b70 l     F .vmlinux	00000024 serio_show_id_id
30107b4c l     F .vmlinux	00000024 serio_show_id_proto
30107b28 l     F .vmlinux	00000024 serio_show_id_type
3025d270 l     O .vmlinux	00000008 serio_event_list
3061acd4 l     O .bss	00000000 serio_event_lock
3025d278 l     O .vmlinux	00000008 serio_wait
3025d280 l     O .vmlinux	00000008 serio_list
301077bc l     F .vmlinux	00000038 serio_connect_driver
301077f4 l     F .vmlinux	00000044 serio_disconnect_driver
30107838 l     F .vmlinux	000000c4 serio_match_port
301078fc l     F .vmlinux	00000024 serio_release_driver
30107920 l     F .vmlinux	00000058 serio_find_driver
30107978 l     F .vmlinux	000000d4 serio_queue_event
30107a4c l     F .vmlinux	00000010 serio_free_event
30107a5c l     F .vmlinux	00000078 serio_remove_pending_events
30107c54 l     F .vmlinux	00000018 serio_release_port
3061acd4 l     O .bss	00000004 serio_no.0
3061acd8 l     O .bss	00000000 __key.1
30107d20 l     F .vmlinux	00000168 serio_destroy_port
30107e88 l     F .vmlinux	00000054 serio_disconnect_port
30107edc l     F .vmlinux	0000007c serio_reconnect_port
30108294 l     F .vmlinux	00000338 serio_thread
301086dc l     F .vmlinux	0000001c serio_set_drv
3061acd8 l     O .bss	00000004 serio_task
00000000 l    df *ABS*	00000000 i8042.c
302ba46c l     O .vmlinux	00000004 __initcall_i8042_init6
302901ec l     F .vmlinux	000001f8 i8042_init
30252f20 l     O .vmlinux	00000014 __param_debug
3025d288 l     O .vmlinux	0000000c __param_str_debug
3061ad0c l     O .bss	00000004 i8042_debug
30252f34 l     O .vmlinux	00000014 __param_panicblink
3025d298 l     O .vmlinux	00000011 __param_str_panicblink
3025d294 l     O .vmlinux	00000004 i8042_blink_frequency
30252f48 l     O .vmlinux	00000014 __param_noloop
3025d2b0 l     O .vmlinux	0000000d __param_str_noloop
3061ad08 l     O .bss	00000004 i8042_noloop
30252f5c l     O .vmlinux	00000014 __param_dumbkbd
3025d2c0 l     O .vmlinux	0000000e __param_str_dumbkbd
3061ad04 l     O .bss	00000004 i8042_dumbkbd
30252f70 l     O .vmlinux	00000014 __param_direct
3025d2d0 l     O .vmlinux	0000000d __param_str_direct
3061ad00 l     O .bss	00000004 i8042_direct
30252f84 l     O .vmlinux	00000014 __param_reset
3025d2e0 l     O .vmlinux	0000000c __param_str_reset
3061acfc l     O .bss	00000004 i8042_reset
30252f98 l     O .vmlinux	00000014 __param_unlock
3025d2f0 l     O .vmlinux	0000000d __param_str_unlock
3061acf8 l     O .bss	00000004 i8042_unlock
30252fac l     O .vmlinux	00000014 __param_nomux
3025d300 l     O .vmlinux	0000000c __param_str_nomux
3061acf4 l     O .bss	00000004 i8042_nomux
30252fc0 l     O .vmlinux	00000014 __param_noaux
3025d310 l     O .vmlinux	0000000c __param_str_noaux
3061acf0 l     O .bss	00000004 i8042_noaux
30252fd4 l     O .vmlinux	00000014 __param_nokbd
3025d320 l     O .vmlinux	0000000c __param_str_nokbd
3061acec l     O .bss	00000004 i8042_nokbd
3025d32c l     O .vmlinux	000000bc i8042_driver
3028fab0 l     F .vmlinux	0000073c i8042_probe
301093ec l     F .vmlinux	00000010 i8042_shutdown
3061acdc l     O .bss	00000000 i8042_lock
3025d3e8 l     O .vmlinux	00000004 i8042_aux_irq
3025d3ec l     O .vmlinux	00000004 i8042_kbd_irq
3025d3f0 l     O .vmlinux	000000c0 sparc_i8042_driver
3025d4b0 l     O .vmlinux	00000188 sparc_i8042_match
3028f7cc l     F .vmlinux	00000120 sparc_i8042_probe
3061ad10 l     O .bss	00000004 kbd_iobase
3061ad14 l     O .bss	00000004 kbd_res
3010883c l     F .vmlinux	00000074 i8042_wait_write
301088b0 l     F .vmlinux	000000c0 i8042_flush
3061ad18 l     O .bss	00000004 i8042_start_time
30108970 l     F .vmlinux	0000028c __i8042_command
30108bfc l     F .vmlinux	00000034 i8042_command
30108c30 l     F .vmlinux	00000080 i8042_kbd_write
30108cb0 l     F .vmlinux	00000040 i8042_aux_write
30108cf0 l     F .vmlinux	00000014 i8042_start
30108d04 l     F .vmlinux	0000001c i8042_stop
3061acdc l     O .bss	00000004 last_transmit.0
3061ace0 l     O .bss	00000001 last_str.1
30108d20 l     F .vmlinux	0000029c i8042_interrupt
3061ad66 l     O .bss	00000001 i8042_mux_present
3061ad1c l     O .bss	00000048 i8042_ports
3061ad69 l     O .bss	00000001 i8042_suppress_kbd_ack
30108fbc l     F .vmlinux	00000050 i8042_enable_aux_port
3061ad65 l     O .bss	00000001 i8042_ctr
3010900c l     F .vmlinux	00000040 i8042_enable_mux_ports
3010904c l     F .vmlinux	000000f8 i8042_set_mux_mode
3028f8ec l     F .vmlinux	00000074 i8042_aux_test_irq
302b47c4 l     O .vmlinux	00000004 i8042_irq_being_tested
302b47b8 l     O .vmlinux	0000000c i8042_aux_irq_delivered
30109144 l     F .vmlinux	00000074 i8042_controller_selftest
301091b8 l     F .vmlinux	00000068 i8042_controller_reset
3061ad64 l     O .bss	00000001 i8042_initial_ctr
3061ace4 l     O .bss	00000004 last_blink.2
3061ace8 l     O .bss	00000001 led.3
30109220 l     F .vmlinux	000001cc i8042_panic_blink
3028f960 l     F .vmlinux	0000011c i8042_create_aux_port
3061ad6c l     O .bss	00000004 i8042_platform_device
3028fa7c l     F .vmlinux	00000034 i8042_free_aux_ports
301093fc l     F .vmlinux	00000078 i8042_free_irqs
3061ad68 l     O .bss	00000001 i8042_aux_irq_registered
3061ad67 l     O .bss	00000001 i8042_kbd_irq_registered
00000000 l    df *ABS*	00000000 serport.c
302ba470 l     O .vmlinux	00000004 __initcall_serport_init6
302903e4 l     F .vmlinux	0000003c serport_init
3025d638 l     O .vmlinux	00000048 serport_ldisc
30109524 l     F .vmlinux	0000006c serport_ldisc_open
30109590 l     F .vmlinux	00000014 serport_ldisc_close
301095fc l     F .vmlinux	000001c8 serport_ldisc_read
301097c4 l     F .vmlinux	0000007c serport_ldisc_ioctl
301095a4 l     F .vmlinux	00000058 serport_ldisc_receive
30109840 l     F .vmlinux	0000005c serport_ldisc_write_wakeup
30109474 l     F .vmlinux	00000038 serport_serio_write
301094ac l     F .vmlinux	0000002c serport_serio_open
301094d8 l     F .vmlinux	0000004c serport_serio_close
00000000 l    df *ABS*	00000000 libps2.c
3022cd20 l     O .vmlinux	0000000a __func__.3
3022cd30 l     O .vmlinux	00000006 keyboard_ids.2
3022cd38 l     O .vmlinux	0000000c __func__.1
30109efc l     F .vmlinux	00000020 ps2_execute_scheduled_command
3061ad70 l     O .bss	00000000 __key.0
00000000 l    df *ABS*	00000000 serio_raw.c
302ba474 l     O .vmlinux	00000004 __initcall_serio_raw_init6
30290420 l     F .vmlinux	00000024 serio_raw_init
3025d680 l     O .vmlinux	000000c8 serio_raw_drv
3025d748 l     O .vmlinux	00000008 serio_raw_serio_ids
3010a674 l     F .vmlinux	0000007c serio_raw_interrupt
3010a6f0 l     F .vmlinux	00000190 serio_raw_connect
3010a880 l     F .vmlinux	00000044 serio_raw_reconnect
3010a8c4 l     F .vmlinux	00000068 serio_raw_disconnect
3025d750 l     O .vmlinux	0000000c serio_raw_mutex
3022cd48 l     O .vmlinux	0000006c serio_raw_fops
3010a350 l     F .vmlinux	000001f0 serio_raw_read
3010a540 l     F .vmlinux	000000d4 serio_raw_write
3010a614 l     F .vmlinux	00000060 serio_raw_poll
3010a1d4 l     F .vmlinux	000000e4 serio_raw_open
3010a310 l     F .vmlinux	00000040 serio_raw_release
3010a1a4 l     F .vmlinux	00000030 serio_raw_fasync
3025d75c l     O .vmlinux	00000008 serio_raw_list
3010a2b8 l     F .vmlinux	00000058 serio_raw_cleanup
3061ad70 l     O .bss	00000004 serio_raw_no
00000000 l    df *ABS*	00000000 leon3ps2.c
302ba478 l     O .vmlinux	00000004 __initcall_leon3ps2_init6
30290444 l     F .vmlinux	000001d8 leon3ps2_init
302ba108 l     O .vmlinux	0000000c __setup_leon3ps2_setup
302b47c8 l     O .vmlinux	00000007 __setup_str_leon3ps2_setup
3029061c l     F .vmlinux	000000f8 leon3ps2_setup
3010a92c l     F .vmlinux	0000007c leon3ps2_int
3010a9a8 l     F .vmlinux	00000090 leon3ps2_write
3061adf4 l     O .bss	00000020 leon3ps2_kmis
3061ad74 l     O .bss	00000080 leon3ps2_devs
00000000 l    df *ABS*	00000000 input.c
302ba3a0 l     O .vmlinux	00000004 __initcall_input_init4
30290714 l     F .vmlinux	00000130 input_init
3010c344 l     F .vmlinux	000003bc input_dev_uevent
3010c254 l     F .vmlinux	00000024 input_dev_release
3022cdb4 l     O .vmlinux	0000006c input_fops
3010cdd4 l     F .vmlinux	0000007c input_open_file
3022ce20 l     O .vmlinux	0000006c input_handlers_fileops
3010bb8c l     F .vmlinux	0000001c input_proc_handlers_open
3022ce8c l     O .vmlinux	0000006c input_devices_fileops
3010b608 l     F .vmlinux	00000050 input_proc_devices_poll
3010bad0 l     F .vmlinux	0000001c input_proc_devices_open
3025d820 l     O .vmlinux	00000010 input_devices_seq_ops
3010b6f8 l     F .vmlinux	00000018 input_devices_seq_start
3010b728 l     F .vmlinux	00000008 input_devices_seq_stop
3010b710 l     F .vmlinux	00000018 input_devices_seq_next
3010b7e4 l     F .vmlinux	000002ec input_devices_seq_show
3025d830 l     O .vmlinux	00000008 input_dev_list
3025d838 l     O .vmlinux	00000008 input_devices_poll_wait
3025d840 l     O .vmlinux	00000010 input_handlers_seq_ops
3010baec l     F .vmlinux	00000020 input_handlers_seq_start
3010bb30 l     F .vmlinux	00000008 input_handlers_seq_stop
3010bb0c l     F .vmlinux	00000024 input_handlers_seq_next
3010bb38 l     F .vmlinux	00000054 input_handlers_seq_show
3025d850 l     O .vmlinux	00000008 input_handler_list
3025d858 l     O .vmlinux	00000008 input_dev_attr_group
3025d860 l     O .vmlinux	00000014 input_dev_attrs
3025d8b0 l     O .vmlinux	00000014 class_device_attr_name
3025d89c l     O .vmlinux	00000014 class_device_attr_phys
3025d888 l     O .vmlinux	00000014 class_device_attr_uniq
3025d874 l     O .vmlinux	00000014 class_device_attr_modalias
3010bec8 l     F .vmlinux	00000030 input_dev_show_modalias
3010bc50 l     F .vmlinux	00000034 input_dev_show_uniq
3010bc1c l     F .vmlinux	00000034 input_dev_show_phys
3010bbe8 l     F .vmlinux	00000034 input_dev_show_name
3025d8c4 l     O .vmlinux	00000008 input_dev_id_attr_group
3025d8cc l     O .vmlinux	00000014 input_dev_id_attrs
3025d91c l     O .vmlinux	00000014 class_device_attr_bustype
3025d908 l     O .vmlinux	00000014 class_device_attr_vendor
3025d8f4 l     O .vmlinux	00000014 class_device_attr_product
3025d8e0 l     O .vmlinux	00000014 class_device_attr_version
3010bf64 l     F .vmlinux	00000024 input_dev_show_id_version
3010bf40 l     F .vmlinux	00000024 input_dev_show_id_product
3010bf1c l     F .vmlinux	00000024 input_dev_show_id_vendor
3010bef8 l     F .vmlinux	00000024 input_dev_show_id_bustype
3025d930 l     O .vmlinux	00000008 input_dev_caps_attr_group
3025d938 l     O .vmlinux	00000028 input_dev_caps_attrs
3025da00 l     O .vmlinux	00000014 class_device_attr_ev
3025d9ec l     O .vmlinux	00000014 class_device_attr_key
3025d9d8 l     O .vmlinux	00000014 class_device_attr_rel
3025d9c4 l     O .vmlinux	00000014 class_device_attr_abs
3025d9b0 l     O .vmlinux	00000014 class_device_attr_msc
3025d99c l     O .vmlinux	00000014 class_device_attr_led
3025d988 l     O .vmlinux	00000014 class_device_attr_snd
3025d974 l     O .vmlinux	00000014 class_device_attr_ff
3025d960 l     O .vmlinux	00000014 class_device_attr_sw
3010c220 l     F .vmlinux	00000034 input_dev_show_cap_sw
3010c1ec l     F .vmlinux	00000034 input_dev_show_cap_ff
3010c1b8 l     F .vmlinux	00000034 input_dev_show_cap_snd
3010c184 l     F .vmlinux	00000034 input_dev_show_cap_led
3010c150 l     F .vmlinux	00000034 input_dev_show_cap_msc
3010c11c l     F .vmlinux	00000034 input_dev_show_cap_abs
3010c0e8 l     F .vmlinux	00000034 input_dev_show_cap_rel
3010c0b4 l     F .vmlinux	00000034 input_dev_show_cap_key
3010c080 l     F .vmlinux	00000034 input_dev_show_cap_ev
3010b134 l     F .vmlinux	00000098 input_repeat_key
3010b398 l     F .vmlinux	00000044 input_link_handle
3010b3dc l     F .vmlinux	0000022c input_match_device
3061ae3c l     O .bss	00000004 input_devices_state
3010b658 l     F .vmlinux	00000074 list_get_nth_element
3010b6cc l     F .vmlinux	0000002c list_get_next_element
3010b730 l     F .vmlinux	000000b4 input_seq_print_bitmap
3010bba8 l     F .vmlinux	00000040 input_proc_exit
3061ae38 l     O .bss	00000004 proc_bus_input_dir
3010bc84 l     F .vmlinux	000000a8 input_print_modalias_bits
3010bd2c l     F .vmlinux	0000019c input_print_modalias
3010bf88 l     F .vmlinux	000000f8 input_print_bitmap
3010c278 l     F .vmlinux	000000cc input_add_uevent_bm_var
3061ae14 l     O .bss	00000000 __key.1
3061ae14 l     O .bss	00000004 input_no.0
3061ae18 l     O .bss	00000020 input_table
00000000 l    df *ABS*	00000000 ff-core.c
3010ce50 l     F .vmlinux	00000050 check_effect_access
3010d1ac l     F .vmlinux	00000088 erase_effect
3010d284 l     F .vmlinux	00000058 flush_effects
3061ae40 l     O .bss	00000000 __key.0
00000000 l    df *ABS*	00000000 atkbd.c
302ba47c l     O .vmlinux	00000004 __initcall_atkbd_init6
30290844 l     F .vmlinux	00000024 atkbd_init
30252fe8 l     O .vmlinux	00000014 __param_extra
3025da18 l     O .vmlinux	0000000c __param_str_extra
3061ae48 l     O .bss	00000004 atkbd_extra
30252ffc l     O .vmlinux	00000014 __param_scroll
3025da28 l     O .vmlinux	0000000d __param_str_scroll
3061ae44 l     O .bss	00000004 atkbd_scroll
30253010 l     O .vmlinux	00000014 __param_softraw
3025da40 l     O .vmlinux	0000000e __param_str_softraw
3025da38 l     O .vmlinux	00000004 atkbd_softraw
30253024 l     O .vmlinux	00000014 __param_softrepeat
3025da50 l     O .vmlinux	00000011 __param_str_softrepeat
3061ae40 l     O .bss	00000004 atkbd_softrepeat
30253038 l     O .vmlinux	00000014 __param_reset
3025da68 l     O .vmlinux	0000000c __param_str_reset
3025da64 l     O .vmlinux	00000004 atkbd_reset
3025304c l     O .vmlinux	00000014 __param_set
3025da78 l     O .vmlinux	0000000a __param_str_set
3025da74 l     O .vmlinux	00000004 atkbd_set
3025da84 l     O .vmlinux	000000c8 atkbd_drv
3025db4c l     O .vmlinux	00000014 atkbd_serio_ids
3010d81c l     F .vmlinux	00000628 atkbd_interrupt
3010e968 l     F .vmlinux	00000204 atkbd_connect
3010eb6c l     F .vmlinux	000000d4 atkbd_reconnect
3010e568 l     F .vmlinux	0000005c atkbd_disconnect
3010e54c l     F .vmlinux	0000001c atkbd_cleanup
3025db60 l     O .vmlinux	00000008 atkbd_attribute_group
3025db68 l     O .vmlinux	0000001c atkbd_attributes
3025dbe8 l     O .vmlinux	00000014 atkbd_attr_extra
3025dbd4 l     O .vmlinux	00000014 atkbd_attr_scroll
3025dbc0 l     O .vmlinux	00000014 atkbd_attr_set
3025dbac l     O .vmlinux	00000014 atkbd_attr_softrepeat
3025db98 l     O .vmlinux	00000014 atkbd_attr_softraw
3025db84 l     O .vmlinux	00000014 atkbd_attr_err_count
3010d7b0 l     F .vmlinux	0000001c atkbd_do_show_err_count
3010d794 l     F .vmlinux	0000001c atkbd_do_show_softraw
3010e228 l     F .vmlinux	00000020 atkbd_do_set_softraw
3010d778 l     F .vmlinux	0000001c atkbd_do_show_softrepeat
3010e208 l     F .vmlinux	00000020 atkbd_do_set_softrepeat
3010d75c l     F .vmlinux	0000001c atkbd_do_show_set
3010e1e8 l     F .vmlinux	00000020 atkbd_do_set_set
3010d740 l     F .vmlinux	0000001c atkbd_do_show_scroll
3010e1c8 l     F .vmlinux	00000020 atkbd_do_set_scroll
3010d724 l     F .vmlinux	0000001c atkbd_do_show_extra
3010e1a8 l     F .vmlinux	00000020 atkbd_do_set_extra
3025dc00 l     O .vmlinux	00000200 atkbd_set3_keycode
3025de00 l     O .vmlinux	0000000e atkbd_scroll_keys
3025de10 l     O .vmlinux	00000080 atkbd_unxlate_table
3025de90 l     O .vmlinux	00000200 atkbd_set2_keycode
3022cef8 l     O .vmlinux	00000018 xl_table
3010d6c8 l     F .vmlinux	0000005c atkbd_attr_show_helper
3010ec40 l     F .vmlinux	00000028 atkbd_show_extra
3010ed78 l     F .vmlinux	00000028 atkbd_show_scroll
3010ee80 l     F .vmlinux	00000020 atkbd_show_set
3010efa8 l     F .vmlinux	00000028 atkbd_show_softrepeat
3010f0c0 l     F .vmlinux	00000028 atkbd_show_softraw
3010f1b8 l     F .vmlinux	00000024 atkbd_show_err_count
3010d7cc l     F .vmlinux	00000050 atkbd_compat_scancode
3010de44 l     F .vmlinux	00000108 atkbd_set_repeat_rate
3010df4c l     F .vmlinux	000000f0 atkbd_set_leds
3010e03c l     F .vmlinux	00000074 atkbd_event_work
3010e0b0 l     F .vmlinux	00000078 atkbd_event
3010e128 l     F .vmlinux	00000080 atkbd_attr_set_helper
3010ec68 l     F .vmlinux	00000110 atkbd_set_extra
3010eda0 l     F .vmlinux	000000e0 atkbd_set_scroll
3010eea0 l     F .vmlinux	00000108 atkbd_set_set
3010efd0 l     F .vmlinux	000000f0 atkbd_set_softrepeat
3010f0e8 l     F .vmlinux	000000d0 atkbd_set_softraw
3010e248 l     F .vmlinux	00000124 atkbd_probe
3010e36c l     F .vmlinux	0000015c atkbd_select_set
3010e4c8 l     F .vmlinux	00000084 atkbd_activate
3010e5c4 l     F .vmlinux	00000190 atkbd_set_keycode_table
3010e754 l     F .vmlinux	00000214 atkbd_set_device_attrs
3061ae40 l     O .bss	00000000 __key.0
00000000 l    df *ABS*	00000000 hid-core.c
3010f220 l     F .vmlinux	00000074 hid_lookup_collection
3010f294 l     F .vmlinux	00000088 hid_add_usage
3010f31c l     F .vmlinux	00000270 hid_add_field
3010f58c l     F .vmlinux	00000040 item_udata
3010f5cc l     F .vmlinux	00000040 item_sdata
3010f60c l     F .vmlinux	000001a8 hid_parser_global
3010f7b4 l     F .vmlinux	00000198 hid_parser_local
3010f94c l     F .vmlinux	00000210 hid_parser_main
3010fb5c l     F .vmlinux	00000008 hid_parser_reserved
3025e090 l     O .vmlinux	00000010 dispatch_type.2
3010ff28 l     F .vmlinux	0000006c snto32
3010ff94 l     F .vmlinux	00000044 s32ton
3010ffd8 l     F .vmlinux	00000078 hid_process_event
3022cf50 l     O .vmlinux	00000008 __func__.1
3022cf58 l     O .vmlinux	0000000a __func__.0
00000000 l    df *ABS*	00000000 hid-input.c
30253060 l     O .vmlinux	00000014 __param_pb_fnmode
3025e0a8 l     O .vmlinux	0000000e __param_str_pb_fnmode
3025e0a0 l     O .vmlinux	00000004 hid_pb_fnmode
3022cf68 l     O .vmlinux	00000100 hid_keyboard
3022d068 l     O .vmlinux	00000048 hid_hat_to_axis
301114d8 l     F .vmlinux	0000001c hidinput_open
301114f4 l     F .vmlinux	00000020 hidinput_close
00000000 l    df *ABS*	00000000 nonet.c
301143b4 l     F .vmlinux	00000008 sock_no_open
00000000 l    df *ABS*	00000000 klist.c
301143d8 l     F .vmlinux	0000004c klist_node_init
30114484 l     F .vmlinux	00000044 klist_release
301144c8 l     F .vmlinux	0000001c klist_dec_and_del
00000000 l    df *ABS*	00000000 sha1.c
00000000 l    df *ABS*	00000000 arch/sparc/boot/btfix.S
40079bd0 g     F .vmlinux	00000068 fcntl_getlease
400457fc  w    F .vmlinux	00000008 sys_recv
40073b04 g     F .vmlinux	00000098 lookup_create
4006bb7c g     F .vmlinux	0000011c generic_shutdown_super
400cf450 g     F .vmlinux	000000ac unregister_framebuffer
40012200 g     F .vmlinux	00000030 sun4d_nmi
4003911c g     F .vmlinux	00000144 sysctl_ms_jiffies
400432a4 g     F .vmlinux	00000058 param_set_ushort
400c6970 g     F .vmlinux	00000068 devm_ioport_unmap
40012050 g       .vmlinux	00000000 sun4c_rett_stackchk
4004a464 g     F .vmlinux	00000018 sysrq_timer_list_show
40115408 g     O .vmlinux	0000006c proc_kcore_operations
40108700 g     F .vmlinux	0000006c input_allocate_device
40031bfc g     F .vmlinux	00000024 console_start
400173d0 g     F .vmlinux	00000058 pci_unmap_sg
400123c0 g     F .vmlinux	0000008c do_hw_interrupt
40020f2c g       .vmlinux	00000000 tsunami_flush_page_to_ram
4013584c g       .vmlinux	00000000 ___f_pte_pfn
4012d208 g     O .vmlinux	00000004 fs_overflowgid
4012972c g       .vmlinux	00000000 __stop___kcrctab_gpl_future
40313b24 g     O .bss	00000004 core_uses_pid
400cc4d0 g     F .vmlinux	000000ac pci_map_rom_copy
40035d50 g     F .vmlinux	00000044 ns_to_timeval
40020bd4 g       .vmlinux	00000000 hypersparc_flush_sig_insns
400457e4 g     F .vmlinux	00000018 kfifo_free
4015535c g     F .vmlinux	00000018 firmware_init
4003e454 g     F .vmlinux	00000024 sys_pause
40078df4 g     F .vmlinux	00000080 posix_test_lock
40314cf8 g     O .bss	00000300 prom_prom_taken
400c6900 g     F .vmlinux	00000070 devm_ioport_map
4003e810 g     F .vmlinux	00000010 raw_notifier_chain_unregister
4003ae90 g     F .vmlinux	0000000c sys_getgid
4014ba18 g     F .vmlinux	00000038 init_bootmem
400118c8 g       .vmlinux	00000000 fnwin_patch2_7win
400457fc  w    F .vmlinux	00000008 sys_setsockopt
400628c8 g     F .vmlinux	00000070 page_add_file_rmap
40077e00 g     F .vmlinux	000002d0 sys_ppoll
4005741c g     F .vmlinux	00000018 truncate_inode_pages
400f25b4 g     F .vmlinux	000002f0 do_blank_screen
400ed3b8 g     F .vmlinux	00000140 paste_selection
400c1d4c g     F .vmlinux	0000002c prom_getstring
40013ba0 g     F .vmlinux	00000048 sun4d_build_irq
4005a204 g     F .vmlinux	00000038 nr_free_highpages
4012ed94 g     O .vmlinux	00000010 partitions_op
400f8680 g     F .vmlinux	00000014 uart_console_device
40152080 g     F .vmlinux	00000414 pci_bus_size_bridges
4030667c g     O .bss	00000004 srmmu_swprobe_trace
40069a3c g     F .vmlinux	00000024 filp_open
400b4730 g     F .vmlinux	00000084 exit_io_context
4005b950 g     F .vmlinux	000000b0 zap_page_range
4000d00c g       .vmlinux	00000000 root_dev
4014e848 g     F .vmlinux	00000118 prom_getbootargs
40036204 g     F .vmlinux	00000108 __local_bh_enable
4031a820 g     O .bss	00000004 console_blanked
40079470 g     F .vmlinux	0000019c locks_mandatory_area
400af7c0 g     F .vmlinux	000000e4 __elv_add_request
4010c534 g     F .vmlinux	00000534 hid_output_report
4012b198 g     O .vmlinux	00000004 lvl14_resolution
400b6268 g     F .vmlinux	00000050 set_disk_ro
400fdec4 g     F .vmlinux	00000028 platform_device_put
40069e58 g     F .vmlinux	000000b0 sys_close
4015cf70 g       .vmlinux	00000000 __setup_start
40135744 g       .vmlinux	00000000 ___is_page_copy
40086b04 g     F .vmlinux	00000064 simple_prepare_write
4006b9d8 g     F .vmlinux	00000044 __put_super_and_need_restart
400bee54 g     F .vmlinux	00000028 strcpy
4012bcb8 g     O .vmlinux	000001bc linux_sparc_fpu
400ae8c8 g     F .vmlinux	00000040 cap_ptrace
4003fe88 g     F .vmlinux	00000088 sys_setsid
40080d44 g     F .vmlinux	00000058 __put_mnt_ns
4002d4d8 g     F .vmlinux	00000040 current_sched_time
400afb20 g     F .vmlinux	00000040 elv_set_request
400ff678 g     F .vmlinux	00000088 dmam_alloc_coherent
40313ca4 g     O .bss	00000000 vfsmount_lock
4004e29c g     F .vmlinux	00000028 filemap_fdatawrite
40043a40 g     F .vmlinux	00000094 register_posix_clock
400c66e8  w    F .vmlinux	00000038 bust_spinlocks
400c8bfc g     F .vmlinux	00000210 pci_save_state
400c242c g       .vmlinux	00000000 __ashldi3
4013584c g       .vmlinux	00000000 ___f_pgoff_to_pte
40080098 g     F .vmlinux	000000d8 alloc_vfsmnt
400ba808 g     F .vmlinux	0000014c bitmap_parselist
400d12ac g     F .vmlinux	00000074 fb_videomode_to_var
400c4c30 g       .vmlinux	00000000 .rem_patch
400fe96c g     F .vmlinux	000000d8 kobj_unmap
400457fc  w    F .vmlinux	00000008 sys_msgget
40059be8 g     F .vmlinux	0000002c set_bdi_congested
40084f98 g     F .vmlinux	00000114 seq_path
40155020 g     F .vmlinux	0000008c uart_parse_options
40000000 g     F .stage2	00000138 __main
4008a998 g     F .vmlinux	00000138 do_utimes
4001258c g     F .vmlinux	00000114 do_fpd_trap
4006d37c g     F .vmlinux	00000088 generic_fillattr
40012be8 g     F .vmlinux	00000174 free_irq
4005fc3c g     F .vmlinux	00000088 find_extend_vma
4001d9b0 g     F .vmlinux	00000138 force_user_fault
40080754 g     F .vmlinux	00000010 mnt_pin
400fd244 g     F .vmlinux	00000028 class_device_initialize
40315a48 g     O .bss	00000004 fb_class
400ec990 g     F .vmlinux	0000015c con_set_default_unimap
400ff40c g     F .vmlinux	0000007c dmam_pool_create
40047a74 g     F .vmlinux	000000cc posix_cpu_nsleep_restart
400457fc  w    F .vmlinux	00000008 sys_mq_getsetattr
4013583c g       .vmlinux	00000000 ___fs_mmu_unlockarea
40053308 g     F .vmlinux	0000003c __pagevec_free
400ced14 g     F .vmlinux	00000068 fb_blank
400c45f4 g       .vmlinux	00000000 memscan
401105b8 g     F .vmlinux	0000008c klist_next
400c05d8 g     F .vmlinux	00000030 vscnprintf
400f95b0 g     F .vmlinux	00000018 device_schedule_callback
4007e584 g     F .vmlinux	00000140 iget_locked
4006a79c g     F .vmlinux	0000013c vfs_write
400bc548 g     F .vmlinux	000001d8 kobject_shadow_add
40315a30 g     O .bss	00000004 num_registered_fb
40111aa0 g     F .vmlinux	00000018 yield
40016d84 g     F .vmlinux	00000018 sbus_set_sbus64
4001402c g     F .vmlinux	00000090 leon_disable_pil_irq
400457fc  w    F .vmlinux	00000008 compat_sys_socketcall
40303038 g     O .bss	00000004 sparc_fpu_type
40032b04 g     F .vmlinux	000000f0 put_files_struct
4005d520 g     F .vmlinux	000000a4 vm_insert_pfn
400eec44 g     F .vmlinux	00000088 setledstate
400cae14 g     F .vmlinux	00000008 pci_uevent
400857e4 g     F .vmlinux	000000f4 vfs_removexattr
4008699c g     F .vmlinux	00000050 simple_rmdir
40087188 g     F .vmlinux	000000d4 simple_attr_write
400cf814 g     F .vmlinux	000001b8 fb_validate_mode
40020ee8 g       .vmlinux	00000000 viking_flush_sig_insns
4003c4e8 g     F .vmlinux	00000038 force_sigsegv
40032e8c g     F .vmlinux	0000024c daemonize
40086140 g     F .vmlinux	000000cc generic_listxattr
400c82e4 g     F .vmlinux	000000c0 pci_remove_bus_device
400bcbac g     F .vmlinux	00000098 prio_tree_replace
40016f84 g     F .vmlinux	00000038 sbus_map_single
40011934 g       .vmlinux	00000000 fwin_mmu_patchme
4004de28 g     F .vmlinux	000000b4 softlockup_tick
4008c1bc g     F .vmlinux	0000003c generic_block_bmap
400fc1d0 g     F .vmlinux	000000dc driver_probe_device
40150360 g     F .vmlinux	000001dc pci_sort_breadthfirst
4006a9a0 g     F .vmlinux	00000090 sys_pread64
40032310 g     F .vmlinux	0000004c create_prof_cpu_mask
4004e2d8 g     F .vmlinux	00000028 filemap_flush
400a910c g     F .vmlinux	0000005c ext2_set_inode_flags
400801ac g     F .vmlinux	00000024 free_vfsmnt
4002debc g     F .vmlinux	00000010 task_prio
4006cebc g     F .vmlinux	00000048 alloc_chrdev_region
4013584c g       .vmlinux	00000000 ___f_disable_pil_irq
4013584c g       .vmlinux	00000000 ___f_pte_clear
40071194 g     F .vmlinux	00000030 get_write_access
400ba43c g     F .vmlinux	0000029c __bitmap_parse
400c4f08 g       .vmlinux	00000000 .div_patch
4001eda0 g     F .vmlinux	00000064 srmmu_nocache_calcsize
4013584c g       .vmlinux	00000000 ___f_pte_free
4008d09c g     F .vmlinux	000000b4 alloc_page_buffers
40020de8 g       .vmlinux	00000000 viking_flush_cache_range
4012972c g       .vmlinux	00000000 __stop___ksymtab_unused
40135854 g       .vmlinux	00000000 __start___fixup
00000000 g       *ABS*	00000000 ___i_page_readonly
40011468 g       .vmlinux	00000000 __udelay
4008579c g     F .vmlinux	00000048 vfs_listxattr
40036df4 g     F .vmlinux	00000024 request_resource
40139cf4  w    F .vmlinux	00000008 smp_setup_processor_id
4008c0c4 g     F .vmlinux	000000f8 nobh_truncate_page
400c9658 g     F .vmlinux	000001b8 pci_request_region
40017454 g     F .vmlinux	0000002c pci_dma_sync_single_for_device
4012d378 g     O .vmlinux	00000050 per_cpu__hrtimer_bases
40007000 g       .vmlinux	00000000 pg1
4012b324 g     O .vmlinux	00000004 stop_a_enabled
4013584c g       .vmlinux	00000000 ___f_enable_irq
40063bdc g     F .vmlinux	00000020 vmalloc_node
400dda28 g     F .vmlinux	00000098 leon3_rs_put_char_base
40011ddc g       .vmlinux	00000000 rtrap_7win_patch1
400c39e4 g       .vmlinux	00000000 __divdi3
40044a54 g     F .vmlinux	000000f8 sys_clock_settime
40300044 g     O .bss	00000004 reset_devices
40010b84 g       .vmlinux	00000000 invalid_segment_patch1_ff
40303034 g     O .bss	00000004 sparc_cpu_type
40046708 g     F .vmlinux	0000013c posix_cpu_timer_schedule
4004148c g     F .vmlinux	000000b0 queue_delayed_work
4007fab8 g     F .vmlinux	000002f8 expand_files
400bea48 g     F .vmlinux	0000001c __init_rwsem
4014fc1c g     F .vmlinux	000000ac pci_scan_child_bus
40017358 g     F .vmlinux	00000078 pci_map_sg
4013584c g       .vmlinux	00000000 ___f_flush_cache_page
401347a0 g       .vmlinux	00000000 ___fs_pgd_none
4007b748 g     F .vmlinux	0000004c d_instantiate
4030cc30 g     O .bss	0000000c avenrun
4009fff4 g     F .vmlinux	0000009c read_dev_sector
40004000 g       .vmlinux	00000000 trapbase
40090468 g     F .vmlinux	00000014 bdput
400f2a10 g     F .vmlinux	00000124 register_con_driver
4014f098 g     F .vmlinux	00000068 pci_bus_add_device
40020e2c g       .vmlinux	00000000 viking_flush_tlb_all
40134280 g       .vmlinux	00000000 ___fs_mmu_get_scsi_one
00000000 g       *ABS*	00000000 ___i_page_shared
400c8608 g     F .vmlinux	000000b8 pci_find_ext_capability
400457fc  w    F .vmlinux	00000008 sys_mq_unlink
400752d4 g     F .vmlinux	00000084 page_put_link
400ed5d0 g     F .vmlinux	000001ac setkeycode
40035814 g     F .vmlinux	000000f4 sys_settimeofday
400e8f58 g     F .vmlinux	000000ec misc_deregister
400c72a8 g     F .vmlinux	00000028 ___set_bit
4003d5d0 g     F .vmlinux	00000110 sys_rt_sigprocmask
4004c944 g     F .vmlinux	00000030 rt_mutex_next_owner
400a0e40 g     F .vmlinux	00000054 sysfs_delete_inode
403143e4 g     O .bss	00000004 prom_root_node
400c25a4 g     F .vmlinux	00000248 bit_map_string_get
40075520 g     F .vmlinux	00000054 set_close_on_exec
400aefa8 g     F .vmlinux	00000078 elv_rb_add
40075878 g     F .vmlinux	0000003c f_setown
40019c78 g     F .vmlinux	00000040 do_solaris_syscall
40034fcc g     F .vmlinux	0000001c it_real_fn
400fcab4 g     F .vmlinux	00000028 driver_find
4008a824 g     F .vmlinux	00000174 sys_utime
4009057c g     F .vmlinux	00000084 bd_claim
4008706c g     F .vmlinux	00000060 simple_attr_open
40019320 g     F .vmlinux	000008d4 do_ptrace
00000000 g       *ABS*	00000000 ___h_sparc_unmapped_base
40018c1c g     F .vmlinux	000000a8 try_to_clear_window_buffer
4030e074 g     O .bss	00000004 percpu_pagelist_fraction
401128c4 g     F .vmlinux	000000ac __down_read
4007ddbc g     F .vmlinux	0000011c clear_inode
400214e0 g     F .vmlinux	0000003c sun4c_complete_all_stores
40085564 g     F .vmlinux	0000016c vfs_setxattr
400af178 g     F .vmlinux	00000060 elv_dispatch_add_tail
40069754 g     F .vmlinux	0000004c sys_lchown
4003eea8 g     F .vmlinux	00000024 kernel_halt
4013582c g       .vmlinux	00000000 ___fs_mmu_lockarea
4014f5b0 g     F .vmlinux	00000134 pci_add_new_bus
4007f560 g     F .vmlinux	0000028c notify_change
40030908 g     F .vmlinux	00000064 get_exec_domain_list
4006e3e8 g     F .vmlinux	000000d0 open_exec
400dff38 g     F .vmlinux	00000058 tty_paranoia_check
400f6004 g     F .vmlinux	0000010c uart_get_baud_rate
40302a08 g     O .bss	00000000 irq_action_lock
4013584c g       .vmlinux	00000000 ___f_free_pte_fast
4007ca14 g     F .vmlinux	000000f0 d_alloc_anon
400911d8 g     F .vmlinux	00000018 close_bdev_excl
400def58 g     F .vmlinux	00000048 add_disk_randomness
4012a0b0 g       .vmlinux	00000000 linux_dbvec
400c0670 g     F .vmlinux	00000024 vsprintf
400457fc  w    F .vmlinux	00000008 sys_shmdt
400457fc  w    F .vmlinux	00000008 sys_recvfrom
40042c0c g     F .vmlinux	00000058 rcu_needs_cpu
40112970 g     F .vmlinux	000000a8 __down_write_nested
40013690 g     F .vmlinux	000001ec show_sun4d_interrupts
40031360  w    F .vmlinux	00000010 printk_clock
401159b4 g     O .vmlinux	0000006c ext2_file_operations
400c1b7c g     F .vmlinux	00000040 __prom_getsibling
400c1ea4 g     F .vmlinux	00000024 prom_nextprop
400bbb94 g     F .vmlinux	00000044 idr_get_new
401495e4 g     F .vmlinux	00000058 init_idle
4006b4e0 g     F .vmlinux	00000114 get_empty_filp
400e0570 g     F .vmlinux	000000c4 tty_ldisc_ref_wait
40053c94 g     F .vmlinux	00000014 nr_free_buffer_pages
400bb118 g     F .vmlinux	0000015c __div64_32
400aff90 g     F .vmlinux	000001c8 elv_iosched_store
400fff48 g     F .vmlinux	000000a0 devres_release_group
40010c2c g       .vmlinux	00000000 invalid_segment_patch1
4005f6e8 g     F .vmlinux	00000108 find_mergeable_anon_vma
400bbe2c g     F .vmlinux	00000084 idr_find
400e08c4 g     F .vmlinux	00000020 proc_clear_tty
40100a38 g     F .vmlinux	00000014 anon_transport_class_unregister
40032bf4 g     F .vmlinux	0000001c reset_files_struct
40011b28 g       .vmlinux	00000000 tsetup_7win_patch6
400bc734 g     F .vmlinux	0000002c kobject_register
4001bc08 g     F .vmlinux	00000074 of_platform_device_create
400b2384 g     F .vmlinux	00000064 blk_get_request
4006b040 g     F .vmlinux	00000064 sys_writev
4003ea2c g     F .vmlinux	000001dc sys_setpriority
4013584c g       .vmlinux	00000000 ___f_pgd_clear
4007b588 g     F .vmlinux	000000e8 lock_may_read
4008fbf8 g     F .vmlinux	00000058 bioset_free
4015d1a4 g       .vmlinux	00000000 __setup_end
40072a64 g     F .vmlinux	000000b8 set_fs_altroot
40058a9c g     F .vmlinux	0000028c try_to_free_pages
400feccc g     F .vmlinux	000001a0 dma_pool_create
4003e820 g     F .vmlinux	00000010 raw_notifier_call_chain
40113c90 g     O .vmlinux	0000006c rdwr_fifo_fops
40135040 g       .vmlinux	00000000 ___fs___swp_offset
4012d5cc g     O .vmlinux	00000004 max_lock_depth
400fbe30 g     F .vmlinux	00000014 bus_unregister_notifier
4001e794 g     F .vmlinux	000000b0 search_extable
400d0a04 g     F .vmlinux	00000048 fb_cleanup_device
400fe7f4 g     F .vmlinux	0000001c firmware_register
4006a074 g     F .vmlinux	000000c8 remote_llseek
40053fec g     F .vmlinux	00000074 setup_pageset
400423d4 g     F .vmlinux	0000007c detach_pid
400a1064 g     F .vmlinux	000000bc sysfs_new_inode
4001bb70 g     F .vmlinux	00000014 of_release_dev
400bd5b8 g     F .vmlinux	0000022c radix_tree_insert
401353c8 g       .vmlinux	00000000 ___fs_pmd_page
400a55dc g     F .vmlinux	00000044 ext2_bg_has_super
40039b38 g     F .vmlinux	00000070 ptrace_detach
400c984c g     F .vmlinux	00000080 pci_request_selected_regions
40082150 g     F .vmlinux	000000b0 copy_mnt_ns
40038b74 g     F .vmlinux	00000038 proc_dointvec_jiffies
4005fda8 g     F .vmlinux	00000118 split_vma
400882dc g     F .vmlinux	000000d4 propagate_mount_busy
400ffe3c g     F .vmlinux	00000070 devres_close_group
400cb538 g     F .vmlinux	000001b0 pci_find_present
400c9810 g     F .vmlinux	0000003c pci_release_selected_regions
400c7794 g     F .vmlinux	0000005c pci_user_write_config_byte
401113d4 g     F .vmlinux	0000012c wait_for_completion_timeout
4013584c g       .vmlinux	00000000 ___f_free_pmd_fast
400c1d78 g     F .vmlinux	0000004c prom_nodematch
400c255c g       .vmlinux	00000000 ___atomic24_sub
400c9ba8 g     F .vmlinux	00000014 pci_set_consistent_dma_mask
40010828 g       .vmlinux	00000000 fpd_trap_handler
4012dc64 g     O .vmlinux	00000004 dirty_expire_interval
401581e0 g     O .vmlinux	00000004 poke_srmmu
401551e4 g     F .vmlinux	00000018 buses_init
4014d300 g     F .vmlinux	00000058 files_init
40114108 g     O .vmlinux	00000054 simple_dir_inode_operations
4006d404 g     F .vmlinux	00000040 vfs_getattr
400c9084 g     F .vmlinux	00000014 pci_enable_device
40303008 g     O .bss	00000004 master_l10_counter
4013584c g       .vmlinux	00000000 ___f_mmu_translate_dvma
4003a3f8  w    F .vmlinux	00000008 read_persistent_clock
400003c4 g     F .stage2	00000034 leon3_getbase
4008ea74 g     F .vmlinux	000000a0 zero_fill_bio
4013584c g       .vmlinux	00000000 ___f_mmu_release_scsi_one
400fb658 g     F .vmlinux	00000160 bus_add_device
400e07d4 g     F .vmlinux	00000070 tty_wakeup
400c14d8 g     F .vmlinux	0000000c prom_meminfo
4003218c g     F .vmlinux	00000074 profile_hits
400b0414 g     F .vmlinux	000000d4 blk_queue_ordered
40011598 g       .vmlinux	00000000 spnwin_patch1_7win
40098f60 g     F .vmlinux	00000148 proc_get_inode
4003fca8 g     F .vmlinux	00000148 sys_setpgid
4012a0ac g       .vmlinux	00000000 nwindowsm1
4030e064 g     O .bss	00000004 hashdist
400e04c0 g     F .vmlinux	0000004c tty_ldisc_put
4008f330 g     F .vmlinux	000002a4 bio_map_user_iov
400dbc9c g     F .vmlinux	00000448 vendor_dev_string
40037540 g     F .vmlinux	00000058 sysctl_perm
400869ec g     F .vmlinux	000000d0 simple_rename
4007b670 g     F .vmlinux	000000d8 lock_may_write
4003f640 g     F .vmlinux	0000019c sys_setresuid
40083dc4 g     F .vmlinux	00000394 io_submit_one
4013584c g       .vmlinux	00000000 ___f_mk_pte
400be820 g     F .vmlinux	0000002c rb_last
4007766c g     F .vmlinux	000002b8 sys_pselect7
400d9d14 g     F .vmlinux	00000040 fb_find_logo
400e0388 g     F .vmlinux	0000006c tty_register_ldisc
40305dec g     O .bss	0000001c sun4c_kfree_ring
40111ae8 g     F .vmlinux	00000040 io_schedule_timeout
400bbf84 g     F .vmlinux	00000058 idr_init
400c83a4 g     F .vmlinux	0000004c pci_remove_behind_bridge
400bfba8 g     F .vmlinux	0000003c simple_strtoll
40102d1c g     F .vmlinux	000000d0 loop_unregister_transfer
4002110c g       .vmlinux	00000000 swift_flush_cache_mm
40090ef8 g     F .vmlinux	0000001c blkdev_get
403143f0 g     O .bss	00000004 prom_nodeops
4001cb84 g     F .vmlinux	0000005c pcibios_align_resource
40014158 g     F .vmlinux	00000004 leon_load_profile_irq
40319324 g     O .bss	00000004 conswitchp
40011c68 g       .vmlinux	00000000 tsetup_patch5
4006a240 g     F .vmlinux	0000008c sys_lseek
4001e844 g     F .vmlinux	00000044 search_extables_range
4014db48 g     F .vmlinux	0000006c buffer_init
400748e0 g     F .vmlinux	0000037c vfs_rename
40011de0 g       .vmlinux	00000000 rtrap_7win_patch2
40154a00 g     F .vmlinux	000000b4 kbd_init
00000000 g       *ABS*	00000000 ___a_pte_dirtyi
4008853c g     F .vmlinux	00000028 drop_slab
4008ef3c g     F .vmlinux	00000014 bio_add_pc_page
40076118 g     F .vmlinux	000003c8 vfs_ioctl
400984d0 g     F .vmlinux	00000120 proc_exe_link
40087df8 g     F .vmlinux	000000c8 writeback_inodes
400d1578 g     F .vmlinux	00000050 fb_match_mode
400168a8 g     F .vmlinux	00000010 sbus_iounmap
400a626c g     F .vmlinux	000000c8 ext2_inode_by_name
4002e828 g     F .vmlinux	000001c4 show_state_filter
4013a74c g     F .vmlinux	00000248 prepare_namespace
400cd0cc g     F .vmlinux	000000d8 pci_proc_attach_device
4001441c g     F .vmlinux	00000094 __show_backtrace
4012dc6c g     O .vmlinux	00000004 vm_dirty_ratio
4012ec74 g     O .vmlinux	00000010 diskstats_op
4007a41c g     F .vmlinux	00000258 fcntl_getlk
400328e4 g     F .vmlinux	00000020 is_current_pgrp_orphaned
400cb334 g     F .vmlinux	00000124 pci_get_device_reverse
4015053c g     F .vmlinux	0000004c pci_bus_max_busnr
400c87d8 g     F .vmlinux	000000b8 pci_find_parent_resource
40049144 g     F .vmlinux	0000027c second_overflow
400fe474 g     F .vmlinux	00000014 platform_driver_unregister
400694d0 g     F .vmlinux	000000d8 sys_fchmodat
40016b58 g     F .vmlinux	00000020 dma_map_single
4008fdb4 g     F .vmlinux	000000a4 set_blocksize
400ecc3c g     F .vmlinux	0000001c con_protect_unimap
4008a4c8 g     F .vmlinux	0000008c do_fsync
4015d2f0 g       .vmlinux	00000000 __security_initcall_start
400b4828 g     F .vmlinux	00000014 swap_io_context
4002f1fc g     F .vmlinux	0000001c __cleanup_signal
4012ded8 g     O .vmlinux	0000001c directly_mappable_cdev_bdi
400fd060 g     F .vmlinux	00000074 make_class_name
40072d9c g     F .vmlinux	0000009c lookup_one_len
4005de34 g     F .vmlinux	000000b8 vmalloc_to_page
400aa458 g     F .vmlinux	00000090 ext2_delete_inode
40130d28 g     O .vmlinux	00000040 default_grn
40010ca8 g       .vmlinux	00000000 vac_hwflush_patch1
4008e474 g     F .vmlinux	00000214 __getblk
40011ebc g       .vmlinux	00000000 rtrap_patch2
400c7194 g     F .vmlinux	000000bc pci_iomap
4012972c g       .vmlinux	00000000 __start___kcrctab_gpl_future
40134848 g       .vmlinux	00000000 ___fs_pte_offset_kernel
40030d30 g     F .vmlinux	00000018 oops_enter
40054c4c g     F .vmlinux	0000002c laptop_io_completion
4005a520 g     F .vmlinux	00000228 kmap_high
400c2b5c g       .vmlinux	00000000 csum_partial
4012972c g       .vmlinux	00000000 __stop___ksymtab_gpl_future
40040b54 g     F .vmlinux	00000024 sys_umask
40088a2c g     F .vmlinux	00000508 generic_file_splice_read
40079820 g     F .vmlinux	0000034c __break_lease
4012972c g       .vmlinux	00000000 __stop___kcrctab_unused
40143630 g     F .vmlinux	000000e8 auxio_power_probe
40010ba0 g       .vmlinux	00000000 vac_hwflush_patch1_on
400c3e3c g     F .vmlinux	00000000 memmove
4001b5fc g     F .vmlinux	00000038 of_find_device_by_node
40134e1c g       .vmlinux	00000000 ___fs_destroy_context
400457fc  w    F .vmlinux	00000008 sys_pciconfig_iobase
400167a0 g     F .vmlinux	00000020 of_ioremap
403041c4 g     O .bss	00000004 vac_entries_per_segment
40313dd0 g     O .bss	00000004 blk_max_low_pfn
400fde00 g     F .vmlinux	0000002c platform_get_irq
400990a8 g     F .vmlinux	0000009c proc_fill_super
4008a440 g     F .vmlinux	0000001c emergency_sync
4007ded8 g     F .vmlinux	00000080 new_inode
4003c068 g     F .vmlinux	00000018 force_sig_specific
40052764 g     F .vmlinux	00000228 sys_fadvise64_64
400438d4 g     F .vmlinux	0000001c param_get_string
40048cf8 g     F .vmlinux	00000124 copy_namespaces
4004eae4 g     F .vmlinux	00000058 find_get_page
40069990 g     F .vmlinux	00000050 nameidata_to_filp
4001f9ac g     F .vmlinux	00000030 leon_flush_pcache_all
400c8264 g     F .vmlinux	00000080 pci_remove_bus
40084e1c g     F .vmlinux	00000020 seq_release
40144424 g     F .vmlinux	00000860 btfixup
400a2324 g     F .vmlinux	00000068 sysfs_dirent_exist
400c8b64 g     F .vmlinux	00000098 pci_choose_state
400c734c g     F .vmlinux	00000044 atomic_add_unless
400ca5d0 g     F .vmlinux	00000100 pci_fixup_device
400397d8 g     F .vmlinux	00000048 ptrace_untrace
400b0894 g     F .vmlinux	00000034 blk_queue_max_segment_size
4013584c g       .vmlinux	00000000 ___f_switch_mm
4009032c g     F .vmlinux	000000fc bdget
4030004c g     O .bss	00000004 late_time_init
4006b4c0 g     F .vmlinux	00000020 proc_nr_files
400c0608 g     F .vmlinux	0000002c snprintf
400520c4 g     F .vmlinux	00000184 badness
40039f70 g     F .vmlinux	00000048 ptrace_traceme
4002db54 g     F .vmlinux	00000040 complete
400e027c g     F .vmlinux	0000003c tty_schedule_flip
400cd1a4 g     F .vmlinux	00000044 pci_proc_detach_device
4013584c g       .vmlinux	00000000 ___f_alloc_thread_info
40317d64 g     O .bss	000003ac amba_conf2
4003e544  w    F .vmlinux	00000008 arch_vma_name
40103704 g     F .vmlinux	000000b8 uhci_check_and_reset_hc
400ffeac g     F .vmlinux	0000009c devres_remove_group
400f82d8 g     F .vmlinux	000001ec uart_resume_port
400cdbd8 g     F .vmlinux	000008b8 fb_show_logo
40011850 g       .vmlinux	00000000 spwin_srmmu_stackchk
40135438 g       .vmlinux	00000000 ___fs_pte_alloc_one
4008601c g     F .vmlinux	00000038 sys_fremovexattr
4014c518 g     F .vmlinux	00000008 page_alloc_init
4006b3bc g     F .vmlinux	000000d0 sys_sendfile64
400c4988 g       .vmlinux	00000000 _Rem
4012972c g       .vmlinux	00000000 __start___ksymtab_gpl
40031c20 g     F .vmlinux	000000bc unregister_console
40062684 g     F .vmlinux	0000017c page_mkclean
4002d2fc g     F .vmlinux	00000088 sched_exit
400cbff0 g     F .vmlinux	0000017c pci_create_sysfs_dev_files
401583b8 g     O .vmlinux	0000009c initkmem_list3
400bc4fc g     F .vmlinux	0000004c kobject_rename
400c1dc4 g     F .vmlinux	00000070 prom_searchsiblings
4003611c g     F .vmlinux	00000008 jiffies_to_clock_t
403004a4 g     O .bss	00000004 initrd_below_start_ok
40052028 g     F .vmlinux	00000018 mempool_kzalloc
40031bd8 g     F .vmlinux	00000024 console_stop
4003ae78 g     F .vmlinux	0000000c sys_getuid
400c6870 g     F .vmlinux	00000068 devm_iounmap
40110da4 g       .vmlinux	00000000 flush_patch_switch
40056290 g     F .vmlinux	00000030 max_sane_readahead
4012972c g       .vmlinux	00000000 __start___ksymtab_unused
400c9ab8 g     F .vmlinux	000000dc pci_msi_off
40010f20 g       .vmlinux	00000000 sys_rt_sigreturn
4014b9d0 g     F .vmlinux	00000010 init_bootmem_node
00000000 g       *ABS*	00000000 ___h_none_mask
4003557c g     F .vmlinux	0000005c sys_time
4001e33c g     F .vmlinux	00000020 check_pgt_cache
40313cd8 g     O .bss	00000004 sysctl_drop_caches
401355c8 g       .vmlinux	00000000 ___fs_pgd_set
4005545c g     F .vmlinux	00000074 do_writepages
400fc98c g     F .vmlinux	00000038 driver_remove_file
4012f170 g     O .vmlinux	00000004 prom_pavl_ptr
400d00ec g     F .vmlinux	00000148 fb_invert_cmaps
4006ba90 g     F .vmlinux	00000020 lock_super
4002e2dc g     F .vmlinux	000000a8 sys_sched_getparam
40010f48 g       .vmlinux	00000000 sys_fork
400beaac g     F .vmlinux	00000048 __down_write_trylock
4005eb78 g     F .vmlinux	00000018 vm_get_page_prot
4013584c g       .vmlinux	00000000 ___f_update_mmu_cache
400bf9c8 g     F .vmlinux	00000038 simple_strtol
40056020 g     F .vmlinux	00000258 page_cache_readahead
40013ec4 g     F .vmlinux	00000038 sparc_leon_eirq_register
400c6754  w    F .vmlinux	00000014 __iowrite64_copy
400cacf0 g     F .vmlinux	00000028 pci_dev_put
400482a4 g     F .vmlinux	00000074 hrtimer_try_to_cancel
4001bcc8 g     F .vmlinux	00000088 devm_request_irq
4030e130 g     O .bss	00000004 page_cluster
4007f198 g     F .vmlinux	0000009c init_special_inode
400fb7b8 g     F .vmlinux	00000068 bus_attach_device
400cd8d0 g     F .vmlinux	000000a8 fb_pad_unaligned_buffer
4014ebac g     F .vmlinux	00000418 prom_meminit
4004cff8 g     F .vmlinux	00000124 sys_getgroups16
40054f4c g     F .vmlinux	00000128 write_one_page
400c45f4 g       .vmlinux	00000000 __memscan_generic
40147754 g     F .vmlinux	00000154 ld_mmu_iounit
4012d2f0 g     O .vmlinux	0000005c module_subsys
400daed0 g     F .vmlinux	000008bc cfb_copyarea
40011048 g       .vmlinux	00000000 sys_vfork
401442b4 g     F .vmlinux	0000006c load_mmu
40048a4c g     F .vmlinux	00000108 remove_acceptable_latency
401582e0 g     O .vmlinux	00000004 nr_kernel_pages
40082f80 g     F .vmlinux	0000005c lookup_ioctx
4014bb10 g     F .vmlinux	00000044 __alloc_bootmem
4007fe5c g     F .vmlinux	0000004c unregister_filesystem
40100ad0 g     F .vmlinux	00000018 transport_remove_device
401500e8 g     F .vmlinux	000001f0 pci_create_bus
4004e874 g     F .vmlinux	000000d8 sync_page_range
400a8100 g     F .vmlinux	0000002c ext2_put_inode
40302a00 g     O .bss	00000004 thiscpus_tbr
40074004 g     F .vmlinux	0000001c sys_mkdir
40091060 g     F .vmlinux	00000034 ioctl_by_bdev
400ef99c g     F .vmlinux	00000018 schedule_console_callback
40140e94 g     F .vmlinux	00000814 setup_arch
40134af0 g       .vmlinux	00000000 ___ss_ptrs_per_pgd
400c3384 g       .vmlinux	00000000 __csum_partial_copy_end
400a1e38 g     F .vmlinux	00000054 sysfs_add_file_to_group
403042d4 g     O .bss	00000004 sparc_aliases
400435bc g     F .vmlinux	00000030 param_get_bool
400457fc  w    F .vmlinux	00000008 sys_socket
4012a0a8 g       .vmlinux	00000000 nwindows
40011c8c g       .vmlinux	00000000 tsetup_sun4c_stackchk
40055764 g     F .vmlinux	00000034 mapping_tagged
400e3168 g     F .vmlinux	00000058 tty_flip_buffer_push
4002e728 g     F .vmlinux	00000048 sys_sched_get_priority_min
40040060 g     F .vmlinux	00000080 groups_search
40302ff8 g     O .bss	00000004 mstk48t02_regs
400ba278 g     F .vmlinux	0000011c __bitmap_shift_left
400fc420 g     F .vmlinux	00000024 driver_attach
40048c58 g     F .vmlinux	000000a0 dup_namespaces
40304194 g     O .bss	00000004 auxio_register
400393f8 g     F .vmlinux	00000370 sys_capset
40134d6c g       .vmlinux	00000000 ___fs_sun4c_flush_context
4030e05c g     O .bss	00000004 max_pfn
4008b834 g     F .vmlinux	00000044 mark_buffer_dirty
400fa024 g     F .vmlinux	00000018 device_unregister
401352f0 g       .vmlinux	00000000 ___fs_pgd_clear
4012f174 g     O .vmlinux	00000004 prom_ptak_ptr
4012972c g       .vmlinux	00000000 __start___kcrctab_unused_gpl
4006da0c g     F .vmlinux	0000003c sys_lstat64
4001b1a4 g     F .vmlinux	00000074 of_n_size_cells
400be84c g     F .vmlinux	0000008c rb_next
400afab0 g     F .vmlinux	00000038 elv_latter_request
400ca86c g     F .vmlinux	000000e4 pci_match_device
400c7280 g     F .vmlinux	00000028 ___clear_bit
4006da48 g     F .vmlinux	0000003c sys_fstat64
4003c384 g     F .vmlinux	000000a4 zap_other_threads
400f2f14 g     F .vmlinux	00000164 do_unblank_screen
400457fc  w    F .vmlinux	00000008 sys_msgrcv
400ba0cc g     F .vmlinux	00000070 __bitmap_weight
400457fc  w    F .vmlinux	00000008 sys_mq_open
400cd7d0 g     F .vmlinux	0000001c fb_unregister_client
4003001c g     F .vmlinux	000001d0 do_fork
400ec104 g     F .vmlinux	00000058 inverse_translate
4012d214 g     O .vmlinux	00000004 overflowuid
4003b600 g     F .vmlinux	00000078 flush_sigqueue
4008b8f4 g     F .vmlinux	000001e0 __find_get_block
40039820 g     F .vmlinux	00000098 __ptrace_unlink
400bcd6c g     F .vmlinux	00000300 prio_tree_insert
40013260 g     F .vmlinux	00000008 init_irq_proc
400836d4 g     F .vmlinux	00000380 sys_io_setup
40047d20 g     F .vmlinux	000000fc ktime_add_ns
400b0210 g     F .vmlinux	00000024 elv_rb_former_request
400457fc  w    F .vmlinux	00000008 compat_sys_mq_getsetattr
400bd898 g     F .vmlinux	00000094 radix_tree_lookup
4007e364 g     F .vmlinux	00000060 inode_needs_sync
40135770 g       .vmlinux	00000000 ___fs_sbint_to_irq
400dfe20 g     F .vmlinux	00000044 randomize_range
40014d58 g     F .vmlinux	00000050 kernel_thread
40042540 g     F .vmlinux	00000038 get_pid_task
40045394 g     F .vmlinux	0000005c finish_wait
400f1250 g     F .vmlinux	00000030 scrollback
40054c78 g     F .vmlinux	00000018 laptop_sync_completion
4012972c g       .vmlinux	00000000 __start___kcrctab_unused
400ab828 g     F .vmlinux	00000154 ext2_write_super
4007c82c g     F .vmlinux	00000070 d_alloc_name
400cb2c8 g     F .vmlinux	0000001c pci_get_device
4008ca94 g     F .vmlinux	00000054 block_sync_page
40072bb8 g     F .vmlinux	0000005c __user_path_lookup_open
40020960 g       .vmlinux	00000000 hypersparc_flush_cache_mm
400208cc g     F .vmlinux	0000004c iounit_map_dma_page
40302b90 g     O .bss	00000004 sun4m_interrupts
4007d97c g     F .vmlinux	00000068 is_subdir
4001469c g     F .vmlinux	0000000c thread_saved_pc
400457fc  w    F .vmlinux	00000008 sys_socketcall
4003d7a8 g     F .vmlinux	00000010 sys_rt_sigpending
4012c4a4 g     O .vmlinux	00000008 log_wait
400fb414 g     F .vmlinux	00000038 bus_remove_file
400a0c88 g     F .vmlinux	000001b8 sun_partition
4004322c g     F .vmlinux	00000058 param_set_short
40010930 g       .vmlinux	00000000 do_watchpoint
4005b140 g     F .vmlinux	0000007c __pte_alloc_kernel
40313d48 g     O .bss	00000004 inotify_max_queued_events
40091c6c g     F .vmlinux	00000bc0 __blockdev_direct_IO
400862f8 g     F .vmlinux	00000024 simple_statfs
400b4d18 g     F .vmlinux	00000068 blkdev_driver_ioctl
400cc57c g     F .vmlinux	00000088 pci_remove_rom
4008eb58 g     F .vmlinux	0000002c bio_phys_segments
40076078 g     F .vmlinux	00000028 kill_fasync
40020918 g       .vmlinux	00000000 hypersparc_flush_cache_all
402ff520 g       .vmlinux	00000000 __per_cpu_end
4007a930 g     F .vmlinux	000001d4 fcntl_getlk64
40112a30 g       .vmlinux	00000000 _etext
400c47b0 g       .vmlinux	00000000 .mul
4004e544 g     F .vmlinux	00000154 wait_on_page_writeback_range
403043b4 g     O .bss	00000004 sun4c_memerr_reg
400fce40 g     F .vmlinux	0000002c class_destroy
403008f0 g     O .bss	00002000 trapbuf
400f84c4 g     F .vmlinux	00000190 uart_register_driver
4006d760 g     F .vmlinux	00000040 sys_newlstat
4013584c g       .vmlinux	00000000 ___f_sparc_mapiorange
400ffb20 g     F .vmlinux	00000038 devres_destroy
40013f94 g     F .vmlinux	00000098 leon_enable_irq
400c0634 g     F .vmlinux	0000003c scnprintf
4008ac44 g     F .vmlinux	00000048 __bforget
4005638c g     F .vmlinux	00000120 put_page
4004e110 g     F .vmlinux	00000070 __remove_from_page_cache
400457fc  w    F .vmlinux	00000008 sys_add_key
40155300 g     F .vmlinux	00000044 register_cpu
400457fc  w    F .vmlinux	00000008 compat_sys_set_robust_list
40300048 g     O .bss	00000004 system_state
40016440 g     F .vmlinux	000000f8 do_sys_sigstack
400a2094 g     F .vmlinux	00000018 sysfs_remove_file
4005ea04 g     F .vmlinux	0000003c sys_munlockall
40042ddc g     F .vmlinux	00000060 core_kernel_text
4006f120 g     F .vmlinux	0000061c do_coredump
400374b4 g     F .vmlinux	00000024 sysctl_head_finish
4012dfd0 g     O .vmlinux	00000004 lease_break_time
40010fc4 g       .vmlinux	00000000 sys_clone
400639a8 g     F .vmlinux	00000158 __vmalloc_area_node
40074eec g     F .vmlinux	00000090 generic_readlink
40131ff0 g     O .vmlinux	00000200 ctrl_map
400ba05c g     F .vmlinux	00000070 __bitmap_full
40113878 g     O .vmlinux	00000010 fragmentation_op
40307088 g     O .bss	00000004 total_forks
40139000 g       .vmlinux	00000000 _sinittext
400bbeb0 g     F .vmlinux	000000b8 idr_replace
40098474 g     F .vmlinux	0000000c task_vsize
40313d40 g     O .bss	00000004 inotify_max_user_instances
40134188 g       .vmlinux	00000000 ___fs_enable_irq
403179b4 g     O .bss	00000004 amba_is_init
400f0620 g     F .vmlinux	000000ac update_region
40016ccc g     F .vmlinux	00000058 dma_sync_sg_for_cpu
40132d88 g     O .vmlinux	00000064 cpu_sysdev_class
40319818 g     O .bss	00000004 last_console
40010b88 g       .vmlinux	00000000 invalid_segment_patch2_ff
40145fe8 g     F .vmlinux	00000444 srmmu_paging_init
40069150 g     F .vmlinux	00000130 sys_faccessat
4012fc7c g     O .vmlinux	00000134 random_table
400cd880 g     F .vmlinux	00000050 fb_pad_aligned_buffer
40011df0 g       .vmlinux	00000000 ret_trap_entry
40315958 g     O .bss	00000004 debug_locks_silent
400cabbc g     F .vmlinux	0000008c __pci_register_driver
4008fe58 g     F .vmlinux	0000004c sb_set_blocksize
4006b7b8 g     F .vmlinux	00000060 fget
4008d7ec g     F .vmlinux	00000240 block_truncate_page
40134e34 g       .vmlinux	00000000 ___fs_alloc_thread_info
4002ea54 g     F .vmlinux	00000100 __put_task_struct
4001c668 g     F .vmlinux	00000038 insb
400b67ac g     F .vmlinux	000003c4 sg_scsi_ioctl
40129948 g       .vmlinux	00000000 __stop___param
40134cfc g       .vmlinux	00000000 ___fs_sun4c_flush_page
4008b43c g     F .vmlinux	00000134 __set_page_dirty_buffers
400b3dfc g     F .vmlinux	00000054 blk_complete_request
400147c8 g     F .vmlinux	00000018 sparc_do_fork
4002d7a4 g     F .vmlinux	00000094 sched_fork
400cc790 g     F .vmlinux	00000138 pci_assign_resource
4000a000 g       .vmlinux	00000000 empty_bad_page
40086c04 g     F .vmlinux	000001a8 simple_fill_super
40302c60 g     O .bss	00000004 leon_debug_irqout
40076870 g     F .vmlinux	000000c4 sys_getdents
40313b44 g     O .bss	00000004 filp_cachep
4003a3c0 g     F .vmlinux	00000038 timekeeping_is_continuous
400aeb3c g     F .vmlinux	00000080 elv_rq_merge_ok
40134e4c g       .vmlinux	00000000 ___fs____xchg32
40045258 g     F .vmlinux	00000038 add_wait_queue_exclusive
40012f30 g     F .vmlinux	0000019c request_fast_irq
401321f0 g     O .vmlinux	00000200 altgr_map
4006da84 g     F .vmlinux	00000088 sys_fstatat64
401118bc g     F .vmlinux	00000094 sleep_on
400b241c g     F .vmlinux	00000034 blk_requeue_request
4002dc94 g     F .vmlinux	00000134 set_user_nice
40056f00 g     F .vmlinux	00000168 invalidate_mapping_pages
400c06c8 g     F .vmlinux	0000063c vsscanf
400c5bc0 g       .vmlinux	00000000 .urem_patch
403042ec g     O .bss	00000004 highstart_pfn
4002d0dc g     F .vmlinux	00000010 wake_up_state
400c6790 g     F .vmlinux	00000070 devm_ioremap
4015d2e4 g       .vmlinux	00000000 __initcall_end
40048bc0 g     F .vmlinux	0000006c free_nsproxy
4007e3c4 g     F .vmlinux	00000018 inode_wait
40048efc g     F .vmlinux	00000028 srcu_read_lock
4004a7a8 g     F .vmlinux	00000128 exit_pi_state_list
40048f24 g     F .vmlinux	00000018 srcu_read_unlock
400307cc g     F .vmlinux	000000c8 __set_personality
400b6bec g     F .vmlinux	00000530 scsi_cmd_ioctl
4006d190 g     F .vmlinux	00000048 unregister_chrdev
40016ca0 g     F .vmlinux	0000002c dma_sync_single_for_device
40115570 g     O .vmlinux	0000006c sysfs_file_operations
4003f3fc g     F .vmlinux	00000174 sys_setreuid
4012c3b8 g     O .vmlinux	00000004 flush_page_for_dma_global
40110340 g     F .vmlinux	00000074 hidinput_disconnect
4005c3bc g     F .vmlinux	0000014c vmtruncate
400bd520 g     F .vmlinux	00000098 radix_tree_preload
400a211c g     F .vmlinux	00000070 sysfs_schedule_callback
400457fc  w    F .vmlinux	00000008 sys_semget
40019cb8 g     F .vmlinux	00000040 do_sunos_syscall
4009c720 g     F .vmlinux	00000074 proc_mkdir_mode
40019bf4 g     F .vmlinux	00000084 syscall_trace
4003630c g     F .vmlinux	000000f0 _local_bh_enable
4006c6e0 g     F .vmlinux	00000164 get_sb_bdev
40054854 g     F .vmlinux	00000080 throttle_vm_writeout
400a5f84 g     F .vmlinux	00000290 ext2_find_entry
400bc1e0 g     F .vmlinux	00000074 kobject_init
4010615c g     F .vmlinux	00000048 ps2_cmd_aborted
400457fc  w    F .vmlinux	00000008 sys_swapoff
400a3da0 g     F .vmlinux	00000038 sysfs_create_bin_file
40085eb8 g     F .vmlinux	0000003c sys_flistxattr
40016818 g     F .vmlinux	00000090 iounmap
400f95f0 g     F .vmlinux	00000080 device_initialize
4013a6e8 g     F .vmlinux	00000064 mount_root
40033be0 g     F .vmlinux	00000018 sys_exit_group
40111950 g     F .vmlinux	00000094 sleep_on_timeout
40084280 g     F .vmlinux	000001b0 sys_io_cancel
400bca4c g     F .vmlinux	00000058 kref_get
400ffab4 g     F .vmlinux	0000006c devres_remove
40140790 g     F .vmlinux	000000e8 sun4d_init_sbi_irq
400483b4 g     F .vmlinux	00000050 hrtimer_init
4004b508 g     F .vmlinux	000000d0 sys_get_robust_list
40135498 g       .vmlinux	00000000 ___fs_pmd_set
40031f78 g     F .vmlinux	000000b8 __printk_ratelimit
40063d3c g     F .vmlinux	000000bc vwrite
400457fc  w    F .vmlinux	00000008 sys_set_mempolicy
4006dce0 g     F .vmlinux	000000f0 sys_uselib
40069280 g     F .vmlinux	0000001c sys_access
4013584c g       .vmlinux	00000000 ___f_pgprot_noncached
4007d9e4 g     F .vmlinux	0000009c d_genocide
4014e098 g     F .vmlinux	000001f8 proc_misc_init
401040bc g     F .vmlinux	00000018 serio_rescan
40014ba0 g     F .vmlinux	00000134 dump_fpu
4008adc0 g     F .vmlinux	00000050 end_buffer_read_sync
403041bc g     O .bss	00000004 vac_do_hw_vac_flushes
400bd2d0 g     F .vmlinux	000001cc prio_tree_next
40100488 g     F .vmlinux	00000028 attribute_container_add_class_device
40319814 g     O .bss	00000004 fg_console
4001f994 g     F .vmlinux	0000000c leon_flush_icache_all
400758b4 g     F .vmlinux	00000024 f_delown
400c47b0 g       .vmlinux	00000000 _Mul
400c85ac g     F .vmlinux	0000005c pci_bus_find_capability
400b443c g     F .vmlinux	00000048 end_request
40060c1c g     F .vmlinux	000000dc exit_mmap
400b59c8 g     F .vmlinux	00000054 add_disk
400cfdf4 g     F .vmlinux	00000118 fb_set_cmap
4009b4cc g     F .vmlinux	000001a4 proc_pid_readdir
400cd64c g     F .vmlinux	00000168 sys_pciconfig_write
400b03ac g     F .vmlinux	00000008 blk_queue_dma_alignment
400168cc g     F .vmlinux	0000002c dma_supported
4012d268 g     O .vmlinux	00000004 pid_max
40045e4c g     F .vmlinux	00000110 posix_cpu_timer_create
40111828 g     F .vmlinux	00000094 interruptible_sleep_on_timeout
40106a38 g     F .vmlinux	00000034 leon3ps2_clr_input
4012e054 g     O .vmlinux	00000010 mounts_op
40043380 g     F .vmlinux	00000044 param_set_uint
40147d10 g     F .vmlinux	00000a50 sun4c_paging_init
4007d208 g     F .vmlinux	000000cc d_splice_alias
4006a8d8 g     F .vmlinux	00000064 sys_read
40012294 g     F .vmlinux	0000012c die_if_kernel
40306680 g     O .bss	00000004 nohz_cpu_mask
40068c08 g     F .vmlinux	000000a0 sys_fstatfs64
4012b2e4 g     O .vmlinux	00000004 pm_power_off
4003cd50 g     F .vmlinux	00000024 kill_pgrp
400b2cbc g     F .vmlinux	00000028 blk_end_sync_rq
40016ba4 g     F .vmlinux	00000024 dma_map_page
4003eecc g     F .vmlinux	00000024 kernel_power_off
400a9e00 g     F .vmlinux	00000010 ext2_write_inode
4014dcf8 g     F .vmlinux	0000008c bdev_cache_init
400457fc  w    F .vmlinux	00000008 sys_request_key
4003c474 g     F .vmlinux	00000040 send_sig_info
400fea44 g     F .vmlinux	000000e8 kobj_lookup
4030436c g     O .bss	00000004 srmmu_context_table
40115c08 g     O .vmlinux	00000054 ext2_fast_symlink_inode_operations
40011eb4 g       .vmlinux	00000000 rtrap_patch1
400452d4 g     F .vmlinux	00000060 prepare_to_wait
40069c7c g     F .vmlinux	0000002c fd_install
400c7064 g     F .vmlinux	00000120 crc32_be
4014d358 g     F .vmlinux	00000018 unnamed_dev_init
400c98e0 g     F .vmlinux	00000018 pci_request_regions
4001c644 g     F .vmlinux	00000018 pmc_leon_idle_fixup
4009d408 g     F .vmlinux	00000014 proc_tgid_stat
400c1668 g     F .vmlinux	00000034 prom_halt
4012c330 g     O .vmlinux	00000010 pmc_leon_fixup_ids
40082200 g     F .vmlinux	000000d0 sys_mount
40041d78 g     F .vmlinux	00000018 flush_scheduled_work
400457fc  w    F .vmlinux	00000008 sys_listen
4012c3b0 g     O .vmlinux	00000008 pgt_cache_water
4001bb18 g     F .vmlinux	00000020 of_register_driver
401357fc g       .vmlinux	00000000 ___fs_pgd_page_vaddr
400e0700 g     F .vmlinux	0000009c tty_check_change
400ec324 g     F .vmlinux	00000058 con_get_trans_new
40018e7c g       .vmlinux	00000000 sunosnop_low
4003e414 g     F .vmlinux	00000040 sys_signal
4013a2f8 g     F .vmlinux	000002dc mount_block_root
40038be4 g     F .vmlinux	00000038 proc_dointvec_ms_jiffies
40071038 g     F .vmlinux	00000124 permission
4001c750 g     F .vmlinux	00000038 outsb
40108a20 g     F .vmlinux	00000184 input_unregister_device
400c3ec4 g     F .vmlinux	00000000 memcpy
4005ac7c g     F .vmlinux	00000010 pud_clear_bad
400ff780 g     F .vmlinux	00000088 dmam_alloc_noncoherent
400fc568 g     F .vmlinux	000000fc driver_detach
400f1140 g     F .vmlinux	000000e0 vc_deallocate
40012518 g     F .vmlinux	00000074 do_memaccess_unaligned
40135640 g       .vmlinux	00000000 ___as_pte_mkoldi
4003ccb8 g     F .vmlinux	00000024 kill_proc
4005c140 g     F .vmlinux	0000027c unmap_mapping_range
400a4d10 g     F .vmlinux	000007ac ext2_new_block
400c7714 g     F .vmlinux	00000080 pci_user_read_config_dword
4002e258 g     F .vmlinux	00000020 sys_sched_setscheduler
40089614 g     F .vmlinux	0000011c generic_file_splice_write
40056d74 g     F .vmlinux	00000024 pagevec_lookup
4012ffdc g     O .vmlinux	00000004 pty_limit
401594a0 g     O .vmlinux	00000018 logo_linux_clut224
40010b98 g       .vmlinux	00000000 num_context_patch2_16
4006a6b8 g     F .vmlinux	000000e4 do_sync_write
40140cf0 g     F .vmlinux	00000068 sbus_arch_bus_ranges_init
40134dec g       .vmlinux	00000000 ___fs_get_pgd_fast
4005d1fc g     F .vmlinux	0000024c remap_pfn_range
4012d178 g     O .vmlinux	0000008c init_groups
4001a134 g     F .vmlinux	000000e4 kernel_mna_trap_fault
4001d1a0 g     F .vmlinux	0000009c sparc_lvl15_nmi
401108e0 g       .vmlinux	00000000 __sched_text_start
40071280 g     F .vmlinux	00000094 follow_up
400118d8 g       .vmlinux	00000000 fnwin_patch2
4008cce4 g     F .vmlinux	000003b8 nobh_prepare_write
40070ef0 g     F .vmlinux	00000148 generic_permission
4007fdb8 g     F .vmlinux	00000008 put_filesystem
40042694 g     F .vmlinux	00000010 free_pid_ns
400115b0 g       .vmlinux	00000000 spnwin_patch1
400f5aa0 g     F .vmlinux	00000034 vcs_scr_readw
40020ee8 g       .vmlinux	00000000 viking_flush_page_to_ram
40020c94 g       .vmlinux	00000000 hypersparc_flush_tlb_range
400ec0dc g     F .vmlinux	00000028 set_translate
40063910 g     F .vmlinux	00000028 vunmap
4007c974 g     F .vmlinux	00000054 d_instantiate_unique
40063b54 g     F .vmlinux	00000014 __vmalloc_area
40014cd4 g     F .vmlinux	00000084 sparc_execve
400541f4 g     F .vmlinux	00000174 setup_per_zone_pages_min
40086f78 g     F .vmlinux	000000a8 simple_transaction_get
400450a0 g     F .vmlinux	000000cc kthread_create
40313d68 g     O .bss	00000004 proc_root_driver
4007e6c4 g     F .vmlinux	00000074 iunique
4006663c g     F .vmlinux	000000c4 kfree
40057434 g     F .vmlinux	00000328 invalidate_inode_pages2_range
4006f09c g     F .vmlinux	00000010 set_binfmt
400b1a34 g     F .vmlinux	00000074 blk_remove_plug
4003cc3c g     F .vmlinux	00000040 kill_pid_info
4001adec g     F .vmlinux	00000018 of_get_parent
4003a0ac g     F .vmlinux	00000014 round_jiffies_relative
4008f800 g     F .vmlinux	0000005c bio_release_pages
40060db4 g     F .vmlinux	00000144 copy_vma
400c7694 g     F .vmlinux	00000080 pci_user_read_config_word
4007943c g     F .vmlinux	0000001c posix_lock_file
400500c4 g     F .vmlinux	000001e4 read_cache_page
4001cbe0 g     F .vmlinux	00000114 pcibios_enable_device
4001c00c g     F .vmlinux	0000010c gptimer_sync
40017834 g     F .vmlinux	00000040 sun_do_break
40111c04 g     F .vmlinux	0000001c schedule_timeout_interruptible
4012dcfc g     O .vmlinux	00000004 randomize_va_space
4001be98 g     F .vmlinux	00000174 gptimer_get_nexttimer
40018840 g     F .vmlinux	00000074 leon23_wait_for
400bc040 g     F .vmlinux	000000b4 kobject_get_path
400b9fec g     F .vmlinux	00000070 __bitmap_empty
400a804c g     F .vmlinux	00000078 ext2_count_dirs
400bca38 g     F .vmlinux	00000014 kref_init
40063b68 g     F .vmlinux	00000014 __vmalloc
40086398 g     F .vmlinux	00000014 dcache_dir_close
40013250 g     F .vmlinux	00000008 probe_irq_on
40048b88 g     F .vmlinux	0000001c register_latency_notifier
40020eb4 g       .vmlinux	00000000 viking_flush_tlb_page
4009f93c g     F .vmlinux	0000007c delete_partition
4005c6d0 g     F .vmlinux	00000058 __pmd_alloc
40031f30 g     F .vmlinux	00000048 tty_write_message
4014b440 g     F .vmlinux	0000038c __alloc_bootmem_core
40031448 g     F .vmlinux	0000000c is_console_locked
4007e04c g     F .vmlinux	000000ac iput
40011b18 g       .vmlinux	00000000 tsetup_7win_patch2
4012fea4 g     O .vmlinux	00000008 tty_drivers
400b0c98 g     F .vmlinux	000000c8 blk_queue_init_tags
400c1b08 g     F .vmlinux	00000040 __prom_getchild
40014eec g     F .vmlinux	00000010 sys_sigsuspend
400bc884 g     F .vmlinux	00000028 kset_unregister
4012ae58 g     O .vmlinux	00000004 loops_per_jiffy
40093f5c g     F .vmlinux	00000018 get_inotify_watch
400f308c g     F .vmlinux	00000104 poke_blanked_console
400a9e10 g     F .vmlinux	00000040 ext2_sync_inode
400baa9c g     F .vmlinux	00000098 bitmap_bitremap
40300040 g     O .bss	00000004 saved_command_line
40010b9c g       .vmlinux	00000000 vac_linesize_patch_32
4012dcb0 g     O .vmlinux	0000001c default_backing_dev_info
40084b80 g     F .vmlinux	0000029c seq_lseek
40017324 g     F .vmlinux	00000024 pci_map_page
40068f24 g     F .vmlinux	00000020 sys_truncate
400dc6d4 g     F .vmlinux	000000b8 amba_init
4001414c g     F .vmlinux	00000008 leon_clear_clock_irq
4007b038 g     F .vmlinux	00000034 posix_unblock_lock
40011518 g       .vmlinux	00000000 kuw_patch1_7win
4008af1c g     F .vmlinux	00000098 freeze_bdev
4001ce18 g     F .vmlinux	0000001c apc_swift_idle
40303010 g     O .bss	00000004 sp_clock_typ
40045220 g     F .vmlinux	00000038 add_wait_queue
400e6cf8 g     F .vmlinux	00000060 tty_termios_baud_rate
4003e3c8 g     F .vmlinux	0000000c sys_sgetmask
40016fbc g     F .vmlinux	00000020 sbus_unmap_single
40050098 g     F .vmlinux	0000002c generic_file_readonly_mmap
40111a30 g     F .vmlinux	00000070 cond_resched_softirq
4005f950 g     F .vmlinux	00000180 arch_get_unmapped_area_topdown
4012c478 g     O .vmlinux	00000004 printk_ratelimit_burst
4007146c g     F .vmlinux	0000007c follow_down
4006abdc g     F .vmlinux	00000070 do_loop_readv_writev
4008636c g     F .vmlinux	0000002c dcache_dir_open
400114a0 g       .vmlinux	00000000 breakpoint_trap
4003aeb8 g     F .vmlinux	0000000c sys_gettid
40304370 g     O .bss	00000004 viking_mxcc_present
40042578 g     F .vmlinux	0000002c find_get_pid
40075e4c g     F .vmlinux	000000c8 send_sigurg
400c9a68 g     F .vmlinux	00000050 pci_clear_mwi
40103c6c g     F .vmlinux	000000b4 __serio_register_port
401354dc g       .vmlinux	00000000 ___as_pte_writei
40052010 g     F .vmlinux	00000018 mempool_kmalloc
40307098 g     O .bss	00000004 max_threads
4011a0b0 g     O .vmlinux	0000006c bad_sock_fops
400edbf8 g     F .vmlinux	0000011c compute_shiftstate
4004e0a0 g     F .vmlinux	00000070 __filemap_copy_from_user_iovec_inatomic
400aa524 g     F .vmlinux	00000284 ext2_ioctl
40313d24 g     O .bss	00000004 blockdev_superblock
401040d4 g     F .vmlinux	00000018 serio_reconnect
4001aea0 g     F .vmlinux	00000068 of_find_node_by_name
4005f864 g     F .vmlinux	00000098 get_unmapped_area
400c2884 g     F .vmlinux	00000034 bit_map_init
40113fb0 g     O .vmlinux	0000006c def_fifo_fops
400c72ec g     F .vmlinux	00000030 __atomic_add_return
4001f2d8 g     F .vmlinux	00000018 srmmu_alloc_thread_info
400942d0 g     F .vmlinux	000000c8 inotify_inode_queue_event
40065d00 g     F .vmlinux	00000098 shmem_lock
40103550 g     F .vmlinux	00000030 unregister_mtd_chip_driver
400c7498 g     F .vmlinux	00000048 pci_bus_write_config_byte
400457fc  w    F .vmlinux	00000008 sys_epoll_create
401340f0 g       .vmlinux	00000000 ___fs_disable_pil_irq
40102fc0 g     F .vmlinux	000000b8 del_mtd_device
40302c5c g     O .bss	00000004 leondebug_irq_disable
400b9ce8 g     F .vmlinux	0000004c __bitmap_and
400fc914 g     F .vmlinux	00000028 get_driver
400188b4 g     F .vmlinux	00000118 do_gettimeofday
4001d06c g     F .vmlinux	0000001c pmc_swift_idle
400b4484 g     F .vmlinux	0000001c kblockd_schedule_work
400fa060 g     F .vmlinux	0000005c device_for_each_child
400b0bdc g     F .vmlinux	00000018 blk_init_tags
4013584c g       .vmlinux	00000000 ___f____xchg32
40012990 g     F .vmlinux	00000040 handle_cp_exception
40056278 g     F .vmlinux	00000018 handle_ra_miss
40080258 g     F .vmlinux	00000038 lookup_mnt
4000049c g     F .stage2	00000040 leon3_amba_init
4003ff10 g     F .vmlinux	000000f8 groups_alloc
400fb57c g     F .vmlinux	00000088 bus_for_each_drv
4008fd3c g     F .vmlinux	00000008 I_BDEV
401350d0 g       .vmlinux	00000000 ___fs_flush_tlb_page
4009839c g     F .vmlinux	000000d8 task_mem
400c5264 g       .vmlinux	00000000 .udiv
4008efa4 g     F .vmlinux	000000fc bio_uncopy_user
401007e8 g     F .vmlinux	00000018 attribute_container_class_device_del
400636f0 g     F .vmlinux	00000018 __get_vm_area
40130ce8 g     O .vmlinux	00000040 default_blu
4005d6dc g     F .vmlinux	0000024c zeromap_page_range
40315988 g     O .bss	00000004 pci_pci_problems
00000000 g       *ABS*	00000000 ___s_pgdir_shift
4003a014 g     F .vmlinux	0000005c __round_jiffies
4004c7e4 g     F .vmlinux	00000064 rt_mutex_adjust_pi
400fa71c g     F .vmlinux	00000014 sysdev_create_file
40111d20 g     F .vmlinux	0000007c out_of_line_wait_on_bit
400f8f0c g     F .vmlinux	00000088 suncore_mouse_baud_cflag_next
4013fc9c g     F .vmlinux	00000190 calibrate_delay
4001af08 g     F .vmlinux	00000068 of_find_node_by_type
40018ae0 g     F .vmlinux	0000002c flush_user_windows
4001c118 g     F .vmlinux	00000064 gptimer_setstate
4007cc64 g     F .vmlinux	000000a4 d_hash_and_lookup
400d0234 g     F .vmlinux	00000058 framebuffer_alloc
40034c78 g     F .vmlinux	0000008c sys_waitid
4006752c g     F .vmlinux	0000007c kmem_cache_zalloc
40043638 g     F .vmlinux	00000044 param_get_invbool
40044108 g     F .vmlinux	00000104 do_schedule_next_timer
400457fc  w    F .vmlinux	00000008 sys_recvmsg
4002113c g       .vmlinux	00000000 swift_flush_tlb_mm
400b4c9c g     F .vmlinux	00000048 blk_unregister_queue
40048b64 g     F .vmlinux	00000024 synchronize_acceptable_latency
4012e064 g     O .vmlinux	0000005c fs_subsys
4030e054 g     O .bss	00000004 max_low_pfn
40056ca8 g     F .vmlinux	00000028 __pagevec_release
400ae6b8 g     F .vmlinux	000000a4 cap_inode_setxattr
4012d24c g     O .vmlinux	00000014 init_pid_ns
40044f20 g     F .vmlinux	0000001c kthread_should_stop
400c6ad4 g     F .vmlinux	00000078 pcim_iounmap
4003e920 g     F .vmlinux	00000038 srcu_init_notifier_head
40020f44 g       .vmlinux	00000000 tsunami_flush_tlb_mm
40008000 g       .vmlinux	00000000 pg2
400457fc  w    F .vmlinux	00000008 compat_sys_mq_timedsend
400b1b58 g     F .vmlinux	0000001c blk_stop_queue
400c8904 g     F .vmlinux	00000260 pci_set_power_state
400b17b8 g     F .vmlinux	000001f8 ll_back_merge_fn
4004e7ac g     F .vmlinux	000000c8 sync_page_range_nolock
400def14 g     F .vmlinux	00000044 add_interrupt_randomness
400533e8 g     F .vmlinux	000000c0 zone_watermark_ok
400898bc g     F .vmlinux	00000194 do_splice_direct
4007cc20 g     F .vmlinux	00000044 d_lookup
403004b0 g     O .bss	00000004 real_root_dev
40074c5c g     F .vmlinux	000001e0 sys_renameat
4002dac0 g     F .vmlinux	00000034 __wake_up
4001ccf4 g     F .vmlinux	00000058 pcibios_set_master
40048f3c g     F .vmlinux	00000088 synchronize_srcu
4002df04 g     F .vmlinux	000002b4 sched_setscheduler
401344d8 g       .vmlinux	00000000 ___fs_pmd_offset
4001159c g       .vmlinux	00000000 spnwin_patch2_7win
40053bfc g     F .vmlinux	0000003c free_pages
40013eac g     F .vmlinux	00000018 sparc_leon_eirq_isr
40113858 g     O .vmlinux	00000010 vmstat_op
400c466c g       .vmlinux	00000000 __bzero
40313664 g     O .bss	00000004 vmlist
40049d4c g     F .vmlinux	00000064 clocksource_change_rating
4003ee70 g     F .vmlinux	00000038 kernel_shutdown_prepare
40012ac4 g     F .vmlinux	00000124 show_interrupts
40146434 g     F .vmlinux	00000dac ld_mmu_srmmu
40047c60 g     F .vmlinux	00000070 ktime_get_ts
400df4f4 g     F .vmlinux	00000038 rand_initialize_disk
4003ae84 g     F .vmlinux	0000000c sys_geteuid
40070c1c g     F .vmlinux	0000003c free_write_pipe
4003612c g     F .vmlinux	00000044 jiffies_64_to_clock_t
400115a4 g       .vmlinux	00000000 spill_window_entry
400c1758 g     F .vmlinux	0000006c prom_write
4012d3fc g     O .vmlinux	00000004 time_maxerror
400434ac g     F .vmlinux	00000060 param_set_charp
400e0894 g     F .vmlinux	00000014 tty_hangup
40060890 g     F .vmlinux	00000040 sys_munmap
400457fc  w    F .vmlinux	00000008 compat_sys_keyctl
400bff70 g     F .vmlinux	00000668 vsnprintf
4008ab74 g     F .vmlinux	00000078 fsstack_copy_attr_all
400c900c g     F .vmlinux	00000024 __pci_reenable_device
4001c6ec g     F .vmlinux	00000064 insl
400172d8 g     F .vmlinux	00000020 pci_map_single
4014a6b8 g     F .vmlinux	00000150 pidhash_init
4003ccdc g     F .vmlinux	00000064 __kill_pgrp_info
4003a000 g     F .vmlinux	00000014 init_timer
40093ac4 g     F .vmlinux	00000224 sys_ioprio_set
400af744 g     F .vmlinux	0000007c elv_requeue_request
401108e0 g     F .vmlinux	000000dc __down
4001d088 g     F .vmlinux	00000108 prom_probe_memory
f0135854 g       *ABS*	00000000 edata
40023038 g     F .vmlinux	000001f0 sun4c_update_mmu_cache
400bbb50 g     F .vmlinux	00000044 idr_get_new_above
400fde2c g     F .vmlinux	0000006c platform_get_resource_byname
4004520c g     F .vmlinux	00000014 init_waitqueue_head
400cc604 g     F .vmlinux	0000003c pci_cleanup_rom
4007fe10 g     F .vmlinux	0000004c register_filesystem
40134a58 g       .vmlinux	00000000 ___fs_flush_tlb_range
4004cb00 g     F .vmlinux	00000058 sys_lchown16
40036170 g     F .vmlinux	00000050 nsec_to_clock_t
400e4268 g     F .vmlinux	00000118 tty_unregister_driver
4013fe50 g     F .vmlinux	00000084 init_IRQ
4003c554 g     F .vmlinux	00000070 sigqueue_free
40042718 g     F .vmlinux	00000074 call_rcu_bh
40067c54 g     F .vmlinux	00000554 kmem_cache_create
400b3cc4 g     F .vmlinux	00000010 end_that_request_chunk
4012dc68 g     O .vmlinux	00000004 dirty_writeback_interval
400f93d8 g     F .vmlinux	00000028 get_device
400c25a4 g       .vmlinux	00000000 __atomic_end
400ceb0c g     F .vmlinux	00000208 fb_set_var
00000000 g       *ABS*	00000000 ___s_ptrs_per_pgd
4007427c g     F .vmlinux	000000bc vfs_unlink
401340b8 g       .vmlinux	00000000 ___btfixup_start
40086530 g     F .vmlinux	000001f8 dcache_readdir
00000000 g       *ABS*	00000000 ___a_pte_youngi
400a54bc g     F .vmlinux	00000078 ext2_count_free_blocks
4014e290 g     F .vmlinux	000000a8 sysfs_init
400c6e9c g     F .vmlinux	0000004c bitrev32
4013584c g       .vmlinux	00000000 ___f_mmu_unmap_dma_area
4001dae8 g     F .vmlinux	00000244 window_overflow_fault
400be2ac g     F .vmlinux	00000164 rb_insert_color
400bda0c g     F .vmlinux	00000158 radix_tree_tag_clear
400165f0 g     F .vmlinux	0000004c _sparc_find_resource
40018e64 g     F .vmlinux	00000018 cpu_get_hwmid
4006af70 g     F .vmlinux	0000006c vfs_writev
400d1408 g     F .vmlinux	000000b4 fb_find_best_mode
401500c8 g     F .vmlinux	00000020 pci_do_scan_bus
40135008 g       .vmlinux	00000000 ___fs___swp_type
400e1ce0 g     F .vmlinux	0000002c proc_set_tty
40103280 g     F .vmlinux	000000b4 get_mtd_device_nm
4013584c g       .vmlinux	00000000 ___f_flush_cache_mm
400b0158 g     F .vmlinux	000000b8 elv_iosched_show
400457fc  w    F .vmlinux	00000008 sys_mq_timedsend
40304368 g     O .bss	00000004 srmmu_ctx_table_phys
40135468 g       .vmlinux	00000000 ___fs_pte_alloc_one_kernel
40086904 g     F .vmlinux	00000054 simple_empty
40055a44 g     F .vmlinux	0000010c read_cache_pages
40045b1c g     F .vmlinux	0000003c posix_cpu_clock_getres
40113000 g     O .vmlinux	0000003f linux_proc_banner
40013268 g     F .vmlinux	00000040 sun4m_sbint_to_irq
40134eec g       .vmlinux	00000000 ___fs_pte_present
40044a4c g     F .vmlinux	00000008 do_posix_clock_nonanosleep
4002decc g     F .vmlinux	00000024 idle_cpu
40010ed8 g       .vmlinux	00000000 sys_sigaltstack
4004caa8 g     F .vmlinux	00000058 sys_chown16
40011638 g       .vmlinux	00000000 spwin_mmu_patchme
400f5400 g     F .vmlinux	0000002c con_set_cmap
400457fc  w    F .vmlinux	00000008 compat_sys_sysctl
400435ec g     F .vmlinux	0000004c param_set_invbool
400621c0 g     F .vmlinux	00000068 anon_vma_unlink
40051f50 g     F .vmlinux	00000088 mempool_free
400949c0 g     F .vmlinux	000000a8 inotify_rm_wd
40014154 g     F .vmlinux	00000004 leon_clear_profile_irq
40302c50 g     O .bss	00000004 sbus_actions
401353e0 g       .vmlinux	00000000 ___fs_pmd_clear
40062078 g     F .vmlinux	000000b0 anon_vma_prepare
400e0458 g     F .vmlinux	00000068 tty_ldisc_get
4012e300 g     O .vmlinux	00000058 proc_root
40157c8c g     O .vmlinux	00000004 rd_doload
400c4c60 g       .vmlinux	00000000 .div
4003d4e8 g     F .vmlinux	00000008 do_no_restart_syscall
4006b8fc g     F .vmlinux	00000038 file_move
4004348c g     F .vmlinux	00000020 param_get_ulong
40080bfc g     F .vmlinux	00000148 umount_tree
400aeaa4 g     F .vmlinux	0000005c elv_dequeue_request
400ff978 g     F .vmlinux	00000028 devres_add
4003f888 g     F .vmlinux	0000014c sys_setresgid
4002d49c g     F .vmlinux	00000014 nr_iowait
40155374 g     F .vmlinux	00000048 driver_init
40068ad0 g     F .vmlinux	000000a8 sys_statfs64
40014304 g     F .vmlinux	000000c8 machine_restart
4006b818 g     F .vmlinux	00000098 fget_light
400c2508 g       .vmlinux	00000000 ___xchg32_sun4md
4004884c g     F .vmlinux	00000014 down_read_trylock
4003b0e8 g     F .vmlinux	0000004c msleep_interruptible
40110644 g     F .vmlinux	00000258 sha_transform
400c8140 g     F .vmlinux	000000a0 pci_cfg_space_size
4003dc38 g     F .vmlinux	00000138 sys_kill
4008c268 g     F .vmlinux	00000174 submit_bh
40048654 g     F .vmlinux	00000158 hrtimer_nanosleep
4003ae9c g     F .vmlinux	0000000c sys_getegid
40016d7c g     F .vmlinux	00000008 dma_mapping_error
400c1bbc g     F .vmlinux	00000034 prom_getsibling
40040d50 g     F .vmlinux	00000134 sys_getcpu
400cac48 g     F .vmlinux	00000018 pci_unregister_driver
4007f234 g     F .vmlinux	00000190 inode_change_ok
40010ba8 g       .vmlinux	00000000 sun4c_fault
40014504 g     F .vmlinux	00000118 show_regs
4003e800 g     F .vmlinux	00000010 raw_notifier_chain_register
40035f94 g     F .vmlinux	0000008c timeval_to_jiffies
40054e68 g     F .vmlinux	000000e4 clear_page_dirty_for_io
40081384 g     F .vmlinux	00000120 do_add_mount
400ab250 g     F .vmlinux	00000084 ext2_update_dynamic_rev
4003725c g     F .vmlinux	000000c0 __release_region
4002f168 g     F .vmlinux	0000005c unshare_files
4001afc8 g     F .vmlinux	0000002c of_get_property
4003e714 g     F .vmlinux	00000054 blocking_notifier_chain_register
40313d58 g     O .bss	00000004 proc_root_fs
4001a4dc g     F .vmlinux	0000004c user_mna_trap_fault
4003bb38 g     F .vmlinux	00000038 signal_wake_up
4014c4e8 g     F .vmlinux	00000030 free_area_init
40131bf0 g     O .vmlinux	00000200 alt_map
40105fc4 g     F .vmlinux	00000030 ps2_init
4006dc90 g     F .vmlinux	00000050 unregister_binfmt
40304338 g     O .bss	00000010 ctx_used
401104e4 g     F .vmlinux	0000003c klist_del
4030d7d4 g     O .bss	00000004 tick_nsec
40305e10 g     O .bss	00000800 sun4c_bucket
40134c34 g       .vmlinux	00000000 ___fs_mk_pte
400fa278 g     F .vmlinux	00000160 device_rename
40043860 g     F .vmlinux	00000074 param_set_copystring
40103190 g     F .vmlinux	000000f0 get_mtd_device
400ecaec g     F .vmlinux	00000060 con_copy_unimap
400fdfbc g     F .vmlinux	00000040 platform_device_add_data
4003ec08 g     F .vmlinux	000001f0 sys_getpriority
4001f9a0 g     F .vmlinux	0000000c leon_flush_dcache_all
4003b704 g     F .vmlinux	00000034 block_all_signals
4007c494 g     F .vmlinux	00000124 shrink_dcache_parent
40132c48 g     O .vmlinux	00000140 platform_bus
40069c60 g     F .vmlinux	0000001c put_unused_fd
40082a2c g     F .vmlinux	000000bc __put_ioctx
40011048 g       .vmlinux	00000000 flush_patch_four
40018320 g     F .vmlinux	000000f8 sys_rt_sigaction
40017f54 g     F .vmlinux	00000010 sparc_remap_file_pages
4010069c g     F .vmlinux	0000014c attribute_container_remove_device
400cf804 g     F .vmlinux	00000008 fb_destroy_modedb
400f955c g     F .vmlinux	0000002c device_create_bin_file
403008e0 g     O .bss	00000004 trap_curbuf
4007bc68 g     F .vmlinux	000000d8 d_prune_aliases
40108ea0 g     F .vmlinux	0000030c input_ff_upload
40082ae8 g     F .vmlinux	000000b8 exit_aio
4031ab18 g     O .bss	00000004 funcbufleft
4008cbb8 g     F .vmlinux	00000040 alloc_buffer_head
4013584c g       .vmlinux	00000000 ___f_pte_read
400e09b0 g     F .vmlinux	0000008c stop_tty
4002d0c8 g     F .vmlinux	00000014 wake_up_process
40041e54 g     F .vmlinux	00000034 current_is_keventd
400fd718 g     F .vmlinux	00000018 class_device_register
40318114 g     O .bss	00000004 leon_ports_nr
400cae70 g     F .vmlinux	0000009c pci_find_next_bus
40134298 g       .vmlinux	00000000 ___fs_mmu_release_scsi_one
400ff000 g     F .vmlinux	0000029c dma_pool_alloc
400a1e00 g     F .vmlinux	00000038 sysfs_create_file
40037598 g     F .vmlinux	00000228 do_sysctl_strategy
400abbc8 g     F .vmlinux	00000104 ext2_error
40073e78 g     F .vmlinux	000000b0 vfs_mkdir
400b14e0 g     F .vmlinux	00000170 blk_rq_map_sg
403042f8 g     O .bss	00000004 kmap_prot
400e0204 g     F .vmlinux	00000078 tty_insert_flip_string
4012c340 g     O .vmlinux	0000004c pcic0
4008bc54 g     F .vmlinux	00000080 unmap_underlying_metadata
400359f4 g     F .vmlinux	00000024 jiffies_to_usecs
40032948 g     F .vmlinux	00000094 __set_special_pids
40130d68 g     O .vmlinux	00000040 default_red
4014cfcc g     F .vmlinux	00000334 kmem_cache_init
40010e80 g       .vmlinux	00000000 sys_nis_syscall
400f9020 g     F .vmlinux	00000038 dev_driver_string
40017f40 g     F .vmlinux	00000014 sys_mmap
4007e9dc g     F .vmlinux	00000018 wake_up_inode
400ec77c g     F .vmlinux	00000214 con_set_unimap
4002d468 g     F .vmlinux	00000020 nr_uninterruptible
4001855c g     F .vmlinux	00000094 profile_pc
401103bc g     F .vmlinux	0000001c klist_init
400fe7d4 g     F .vmlinux	00000020 get_cpu_sysdev
4003cd40 g     F .vmlinux	00000010 kill_pgrp_info
4002d4b0 g     F .vmlinux	00000028 nr_active
4030e138 g     O .bss	0000007c per_cpu__vm_event_states
400b9e78 g     F .vmlinux	0000007c __bitmap_equal
4009462c g     F .vmlinux	00000080 inotify_init
40147638 g     F .vmlinux	0000011c iounit_init
400129d0 g     F .vmlinux	00000040 handle_hw_divzero
4013518c g       .vmlinux	00000000 ___hs_none_mask
4030708c g     O .bss	00000004 nr_threads
40063c18 g     F .vmlinux	0000001c vmalloc_32
400c8784 g     F .vmlinux	00000014 pci_find_next_ht_capability
400ff488 g     F .vmlinux	0000006c dmam_pool_destroy
40011f78 g       .vmlinux	00000000 rtrap_patch5
4013584c g       .vmlinux	00000000 ___f_sparc_unmapiorange
40059394 g     F .vmlinux	000000f4 vma_prio_tree_remove
40318ff8 g     O .bss	00000004 ptm_driver
40017020 g     F .vmlinux	00000008 sbus_dma_sync_single_for_device
4013584c g       .vmlinux	00000000 ___f_sun4c_flush_segment
400cf7fc g     F .vmlinux	00000008 fb_edid_to_monspecs
4001b084 g     F .vmlinux	0000008c of_find_compatible_node
4009c59c g     F .vmlinux	000000ec create_proc_entry
40054368 g     F .vmlinux	00000034 min_free_kbytes_sysctl_handler
400f59ac g     F .vmlinux	00000068 screen_glyph
40130cd8 g     O .vmlinux	00000010 con_buf_sem
40068834 g     F .vmlinux	0000007c vfs_statfs
400bbfdc g     F .vmlinux	00000064 int_sqrt
4005066c g     F .vmlinux	00000800 generic_file_buffered_write
400eccdc g     F .vmlinux	00000058 sel_loadlut
40011b24 g       .vmlinux	00000000 tsetup_7win_patch5
4006ab0c g     F .vmlinux	000000d0 do_sync_readv_writev
4001cd4c g     F .vmlinux	00000008 pcibios_assign_resource
4006d514 g     F .vmlinux	0000003c vfs_fstat
40157e50 g     O .vmlinux	00000004 cmdline_memory_size
4006aac0 g     F .vmlinux	0000004c iov_shorten
40011130 g       .vmlinux	00000000 syscall_is_too_hard
40052040 g     F .vmlinux	00000010 mempool_kfree
4006d248 g     F .vmlinux	000000f0 register_chrdev
4002c9f4  w    F .vmlinux	0000008c sched_clock
400a34d8 g     F .vmlinux	00000010 sysfs_remove_shadow_dir
4013584c g       .vmlinux	00000000 ___f_pgd_page_vaddr
40017f64 g     F .vmlinux	000001e0 sparc_mremap
40080af0 g     F .vmlinux	00000048 may_umount_tree
403159b0 g     O .bss	00000080 registered_fb
40011b20 g       .vmlinux	00000000 tsetup_7win_patch4
40303044 g     O .bss	00000004 cpu_pwr_save
4013584c g       .vmlinux	00000000 ___f_pgd_bad
40031370 g     F .vmlinux	00000088 acquire_console_sem
4012dc54 g     O .vmlinux	00000008 sysctl_lowmem_reserve_ratio
40100a7c g     F .vmlinux	00000018 transport_setup_device
4005695c g     F .vmlinux	00000108 __pagevec_lru_add_active
4004f4bc g     F .vmlinux	000001b8 file_read_actor
4006dbcc g     F .vmlinux	00000030 inode_get_bytes
403143f4 g     O .bss	00000004 sun4_romvec
40111638 g     F .vmlinux	0000015c wait_for_completion_interruptible_timeout
4014a2fc g     F .vmlinux	00000140 timekeeping_init
400a1c8c g     F .vmlinux	000000f8 sysfs_notify
400fceec g     F .vmlinux	00000028 class_device_remove_bin_file
4003c4d0 g     F .vmlinux	00000018 force_sig
400eec38 g     F .vmlinux	0000000c getledstate
4003c520 g     F .vmlinux	00000034 sigqueue_alloc
4004d2f8 g     F .vmlinux	0000002c sys_getegid16
4006dbfc g     F .vmlinux	0000001c inode_set_bytes
40313d98 g     O .bss	00000004 sysfs_sb
400c18cc g     F .vmlinux	00000120 prom_adjust_ranges
400ae5c8 g     F .vmlinux	0000004c cap_syslog
4013584c g       .vmlinux	00000000 ___f_pgd_set
4013584c g       .vmlinux	00000000 ___f_mmu_unlockarea
4010876c g     F .vmlinux	0000004c input_free_device
401346d8 g       .vmlinux	00000000 ___hs_pgdir_mask
403070a8 g     O .bss	00000004 panic_notifier_list
4003f144 g     F .vmlinux	00000138 sys_setregid
4030e1f0 g     O .bss	00000004 totalhigh_pages
4004d274 g     F .vmlinux	0000002c sys_getuid16
401342e0 g       .vmlinux	00000000 ___fs_mmu_info
400b1c84 g     F .vmlinux	0000013c blk_init_queue_node
400314a0 g     F .vmlinux	0000024c release_console_sem
40069108 g     F .vmlinux	00000024 sys_ftruncate
40135078 g       .vmlinux	00000000 ___fs_flush_cache_page
4006bf4c g     F .vmlinux	00000018 drop_super
40132830 g     O .vmlinux	0000005c devices_subsys
4012b3a4 g     O .vmlinux	00000080 Sun_Machines
400ae8ac g     F .vmlinux	0000001c cap_settime
40063708 g     F .vmlinux	00000018 get_vm_area
40020f74 g       .vmlinux	00000000 tsunami_flush_tlb_page
40151a90 g     F .vmlinux	000000e8 pci_claim_resource
4014a688 g     F .vmlinux	00000030 usermodehelper_init
40036578 g     F .vmlinux	000000c8 local_bh_enable
400ba6d8 g     F .vmlinux	00000040 bitmap_parse_user
4005f7f0 g     F .vmlinux	00000074 vm_stat_account
4012ec84 g     O .vmlinux	0000005c block_subsys
400106d4 g       .vmlinux	00000000 real_irq_entry
4014983c g     F .vmlinux	00000100 proc_caches_init
4003737c g     F .vmlinux	00000080 __devm_request_region
400c16bc g     F .vmlinux	00000074 prom_get_idprom
40134b64 g       .vmlinux	00000000 ___fs_flush_cache_mm
400524fc g     F .vmlinux	0000001c register_oom_notifier
400117b4 g       .vmlinux	00000000 spwin_sun4c_stackchk
400147e0 g     F .vmlinux	00000234 copy_thread
400481b0 g     F .vmlinux	000000f4 hrtimer_start
40109234 g     F .vmlinux	00000050 input_ff_erase
4000c000 g       .vmlinux	00000000 empty_zero_page
400457fc  w    F .vmlinux	00000008 sys_semctl
40014684 g     F .vmlinux	00000018 dump_stack
4031428c g     O .bss	00000020 per_cpu__radix_tree_preloads
40135140 g       .vmlinux	00000000 ___as_pte_dirtyi
40319134 g     O .bss	00000008 vt_spawn_con
4012972c g       .vmlinux	00000000 __start___ksymtab_unused_gpl
400695a8 g     F .vmlinux	00000020 sys_chmod
400410d0 g     F .vmlinux	000000cc call_usermodehelper_keys
4004045c g     F .vmlinux	0000002c in_group_p
4006c844 g     F .vmlinux	00000024 kill_block_super
4006ba2c g     F .vmlinux	00000064 deactivate_super
400c3e3c g     F .vmlinux	00000000 __memmove
40018418 g     F .vmlinux	000000bc sys_getdomainname
4007f0a8 g     F .vmlinux	0000001c unlock_new_inode
4002dbdc g     F .vmlinux	000000b8 rt_mutex_setprio
400908f8 g     F .vmlinux	000000f8 bd_release_from_disk
4004dacc g     F .vmlinux	0000003c acct_auto_close_mnt
40042e58 g     F .vmlinux	0000001c kernel_text_address
400822d0 g     F .vmlinux	00000088 set_fs_root
401354b0 g       .vmlinux	00000000 ___as_pte_youngi
4002de10 g     F .vmlinux	000000ac sys_nice
400b057c g     F .vmlinux	00000070 blk_ordered_req_seq
400bae28 g     F .vmlinux	00000014 bitmap_release_region
40018e3c g     F .vmlinux	00000028 cpu_find_by_mid
4006a498 g     F .vmlinux	000000e4 do_sync_read
400cf80c g     F .vmlinux	00000008 fb_get_mode
4008fc50 g     F .vmlinux	000000ec bioset_create
4031360c g     O .bss	00000004 high_memory
40051c8c g     F .vmlinux	00000014 mempool_create
40076ce8 g     F .vmlinux	0000045c do_select
4004060c g     F .vmlinux	000000b0 sys_gethostname
4014506c g     F .vmlinux	00000198 srmmu_allocate_ptable_skeleton
40315980 g     O .bss	00000004 platform_pci_choose_state
4012972c g       .vmlinux	00000000 __end_pci_fixups_resume
4008e774 g     F .vmlinux	0000005c __breadahead
400aed58 g     F .vmlinux	000000fc elevator_init
4013d01c g     F .vmlinux	000000cc rd_load_disk
40047e1c g     F .vmlinux	000000b8 ktime_divns
400b6218 g     F .vmlinux	00000028 put_disk
40036528 g     F .vmlinux	00000050 local_bh_enable_ip
40041280 g     F .vmlinux	00000128 run_scheduled_work
400d1788 g     F .vmlinux	00000048 fb_videomode_to_modelist
403143ec g     O .bss	00000004 prom_stdout
400431b8 g     F .vmlinux	00000054 param_set_byte
4012972c g       .vmlinux	00000000 __start___ksymtab_gpl_future
40093a14 g     F .vmlinux	0000004c mpage_writepage
4003b510 g     F .vmlinux	00000014 recalc_sigpending
4001d2f4 g     F .vmlinux	000000c8 lookup_fault
4010352c g     F .vmlinux	00000024 register_mtd_chip_driver
400fbb58 g     F .vmlinux	00000080 device_reprobe
400afb60 g     F .vmlinux	00000030 elv_put_request
40302a90 g     O .bss	00000100 sparc_irq
40017018 g     F .vmlinux	00000008 sbus_dma_sync_single_for_cpu
40090428 g     F .vmlinux	00000040 nr_blockdev_pages
400b3f54 g     F .vmlinux	00000384 blk_do_ordered
400c7184 g     F .vmlinux	00000008 ioport_map
4006ca58 g     F .vmlinux	00000040 do_kern_mount
401194fc g     O .vmlinux	0000003c max_vals
40110ac8 g     F .vmlinux	00000818 schedule
40111b54 g     F .vmlinux	000000b0 schedule_timeout
400fa810 g     F .vmlinux	00000100 sysdev_driver_register
400130cc g     F .vmlinux	00000184 request_irq
4005c5d0 g     F .vmlinux	00000018 swapin_readahead
400779a4 g     F .vmlinux	00000414 do_sys_poll
401345c0 g       .vmlinux	00000000 ___fs_pmd_present
400fb3d8 g     F .vmlinux	0000003c bus_create_file
4013584c g       .vmlinux	00000000 ___f_flush_page_for_dma
4003e7bc g     F .vmlinux	00000044 blocking_notifier_call_chain
400c54f4 g       .vmlinux	00000000 __udivdi3
4008bf60 g     F .vmlinux	00000084 generic_commit_write
400fde98 g     F .vmlinux	0000002c platform_get_irq_byname
4014ca98 g     F .vmlinux	00000038 anon_vma_init
4004d11c g     F .vmlinux	00000158 sys_setgroups16
4002e6a4 g     F .vmlinux	0000003c cond_resched_lock
400f1cb4 g     F .vmlinux	00000070 reset_palette
40085abc g     F .vmlinux	00000044 sys_fsetxattr
40011de8 g       .vmlinux	00000000 rtrap_7win_patch4
40039fb8 g     F .vmlinux	00000048 ptrace_get_task_struct
401087b8 g     F .vmlinux	00000268 input_register_device
400433c4 g     F .vmlinux	00000020 param_get_uint
400b9dcc g     F .vmlinux	0000004c __bitmap_andnot
40011ec4 g       .vmlinux	00000000 rtrap_mmu_patchme
4007ab04 g     F .vmlinux	000002bc fcntl_setlk64
4006bad0 g     F .vmlinux	00000090 __fsync_super
40035da4 g     F .vmlinux	00000030 msecs_to_jiffies
4001ae04 g     F .vmlinux	00000018 of_get_next_child
40039260 g     F .vmlinux	00000148 sys_capget
40042798 g     F .vmlinux	0000000c rcu_batches_completed_bh
4008acfc g     F .vmlinux	0000000c init_buffer
400126a0 g     F .vmlinux	000001f4 do_fpe_trap
40041ca4 g     F .vmlinux	00000024 schedule_delayed_work
400c90d0 g     F .vmlinux	000000a4 pci_intx
40005000 g       .vmlinux	00000000 swapper_pg_dir
4014ca08 g     F .vmlinux	00000080 page_address_init
4031ab24 g     O .bss	00000004 platform_notify_remove
403042e4 g     O .bss	00000004 page_kernel
4005ce94 g     F .vmlinux	00000368 get_user_pages
400af1d8 g     F .vmlinux	00000238 elv_merge
40059488 g     F .vmlinux	00000068 vma_prio_tree_next
4014fcc8 g     F .vmlinux	00000400 pci_scan_bridge
400af8d4 g     F .vmlinux	00000198 elv_next_request
4003e694 g     F .vmlinux	00000034 atomic_notifier_chain_register
4014ba08 g     F .vmlinux	00000010 free_all_bootmem_node
4004fcb8 g     F .vmlinux	00000380 filemap_populate
4014bc10 g     F .vmlinux	00000018 __alloc_bootmem_low_node
40063b98 g     F .vmlinux	00000044 vmalloc_user
400fce98 g     F .vmlinux	00000028 class_device_remove_file
40081f80 g     F .vmlinux	000001d0 dup_mnt_ns
400ae418 g     F .vmlinux	00000020 cap_capget
4004153c g     F .vmlinux	0000009c queue_delayed_work_on
400818d4 g     F .vmlinux	000006ac do_mount
4006afdc g     F .vmlinux	00000064 sys_readv
40011c70 g       .vmlinux	00000000 tsetup_patch6
4008033c g     F .vmlinux	0000005c mnt_set_mountpoint
400b29b0 g     F .vmlinux	00000098 blk_execute_rq
40053b04 g     F .vmlinux	00000090 __get_free_pages
40037aa4 g     F .vmlinux	0000005c unregister_sysctl_table
400c5938 g       .vmlinux	00000000 .umul_patch
40315ad0 g     O .bss	00000004 global_mode_option
40135318 g       .vmlinux	00000000 ___fs_pgd_bad
400146a8 g     F .vmlinux	00000068 exit_thread
40302a04 g     O .bss	00000004 thiscpus_mid
400bc814 g     F .vmlinux	00000048 kset_add
400f9400 g     F .vmlinux	00000028 put_device
400b02cc g     F .vmlinux	00000008 blk_queue_softirq_done
4010bb64 g     F .vmlinux	00000094 hid_free_device
400c83f0 g     F .vmlinux	00000044 pci_stop_bus_device
4014a58c g     F .vmlinux	00000040 init_timers
400a6214 g     F .vmlinux	00000058 ext2_dotdot
400ebdf0 g     F .vmlinux	00000058 vcs_make_sysfs
40011c84 g       .vmlinux	00000000 tsetup_mmu_patchme
40151b78 g     F .vmlinux	00000174 pdev_sort_resources
4003edf8 g     F .vmlinux	00000014 emergency_restart
4005fec0 g     F .vmlinux	0000023c do_munmap
400be8d8 g     F .vmlinux	0000008c rb_prev
4001bd50 g     F .vmlinux	00000074 devm_free_irq
40056d98 g     F .vmlinux	00000028 pagevec_lookup_tag
40013efc g     F .vmlinux	00000098 leon_disable_irq
4005782c g     F .vmlinux	000001c4 shrink_slab
400bd7e4 g     F .vmlinux	000000b4 radix_tree_lookup_slot
4008bf30 g     F .vmlinux	00000030 generic_cont_expand_simple
40041e88 g     F .vmlinux	00000038 init_workqueues
4008eb84 g     F .vmlinux	0000002c bio_hw_segments
400457fc  w    F .vmlinux	00000008 sys_bind
40155344 g     F .vmlinux	00000018 cpu_dev_init
4004edfc g     F .vmlinux	000000a0 find_get_pages_tag
4008f684 g     F .vmlinux	000000f4 bio_map_kern
4009cb50 g     F .vmlinux	00000444 proc_pid_status
40105b04 g     F .vmlinux	000003f8 ps2_command
4012a000 g       .vmlinux	00000000 cputyp
400b3cb0 g     F .vmlinux	00000014 end_that_request_first
400c743c g     F .vmlinux	0000005c pci_bus_read_config_dword
4002ede4 g     F .vmlinux	0000011c copy_fs_struct
400b2be4 g     F .vmlinux	00000098 __blk_put_request
4008cc38 g     F .vmlinux	000000ac try_to_free_buffers
400457fc  w    F .vmlinux	00000008 compat_sys_move_pages
40043428 g     F .vmlinux	00000020 param_get_long
4008d150 g     F .vmlinux	00000110 create_empty_buffers
4005bbec g     F .vmlinux	00000008 get_gate_vma
400b23e8 g     F .vmlinux	00000034 blk_start_queueing
4012b33c g     O .vmlinux	0000003c screen_info
4004c8a4 g     F .vmlinux	00000048 rt_mutex_destroy
40080fc4 g     F .vmlinux	00000198 copy_tree
400b07bc g     F .vmlinux	000000d8 blk_queue_make_request
400748bc g     F .vmlinux	00000024 sys_link
4006db60 g     F .vmlinux	0000006c inode_sub_bytes
4012c494 g     O .vmlinux	00000010 console_printk
4003e958 g     F .vmlinux	0000001c register_reboot_notifier
4007c6c4 g     F .vmlinux	00000168 d_alloc
40094218 g     F .vmlinux	00000088 inotify_d_instantiate
400ec1d0 g     F .vmlinux	00000068 con_set_trans_old
4008aebc g     F .vmlinux	00000024 sync_blockdev
40010af0 g       .vmlinux	00000000 setcc_trap_handler
400c77f0 g     F .vmlinux	00000074 pci_user_write_config_word
4008d640 g     F .vmlinux	000000c8 block_write_full_page
4009f780 g     F .vmlinux	00000030 bdevname
4014c958 g     F .vmlinux	00000038 page_writeback_init
40133768 g     O .vmlinux	000000b8 input_class
4008cbf8 g     F .vmlinux	00000040 free_buffer_head
400806dc g     F .vmlinux	00000078 mntput_no_expire
4008ebb0 g     F .vmlinux	000000a8 __bio_clone
400f81c0 g     F .vmlinux	00000118 uart_suspend_port
400ae570 g     F .vmlinux	00000028 cap_task_reparent_to_init
40066d08 g     F .vmlinux	0000004c kmem_cache_shrink
400106a4 g       .vmlinux	00000000 bad_trap_handler
400c73e0 g     F .vmlinux	0000005c pci_bus_read_config_word
4010d3d4 g     F .vmlinux	00000044 hidinput_report_event
40048b54 g     F .vmlinux	00000010 system_latency_constraint
40020f24 g       .vmlinux	00000000 tsunami_flush_page_for_dma
400432fc g     F .vmlinux	00000020 param_get_ushort
400ebe48 g     F .vmlinux	0000003c vcs_remove_sysfs
400457fc  w    F .vmlinux	00000008 sys_mq_notify
400dcc9c g     F .vmlinux	00000030 amba_free_ahbslv_device
40115474 g     O .vmlinux	0000006c proc_kmsg_operations
40154120 g     F .vmlinux	00000050 console_init
400c60e8 g     F .vmlinux	00000030 match_strcpy
4011415c g     O .vmlinux	0000006c simple_dir_operations
40050038 g     F .vmlinux	00000060 generic_file_mmap
4004f6e4 g     F .vmlinux	00000058 generic_file_sendfile
4013584c g       .vmlinux	00000000 ___f_mk_pte_phys
40072a40 g     F .vmlinux	00000024 path_lookup
400d0c74 g     F .vmlinux	00000520 fb_find_mode
400c7a40 g     F .vmlinux	0000006c pci_enable_bridges
400bd92c g     F .vmlinux	000000e0 radix_tree_tag_set
400bf1e0 g     F .vmlinux	00000044 strnlen
400fc950 g     F .vmlinux	0000003c driver_create_file
400d14bc g     F .vmlinux	000000bc fb_find_nearest_mode
4001a8e0 g     F .vmlinux	00000490 do_user_muldiv
4008c57c g     F .vmlinux	0000029c sync_mapping_buffers
40069dc4 g     F .vmlinux	00000018 sys_creat
4012df18 g     O .vmlinux	00000080 core_pattern
40051bac g     F .vmlinux	000000e0 mempool_create_node
402ff50d g       .vmlinux	00000000 __initramfs_end
40048e78 g     F .vmlinux	00000028 srcu_readers_active
400dc400 g     F .vmlinux	000001f4 amba_scan
400c48a4 g       .vmlinux	00000000 .mul_patch
4003b488 g     F .vmlinux	00000088 recalc_sigpending_tsk
400bc4c0 g     F .vmlinux	0000003c kobject_shadow_rename
400cff0c g     F .vmlinux	000001e0 fb_set_user_cmap
4014a084 g     F .vmlinux	00000030 softirq_init
4008ec58 g     F .vmlinux	00000040 bio_clone
400fe1c8 g     F .vmlinux	00000018 platform_device_register
400c1c4c g     F .vmlinux	00000080 prom_getproperty
400fbe1c g     F .vmlinux	00000014 bus_register_notifier
4012d140 g     O .vmlinux	0000002c root_user
40018ee4 g       .vmlinux	00000000 getpagesize_low
400bb4d8 g     F .vmlinux	0000022c generic_find_next_zero_le_bit
40078528 g     F .vmlinux	00000060 locks_init_lock
400a44d0 g     F .vmlinux	000000b4 ext2_get_group_desc
400909f0 g     F .vmlinux	00000090 bd_set_size
400bcc44 g     F .vmlinux	00000128 prio_tree_remove
400e6be8 g     F .vmlinux	00000110 tty_wait_until_sent
400579f0 g     F .vmlinux	000000a4 remove_mapping
40051e48 g     F .vmlinux	00000108 mempool_alloc
4014e7c8 g     F .vmlinux	00000080 radix_tree_init
4003071c g     F .vmlinux	00000060 register_exec_domain
401355e0 g       .vmlinux	00000000 ___fs_pte_to_pgoff
4013584c g       .vmlinux	00000000 ___f_pte_to_pgoff
400c0d9c g     F .vmlinux	000000a4 prom_nbgetchar
4005a030 g     F .vmlinux	000001d4 sys_remap_file_pages
400457fc  w    F .vmlinux	00000008 compat_sys_mbind
4005df18 g     F .vmlinux	000001ec access_process_vm
4014dee8 g     F .vmlinux	000000f8 proc_root_init
40090f60 g     F .vmlinux	00000014 blkdev_put
40086958 g     F .vmlinux	00000044 simple_unlink
400cd458 g     F .vmlinux	000001f4 sys_pciconfig_read
4012d400 g     O .vmlinux	00000004 time_status
400457fc  w    F .vmlinux	00000008 sys_mbind
4003e478 g     F .vmlinux	000000cc sys_rt_sigsuspend
4003f27c g     F .vmlinux	000000d4 sys_setgid
400ebf64 g     F .vmlinux	000000d0 conv_uni_to_pc
400fd2bc g     F .vmlinux	0000045c class_device_add
400457fc  w    F .vmlinux	00000008 sys_semtimedop
4012bb44 g     O .vmlinux	00000174 linux_sparc_chips
401499ac g     F .vmlinux	000000cc add_preferred_console
4012feac g     O .vmlinux	0000002c tty_std_termios
40053358 g     F .vmlinux	00000040 __free_pages
4015d2e4 g       .vmlinux	00000000 __con_initcall_start
4007e558 g     F .vmlinux	0000002c ilookup
40042450 g     F .vmlinux	00000064 transfer_pid
40013258 g     F .vmlinux	00000008 probe_irq_off
4012ff08 g     O .vmlinux	00000048 tty_ldisc_N_TTY
400bc9ac g     F .vmlinux	0000008c subsys_create_file
4003e264 g     F .vmlinux	00000164 sys_sigprocmask
40066ed8 g     F .vmlinux	00000064 kmem_cache_alloc
400457fc  w    F .vmlinux	00000008 sys_shmctl
4012a004 g       .vmlinux	00000000 cputypval
40302ffd g     O .bss	00000000 rtc_lock
40056ad4 g     F .vmlinux	000000fc __pagevec_lru_add
4012f604 g     O .vmlinux	00000104 pci_dev_attrs
400fb470 g     F .vmlinux	00000080 bus_for_each_dev
400b47b4 g     F .vmlinux	00000034 get_io_context
400bdb64 g     F .vmlinux	0000019c radix_tree_gang_lookup
400bf070 g     F .vmlinux	00000048 strrchr
400f8f94 g     F .vmlinux	0000008c suncore_mouse_baud_detection
40140e44 g     F .vmlinux	0000002c sbus_arch_postinit
4005ac94 g     F .vmlinux	00000314 free_pgd_range
40037218 g     F .vmlinux	00000044 __check_region
40106a6c g     F .vmlinux	00000080 leon3ps2_open
4012d210 g     O .vmlinux	00000004 overflowgid
4007adc0 g     F .vmlinux	000000d8 locks_remove_posix
400afa6c g     F .vmlinux	00000044 elv_queue_empty
40030c08 g     F .vmlinux	0000001c add_taint
40315984 g     O .bss	00000004 platform_pci_set_power_state
40157d04 g     O .vmlinux	00000004 rd_image_start
400696f0 g     F .vmlinux	00000064 sys_fchownat
4014d490 g     F .vmlinux	000000a8 vfs_caches_init_early
400112e4 g       .vmlinux	00000000 bsd_is_too_hard
400fc888 g     F .vmlinux	0000008c driver_find_device
400dfdb0 g     F .vmlinux	0000004c secure_ip_id
400e3f34 g     F .vmlinux	0000002c tty_unregister_device
40157868 g       .vmlinux	00000000 __init_text_end
4013584c g       .vmlinux	00000000 ___f_free_thread_info
40071178 g     F .vmlinux	0000001c file_permission
4002ebf0 g     F .vmlinux	00000040 mm_alloc
4008a5b8 g     F .vmlinux	0000010c do_sync_file_range
4007a674 g     F .vmlinux	000002bc fcntl_setlk
4006913c g     F .vmlinux	00000014 sys_ftruncate64
4003e830 g     F .vmlinux	00000054 srcu_notifier_chain_register
400cd1e8 g     F .vmlinux	0000002c pci_proc_detach_bus
400697a0 g     F .vmlinux	00000040 sys_fchown
4014e538 g     F .vmlinux	00000108 blk_dev_init
400ed53c g     F .vmlinux	00000094 getkeycode
400a73f8 g     F .vmlinux	00000c54 ext2_new_inode
40090f14 g     F .vmlinux	0000004c open_by_devnum
4008b570 g     F .vmlinux	000000dc invalidate_inode_buffers
403078f4 g     O .bss	00000004 oops_in_progress
4008bfe4 g     F .vmlinux	00000024 block_commit_write
400b2888 g     F .vmlinux	0000009c blk_rq_map_kern
40314ff8 g     O .bss	00000300 prom_phys_avail
40010b94 g       .vmlinux	00000000 num_context_patch1_16
4030d4b0 g     O .bss	0000003c per_cpu__rcu_data
400758d8 g     F .vmlinux	00000030 f_getown
40010ca8 g       .vmlinux	00000000 vac_linesize_patch
40110520 g     F .vmlinux	00000018 klist_remove
40318110 g     O .bss	00000004 amba_proc_dir_entry
4003a770 g     F .vmlinux	000006dc do_timer
4012a0d0 g     O .vmlinux	000003a0 init_task
4007960c g     F .vmlinux	00000104 posix_lock_file_wait
4014a808 g     F .vmlinux	00000064 pidmap_init
40143f88 g     F .vmlinux	0000032c mem_init
4005298c g     F .vmlinux	00000024 sys_fadvise64
400361f0 g     F .vmlinux	00000014 local_bh_disable
40039ba8 g     F .vmlinux	000000d4 ptrace_readdata
4006d7dc g     F .vmlinux	00000098 sys_readlinkat
40020d04 g       .vmlinux	00000000 viking_flush_page
400393e0 g     F .vmlinux	00000018 capable
40112a2c g       .vmlinux	00000000 __sched_text_end
400fa9cc g     F .vmlinux	00000150 sysdev_register
00000000 g       *ABS*	00000000 ___a_pte_mkoldi
400b3710 g     F .vmlinux	000000d8 submit_bio
400425a4 g     F .vmlinux	000000c8 find_ge_pid
40100368 g     F .vmlinux	000000b8 attribute_container_trigger
4001e3cc g     F .vmlinux	000000b0 free_initmem
4005ead4 g     F .vmlinux	000000a4 find_vma
400457fc  w    F .vmlinux	00000008 compat_sys_kexec_load
400afe24 g     F .vmlinux	000000b0 elv_register
400c9bbc g     F .vmlinux	00000040 pci_select_bars
401341e8 g       .vmlinux	00000000 ___fs_sparc_mapiorange
400b0764 g     F .vmlinux	00000058 blk_queue_bounce_limit
40133764 g     O .vmlinux	00000004 leon3ps2_kbd_irq
40110538 g     F .vmlinux	00000010 klist_node_attached
4007cb04 g     F .vmlinux	0000011c __d_lookup
4013584c g       .vmlinux	00000000 ___f_pmd_populate
400894f0 g     F .vmlinux	00000054 splice_from_pipe
40018518 g       .vmlinux	00000000 sunos_getuid
400c17c4 g     F .vmlinux	00000048 prom_printf
4006ca98 g     F .vmlinux	0000001c kern_mount
400752a4 g     F .vmlinux	00000030 page_follow_link_light
4008a590 g     F .vmlinux	00000014 sys_fsync
4003e884 g     F .vmlinux	0000005c srcu_notifier_chain_unregister
403042d8 g     O .bss	00000004 sparc_unmapped_base
4013584c g       .vmlinux	00000000 ___f_pte_mkyoung
400cf9d4 g     F .vmlinux	00000040 fb_dealloc_cmap
400457fc  w    F .vmlinux	00000008 sys_epoll_pwait
40049ce8 g     F .vmlinux	00000064 clocksource_register
4006fa84 g     F .vmlinux	00000098 generic_pipe_buf_unmap
40113d68 g     O .vmlinux	0000006c read_fifo_fops
4004c884 g     F .vmlinux	00000020 rt_mutex_timed_lock
400862c4 g     F .vmlinux	00000034 simple_getattr
4005afa8 g     F .vmlinux	000000d0 free_pgtables
400b1dd4 g     F .vmlinux	0000002c blk_get_queue
4012c3c4 g     O .vmlinux	00000004 cpu_online_map
400a34e8 g     F .vmlinux	00000138 sysfs_create_link
40039c7c g     F .vmlinux	0000010c ptrace_writedata
400457fc  w    F .vmlinux	00000008 sys_init_module
4002112c g       .vmlinux	00000000 swift_flush_sig_insns
400c2214 g     F .vmlinux	0000004c prom_inst2pkg
4007cd08 g     F .vmlinux	000000fc d_validate
40042e74 g     F .vmlinux	00000344 parse_args
40011170 g       .vmlinux	00000000 ret_sys_call
400457fc  w    F .vmlinux	00000008 sys32_sysctl
4005fb00 g     F .vmlinux	0000013c expand_stack
40087054 g     F .vmlinux	00000018 simple_transaction_release
4012c3c0 g     O .vmlinux	00000004 cpu_possible_map
400b468c g     F .vmlinux	000000a4 put_io_context
40069a60 g     F .vmlinux	00000098 lookup_instantiate_filp
40134d94 g       .vmlinux	00000000 ___fs_sun4c_flush_segment
400bb790 g     F .vmlinux	00000064 idr_pre_get
40018144 g     F .vmlinux	00000044 c_sys_nis_syscall
400533ac g     F .vmlinux	0000003c split_page
40144c84 g     F .vmlinux	00000020 early_pgtable_allocfail
400c9960 g     F .vmlinux	00000108 pci_set_mwi
40069d90 g     F .vmlinux	00000024 sys_open
400543d0 g     F .vmlinux	000000c8 percpu_pagelist_fraction_sysctl_handler
40098480 g     F .vmlinux	00000050 task_statm
4005c728 g     F .vmlinux	0000076c __handle_mm_fault
4007dc40 g     F .vmlinux	000000c8 inode_init_once
4013d16c g     F .vmlinux	00000340 initrd_load
4003e3d4 g     F .vmlinux	00000040 sys_ssetmask
400fdf6c g     F .vmlinux	00000050 platform_device_add_resources
400128ec g     F .vmlinux	00000024 handle_watchpoint
4005439c g     F .vmlinux	00000034 lowmem_reserve_ratio_sysctl_handler
40130810 g     O .vmlinux	00000254 dfont_unitable
400dc78c g     F .vmlinux	00000088 amba_get_number_apbslv_devices
403004a8 g     O .bss	00000004 initrd_start
400493c0 g     F .vmlinux	0000000c current_tick_length
40020ef0 g       .vmlinux	00000000 tsunami_flush_cache_page
40085cac g     F .vmlinux	00000050 sys_lgetxattr
400545b8 g     F .vmlinux	000001d4 balance_dirty_pages_ratelimited_nr
400b03a4 g     F .vmlinux	00000008 blk_queue_hardsect_size
400457fc  w    F .vmlinux	00000008 sys_mq_timedreceive
40140878 g     F .vmlinux	000000fc sun4d_init_IRQ
403041b4 g     O .bss	00000004 vac_size
400c3da0 g       .vmlinux	00000000 __lshrdi3
40063c78 g     F .vmlinux	000000c4 vread
4008b404 g     F .vmlinux	00000020 mark_buffer_async_write
40013510 g     F .vmlinux	0000003c sun4c_sbint_to_irq
40070a94 g     F .vmlinux	00000188 create_write_pipe
400c5840 g       .vmlinux	00000000 _Umul
400ae908 g     F .vmlinux	00000170 cap_task_post_setuid
40100800 g     F .vmlinux	00000054 attribute_container_find_class_device
4006d12c g     F .vmlinux	00000040 cdev_add
400b5864 g     F .vmlinux	000000bc unregister_blkdev
4003ae4c g     F .vmlinux	00000010 sys_alarm
401549a8 g     F .vmlinux	00000058 console_map_init
4014be3c g     F .vmlinux	00000070 build_all_zonelists
40059170 g     F .vmlinux	00000080 wakeup_kswapd
400f9428 g     F .vmlinux	0000003c device_create_file
40011de4 g       .vmlinux	00000000 rtrap_7win_patch3
4031361c g     O .bss	00000040 protection_map
400708e0 g     F .vmlinux	00000078 __free_pipe_info
400a80c4 g     F .vmlinux	0000003c ext2_discard_prealloc
4003e974 g     F .vmlinux	0000001c unregister_reboot_notifier
40045498 g     F .vmlinux	0000008c bit_waitqueue
40011f58 g       .vmlinux	00000000 rtrap_patch3
400600fc g     F .vmlinux	00000794 do_mmap_pgoff
40134b0c g       .vmlinux	00000000 ___fs_flush_tlb_mm
4013584c g       .vmlinux	00000000 ___f_pmd_offset
4003b678 g     F .vmlinux	00000040 flush_signals
400457fc  w    F .vmlinux	00000008 sys_send
4013584c g       .vmlinux	00000000 ___f_mk_pte_io
400111f8 g       .vmlinux	00000000 solaris_syscall
400c3e3c g     F .vmlinux	00000000 amemmove
4030bc28 g     O .bss	00001008 boot_tvec_bases
40036a18 g     F .vmlinux	00000080 tasklet_kill
400bc3bc g     F .vmlinux	00000104 kobject_move
400c8574 g     F .vmlinux	00000038 pci_find_capability
4030e1b4 g     O .bss	00000038 vm_stat
400678a0 g     F .vmlinux	00000008 kmem_cache_size
403143d4 g     O .bss	00000004 romvec
400bbbd8 g     F .vmlinux	00000214 idr_remove
40135480 g       .vmlinux	00000000 ___fs_free_pte_fast
40044a44 g     F .vmlinux	00000008 do_posix_clock_nosettime
400beef4 g     F .vmlinux	00000040 strcat
400e3e60 g     F .vmlinux	000000d4 tty_register_device
4008d708 g     F .vmlinux	000000e4 nobh_writepage
400562c0 g     F .vmlinux	00000094 __pagevec_release_nonlru
400fe264 g     F .vmlinux	0000005c platform_add_devices
40068674 g     F .vmlinux	00000160 slabinfo_write
40302e68 g     O .bss	00000004 sparc_cpu_model
400566f8 g     F .vmlinux	0000006c mark_page_accessed
4013584c g       .vmlinux	00000000 ___f_pte_offset_kernel
40010d04 g       .vmlinux	00000000 invalid_segment_patch2
400630f4 g     F .vmlinux	000001d8 unmap_vm_area
4001bb84 g     F .vmlinux	00000060 of_device_register
400a241c g     F .vmlinux	00000040 sysfs_make_dirent
400c8890 g     F .vmlinux	00000074 pci_restore_bars
40016538 g     F .vmlinux	000000b8 ptrace_signal_deliver
400457fc  w    F .vmlinux	00000008 sys_msgsnd
40016944 g     F .vmlinux	0000014c dma_alloc_coherent
4030b9e0 g     O .bss	00000020 irq_stat
4007e82c g     F .vmlinux	0000002c ilookup5
400ff808 g     F .vmlinux	00000080 dmam_free_noncoherent
400c6b4c g     F .vmlinux	0000012c pcim_iomap_regions
40149754 g     F .vmlinux	00000084 fork_init
400e0184 g     F .vmlinux	00000080 tty_insert_flip_string_flags
400b42d8 g     F .vmlinux	000000f8 blk_ordered_complete_seq
40050320 g     F .vmlinux	00000020 __remove_suid
400172f8 g     F .vmlinux	0000002c pci_unmap_single
4030b9b4 g     O .bss	00000008 sys_tz
400329dc g     F .vmlinux	00000098 allow_signal
40086270 g     F .vmlinux	00000054 generic_removexattr
400f5458 g     F .vmlinux	00000554 con_font_op
400687d4 g     F .vmlinux	00000060 ksize
403179b8 g     O .bss	000003ac amba_conf
40049b90 g     F .vmlinux	0000004c clocksource_get_next
4008eb14 g     F .vmlinux	00000044 bio_put
4005d5c4 g     F .vmlinux	00000118 vm_insert_page
4005b2b4 g     F .vmlinux	0000069c unmap_vmas
4006e1b8 g     F .vmlinux	000000c0 install_arg_page
4014dea4 g     F .vmlinux	00000044 proc_init_inodecache
400708a4 g     F .vmlinux	0000003c alloc_pipe_info
40156080 g     F .vmlinux	00000150 dvma_init
400c6720  w    F .vmlinux	00000034 __iowrite32_copy
4001ae70 g     F .vmlinux	00000030 of_find_node_by_phandle
40037b00 g     F .vmlinux	00000264 proc_dostring
40010784 g       .vmlinux	00000000 priv_instruction
403136c0 g     O .bss	00000000 sb_lock
400bdf0c g     F .vmlinux	0000027c radix_tree_delete
4008f97c g     F .vmlinux	000000a4 bio_endio
4012d81c g     O .vmlinux	00000434 contig_page_data
400afdfc g     F .vmlinux	00000028 elv_unregister_queue
400457fc  w    F .vmlinux	00000008 sys_move_pages
40052518 g     F .vmlinux	0000001c unregister_oom_notifier
40011a10 g       .vmlinux	00000000 sun4c_fwin_stackchk
4013584c g       .vmlinux	00000000 ___f___swp_entry
f031ae0c g       *ABS*	00000000 end
4006613c g     F .vmlinux	000001ac shmem_file_setup
40059e78 g     F .vmlinux	00000110 install_page
4008abec g     F .vmlinux	00000058 __brelse
4006fb8c g     F .vmlinux	00000030 generic_pipe_buf_get
40048640 g     F .vmlinux	00000014 hrtimer_init_sleeper
40079710 g     F .vmlinux	00000054 lease_modify
4001b2f4 g     F .vmlinux	00000124 of_match_device
40041988 g     F .vmlinux	0000004c flush_workqueue
400a42b8 g     F .vmlinux	00000168 devpts_pty_new
400468cc g     F .vmlinux	000003d8 posix_cpu_timer_set
4013581c g       .vmlinux	00000000 ___fs_mk_pte_phys
40073c94 g     F .vmlinux	000001c0 sys_mknodat
4009d3f4 g     F .vmlinux	00000014 proc_tid_stat
400ae4c4 g     F .vmlinux	00000070 cap_bprm_set_security
4004266c g     F .vmlinux	00000028 copy_pid_ns
400457fc  w    F .vmlinux	00000008 compat_sys_migrate_pages
40033290 g     F .vmlinux	0000089c do_exit
4001dd2c g     F .vmlinux	00000240 window_underflow_fault
4003cadc g     F .vmlinux	000000dc kill_pid_info_as_uid
40094398 g     F .vmlinux	0000007c inotify_dentry_parent_queue_event
400457fc  w    F .vmlinux	00000008 sys_accept
403074cc g     O .bss	00000004 panic_timeout
4001e1b0 g     F .vmlinux	0000005c show_mem
40076b30 g     F .vmlinux	0000001c poll_initwait
400139c4 g     F .vmlinux	000001dc sun4d_handler_irq
40056764 g     F .vmlinux	000001f8 release_pages
400f28c0 g     F .vmlinux	00000040 con_is_bound
400115b8 g       .vmlinux	00000000 spnwin_patch2
4002110c g       .vmlinux	00000000 swift_flush_cache_all
4003cca0 g     F .vmlinux	00000018 kill_proc_info
400ae534 g     F .vmlinux	0000003c cap_bprm_secureexec
4000d00e g       .vmlinux	00000000 ram_flags
4006b9a8 g     F .vmlinux	00000030 __put_super
400b25cc g     F .vmlinux	0000020c blk_rq_map_user
40014a14 g     F .vmlinux	0000018c dump_thread
40116318 g     O .vmlinux	00000100 byte_rev_table
40048e1c g     F .vmlinux	0000004c init_srcu_struct
40319130 g     O .bss	00000004 shift_state
40036810 g     F .vmlinux	0000007c raise_softirq
40076a88 g     F .vmlinux	000000a8 sys_getdents64
4014fba4 g     F .vmlinux	00000078 pci_scan_slot
400cb6e8 g     F .vmlinux	0000001c pci_dev_present
400457fc  w    F .vmlinux	00000008 compat_sys_futex
400fe810 g     F .vmlinux	00000010 firmware_unregister
4014d8b4 g     F .vmlinux	0000021c mnt_init
4006b300 g     F .vmlinux	000000bc sys_sendfile
400ec2c4 g     F .vmlinux	00000060 con_set_trans_new
400dfdfc g     F .vmlinux	00000024 get_random_int
40080170 g     F .vmlinux	0000003c simple_set_mnt
400b5980 g     F .vmlinux	0000002c get_disk
40056c20 g     F .vmlinux	00000018 lru_add_drain_all
40050fec g     F .vmlinux	00000138 generic_file_direct_write
400fbdb0 g     F .vmlinux	0000006c bus_unregister
4006b788 g     F .vmlinux	00000030 fput
400a01c8 g     F .vmlinux	00000ac0 msdos_partition
40048860 g     F .vmlinux	00000010 down_write
400c2d24 g       .vmlinux	00000000 __csum_partial_copy_start
40100064 g     F .vmlinux	00000060 devm_kfree
4001c17c g     F .vmlinux	000000b0 gptimer_SameClkInt
40072e88 g     F .vmlinux	00000024 __user_walk
403004ac g     O .bss	00000004 initrd_end
4014b1b8 g     F .vmlinux	00000050 spawn_softlockup_task
400301f8 g     F .vmlinux	00000524 sys_unshare
400f5ad4 g     F .vmlinux	00000034 vcs_scr_writew
400afae8 g     F .vmlinux	00000038 elv_former_request
400bc720 g     F .vmlinux	00000014 kobject_add
400595a0 g     F .vmlinux	000000c8 strndup_user
4007bfb8 g     F .vmlinux	00000118 shrink_dcache_sb
40012e34 g     F .vmlinux	000000fc handler_irq
400c47b0 g       .vmlinux	00000000 __memset_end
400b2b5c g     F .vmlinux	00000088 blk_insert_request
401009e4 g     F .vmlinux	00000010 transport_class_unregister
4001f9f8 g     F .vmlinux	00000034 leon3_getCacheRegs
40048894 g     F .vmlinux	00000010 up_write
400711fc g     F .vmlinux	00000034 path_release
400bc770 g     F .vmlinux	00000084 kobject_add_dir
4010473c g     F .vmlinux	00000054 serio_open
400fb820 g     F .vmlinux	00000094 bus_remove_device
400c5c20 g     F .vmlinux	000001a8 sort
4013436c g       .vmlinux	00000000 ___fs_load_profile_irq
4006cf98 g     F .vmlinux	00000104 chrdev_open
400f5a78 g     F .vmlinux	00000028 putconsxy
400a8464 g     F .vmlinux	0000080c ext2_get_block
4007ae98 g     F .vmlinux	000001a0 locks_remove_flock
40010f4c g       .vmlinux	00000000 flush_patch_two
4013584c g       .vmlinux	00000000 ___f_pte_present
400b0a00 g     F .vmlinux	00000030 blk_queue_find_tag
40140974 g     F .vmlinux	00000108 leon_init_timers
400beb9c g     F .vmlinux	0000013c __up_write
4004e94c g     F .vmlinux	00000034 unlock_page
400fcb6c g     F .vmlinux	0000002c class_create_file
400696a4 g     F .vmlinux	0000004c sys_chown
40020e00 g       .vmlinux	00000000 viking_flush_cache_all
40313d50 g     O .bss	00000004 proc_mnt
4005bbe4 g     F .vmlinux	00000008 in_gate_area_no_task
4005e850 g     F .vmlinux	00000050 sys_munlock
40011d18 g       .vmlinux	00000000 tsetup_srmmu_stackchk
40080010 g     F .vmlinux	00000070 get_filesystem_list
40113868 g     O .vmlinux	00000010 zoneinfo_op
400dc3b8 g     F .vmlinux	00000048 amba_prinf_config
40135450 g       .vmlinux	00000000 ___fs_pmd_populate
400af470 g     F .vmlinux	0000005c elv_merge_requests
400beaf4 g     F .vmlinux	000000a8 __up_read
40114350 g     O .vmlinux	0000006c def_blk_fops
40010cb0 g       .vmlinux	00000000 vac_hwflush_patch2
4010d0e4 g     F .vmlinux	000002f0 hidinput_hid_event
40042d80 g     F .vmlinux	00000034 synchronize_rcu
40104790 g     F .vmlinux	00000034 serio_close
40016bc8 g     F .vmlinux	00000010 dma_unmap_page
40051ca0 g     F .vmlinux	00000188 mempool_resize
400a4760 g     F .vmlinux	00000410 ext2_free_blocks
40306628 g     O .bss	00000054 sun4c_kstack_vma
401357e0 g       .vmlinux	00000000 ___is_page_none
4010ca68 g     F .vmlinux	00000068 hid_set_field
400fb4f0 g     F .vmlinux	0000008c bus_find_device
400cc640 g     F .vmlinux	00000150 pci_update_resource
400ad444 g     F .vmlinux	00000120 ramfs_get_inode
4004c384 g     F .vmlinux	0000003c rt_mutex_getprio
40014efc g     F .vmlinux	00000320 do_sigreturn
40111b28 g     F .vmlinux	0000002c console_conditional_schedule
400f9698 g     F .vmlinux	00000730 device_add
4004e498 g     F .vmlinux	000000ac wait_on_page_bit
4006ebac g     F .vmlinux	000000e4 prepare_binprm
4003fbcc g     F .vmlinux	000000dc sys_times
400c60ac g     F .vmlinux	00000014 match_int
40069db4 g     F .vmlinux	00000010 sys_openat
40045f5c g     F .vmlinux	000000ac posix_cpu_timer_del
40094430 g     F .vmlinux	00000188 inotify_unmount_inodes
4013584c g       .vmlinux	00000000 ___f_sun4c_flush_context
40134f5c g       .vmlinux	00000000 ___as_pte_filei
40113bb8 g     O .vmlinux	0000006c generic_ro_fops
400f2384 g     F .vmlinux	00000184 vc_allocate
400fe3d0 g     F .vmlinux	000000a4 platform_driver_register
400e91a4 g     F .vmlinux	000000d4 vt_waitactive
400c21a4 g     F .vmlinux	00000070 prom_setprop
400389d4 g     F .vmlinux	00000038 proc_doulongvec_ms_jiffies_minmax
40045524 g     F .vmlinux	0000003c __wake_up_bit
40051ff4 g     F .vmlinux	0000001c mempool_free_slab
400a3620 g     F .vmlinux	00000014 sysfs_remove_link
4013584c g       .vmlinux	00000000 ___f___flush_page_to_ram
4002e5e8 g     F .vmlinux	00000084 sys_sched_yield
40090508 g     F .vmlinux	00000074 bd_forget
400b2924 g     F .vmlinux	0000008c blk_execute_rq_nowait
4002d960 g     F .vmlinux	0000007c account_steal_time
40304360 g     O .bss	00000004 srmmu_swapper_pg_dir
400364cc g     F .vmlinux	0000005c do_softirq
40017348 g     F .vmlinux	00000010 pci_unmap_page
f0112a30 g       *ABS*	00000000 etext
400bf444 g     F .vmlinux	00000048 memchr
40087760 g     F .vmlinux	00000020 writeback_acquire
400e0634 g     F .vmlinux	00000024 tty_ldisc_ref
40115888 g     O .vmlinux	0000006c ext2_dir_operations
400fa7a8 g     F .vmlinux	00000014 sysdev_class_create_file
40059b84 g     F .vmlinux	00000064 clear_bdi_congested
40020f50 g       .vmlinux	00000000 tsunami_flush_tlb_all
4006a93c g     F .vmlinux	00000064 sys_write
4013584c g       .vmlinux	00000000 ___f_pte_alloc_one
400bae3c g     F .vmlinux	00000048 bitmap_allocate_region
400144b0 g     F .vmlinux	00000054 show_backtrace
40020f34 g       .vmlinux	00000000 tsunami_flush_sig_insns
40086abc g     F .vmlinux	00000048 simple_readpage
400457fc  w    F .vmlinux	00000008 sys_epoll_ctl
400c1e78 g     F .vmlinux	0000002c prom_firstprop
400311a4 g     F .vmlinux	00000010 sys_syslog
400e1504 g     F .vmlinux	00000014 tty_vhangup
400dc814 g     F .vmlinux	000000e0 amba_find_next_apbslv_devices
400756a4 g     F .vmlinux	00000114 sys_dup2
400b3564 g     F .vmlinux	000001ac generic_make_request
400ae438 g     F .vmlinux	00000054 cap_capset_check
400424b4 g     F .vmlinux	0000003c pid_task
40011370 g       .vmlinux	00000000 fpsave
4006d874 g     F .vmlinux	00000024 sys_readlink
4008786c g     F .vmlinux	000000e0 generic_osync_inode
40047990 g     F .vmlinux	000000e4 posix_cpu_nsleep
40038fc8 g     F .vmlinux	00000154 sysctl_jiffies
4002daf4 g     F .vmlinux	00000018 __wake_up_locked
400b10f4 g     F .vmlinux	00000228 blk_recount_segments
40302e70 g     O .bss	00000004 prom_palette
400c2474 g       .vmlinux	00000000 __ashrdi3
403143dc g     O .bss	00000004 prom_rev
400114d4 g       .vmlinux	00000000 __handle_exception
4013584c g       .vmlinux	00000000 ___f_set_pte
401030fc g     F .vmlinux	00000094 unregister_mtd_user
403143e8 g     O .bss	00000004 prom_stdin
4003cc7c g     F .vmlinux	00000024 kill_pid
4031ac04 g     O .bss	00000080 mtd_table
400ff29c g     F .vmlinux	00000148 dma_pool_free
40019084 g     F .vmlinux	0000009c claim_ticker14
4008c818 g     F .vmlinux	0000012c sync_dirty_buffer
400f15e4 g     F .vmlinux	00000054 mouse_report
400457fc  w    F .vmlinux	00000008 sys_sendto
4012af70 g     O .vmlinux	0000018c init_uts_ns
400a9168 g     F .vmlinux	0000063c ext2_read_inode
400caf0c g     F .vmlinux	00000068 pci_find_bus
400fe24c g     F .vmlinux	00000018 platform_device_unregister
40039d88 g     F .vmlinux	000001e8 ptrace_request
4004320c g     F .vmlinux	00000020 param_get_byte
40019038 g     F .vmlinux	0000004c install_obp_ticker
400457fc  w    F .vmlinux	00000008 compat_sys_get_robust_list
40313b58 g     O .bss	00000000 inode_lock
4004cd4c g     F .vmlinux	000000e0 sys_getresuid16
4008926c g     F .vmlinux	00000284 __splice_from_pipe
40112a30 g       .vmlinux	00000000 __lock_text_end
40046ca4 g     F .vmlinux	0000025c posix_cpu_timer_get
4006c16c g     F .vmlinux	000000a8 get_super
4001d190 g     F .vmlinux	00000010 probe_memory
40131550 g     O .vmlinux	00000099 func_buf
4004f674 g     F .vmlinux	00000070 file_send_actor
4008afb4 g     F .vmlinux	0000008c thaw_bdev
40314208 g     O .bss	00000004 per_cpu____irq_regs
4000b000 g       .vmlinux	00000000 empty_bad_page_table
40304190 g     O .bss	00000004 auxio_power_register
400457fc  w    F .vmlinux	00000008 sys_epoll_wait
4030437c g     O .bss	00000004 srmmu_nocache_size
4003a310 g     F .vmlinux	0000003c mod_timer
400628ac g     F .vmlinux	0000001c page_add_new_anon_rmap
40076b6c g     F .vmlinux	00000088 poll_freewait
400dfae4 g     F .vmlinux	00000038 generate_random_uuid
40012894 g     F .vmlinux	00000058 handle_tag_overflow
4001a218 g     F .vmlinux	000002c4 kernel_unaligned_trap
400369f0 g     F .vmlinux	00000028 tasklet_init
400fa140 g     F .vmlinux	0000009c device_create
4013584c g       .vmlinux	00000000 ___f_flush_tlb_range
400b9e18 g     F .vmlinux	00000060 __bitmap_complement
401420dc g     F .vmlinux	00000168 clock_stop_probe
400d1320 g     F .vmlinux	000000e8 fb_mode_is_equal
400e1db8 g     F .vmlinux	00001024 tty_ioctl
4003e8e0 g     F .vmlinux	00000040 srcu_notifier_call_chain
400a13a4 g     F .vmlinux	00000148 sysfs_hash_and_remove
4006d4ac g     F .vmlinux	0000004c vfs_lstat_fd
400b571c g     F .vmlinux	00000148 register_blkdev
4009b328 g     F .vmlinux	0000013c proc_pid_lookup
403078f8 g     O .bss	00000004 console_drivers
40035b3c g     F .vmlinux	000000c0 mktime
403042f4 g     O .bss	00000004 kmap_pte
40080764 g     F .vmlinux	00000034 mnt_unpin
400fdda0 g     F .vmlinux	00000060 platform_get_resource
4004cbb0 g     F .vmlinux	00000058 sys_setregid16
4003b6b8 g     F .vmlinux	0000004c flush_signal_handlers
400afd70 g     F .vmlinux	00000078 elv_register_queue
400fc93c g     F .vmlinux	00000014 put_driver
400fc1b0 g     F .vmlinux	00000020 driver_probe_done
40075500 g     F .vmlinux	00000020 page_symlink
400fcb98 g     F .vmlinux	00000028 class_remove_file
40000000 g       .stage2	00000000 _start
40141850 g     F .vmlinux	0000015c idprom_init
40023234 g     F .vmlinux	000003e8 srmmu_swprobe
400457fc  w    F .vmlinux	00000008 sys_getsockname
400457fc  w    F .vmlinux	00000008 sys_vm86
40059668 g     F .vmlinux	0000000c first_online_pgdat
40113000 g       .vmlinux	00000000 __start_rodata
40134ad4 g       .vmlinux	00000000 ___ss_user_ptrs_per_pgd
4001c304 g     F .vmlinux	00000118 gptimerShowTimer
4009fd60 g     F .vmlinux	00000294 rescan_partitions
400bdd00 g     F .vmlinux	0000020c radix_tree_gang_lookup_tag
4013584c g       .vmlinux	00000000 ___f_disable_irq
40135370 g       .vmlinux	00000000 ___fs_pmd_bad
40020f40 g       .vmlinux	00000000 tsunami_flush_tlb_range
40107260 g     F .vmlinux	0000008c input_open_device
4014a8f0 g     F .vmlinux	00000020 sort_main_extable
40143adc g     F .vmlinux	00000388 bootmem_init
40147958 g       .vmlinux	00000000 hypersparc_setup_blockops
400d1194 g     F .vmlinux	00000118 fb_var_to_videomode
400bf3e0 g     F .vmlinux	00000064 strstr
400fcddc g     F .vmlinux	00000064 class_create
40010a90 g       .vmlinux	00000000 flush_patch_one
40304384 g     O .bss	00000004 srmmu_nocache_bitmap
400fa7fc g     F .vmlinux	00000014 sysdev_class_unregister
400fc2bc g     F .vmlinux	00000094 device_attach
400115a0 g       .vmlinux	00000000 spnwin_patch3_7win
40030d48 g     F .vmlinux	00000010 oops_exit
401128ac g     F .vmlinux	00000018 rt_mutex_unlock
4002d890 g     F .vmlinux	000000d0 account_system_time
40074020 g     F .vmlinux	00000080 dentry_unhash
4006fb1c g     F .vmlinux	00000070 generic_pipe_buf_steal
400fa498 g     F .vmlinux	00000120 device_move
400ba394 g     F .vmlinux	000000a8 bitmap_scnprintf
40132ea4 g     O .vmlinux	00000004 rd_size
400a3390 g     F .vmlinux	00000064 sysfs_make_shadowed_dir
4006d4f8 g     F .vmlinux	0000001c vfs_lstat
4014d880 g     F .vmlinux	00000034 files_defer_init
4012f36c g     O .vmlinux	00000001 pci_cache_line_size
400fa910 g     F .vmlinux	000000bc sysdev_driver_unregister
4014f100 g     F .vmlinux	00000198 pci_bus_add_devices
40134250 g       .vmlinux	00000000 ___fs_mmu_translate_dvma
4006e518 g     F .vmlinux	00000020 set_task_comm
400675a8 g     F .vmlinux	00000108 kmem_ptr_validate
40010fc8 g       .vmlinux	00000000 flush_patch_three
400c151c g     F .vmlinux	0000009c prom_feval
400170cc g     F .vmlinux	00000144 pci_alloc_consistent
40041ab8 g     F .vmlinux	000000a0 destroy_workqueue
40105f1c g     F .vmlinux	000000a8 ps2_schedule_command
400ae75c g     F .vmlinux	00000150 cap_bprm_apply_creds
40313b38 g     O .bss	00000000 dcache_lock
400ae4a8 g     F .vmlinux	0000001c cap_capable
40112898 g     F .vmlinux	00000014 rt_mutex_trylock
400c6ee8 g     F .vmlinux	0000017c crc32_le
40115ad4 g     O .vmlinux	00000054 ext2_special_inode_operations
40034d04 g     F .vmlinux	0000003c sys_wait4
400577dc g     F .vmlinux	00000050 remove_shrinker
4005a4a0 g     F .vmlinux	00000080 kunmap_high
40045608 g     F .vmlinux	00000078 __kfifo_get
40042380 g     F .vmlinux	00000054 attach_pid
4013584c g       .vmlinux	00000000 ___f___swp_type
40044ec4 g     F .vmlinux	0000005c clock_nanosleep_restart
400ff8f8 g     F .vmlinux	00000048 devres_alloc
4008ec98 g     F .vmlinux	00000040 bio_get_nr_vecs
40313608 g     O .bss	00000004 num_physpages
40042304 g     F .vmlinux	0000007c find_pid
4007e28c g     F .vmlinux	000000d8 file_update_time
40110548 g     F .vmlinux	00000034 klist_iter_init_node
4008ac8c g     F .vmlinux	00000034 __wait_on_buffer
40111ec4 g     F .vmlinux	00000038 mutex_lock
4012ae5c g     O .vmlinux	00000088 envp_init
40094a68 g     F .vmlinux	00000014 inotify_rm_watch
401000f4 g     F .vmlinux	00000088 attribute_container_register
4031ae0c g       *ABS*	00000000 bss_end
4005eaac g     F .vmlinux	00000028 user_shm_unlock
400c1740 g     F .vmlinux	0000000c prom_getrev
401550ac g     F .vmlinux	000000f4 uart_set_options
400b45f0 g     F .vmlinux	00000018 blk_sync_queue
400167c0 g     F .vmlinux	00000020 sbus_ioremap
400c7534 g     F .vmlinux	00000050 pci_bus_write_config_dword
40072fe8 g     F .vmlinux	000000d8 lock_rename
40011ba0 g       .vmlinux	00000000 tsetup_patch2
40012a5c g     F .vmlinux	00000024 local_irq_restore
400b0e50 g     F .vmlinux	000000fc blk_queue_start_tag
400fce6c g     F .vmlinux	0000002c class_device_create_file
4003a2c8 g     F .vmlinux	00000048 add_timer_on
4001c788 g     F .vmlinux	0000004c outsw
401035d4 g     F .vmlinux	00000038 do_map_probe
40139000 g       .vmlinux	00000000 __init_begin
401497d8  w    F .vmlinux	00000018 idle_regs
400829d8 g     F .vmlinux	00000054 wait_on_sync_kiocb
40011c50 g       .vmlinux	00000000 tsetup_patch3
40111ab8 g     F .vmlinux	00000030 io_schedule
40010348 g     F .vmlinux	0000035c name_to_dev_t
40130da8 g     O .vmlinux	00000010 color_table
40066700 g     F .vmlinux	000000b8 kmem_cache_free
40080b58 g     F .vmlinux	000000a4 release_mounts
400fd26c g     F .vmlinux	00000028 class_device_get
400c23a4 g     F .vmlinux	00000088 prom_seek
40031704 g     F .vmlinux	00000320 vprintk
40039768 g     F .vmlinux	00000070 __ptrace_link
400bf11c g     F .vmlinux	000000c4 strstrip
40055a24 g     F .vmlinux	00000008 default_unplug_io_fn
4013580c g       .vmlinux	00000000 ___fs_pte_read
4005d448 g     F .vmlinux	000000d8 get_locked_pte
4007f0c4 g     F .vmlinux	00000080 inode_double_lock
400beeb0 g     F .vmlinux	00000044 strlcpy
4012b0fc g     O .vmlinux	00000004 root_mountflags
40038ec4 g     F .vmlinux	00000104 sysctl_intvec
400520b4 g     F .vmlinux	00000010 mempool_free_pages
40055798 g     F .vmlinux	00000094 pdflush_operation
400c510c g       .vmlinux	00000000 strncmp
40011588 g       .vmlinux	00000000 restore_current
4004ef80 g     F .vmlinux	0000053c do_generic_mapping_read
40062168 g     F .vmlinux	0000002c __anon_vma_link
40088478 g     F .vmlinux	000000c4 drop_pagecache
400b5920 g     F .vmlinux	00000034 blk_register_region
4013473c g       .vmlinux	00000000 ___hs_pgdir_size
4003b3b8 g     F .vmlinux	00000038 switch_uid
40091140 g     F .vmlinux	00000098 open_bdev_excl
40154f80 g     F .vmlinux	000000a0 uart_get_console
400209ec g       .vmlinux	00000000 hypersparc_flush_cache_range
401327fc g     O .vmlinux	00000004 sunserial_current_minor
4004c92c g     F .vmlinux	00000018 rt_mutex_proxy_unlock
401319f0 g     O .vmlinux	00000200 ctrl_alt_map
40020f00 g       .vmlinux	00000000 tsunami_flush_cache_all
40303014 g     O .bss	0000001c per_cpu____cpu_data
4005efdc g     F .vmlinux	00000398 vma_adjust
4012e01c g     O .vmlinux	00000004 sysctl_vfs_cache_pressure
4007d1f8 g     F .vmlinux	00000010 d_move
400851c8 g     F .vmlinux	00000030 seq_putc
400132a8 g     F .vmlinux	0000005c sun4m_get_irqmask
400b030c g     F .vmlinux	00000038 blk_queue_max_hw_segments
400ba718 g     F .vmlinux	000000f0 bitmap_scnlistprintf
400a2694 g     F .vmlinux	0000001c sysfs_create_subdir
4007e858 g     F .vmlinux	0000002c ilookup5_nowait
403149f8 g     O .bss	00000300 prom_phys_total
403041a8 g     O .bss	00000004 num_contexts
40016a90 g     F .vmlinux	000000c8 dma_free_coherent
4030bc00  w    O .bss	00000004 xtime_lock
4030e03c g     O .bss	00000000 dma_spin_lock
400457fc  w    F .vmlinux	00000008 sys32_ipc
400457fc  w    F .vmlinux	00000008 compat_sys_ipc
400fdffc g     F .vmlinux	000001cc platform_device_add
400947b0 g     F .vmlinux	00000060 inotify_find_watch
4001b480 g     F .vmlinux	00000028 of_dev_put
40075f14 g     F .vmlinux	000000e8 fasync_helper
40131544 g     O .vmlinux	00000004 funcbufsize
400389a0 g     F .vmlinux	00000034 proc_doulongvec_minmax
400952f0 g     F .vmlinux	000001bc sys_inotify_add_watch
400aee54 g     F .vmlinux	00000060 elevator_exit
400731bc g     F .vmlinux	00000244 may_open
4006e188 g     F .vmlinux	00000030 copy_strings_kernel
400af0b0 g     F .vmlinux	000000c8 elv_dispatch_sort
400bee7c g     F .vmlinux	00000034 strncpy
4030e060 g     O .bss	00000004 sysctl_panic_on_oom
400be410 g     F .vmlinux	000003e4 rb_erase
40115da4 g     O .vmlinux	0000006c ramfs_file_operations
401551c0 g     F .vmlinux	00000024 system_bus_init
40040980 g     F .vmlinux	000001a8 getrusage
40302bb0 g     O .bss	00000020 cpu_leds
40110424 g     F .vmlinux	00000030 klist_add_head
40134940 g       .vmlinux	00000000 ___fs_mk_pte_io
4007115c g     F .vmlinux	0000001c vfs_permission
4014e960 g     F .vmlinux	0000013c prom_init
400856d0 g     F .vmlinux	000000cc vfs_getxattr
400448f0 g     F .vmlinux	00000154 exit_itimers
400cf2dc g     F .vmlinux	00000174 register_framebuffer
4003678c g     F .vmlinux	00000084 __tasklet_schedule
40081604 g     F .vmlinux	000000d4 mark_mounts_for_expiry
4004438c g     F .vmlinux	00000108 sys_timer_gettime
40018188 g     F .vmlinux	00000044 sparc_breakpoint
40042bb8 g     F .vmlinux	00000054 rcu_pending
400c22a4 g     F .vmlinux	0000008c prom_devopen
4001cd54 g     F .vmlinux	00000008 pcic_present
4030e0a0 g     O .bss	00000004 laptop_mode
40115a98 g     O .vmlinux	0000003c ext2_aops
4012e028 g     O .vmlinux	00000008 inode_unused
40144ca4 g     F .vmlinux	000001e0 srmmu_early_allocate_ptable_skeleton
4013584c g       .vmlinux	00000000 ___f___swp_offset
400cc8c8 g     F .vmlinux	0000011c pci_assign_resource_fixed
40089f94 g     F .vmlinux	00000418 sys_tee
4012d16c g     O .vmlinux	0000000c uts_sem
40302a8c g     O .bss	00000004 static_irq_count
400751f4 g     F .vmlinux	000000b0 page_readlink
4004352c g     F .vmlinux	00000090 param_set_bool
400b0d60 g     F .vmlinux	000000f0 blk_queue_end_tag
40105ad8 g     F .vmlinux	0000002c ps2_is_keyboard_id
40082f54 g     F .vmlinux	0000002c aio_put_req
400457fc  w    F .vmlinux	00000008 sys_semop
400946e0 g     F .vmlinux	000000d0 inotify_destroy
40152854 g     F .vmlinux	0000006c pci_assign_unassigned_resources
4006a390 g     F .vmlinux	000000bc rw_verify_area
401342f8 g       .vmlinux	00000000 ___hs_sparc_unmapped_base
40315304 g     O .bss	00000000 prom_lock
400457fc  w    F .vmlinux	00000008 sys_getsockopt
40031b5c g     F .vmlinux	0000007c console_device
400b0bf4 g     F .vmlinux	000000a4 blk_queue_resize_tags
4005b20c g     F .vmlinux	000000a8 vm_normal_page
40017040 g     F .vmlinux	00000018 sbus_dma_sync_sg_for_device
40069f08 g     F .vmlinux	00000034 sys_vhangup
4009d9e0 g     F .vmlinux	0000002c proc_tty_unregister_driver
40069ca8 g     F .vmlinux	000000e8 do_sys_open
400fca80 g     F .vmlinux	00000034 driver_unregister
400bb3a0 g     F .vmlinux	00000138 find_next_zero_bit
400b09cc g     F .vmlinux	00000034 blk_queue_segment_boundary
40088564 g     F .vmlinux	00000074 drop_caches_sysctl_handler
40111500 g     F .vmlinux	00000138 wait_for_completion_interruptible
4030d458 g     O .bss	00000004 cad_pid
400549e4 g     F .vmlinux	00000038 wakeup_pdflush
00000000 g       *ABS*	00000000 ___s_user_ptrs_per_pgd
400d9a18 g     F .vmlinux	00000030 find_font
400f2b34 g     F .vmlinux	000000e0 unregister_con_driver
400fdf10 g     F .vmlinux	0000005c platform_device_alloc
40140d58 g     F .vmlinux	00000084 sbus_setup_iommu
4012e044 g     O .vmlinux	00000010 mountstats_op
40100b30 g     F .vmlinux	00000018 transport_configure_device
400121ac g     F .vmlinux	00000008 syscall_trace_exit
400fdb50 g     F .vmlinux	00000110 class_interface_unregister
40073400 g     F .vmlinux	00000704 open_namei
4014c574 g     F .vmlinux	000003cc alloc_large_system_hash
4030e134 g     O .bss	00000004 vm_total_pages
40032cec g     F .vmlinux	000000b8 exit_fs
400935b4 g     F .vmlinux	00000460 mpage_writepages
400b9f70 g     F .vmlinux	0000007c __bitmap_subset
400cc264 g     F .vmlinux	00000228 pci_map_rom
40307090 g     O .bss	00000004 files_cachep
4009c1e4 g     F .vmlinux	00000194 proc_readdir
4001ad90 g     F .vmlinux	0000005c __down_trylock
40130e40 g     O .vmlinux	00000004 accent_table_size
400afed4 g     F .vmlinux	000000bc elv_unregister
40313c60 g     O .bss	0000001c inodes_stat
400757b8 g     F .vmlinux	00000030 sys_dup
4004f73c g     F .vmlinux	000000c8 sys_readahead
400ffd08 g     F .vmlinux	000000b0 devres_open_group
400cb010 g     F .vmlinux	0000010c pci_find_device
40020cd8 g       .vmlinux	00000000 hypersparc_flush_tlb_page
4013584c g       .vmlinux	00000000 ___f_pte_alloc_one_kernel
403042dc g     O .bss	00000004 phys_base
400309bc g     F .vmlinux	00000164 panic
400490e8 g     F .vmlinux	0000005c ntp_clear
400fa730 g     F .vmlinux	00000014 sysdev_remove_file
40300040 g       *ABS*	00000000 bss_start
40063938 g     F .vmlinux	00000070 vmap
4007c9c8 g     F .vmlinux	0000004c d_alloc_root
400678a8 g     F .vmlinux	00000008 kmem_cache_name
40014edc g     F .vmlinux	00000010 sys_sigpause
4001af70 g     F .vmlinux	00000058 of_find_property
40044d8c g     F .vmlinux	00000138 sys_clock_nanosleep
4002def0 g     F .vmlinux	00000014 idle_task
40032200 g     F .vmlinux	00000094 profile_tick
40085cfc g     F .vmlinux	00000040 sys_fgetxattr
400aa840 g     F .vmlinux	000000a4 ext2_get_parent
400155cc g     F .vmlinux	000001a0 svr4_setcontext
4006912c g     F .vmlinux	00000010 sys_truncate64
401356a0 g       .vmlinux	00000000 ___is_page_kernel
4006bc98 g     F .vmlinux	000002b4 sget
40079e24 g     F .vmlinux	00000064 setlease
40055074 g     F .vmlinux	000003e8 generic_writepages
4009b0ec g     F .vmlinux	000001a4 proc_flush_task
401552b0 g     F .vmlinux	00000050 platform_bus_init
4004ec04 g     F .vmlinux	000000d8 find_or_create_page
400400e0 g     F .vmlinux	00000160 set_current_groups
40000308 g     F .stage2	0000006c leon3_ahbslv_scan
4012b424 g       .vmlinux	00000000 sys_call_table
400167e0 g     F .vmlinux	00000038 ioremap
40103334 g     F .vmlinux	0000004c put_mtd_device
40115b28 g     O .vmlinux	00000054 ext2_dir_inode_operations
4008ef50 g     F .vmlinux	0000003c bio_add_page
40103078 g     F .vmlinux	00000084 register_mtd_user
400e0844 g     F .vmlinux	00000050 tty_ldisc_flush
400457fc  w    F .vmlinux	00000008 sys_migrate_pages
4001d404 g     F .vmlinux	000003e0 do_sparc_fault
40304374 g     O .bss	00000004 is_hypersparc
40134b94 g       .vmlinux	00000000 ___fs_flush_tlb_all
4002ecfc g     F .vmlinux	00000048 get_task_mm
400fcd50 g     F .vmlinux	00000064 class_unregister
400bc284 g     F .vmlinux	00000094 kobject_cleanup
400bc7f4 g     F .vmlinux	00000020 kset_init
4010360c g     F .vmlinux	00000038 map_destroy
400b4c20 g     F .vmlinux	0000007c blk_register_queue
400f2c14 g     F .vmlinux	000002f0 take_over_console
400982dc g     F .vmlinux	000000c0 get_vmalloc_info
4014b9e0 g     F .vmlinux	00000014 reserve_bootmem_node
4013bed8 g     F .vmlinux	00001144 rd_load_image
4030434c g     O .bss	00000004 srmmu_nocache_pool
400feb2c g     F .vmlinux	00000098 kobj_map_init
400c11b0 g     F .vmlinux	00000328 prom_query_output_device
4003fa80 g     F .vmlinux	000000b0 sys_setfsuid
40016d9c g     F .vmlinux	00000124 sbus_alloc_consistent
40087020 g     F .vmlinux	00000034 simple_transaction_read
400877b4 g     F .vmlinux	000000a8 write_inode_now
400fe1e0 g     F .vmlinux	0000006c platform_device_del
40017874 g     F .vmlinux	00000008 sys_getpagesize
400a0090 g     F .vmlinux	00000108 del_gendisk
4002d0ec g     F .vmlinux	00000210 wake_up_new_task
400be9e4 g     F .vmlinux	00000064 reciprocal_value
4013584c g       .vmlinux	00000000 ___f_mmu_release_scsi_sgl
400c3de8 g       .vmlinux	00000000 memcmp
4030b9a0 g     O .bss	00000004 prof_on
4012f2ac g     O .vmlinux	00000008 pci_root_buses
4013584c g       .vmlinux	00000000 ___f_flush_tlb_page
40048ea0 g     F .vmlinux	0000005c cleanup_srcu_struct
400a1d84 g     F .vmlinux	0000007c sysfs_add_file
400a20ac g     F .vmlinux	00000044 sysfs_remove_file_from_group
400c66c8 g     F .vmlinux	00000020 srandom32
400cfb40 g     F .vmlinux	000000cc fb_alloc_cmap
4004eb3c g     F .vmlinux	000000c8 find_lock_page
400a6334 g     F .vmlinux	000001b0 ext2_set_link
400ddafc g     F .vmlinux	000000ac console_print_LEON
400fda1c g     F .vmlinux	00000134 class_interface_register
400ec408 g     F .vmlinux	0000004c con_free_unimap
400a6d8c g     F .vmlinux	00000260 ext2_empty_dir
40010ba4 g       .vmlinux	00000000 vac_hwflush_patch2_on
400a3e7c g     F .vmlinux	0000011c sysfs_create_group
400663b0 g     F .vmlinux	00000018 slab_is_available
400a2de0 g     F .vmlinux	0000014c sysfs_move_dir
40080d9c g     F .vmlinux	00000214 sys_umount
4003eef0 g     F .vmlinux	000001fc sys_reboot
40038cc0 g     F .vmlinux	00000204 sysctl_string
40072734 g     F .vmlinux	00000104 link_path_walk
40135788 g       .vmlinux	00000000 ___fs_clear_profile_irq
40056a64 g     F .vmlinux	00000070 lru_cache_add_active
400637dc g     F .vmlinux	0000010c __vunmap
400e0658 g     F .vmlinux	0000007c tty_ldisc_deref
400c9254 g     F .vmlinux	00000080 pcim_pin_device
4002e770 g     F .vmlinux	000000b8 sys_sched_rr_get_interval
40302a0c g     O .bss	00000080 static_irqaction
400363fc g     F .vmlinux	000000d0 __do_softirq
4007cf70 g     F .vmlinux	00000010 d_rehash
40045184 g     F .vmlinux	00000088 kthread_stop
4013584c g       .vmlinux	00000000 ___f_get_pgd_fast
400114d4 g       .vmlinux	00000000 flush_patch_exception
4006287c g     F .vmlinux	00000030 page_add_anon_rmap
4002d838 g     F .vmlinux	00000058 account_user_time
4003fb30 g     F .vmlinux	0000009c sys_setfsgid
40102ea0 g     F .vmlinux	00000120 add_mtd_device
400143cc g     F .vmlinux	00000050 machine_power_off
400c0d04 g     F .vmlinux	0000002c sscanf
400c1ec8 g     F .vmlinux	0000028c prom_finddevice
40300000 g       .vmlinux	00000000 __init_end
40031a24 g     F .vmlinux	0000002c printk
4003f570 g     F .vmlinux	000000d0 sys_setuid
400fa0bc g     F .vmlinux	00000074 device_find_child
4007fea8 g     F .vmlinux	00000168 sys_sysfs
400dcaf8 g     F .vmlinux	000001a4 amba_get_free_ahbslv_devices
40036124 g     F .vmlinux	00000008 clock_t_to_jiffies
400461c4 g     F .vmlinux	00000048 posix_cpu_timers_exit_group
4005f65c g     F .vmlinux	0000008c find_vma_prev
40011c60 g       .vmlinux	00000000 tsetup_patch4
40047bec g     F .vmlinux	00000024 __mutex_init
4011057c g     F .vmlinux	00000014 klist_iter_init
40100ae8 g     F .vmlinux	00000018 transport_add_device
4013584c g       .vmlinux	00000000 ___f_pmd_bad
400c3ec4 g     F .vmlinux	00000000 __memcpy
400fa7bc g     F .vmlinux	00000014 sysdev_class_remove_file
400112c4 g       .vmlinux	00000000 bsd_syscall
400c2514 g       .vmlinux	00000000 ___atomic24_add
4003a6b8 g     F .vmlinux	00000018 run_local_timers
40035a90 g     F .vmlinux	00000074 current_fs_time
400cfa14 g     F .vmlinux	00000044 fb_default_cmap
4012f178 g     O .vmlinux	00000004 prom_ptot_ptr
4012dfd4 g     O .vmlinux	00000004 leases_enable
40041dd0 g     F .vmlinux	0000001c cancel_rearming_delayed_work
40091240 g     F .vmlinux	000000a8 check_disk_change
400a7128 g     F .vmlinux	00000258 ext2_free_inode
40319018 g     O .bss	00000001 vt_dont_switch
4008f8b0 g     F .vmlinux	000000cc bio_check_pages_dirty
400e6d68 g     F .vmlinux	00000070 tty_get_baud_rate
40014160 g     F .vmlinux	00000130 cpu_idle
40111ffc g     F .vmlinux	00000038 mutex_lock_interruptible
4008785c g     F .vmlinux	00000010 sync_inode
4031ac88 g     O .bss	00000004 sbus_root
400c0f1c g     F .vmlinux	00000024 prom_putchar
40018fec g     F .vmlinux	0000004c install_linux_ticker
400c0f40 g     F .vmlinux	00000270 prom_query_input_device
400baf20 g     F .vmlinux	00000080 get_option
40113cfc g     O .vmlinux	0000006c write_fifo_fops
400407a0 g     F .vmlinux	00000074 sys_getrlimit
40035d94 g     F .vmlinux	00000010 jiffies_to_msecs
400bef34 g     F .vmlinux	00000058 strncat
400d9a48 g     F .vmlinux	0000005c get_default_font
4012b2e0 g     O .vmlinux	00000004 scons_pwroff
4001072c g       .vmlinux	00000000 bad_instruction
400e2fcc g     F .vmlinux	00000028 do_SAK
4014a148 g     F .vmlinux	00000040 spawn_ksoftirqd
403042fc g     O .bss	00000010 pgt_quicklists
4012deb8 g     O .vmlinux	0000000c files_stat
4012e030 g     O .vmlinux	00000008 inode_in_use
400457fc  w    F .vmlinux	00000008 sys_nfsservctl
4002e9ec g     F .vmlinux	00000038 in_sched_functions
4031a824 g     O .bss	00000004 do_poke_blanked_console
401551fc g     F .vmlinux	0000004c classes_init
40069b40 g     F .vmlinux	000000e0 get_unused_fd
4006e538 g     F .vmlinux	00000674 flush_old_exec
400cf640 g     F .vmlinux	000001b4 fb_get_options
40018500 g       .vmlinux	00000000 sunos_getpid
40072ba4 g     F .vmlinux	00000014 path_lookup_open
40063bfc g     F .vmlinux	0000001c vmalloc_exec
4006eed0 g     F .vmlinux	000001cc do_execve
4004c910 g     F .vmlinux	0000001c rt_mutex_init_proxy_locked
4012f374 g     O .vmlinux	00000004 pci_cardbus_io_size
403042e8 g     O .bss	00000004 sparc_valid_addr_bitmap
40107320 g     F .vmlinux	00000078 input_close_device
4000d014 g       .vmlinux	00000000 sparc_ramdisk_size
4007124c g     F .vmlinux	00000034 release_open_intent
40300000 g     O .vmlinux	00000000 tasklist_lock
40013c24 g     F .vmlinux	0000019c sun4d_request_irq
40011554 g       .vmlinux	00000000 kuw_patch1
400456f0 g     F .vmlinux	000000f4 kfifo_alloc
401071cc g     F .vmlinux	00000028 input_grab_device
400c4624 g       .vmlinux	00000000 __memset_start
4014bf38 g     F .vmlinux	000001c4 init_currently_empty_zone
40045680 g     F .vmlinux	00000070 kfifo_init
4006256c g     F .vmlinux	00000118 page_referenced
400db78c g     F .vmlinux	00000510 cfb_imageblit
4008a45c g     F .vmlinux	0000006c file_fsync
400c6d38 g     F .vmlinux	0000002c hweight8
4005ea40 g     F .vmlinux	0000006c user_shm_lock
40056dc0 g     F .vmlinux	0000003c do_invalidatepage
400c7250 g     F .vmlinux	00000008 pci_iounmap
4008fa20 g     F .vmlinux	00000044 bio_pair_release
00000000 g       *ABS*	00000000 ___a_pte_writei
4012f050 g     O .vmlinux	00000100 _ctype
4002110c g       .vmlinux	00000000 swift_flush_cache_page
400b1b74 g     F .vmlinux	00000014 blk_put_queue
400c9030 g     F .vmlinux	00000054 pci_enable_device_bars
40004000 g       .vmlinux	00000000 _text
40036e18 g     F .vmlinux	00000010 ____request_resource
4006db0c g     F .vmlinux	00000054 inode_add_bytes
400f9dc8 g     F .vmlinux	00000018 device_register
403143d8 g     O .bss	00000004 prom_vers
40110454 g     F .vmlinux	00000030 klist_add_tail
40070df0 g     F .vmlinux	00000100 getname
400c8e0c g     F .vmlinux	00000198 pci_restore_state
40002000 g       .stage2	00000000 _bootloader_ph
4008f778 g     F .vmlinux	00000088 bio_set_pages_dirty
4006d09c g     F .vmlinux	00000024 cd_forget
40030d84 g     F .vmlinux	00000420 do_syslog
40011b98 g       .vmlinux	00000000 tsetup_patch1
40017b18 g     F .vmlinux	00000048 sparc_brk
4002110c g       .vmlinux	00000000 swift_flush_page_for_dma
400b9ef4 g     F .vmlinux	0000007c __bitmap_intersects
400f9de0 g     F .vmlinux	00000244 device_del
40134648 g       .vmlinux	00000000 ___fs_do_check_pgt_cache
400c66b0 g     F .vmlinux	00000018 random32
4000d00a g       .vmlinux	00000000 root_flags
4012d3f8 g     O .vmlinux	00000004 time_esterror
40131548 g     O .vmlinux	00000004 funcbufptr
400487ac g     F .vmlinux	00000090 sys_nanosleep
40313d5c g     O .bss	00000004 proc_net
4003ca3c g     F .vmlinux	000000a0 __group_send_sig_info
40059298 g     F .vmlinux	000000c4 vma_prio_tree_add
400945b8 g     F .vmlinux	00000074 inotify_inode_is_dead
401434fc g     F .vmlinux	00000134 auxio_probe
4004cc9c g     F .vmlinux	0000003c sys_setuid16
4012b32c g     O .vmlinux	00000010 cpuinfo_op
400bbdec g     F .vmlinux	00000040 idr_destroy
401380b4 g       .vmlinux	00000000 __stop___ex_table
4006c5a4 g     F .vmlinux	0000001c emergency_remount
40113b78 g     O .vmlinux	00000010 slabinfo_op
400b56ac g     F .vmlinux	00000070 blkdev_show
4013566c g       .vmlinux	00000000 ___is_pte_modify_mask
40054b80 g     F .vmlinux	00000060 dirty_writeback_centisecs_handler
40093018 g     F .vmlinux	00000060 mpage_readpage
400b1c70 g     F .vmlinux	00000014 blk_alloc_queue
40045b58 g     F .vmlinux	00000024 posix_cpu_clock_set
40082358 g     F .vmlinux	00000088 set_fs_pwd
400181cc g     F .vmlinux	00000154 sparc_sigaction
40031a98 g     F .vmlinux	000000c4 console_unblank
4006a148 g     F .vmlinux	00000098 default_llseek
4012e004 g     O .vmlinux	00000018 dentry_stat
4006c680 g     F .vmlinux	00000030 kill_litter_super
401045cc g     F .vmlinux	000000a0 __serio_register_driver
40010ae0 g       .vmlinux	00000000 getcc_trap_handler
40069300 g     F .vmlinux	00000080 sys_fchdir
40022d6c g     F .vmlinux	0000002c sun4c_pte_offset_kernel
4005deec g     F .vmlinux	0000002c vmalloc_to_pfn
4030300c g     O .bss	00000004 master_l10_limit
400c9b94 g     F .vmlinux	00000014 pci_set_dma_mask
401315f0 g     O .vmlinux	00000400 key_maps
40135688 g       .vmlinux	00000000 ___fs___swp_entry
400a1fc4 g     F .vmlinux	000000d0 sysfs_chmod_file
4001cd5c g     F .vmlinux	00000020 get_auxio
400c790c g     F .vmlinux	00000080 pci_unblock_user_cfg_access
400596ac g     F .vmlinux	00000044 all_vm_events
4006c214 g     F .vmlinux	000000a0 user_get_super
4013584c g       .vmlinux	00000000 ___f_pmd_set
40053ca8 g     F .vmlinux	00000014 nr_free_pagecache_pages
4009c794 g     F .vmlinux	00000018 proc_mkdir
40087c64 g     F .vmlinux	000000a0 sync_inodes_sb
40013e8c g     F .vmlinux	00000020 sparc_leon_eirq_get
400f1638 g     F .vmlinux	00000030 mouse_reporting
4005e13c g     F .vmlinux	000003f8 sys_mincore
4030bc10 g     O .bss	00000008 xtime
40313d08 g     O .bss	00000004 buffer_heads_over_limit
40034d40 g     F .vmlinux	00000014 sys_waitpid
4008f5d4 g     F .vmlinux	00000028 bio_map_user
40010968 g       .vmlinux	00000000 do_reg_access
40017028 g     F .vmlinux	00000018 sbus_dma_sync_sg_for_cpu
400dd68c g     F .vmlinux	00000050 leonuart_int
4002cf10 g     F .vmlinux	00000020 task_curr
400c6cd0 g     F .vmlinux	00000020 hweight64
4008e894 g     F .vmlinux	00000054 bio_init
40016ec0 g     F .vmlinux	000000c4 sbus_free_consistent
40016c74 g     F .vmlinux	0000002c dma_sync_single_for_cpu
400764e0 g     F .vmlinux	00000058 sys_ioctl
4012972c g       .vmlinux	00000000 __start___kcrctab
4008e844 g     F .vmlinux	00000038 bio_free
400cb16c g     F .vmlinux	0000015c pci_get_subsys
40016d24 g     F .vmlinux	00000058 dma_sync_sg_for_device
400c2958 g       .vmlinux	00000000 __copy_1page
4004de14 g     F .vmlinux	00000014 touch_softlockup_watchdog
40093cf0 g     F .vmlinux	0000006c ioprio_best
40108cf4 g     F .vmlinux	000000e0 input_unregister_handler
40103380 g     F .vmlinux	000000b8 default_mtd_writev
40100640 g     F .vmlinux	0000005c attribute_container_remove_attrs
4030d7dc g     O .bss	00000004 time_adjust
400c1d28 g     F .vmlinux	00000024 prom_getbool
400fbfdc g     F .vmlinux	0000002c device_bind_driver
4004cf80 g     F .vmlinux	0000003c sys_setfsuid16
40048fc4 g     F .vmlinux	00000008 srcu_batches_completed
400608d0 g     F .vmlinux	0000024c do_brk
400ff700 g     F .vmlinux	00000080 dmam_free_coherent
400c4624 g       .vmlinux	00000000 __memset
4012d4e8 g     O .vmlinux	00000058 clocksource_jiffies
403074d4 g     O .bss	00000004 tainted
4012c518 g     O .vmlinux	0000001c ioport_resource
4013584c g       .vmlinux	00000000 ___f_bus_do_settimeofday
4005935c g     F .vmlinux	00000038 vma_prio_tree_insert
4004f904 g     F .vmlinux	000003b4 filemap_nopage
40300040 g       *ABS*	00000000 __bss_start
40141e94 g     F .vmlinux	0000004c sbus_time_init
40140ddc g     F .vmlinux	00000050 sbus_setup_arch_props
4013433c g       .vmlinux	00000000 ___fs_clear_clock_irq
400c28b8 g       .vmlinux	00000000 bzero_1page
4005fad0 g     F .vmlinux	00000030 arch_unmap_area_topdown
4012966c g       .vmlinux	00000000 __end_pci_fixups_final
4001576c g     F .vmlinux	00000cd4 do_signal
40061ef0 g     F .vmlinux	00000188 sys_msync
40134a80 g       .vmlinux	00000000 ___ss_ptrs_per_pmd
400c2154 g     F .vmlinux	00000050 prom_node_has_property
400fb8b4 g     F .vmlinux	00000154 bus_add_driver
400e9278 g     F .vmlinux	00000080 reset_vc
40019318 g     F .vmlinux	00000008 ptrace_disable
40302b94 g     O .bss	00000004 sun4m_timers
400c4624 g       .vmlinux	00000000 memset
40012d5c g     F .vmlinux	000000d8 unexpected_irq
4004b660 g     F .vmlinux	00000164 exit_robust_list
4005ac8c g     F .vmlinux	00000004 pgd_clear_bad
400316ec g     F .vmlinux	00000018 resume_console
4006af04 g     F .vmlinux	0000006c vfs_readv
4012f378 g     O .vmlinux	00000004 pci_pm_d3_delay
40057774 g     F .vmlinux	00000068 set_shrinker
40048c2c g     F .vmlinux	0000002c get_task_namespaces
400a4470 g     F .vmlinux	00000060 devpts_pty_kill
4006ac4c g     F .vmlinux	00000118 rw_copy_check_uvector
4013584c g       .vmlinux	00000000 ___f_clear_profile_irq
40040324 g     F .vmlinux	00000138 sys_setgroups
400b02d4 g     F .vmlinux	00000038 blk_queue_max_phys_segments
400783e4 g     F .vmlinux	0000005c locks_mandatory_locked
4014963c g     F .vmlinux	0000000c sched_init_smp
4001151c g       .vmlinux	00000000 kill_user_windows
4014e78c g     F .vmlinux	0000003c prio_tree_init
4012972c g       .vmlinux	00000000 __stop___kcrctab_unused_gpl
400457fc  w    F .vmlinux	00000008 sys_swapon
4006c8fc g     F .vmlinux	000000d0 get_sb_single
400f0ae4 g     F .vmlinux	00000038 vc_cons_allocated
40047754 g     F .vmlinux	000000f4 set_process_cpu_timer
4001e2ac g     F .vmlinux	00000090 calc_max_low_pfn
400ae48c g     F .vmlinux	0000001c cap_capset_set
40100420 g     F .vmlinux	00000068 attribute_container_add_attrs
40021240 g     F .vmlinux	000000f0 kmap_atomic_to_page
4012e820 g     O .vmlinux	0000000c ktype_part
400b6240 g     F .vmlinux	00000028 set_device_ro
400e0dc0 g     F .vmlinux	00000060 redirected_tty_write
400393a8 g     F .vmlinux	00000038 __capable
400fd7d8 g     F .vmlinux	00000194 class_device_del
40158808 g     O .vmlinux	00000018 logo_linux_vga16
400c54dc g       .vmlinux	00000000 .udiv_patch
401352c8 g       .vmlinux	00000000 ___fs_pgoff_to_pte
4010d514 g     F .vmlinux	00002e2c hidinput_connect
400f2f04 g     F .vmlinux	00000010 give_up_console
400632cc g     F .vmlinux	00000208 map_vm_area
4014efc4 g     F .vmlinux	00000088 prom_ranges_init
40020be0 g       .vmlinux	00000000 hypersparc_flush_page_to_ram
400911f0 g     F .vmlinux	00000050 __invalidate_device
400cb2e4 g     F .vmlinux	00000050 pci_get_bus_and_slot
40079e88 g     F .vmlinux	00000134 fcntl_setlease
40010e90 g       .vmlinux	00000000 sys_ptrace
400457fc  w    F .vmlinux	00000008 sys_vm86old
40139cfc g     F .vmlinux	00000328 start_kernel
40304350 g     O .bss	00000004 vac_cache_size
40313660 g     O .bss	00000000 vmlist_lock
400e8db0 g     F .vmlinux	000001a8 misc_register
4007584c g     F .vmlinux	0000002c __f_setown
400c718c g     F .vmlinux	00000008 ioport_unmap
4001c7d4 g     F .vmlinux	00000064 outsl
40053808 g     F .vmlinux	000002fc __alloc_pages
400af548 g     F .vmlinux	000001fc elv_insert
40036fa0 g     F .vmlinux	00000130 insert_resource
400cda30 g     F .vmlinux	000001a8 fb_prepare_logo
400457fc  w    F .vmlinux	00000008 sys_shmat
40092ec4 g     F .vmlinux	00000154 mpage_readpages
400f08a8 g     F .vmlinux	0000023c redraw_screen
40021198 g     F .vmlinux	000000a8 kmap_atomic
400744ac g     F .vmlinux	00000018 sys_unlink
40040528 g     F .vmlinux	000000e4 sys_sethostname
400eb2f0 g     F .vmlinux	000000ac change_console
40085e6c g     F .vmlinux	0000004c sys_llistxattr
400b9d34 g     F .vmlinux	0000004c __bitmap_or
40009000 g       .vmlinux	00000000 pg3
4006a57c g     F .vmlinux	0000013c vfs_read
400af05c g     F .vmlinux	00000054 elv_rb_find
400bef8c g     F .vmlinux	00000058 strlcat
400c6cf0 g     F .vmlinux	00000048 hweight16
400863ac g     F .vmlinux	00000184 dcache_dir_lseek
400c98f8 g     F .vmlinux	00000068 pci_set_master
4006e4b8 g     F .vmlinux	00000040 kernel_read
401112e0 g     F .vmlinux	000000f4 wait_for_completion
4007dfa4 g     F .vmlinux	00000044 __insert_inode_hash
4013584c g       .vmlinux	00000000 ___f_sun4c_flush_page
00000000 g       *ABS*	00000000 ___i_page_none
400bc93c g     F .vmlinux	0000004c subsystem_register
4012972c g       .vmlinux	00000000 __stop___ksymtab_gpl
4001e78c g     F .vmlinux	00000008 sort_extable
4003d6e0 g     F .vmlinux	000000c8 do_sigpending
400e6d58 g     F .vmlinux	00000010 tty_termios_input_baud_rate
4001ae1c g     F .vmlinux	00000054 of_find_node_by_path
400a9e50 g     F .vmlinux	00000608 ext2_truncate
40313618 g     O .bss	00000004 sysctl_overcommit_memory
40051fd8 g     F .vmlinux	0000001c mempool_alloc_slab
4001a528 g     F .vmlinux	000003b8 user_unaligned_trap
401040ec g     F .vmlinux	0000002c serio_unregister_port
4012e1d8 g     O .vmlinux	000000b0 inotify_table
40319320 g     O .bss	00000004 kmsg_redirect
4004350c g     F .vmlinux	00000020 param_get_charp
40010ee8 g       .vmlinux	00000000 sys_sigstack
40087db4 g     F .vmlinux	00000044 sync_inodes
4012d088 g     O .vmlinux	00000008 jiffies_64
40104118 g     F .vmlinux	00000048 serio_unregister_child_port
40141ef0 g     F .vmlinux	00000148 cpu_probe
40044b4c g     F .vmlinux	00000118 sys_clock_gettime
40135854 g       .vmlinux	00000000 __ret_efault
4004b7c4 g     F .vmlinux	00000a5c do_futex
4030e058 g     O .bss	00000004 min_low_pfn
40095128 g     F .vmlinux	000001c8 sys_inotify_init
400dca70 g     F .vmlinux	00000088 amba_get_number_ahbslv_devices
40315990 g     O .bss	00000004 isa_dma_bridge_buggy
4006f9e4 g     F .vmlinux	000000a0 generic_pipe_buf_map
4002da40 g     F .vmlinux	00000014 default_wake_function
40155f28 g     F .vmlinux	00000158 init_one_dvma
40110e90 g       .vmlinux	00000000 patchme_store_new_current
400c1730 g     F .vmlinux	00000010 prom_version
4003e704 g     F .vmlinux	00000010 atomic_notifier_call_chain
40032050 g     F .vmlinux	00000050 printk_timed_ratelimit
400652d4 g     F .vmlinux	000002d4 shmem_unuse
401353f8 g       .vmlinux	00000000 ___fs_pte_free
4003cc2c g     F .vmlinux	00000010 send_group_sig_info
40315708 g     O .bss	00000140 promlib_obio_ranges
40074570 g     F .vmlinux	000000f8 sys_symlinkat
401315ec g     O .vmlinux	00000004 keymap_count
400fe684 g     F .vmlinux	00000150 dma_get_required_mask
40032030 g     F .vmlinux	00000020 printk_ratelimit
401473d0 g     F .vmlinux	00000268 ld_mmu_iommu
40010ce0 g       .vmlinux	00000000 num_context_patch1
4002cf30 g     F .vmlinux	00000014 weighted_cpuload
400444c4 g     F .vmlinux	000002fc sys_timer_settime
4003c964 g     F .vmlinux	000000d8 send_group_sigqueue
400fd294 g     F .vmlinux	00000028 class_device_put
400457fc  w    F .vmlinux	00000008 sys_kexec_load
40073f28 g     F .vmlinux	000000dc sys_mkdirat
40112a30 g       .vmlinux	00000000 __lock_text_start
400184d4 g     F .vmlinux	0000002c kernel_execve
400c34e4 g       .vmlinux	00000000 __copy_user
40106b70 g     F .vmlinux	00000588 input_event
400c15b8 g     F .vmlinux	000000b0 prom_cmdline
4012dd00 g     O .vmlinux	00000004 sysctl_max_map_count
40313d14 g     O .bss	00000004 bio_split_pool
400af020 g     F .vmlinux	0000003c elv_rb_del
4006a2cc g     F .vmlinux	000000c4 sys_llseek
400bb0f8 g     F .vmlinux	00000020 _atomic_dec_and_lock
400ec6b0 g     F .vmlinux	000000cc con_clear_unimap
400324f0 g     F .vmlinux	00000314 release_task
40041b58 g     F .vmlinux	00000130 __create_workqueue
4001b150 g     F .vmlinux	00000054 of_n_addr_cells
4012d260 g     O .vmlinux	00000004 pid_max_max
40059674 g     F .vmlinux	00000008 next_online_pgdat
400becd8 g     F .vmlinux	000000e0 __downgrade_write
4030b9a4 g     O .bss	00000004 timer_hook
4030707c g     O .bss	00000004 per_cpu__process_counts
400c0ef8 g     F .vmlinux	00000024 prom_getchar
4003c5c4 g     F .vmlinux	00000100 send_sigqueue
400594f0 g     F .vmlinux	00000030 __kzalloc
40068b78 g     F .vmlinux	00000090 sys_fstatfs
4001b218 g     F .vmlinux	000000dc of_set_property
40302fd0 g     O .bss	00000004 idprom
400353b4 g     F .vmlinux	00000088 alarm_setitimer
40055db8 g     F .vmlinux	00000090 force_page_cache_readahead
400d18fc g     F .vmlinux	000007f0 fb_find_mode_cvt
401155f0 g     O .vmlinux	0000006c sysfs_dir_operations
4006d7a0 g     F .vmlinux	0000003c sys_newfstat
400c19ec g     F .vmlinux	00000030 prom_apply_obio_ranges
40144e84 g     F .vmlinux	000001e8 srmmu_nocache_init
400502a8 g     F .vmlinux	00000078 should_remove_suid
4008bad4 g     F .vmlinux	00000070 invalidate_bdev
400e92f8 g     F .vmlinux	00000048 vc_SAK
400493d4 g     F .vmlinux	000007bc do_adjtimex
4001e47c g     F .vmlinux	0000008c free_initrd_mem
40016b78 g     F .vmlinux	0000002c dma_unmap_single
4006b5f4 g     F .vmlinux	0000002c file_kill
4003dea8 g     F .vmlinux	00000078 sys_rt_sigqueueinfo
40038bac g     F .vmlinux	00000038 proc_dointvec_userhz_jiffies
400be7f4 g     F .vmlinux	0000002c rb_first
40010b1c g       .vmlinux	00000000 linux_trap_nmi_sun4c
40041d90 g     F .vmlinux	00000040 cancel_rearming_delayed_workqueue
40021184 g     F .vmlinux	00000014 kunmap_atomic
4001c41c g     F .vmlinux	000001d8 gptimer_gptimerShow
400c5230 g       .vmlinux	00000000 __strncpy_from_user
400cf4fc g     F .vmlinux	00000048 fb_set_suspend
40040240 g     F .vmlinux	000000e4 sys_getgroups
4012c47c g     O .vmlinux	00000004 printk_ratelimit_jiffies
40302c7c g     O .bss	00000004 current_set
40302ffc g     O .bss	00000000 mostek_lock
400747b4 g     F .vmlinux	00000108 sys_linkat
4004516c g     F .vmlinux	00000018 kthread_bind
4002db94 g     F .vmlinux	00000048 complete_all
40134120 g       .vmlinux	00000000 ___fs_flush_cache_all
401119e4 g     F .vmlinux	0000004c cond_resched
4007ce04 g     F .vmlinux	000000dc d_delete
401143bc g     O .vmlinux	0000003c def_blk_aops
4012dd04 g     O .vmlinux	00000004 sysctl_overcommit_ratio
4012dc70 g     O .vmlinux	00000004 dirty_background_ratio
40018530 g       .vmlinux	00000000 sunos_getgid
4001f9dc g     F .vmlinux	0000001c leon_flush_tlb_all
4008b73c g     F .vmlinux	0000006c set_bh_page
400f3078 g     F .vmlinux	00000014 unblank_screen
400fbb38 g     F .vmlinux	00000020 bus_rescan_devices
4012c3c8 g     O .vmlinux	0000002c default_exec_domain
40048ba4 g     F .vmlinux	0000001c unregister_latency_notifier
40084158 g     F .vmlinux	00000128 sys_io_submit
400cb11c g     F .vmlinux	00000050 pci_find_slot
400b1ae8 g     F .vmlinux	00000020 generic_unplug_device
40304328 g     O .bss	00000010 ctx_free
400457fc  w    F .vmlinux	00000008 sys_shutdown
40079fbc g     F .vmlinux	000002f0 flock_lock_file_wait
400ec238 g     F .vmlinux	0000008c con_get_trans_old
40060b1c g     F .vmlinux	00000100 sys_brk
4015d2f0 g       .vmlinux	00000000 __security_initcall_end
4030e06c g     O .bss	00000004 totalreserve_pages
40085a14 g     F .vmlinux	00000054 sys_setxattr
4015aff0 g     O .vmlinux	00000018 logo_sun_clut224
40085a68 g     F .vmlinux	00000054 sys_lsetxattr
40030d1c g     F .vmlinux	00000014 oops_may_print
4008ded0 g     F .vmlinux	00000044 block_prepare_write
400df49c g     F .vmlinux	00000058 rand_initialize_irq
401342b0 g       .vmlinux	00000000 ___fs_mmu_get_scsi_sgl
4012f280 g     O .vmlinux	00000004 debug_locks
4030e068 g     O .bss	00000004 totalram_pages
4008bef4 g     F .vmlinux	0000003c generic_cont_expand
400b2558 g     F .vmlinux	00000074 blk_rq_unmap_user
4008aee0 g     F .vmlinux	0000003c fsync_bdev
400cf544 g     F .vmlinux	000000fc fb_new_modelist
4015311c g     F .vmlinux	0000060c grvga_setup
4005ba00 g     F .vmlinux	000001e4 follow_page
400730c0 g     F .vmlinux	00000044 unlock_rename
4006c38c g     F .vmlinux	0000017c do_remount_sb
400c0d30 g     F .vmlinux	0000006c kasprintf
4002ed44 g     F .vmlinux	000000a0 mm_release
400740a0 g     F .vmlinux	000000d8 vfs_rmdir
40012a3c g     F .vmlinux	00000020 __local_irq_save
40020c5c g       .vmlinux	00000000 hypersparc_flush_tlb_all
400870e0 g     F .vmlinux	000000a8 simple_attr_read
400f0128 g     F .vmlinux	000001c4 complement_pos
4008cae8 g     F .vmlinux	00000080 sys_bdflush
4004e980 g     F .vmlinux	0000005c end_page_writeback
4003fdf0 g     F .vmlinux	00000044 sys_getpgid
40033b64 g     F .vmlinux	0000007c do_group_exit
40313da0 g     O .bss	00000004 sysfs_dir_cachep
4001b110 g     F .vmlinux	00000040 of_getintprop_default
40048870 g     F .vmlinux	00000014 down_write_trylock
4031aafc g     O .bss	00000004 console_blank_hook
400a26b0 g     F .vmlinux	00000084 sysfs_create_dir
4012924c g       .vmlinux	00000000 __end_pci_fixups_early
4009edc0 g     F .vmlinux	00000048 proc_sys_init
401439e8 g     F .vmlinux	0000004c kmap_init
400493cc  w    F .vmlinux	00000008 notify_arch_cmos_timer
40042c64 g     F .vmlinux	000000bc rcu_check_callbacks
400ed84c g     F .vmlinux	000000d8 kd_mksound
40319328 g     O .bss	000004ec vc_cons
40111e48 g     F .vmlinux	0000007c out_of_line_wait_on_bit_lock
401582e4 g     O .vmlinux	00000004 nr_all_pages
403041b0 g     O .bss	00000004 num_segmaps
400b9d80 g     F .vmlinux	0000004c __bitmap_xor
40021138 g       .vmlinux	00000000 swift_flush_tlb_range
40012950 g     F .vmlinux	00000040 handle_cp_disabled
40143a34 g     F .vmlinux	000000a8 sparc_context_init
400457fc  w    F .vmlinux	00000008 sys_sendmsg
4004883c g     F .vmlinux	00000010 down_read
4011565c g     O .vmlinux	00000054 sysfs_dir_inode_operations
400befe4 g     F .vmlinux	0000003c strcmp
400457fc  w    F .vmlinux	00000008 sys_quotactl
40077924 g     F .vmlinux	00000080 sys_pselect6
403043b8 g     O .bss	0000001c sun4c_vacinfo
400fac0c g     F .vmlinux	00000170 sysdev_shutdown
4004da8c g     F .vmlinux	00000040 acct_auto_close
401120ec g     F .vmlinux	00000014 mutex_trylock
4002ec30 g     F .vmlinux	0000003c __mmdrop
40051aa8 g     F .vmlinux	0000006c try_to_release_page
4002d384 g     F .vmlinux	000000d0 schedule_tail
40043ad4 g     F .vmlinux	000000dc posix_timer_event
4007f3c4 g     F .vmlinux	0000019c inode_setattr
4013584c g       .vmlinux	00000000 ___f_mmu_map_dma_area
40050340 g     F .vmlinux	00000028 remove_suid
401070f8 g     F .vmlinux	0000003c input_inject_event
4030d474 g     O .bss	0000003c per_cpu__rcu_bh_data
400b029c g     F .vmlinux	00000020 blk_get_backing_dev_info
4010cad0 g     F .vmlinux	0000013c hid_input_report
400f8960 g     F .vmlinux	00000124 uart_remove_one_port
4004dc34 g     F .vmlinux	0000018c acct_collect
400e3fb4 g     F .vmlinux	000000bc tty_set_operations
4012d404 g     O .vmlinux	00000004 tick_usec
4002d454 g     F .vmlinux	00000014 nr_running
40115a20 g     O .vmlinux	0000003c ext2_nobh_aops
40070d04 g     F .vmlinux	000000c8 do_pipe
400c6e28 g     F .vmlinux	00000074 plist_del
400be964 g     F .vmlinux	00000080 rb_replace_node
40056dfc g     F .vmlinux	00000090 cancel_dirty_page
400941d8 g     F .vmlinux	00000040 inotify_remove_watch_locked
4004e208 g     F .vmlinux	00000094 __filemap_fdatawrite_range
40091094 g     F .vmlinux	000000ac lookup_bdev
40115c5c g     O .vmlinux	00000054 ext2_symlink_inode_operations
400bf0b8 g     F .vmlinux	00000064 strnchr
40041cec g     F .vmlinux	0000008c schedule_on_each_cpu
400afb90 g     F .vmlinux	00000038 elv_may_queue
400cd7ec g     F .vmlinux	00000024 fb_notifier_call_chain
4012d08c g       *ABS*	00000000 jiffies
400e03f4 g     F .vmlinux	00000064 tty_unregister_ldisc
40140bbc g     F .vmlinux	00000134 sbus_fill_device_irq
40069f84 g     F .vmlinux	00000014 nonseekable_open
400b2a94 g     F .vmlinux	00000060 disk_round_stats
40034df0 g     F .vmlinux	00000164 do_getitimer
4007d7ac g     F .vmlinux	000001d0 sys_getcwd
400cfa58 g     F .vmlinux	000000e8 fb_copy_cmap
4009f9b8 g     F .vmlinux	0000013c add_partition
40077db8 g     F .vmlinux	00000048 sys_poll
4030e1ec g     O .bss	00000004 pkmap_page_table
40070958 g     F .vmlinux	00000018 free_pipe_info
400c169c g     F .vmlinux	00000020 prom_setsync
4013584c g       .vmlinux	00000000 ___f_sbint_to_irq
4001ecdc g     F .vmlinux	000000c4 srmmu_free_nocache
400370d0 g     F .vmlinux	000000cc adjust_resource
4009d95c g     F .vmlinux	00000084 proc_tty_register_driver
40302c80 g     O .bss	00000004 pm_idle
4005478c g     F .vmlinux	00000080 set_page_dirty
4031ab0c g     O .bss	00000004 console_driver
40032a74 g     F .vmlinux	00000068 disallow_signal
40154928 g     F .vmlinux	00000080 vcs_init
4013584c g       .vmlinux	00000000 ___f_pgd_present
400cf9cc g     F .vmlinux	00000008 fb_firmware_edid
400118c4 g       .vmlinux	00000000 fnwin_patch1_7win
4002190c g     F .vmlinux	00000070 sun4c_grow_kernel_ring
400b04f0 g     F .vmlinux	0000008c blk_ordered_cur_seq
400cac60 g     F .vmlinux	0000004c pci_dev_driver
40147b78 g     F .vmlinux	00000064 sun4c_probe_memerr_reg
400c1ac8 g     F .vmlinux	00000040 prom_putsegment
4008aad0 g     F .vmlinux	00000074 sys_futimesat
400b1bd8 g     F .vmlinux	00000098 blk_alloc_queue_node
40017210 g     F .vmlinux	000000c8 pci_free_consistent
40306684 g     O .bss	00000004 cpu_present_map
40059520 g     F .vmlinux	0000004c kstrdup
4004cc08 g     F .vmlinux	0000003c sys_setgid16
400a1e8c g     F .vmlinux	00000138 sysfs_update_file
4008a5a4 g     F .vmlinux	00000014 sys_fdatasync
40102cdc g     F .vmlinux	00000040 loop_register_transfer
403179a4 g     O .bss	00000004 LEON3_GpTimer_Irq
4005a7a8 g     F .vmlinux	000004d4 sys_madvise
4005f4b0 g     F .vmlinux	000001ac vma_merge
400c4c60 g       .vmlinux	00000000 _Div
40036e6c g     F .vmlinux	00000134 allocate_resource
400a3f98 g     F .vmlinux	00000098 sysfs_remove_group
40129948 g       .vmlinux	00000000 __end_rodata
4012d3e0 g     O .vmlinux	00000014 init_nsproxy
40135600 g       .vmlinux	00000000 ___as_pte_wrprotecti
40053cbc g     F .vmlinux	0000004c si_meminfo
400ab208 g     F .vmlinux	00000048 ext2_warning
4014d370 g     F .vmlinux	00000028 chrdev_init
400c7bac g     F .vmlinux	00000008 pci_remove_legacy_files
4003de50 g     F .vmlinux	00000030 sys_tgkill
4013584c g       .vmlinux	00000000 ___f_flush_sig_insns
40085fd4 g     F .vmlinux	00000048 sys_lremovexattr
4008480c g     F .vmlinux	00000374 seq_read
4009ee24 g     F .vmlinux	0000001c kclist_add
401404bc g     F .vmlinux	000001e8 sun4c_init_IRQ
403043d4 g     O .bss	00000004 sun4c_kernel_faults
40051718 g     F .vmlinux	000000e4 generic_file_aio_write
400cc16c g     F .vmlinux	000000b8 pci_remove_sysfs_dev_files
40134268 g       .vmlinux	00000000 ___fs_mmu_unmap_dma_area
400361c0 g     F .vmlinux	00000030 get_jiffies_64
400ad7e0 g     F .vmlinux	0000001c ramfs_get_sb
40035bfc g     F .vmlinux	00000154 ns_to_timespec
4014c0fc g     F .vmlinux	000003e0 free_area_init_node
4004367c g     F .vmlinux	0000011c param_array_set
40115960 g     O .vmlinux	00000054 ext2_file_inode_operations
40012910 g     F .vmlinux	00000040 handle_reg_access
4012d084 g     O .vmlinux	00000004 cap_bset
400c731c g     F .vmlinux	00000030 atomic_cmpxchg
400c0694 g     F .vmlinux	00000034 sprintf
40313604 g     O .bss	00000004 max_mapnr
401059b8 g     F .vmlinux	00000120 ps2_drain
40304320 g     O .bss	00000004 last_valid_pfn
4012f180 g       .vmlinux	00000100 __clz_tab
4003de80 g     F .vmlinux	00000028 sys_tkill
4012e8b0 g     O .vmlinux	00000004 warn_no_part
40153a1c g     F .vmlinux	0000009c grvga_init
400c5948 g       .vmlinux	00000000 _Urem
401342c8 g       .vmlinux	00000000 ___fs_mmu_release_scsi_sgl
400a2afc g     F .vmlinux	00000010 sysfs_remove_subdir
4006fbbc g     F .vmlinux	00000008 generic_pipe_buf_pin
400b4528 g     F .vmlinux	0000009c blk_start_queue
401479c4 g     F .vmlinux	000001b4 sun4c_probe_vac
4013584c g       .vmlinux	00000000 ___f_mmu_get_scsi_one
4012b328 g     O .vmlinux	00000004 serial_console
40054e00 g     F .vmlinux	00000020 redirty_page_for_writepage
4013584c g       .vmlinux	00000000 ___f_pmd_present
400a1284 g     F .vmlinux	00000120 sysfs_drop_dentry
40080b38 g     F .vmlinux	00000020 may_umount
400404b4 g     F .vmlinux	00000074 sys_newuname
40108ba4 g     F .vmlinux	00000150 input_register_handler
400c6514 g     F .vmlinux	00000060 debug_locks_off
00000000 g       *ABS*	00000000 ___a_pte_wrprotecti
400e4380 g     F .vmlinux	00000024 tty_devnum
400c8500 g     F .vmlinux	00000024 pci_find_next_capability
400ffcec g     F .vmlinux	0000001c devres_release_all
400f5f74 g     F .vmlinux	00000090 uart_update_timeout
4007fdb0 g     F .vmlinux	00000008 get_filesystem
40131df0 g     O .vmlinux	00000200 shift_ctrl_map
403041c0 g     O .bss	00000004 vac_entries_per_context
4005967c g     F .vmlinux	00000030 next_zone
403136b0 g     O .bss	00000000 files_lock
4008b64c g     F .vmlinux	000000f0 remove_inode_buffers
400f1110 g     F .vmlinux	00000030 vc_lock_resize
40014710 g     F .vmlinux	000000b8 flush_thread
40010b90 g       .vmlinux	00000000 invalid_segment_patch2_1ff
401325f0 g     O .vmlinux	00000200 plain_map
40032c10 g     F .vmlinux	00000030 exit_files
400bf2b4 g     F .vmlinux	00000074 strcspn
4008620c g     F .vmlinux	00000064 generic_setxattr
400b04e8 g     F .vmlinux	00000008 blk_queue_issue_flush_fn
400e2ddc g     F .vmlinux	000001dc __do_SAK
4003d4cc g     F .vmlinux	0000001c sys_restart_syscall
40134ec4 g       .vmlinux	00000000 ___fs_switch_mm
40087958 g     F .vmlinux	00000024 writeback_release
4004ce2c g     F .vmlinux	00000074 sys_setresgid16
400fee6c g     F .vmlinux	00000194 dma_pool_destroy
4008ad6c g     F .vmlinux	0000001c unlock_buffer
400426a4 g     F .vmlinux	00000074 call_rcu
400c5948 g       .vmlinux	00000000 .urem
400dca40 g     F .vmlinux	00000030 amba_free_apbslv_device
400124c0 g     F .vmlinux	00000058 do_priv_instruction
400716d0 g     F .vmlinux	00000018 path_walk
4001244c g     F .vmlinux	00000074 do_illegal_instruction
400c27ec g     F .vmlinux	00000098 bit_map_clear
4003cbb8 g     F .vmlinux	00000074 group_send_sig_info
40020ee8 g       .vmlinux	00000000 viking_flush_page_for_dma
400a5620 g     F .vmlinux	00000050 ext2_bg_num_gdb
400564ac g     F .vmlinux	0000005c put_pages_list
40075c70 g     F .vmlinux	00000090 sys_fcntl64
400744c4 g     F .vmlinux	000000ac vfs_symlink
400118cc g       .vmlinux	00000000 fill_window_entry
400210c8 g       .vmlinux	00000000 tsunami_setup_blockops
400a33f4 g     F .vmlinux	000000e4 sysfs_create_shadow_dir
400003f8 g     F .stage2	000000a4 leon3_getapbbase
400c798c g     F .vmlinux	000000b4 pci_bus_alloc_resource
40006000 g       .vmlinux	00000000 pg0
400174d8 g     F .vmlinux	00000058 pci_dma_sync_sg_for_device
40010e18 g       .vmlinux	00000000 srmmu_fault
400dc8f4 g     F .vmlinux	0000014c amba_get_free_apbslv_devices
40045d60 g     F .vmlinux	000000ec posix_cpu_clock_get
40005000 g       .vmlinux	00000000 end_traptable
4003da04 g     F .vmlinux	00000234 sys_rt_sigtimedwait
40315848 g     O .bss	00000004 num_obio_ranges
400c92d4  w    F .vmlinux	00000008 pcibios_disable_device
400e02b8 g     F .vmlinux	00000058 tty_prepare_flip_string
40075d00 g     F .vmlinux	0000014c send_sigio
400c1e34 g     F .vmlinux	00000044 __prom_nextprop
40313d44 g     O .bss	00000004 inotify_max_user_watches
40304380 g     O .bss	00000004 srmmu_nocache_end
400c4988 g       .vmlinux	00000000 .rem
4012a0b8 g       .vmlinux	00000000 lvl14_save
4003e768 g     F .vmlinux	00000054 blocking_notifier_chain_unregister
400aa4e8 g     F .vmlinux	0000003c ext2_setattr
4001efb4 g     F .vmlinux	00000010 leon_flush_cache_all
4006bb60 g     F .vmlinux	0000001c fsync_super
40152494 g     F .vmlinux	000003c0 pci_bus_assign_resources
4004c974 g     F .vmlinux	0000004c request_dma
4007dfe8 g     F .vmlinux	00000030 igrab
401355b0 g       .vmlinux	00000000 ___fs_pmd_alloc_one
40056bd0 g     F .vmlinux	00000050 lru_add_drain
4012972c g       .vmlinux	00000000 __stop___ksymtab
4004331c g     F .vmlinux	00000044 param_set_int
400e3fa4 g     F .vmlinux	00000010 put_tty_driver
403041c8 g     O .bss	00000004 vac_entries_per_page
4008794c g     F .vmlinux	0000000c writeback_in_progress
40047cf8 g     F .vmlinux	00000028 ktime_get_real
4003b738 g     F .vmlinux	00000038 unblock_all_signals
400c74e0 g     F .vmlinux	00000054 pci_bus_write_config_word
400f5a64 g     F .vmlinux	00000014 getconsxy
4014ba98 g     F .vmlinux	00000018 free_all_bootmem
400a7010 g     F .vmlinux	00000054 ext2_sync_file
40300064 g     O .bss	00000004 Version_132629
4003e6c8 g     F .vmlinux	0000003c atomic_notifier_chain_unregister
400638e8 g     F .vmlinux	00000028 vfree
40086728 g     F .vmlinux	00000008 generic_read_dir
400b44a0 g     F .vmlinux	00000088 blk_run_queue
4012972c g       .vmlinux	00000000 __start_rio_route_ops
400b1aa8 g     F .vmlinux	00000040 __generic_unplug_device
400bc364 g     F .vmlinux	0000002c kobject_del
40113f38 g     O .vmlinux	00000054 page_symlink_inode_operations
4006cf04 g     F .vmlinux	0000005c unregister_chrdev_region
400c2260 g     F .vmlinux	00000044 prom_pathtoinode
400c9388 g     F .vmlinux	000000d8 pci_enable_wake
40060f8c g     F .vmlinux	000000b0 install_special_mapping
40059ca4 g     F .vmlinux	000000b0 congestion_wait_interruptible
400942a0 g     F .vmlinux	00000030 inotify_d_move
4007c418 g     F .vmlinux	0000007c have_submounts
403074c8 g     O .bss	00000004 panic_blink
40056c38 g     F .vmlinux	00000070 lru_cache_add
400185f0 g     F .vmlinux	00000250 timer_interrupt
4001aff4 g     F .vmlinux	00000090 of_device_is_compatible
40042e3c g     F .vmlinux	0000001c __kernel_text_address
400366a0 g     F .vmlinux	00000068 raise_softirq_irqoff
401047c4 g     F .vmlinux	00000078 serio_interrupt
4002ec6c g     F .vmlinux	00000090 mmput
400cd810 g     F .vmlinux	00000070 fb_get_color_depth
4001ad70 g     F .vmlinux	00000020 __up
4002e520 g     F .vmlinux	00000054 sched_getaffinity
40305dd0 g     O .bss	0000001c sun4c_kernel_ring
40134958 g       .vmlinux	00000000 ___fs_set_pte
4012ff54 g     O .vmlinux	00000084 pty_table
4004cc44 g     F .vmlinux	00000058 sys_setreuid16
4002110c g       .vmlinux	00000000 swift_flush_cache_range
4030e0a8 g     O .bss	00000004 nr_pdflush_threads
40083018 g     F .vmlinux	00000178 aio_complete
40063eb4 g     F .vmlinux	00000058 init_emergency_isa_pool
400457fc  w    F .vmlinux	00000008 sys_msgctl
400c6c78 g     F .vmlinux	00000058 hweight32
401553bc g     F .vmlinux	00000018 attribute_container_init
4012dec4 g     O .vmlinux	00000008 super_blocks
00000000 g       *ABS*	00000000 ___a_pte_mkcleani
400e002c g     F .vmlinux	00000158 tty_buffer_request_room
40048404 g     F .vmlinux	00000048 hrtimer_get_res
4003b134 g     F .vmlinux	00000078 find_user
40157c88 g     O .vmlinux	00000004 root_device_name
400bf398 g     F .vmlinux	00000048 strsep
40004000 g       .vmlinux	00000000 __stext
4030e09c g     O .bss	00000004 block_dump
4004c220 g     F .vmlinux	000000f8 sys_futex
4009c7ac g     F .vmlinux	00000088 free_proc_entry
40011108 g       .vmlinux	00000000 ret_from_fork
4013584c g       .vmlinux	00000000 ___btfixup_end
40111efc g     F .vmlinux	00000034 mutex_unlock
40011dec g       .vmlinux	00000000 rtrap_7win_patch5
4003688c g     F .vmlinux	0000001c open_softirq
4010017c g     F .vmlinux	00000088 attribute_container_unregister
4001bbe4 g     F .vmlinux	00000024 of_device_unregister
4002ea24 g     F .vmlinux	0000000c nr_processes
4004e9dc g     F .vmlinux	00000084 __lock_page_nosync
4006bab0 g     F .vmlinux	00000020 unlock_super
4003b23c g     F .vmlinux	0000017c alloc_uid
4007ef14 g     F .vmlinux	00000194 generic_drop_inode
400fd96c g     F .vmlinux	00000018 class_device_unregister
4001e534 g     F .vmlinux	00000258 io_remap_pfn_range
40135500 g       .vmlinux	00000000 ___fs_pte_mkdirty
400c6d64 g     F .vmlinux	000000c4 plist_add
400b0a94 g     F .vmlinux	0000001c blk_free_tags
4012920c g       .vmlinux	00000000 __start_pci_fixups_early
40000374 g     F .stage2	00000050 leon3_apbslv_scan
400c1b48 g     F .vmlinux	00000034 prom_getchild
40045334 g     F .vmlinux	00000060 prepare_to_wait_exclusive
4012dc5c g     O .vmlinux	00000004 node_possible_map
4004e3dc g     F .vmlinux	00000038 add_to_page_cache_lru
400fba08 g     F .vmlinux	00000088 bus_remove_driver
400c4504 g       .vmlinux	00000000 __memscan_zero
400d16a4 g     F .vmlinux	00000084 fb_delete_videomode
400c1d00 g     F .vmlinux	00000028 prom_getintdefault
400457fc  w    F .vmlinux	00000008 sys_get_mempolicy
00000000 g       *ABS*	00000000 ___i_page_kernel
4014dfe0 g     F .vmlinux	000000b8 proc_tty_init
400f8654 g     F .vmlinux	0000002c uart_unregister_driver
40313b40 g     O .bss	00000004 names_cachep
4014a654 g     F .vmlinux	00000034 signals_init
40012174 g     F .vmlinux	00000038 syscall_trace_entry
40074e5c g     F .vmlinux	00000090 vfs_readlink
400badb0 g     F .vmlinux	00000078 bitmap_find_free_region
401009fc g     F .vmlinux	0000003c anon_transport_class_register
40052534 g     F .vmlinux	00000218 out_of_memory
400dabe4 g     F .vmlinux	000002ec cfb_fillrect
40134dd4 g       .vmlinux	00000000 ___fs_free_thread_info
40045434 g     F .vmlinux	00000064 wake_bit_function
40157d00 g     O .vmlinux	00000004 rd_prompt
400313f8 g     F .vmlinux	00000050 try_acquire_console_sem
4007dbec g     F .vmlinux	00000054 destroy_inode
400dc5f4 g     F .vmlinux	000000e0 amba_find_apbslv_addr
40053fc4 g     F .vmlinux	00000028 zone_init_free_lists
40040008 g     F .vmlinux	00000058 groups_free
400e4070 g     F .vmlinux	000001f8 tty_register_driver
400004dc g     F .stage2	00000014 mark
400c1bf0 g     F .vmlinux	0000005c prom_getproplen
400b08c8 g     F .vmlinux	00000104 blk_queue_stack_limits
40073b9c g     F .vmlinux	000000f8 vfs_mknod
400140bc g     F .vmlinux	00000090 leon_enable_pil_irq
400c7630 g     F .vmlinux	00000064 pci_user_read_config_byte
4003e0ec g     F .vmlinux	00000164 do_sigaltstack
40080080 g     F .vmlinux	00000018 get_fs_type
4012924c g       .vmlinux	00000000 __start_pci_fixups_header
4005e934 g     F .vmlinux	000000d0 sys_mlockall
4003df20 g     F .vmlinux	000001cc do_sigaction
40130b90 g     O .vmlinux	00000014 keyboard_tasklet
40302ba0 g     O .bss	00000004 sun4c_timers
4005ed38 g     F .vmlinux	0000002c unlink_file_vma
400c4624 g       .vmlinux	00000000 __bzero_begin
400591f0 g     F .vmlinux	000000a8 kswapd_run
400c98cc g     F .vmlinux	00000014 pci_release_regions
4006aa30 g     F .vmlinux	00000090 sys_pwrite64
40089cdc g     F .vmlinux	000002b8 sys_splice
400457fc  w    F .vmlinux	00000008 sys_spu_create
40068ca8 g     F .vmlinux	00000074 do_truncate
4012f2a4 g     O .vmlinux	00000008 pci_devices
4012d264 g     O .vmlinux	00000004 pid_max_min
400373fc g     F .vmlinux	0000007c __devm_release_region
40062284 g     F .vmlinux	000000b0 page_address_in_vma
400489b8 g     F .vmlinux	00000094 modify_acceptable_latency
4003a6d0 g     F .vmlinux	000000a0 update_process_times
400fc808 g     F .vmlinux	00000080 driver_for_each_device
400c2330 g     F .vmlinux	00000074 prom_devclose
400c0e40 g     F .vmlinux	000000b8 prom_nbputchar
4006dc18 g     F .vmlinux	00000078 register_binfmt
40139c94 g     F .vmlinux	00000060 parse_early_param
400948a0 g     F .vmlinux	00000120 inotify_add_watch
400ff940 g     F .vmlinux	00000038 devres_free
40136788 g       .vmlinux	00000000 __bzero_end
400bc390 g     F .vmlinux	0000002c kobject_unregister
4012b190 g     O .vmlinux	00000004 sparc_init_timers
400bedb8 g     F .vmlinux	0000009c strnicmp
00000000 g       *ABS*	00000000 ___h_pgdir_size
4013584c g       .vmlinux	00000000 ___f_do_check_pgt_cache
400457fc  w    F .vmlinux	00000008 ppc_rtas
40069af8 g     F .vmlinux	00000048 dentry_open
4012972c g       .vmlinux	00000000 __stop___kcrctab_gpl
4030435c g     O .bss	00000004 hwbug_bitmask
400816d8 g     F .vmlinux	00000100 shrink_submounts
40075ffc g     F .vmlinux	0000007c __kill_fasync
40041fc0 g     F .vmlinux	00000344 alloc_pid
4007bc34 g     F .vmlinux	00000034 d_find_alias
400bc8ac g     F .vmlinux	00000068 kset_find_obj
4005775c g     F .vmlinux	00000018 invalidate_inode_pages2
40313d8c g     O .bss	00000004 proc_root_kcore
40074f7c g     F .vmlinux	00000194 vfs_follow_link
400f6110 g     F .vmlinux	00000054 uart_get_divisor
40034f54 g     F .vmlinux	00000078 sys_getitimer
40043284 g     F .vmlinux	00000020 param_get_short
4010938c g     F .vmlinux	00000174 input_ff_create
40021158 g       .vmlinux	00000000 swift_flush_tlb_page
4008a6c4 g     F .vmlinux	00000160 sys_sync_file_range
40134238 g       .vmlinux	00000000 ___fs_mmu_map_dma_area
4008c040 g     F .vmlinux	00000084 nobh_commit_write
40148760 g     F .vmlinux	00000e84 ld_mmu_sun4c
40069ddc g     F .vmlinux	0000007c filp_close
4008e184 g     F .vmlinux	000002f0 block_read_full_page
40130a68 g     O .vmlinux	00000100 dfont_unicount
40017e14 g     F .vmlinux	0000007c sparc_mmap_check
4004cea0 g     F .vmlinux	000000e0 sys_getresgid16
40080fb0 g     F .vmlinux	00000014 sys_oldumount
400bc914 g     F .vmlinux	00000028 subsystem_init
4013584c g       .vmlinux	00000000 ___f_enable_pil_irq
4014bab0 g     F .vmlinux	00000060 __alloc_bootmem_nopanic
4007baa4 g     F .vmlinux	00000058 dget_locked
4002c8e4 g     F .vmlinux	00000100 do_mathemu
400caccc g     F .vmlinux	00000024 pci_dev_get
40011448 g       .vmlinux	00000000 __ndelay
4015e000 g       .vmlinux	00000000 __initramfs_start
4005956c g     F .vmlinux	00000034 kmemdup
400517fc g     F .vmlinux	000000d0 generic_file_aio_write_nolock
4014a8cc g     F .vmlinux	00000024 rcu_init
4007d2d4 g     F .vmlinux	000002e8 d_materialise_unique
40020ef0 g       .vmlinux	00000000 tsunami_flush_cache_range
4002e384 g     F .vmlinux	000000d0 sched_setaffinity
4013584c g       .vmlinux	00000000 ___f_flush_cache_range
4005ac90 g     F .vmlinux	00000004 pmd_clear_bad
40041424 g     F .vmlinux	00000048 queue_work
400041f0 g       .vmlinux	00000000 t_nmi
4002c9e4 g     F .vmlinux	00000010 task_nice
400c5e1c g     F .vmlinux	00000200 match_token
400108f8 g       .vmlinux	00000000 do_tag_overflow
40145204 g     F .vmlinux	000002c8 srmmu_inherit_prom_mappings
40051e28 g     F .vmlinux	00000020 mempool_destroy
400bafa0 g     F .vmlinux	000000b8 get_options
40143e64 g     F .vmlinux	00000124 paging_init
40018dbc g     F .vmlinux	0000002c cpu_find_by_instance
40109500 g     F .vmlinux	00000070 input_ff_destroy
400cb458 g     F .vmlinux	000000e0 pci_get_class
4006103c g     F .vmlinux	00000648 sys_mprotect
400175e0 g     F .vmlinux	000000fc prom_sync_me
400b0234 g     F .vmlinux	00000024 elv_rb_latter_request
40132ac0 g     O .vmlinux	00000160 platform_bus_type
4011218c g     F .vmlinux	00000140 hrtimer_nanosleep_restart
400a121c g     F .vmlinux	00000068 sysfs_get_name
40014290 g     F .vmlinux	00000074 machine_halt
400bc0f4 g     F .vmlinux	000000c8 kobject_set_name
400b5a1c g     F .vmlinux	00000030 unlink_gendisk
400109d8 g       .vmlinux	00000000 do_cp_exception
40302c58 g     O .bss	00000004 sparc_leon_eirq
40100bf0 g     F .vmlinux	00000018 transport_destroy_device
40075c28 g     F .vmlinux	00000048 sys_fcntl
4007c3a0 g     F .vmlinux	00000078 shrink_dcache_for_umount
40119028 g     O .vmlinux	0000006c urandom_fops
400fa1dc g     F .vmlinux	0000009c device_destroy
4003e250 g     F .vmlinux	00000014 sys_sigpending
40040814 g     F .vmlinux	0000016c sys_setrlimit
4009c834 g     F .vmlinux	000001a8 remove_proc_entry
400be188 g     F .vmlinux	00000018 radix_tree_tagged
400398b8 g     F .vmlinux	000000ac ptrace_check_attach
400fa7d0 g     F .vmlinux	0000002c sysdev_class_register
40047cd0 g     F .vmlinux	00000028 ktime_get
401497f0 g     F .vmlinux	0000004c fork_idle
400118d0 g       .vmlinux	00000000 fnwin_patch1
4002d9dc g     F .vmlinux	00000064 scheduler_tick
400c7864 g     F .vmlinux	00000070 pci_user_write_config_dword
4006e278 g     F .vmlinux	00000170 setup_arg_pages
400406bc g     F .vmlinux	000000e4 sys_setdomainname
400dfed0 g     F .vmlinux	00000068 tty_name
400fae48 g     F .vmlinux	000002c4 sysdev_suspend
40011b2c g       .vmlinux	00000000 trap_setup
40307094 g     O .bss	00000004 vm_area_cachep
40017f30 g     F .vmlinux	00000010 sys_mmap2
400a6b78 g     F .vmlinux	00000214 ext2_make_empty
4013584c g       .vmlinux	00000000 ___f_flush_cache_all
40302ba8 g     O .bss	00000004 sun4d_timers
400cd230 g     F .vmlinux	00000228 pci_setup_cardbus
40149fb4 g     F .vmlinux	0000006c profile_init
4003aec4 g     F .vmlinux	00000180 do_sysinfo
4013584c g       .vmlinux	00000000 ___f_pte_mkwrite
400c24bc g       .vmlinux	00000000 __atomic_begin
4015d1a4 g       .vmlinux	00000000 __initcall_start
40084f2c g     F .vmlinux	0000006c seq_printf
40020b14 g       .vmlinux	00000000 hypersparc_flush_cache_page
40116148 g     O .vmlinux	00000008 scsi_command_size
4014bb94 g     F .vmlinux	0000007c __alloc_bootmem_low
40135548 g       .vmlinux	00000000 ___fs_pte_mkwrite
400b0344 g     F .vmlinux	00000060 blk_queue_max_sectors
40085e20 g     F .vmlinux	0000004c sys_listxattr
4007b8f4 g     F .vmlinux	000001b0 dput
4005b1bc g     F .vmlinux	00000050 print_bad_pte
400457fc  w    F .vmlinux	00000008 sys_spu_run
400457fc  w    F .vmlinux	00000008 sys_connect
40043798 g     F .vmlinux	000000c8 param_array_get
00000000 g       *ABS*	00000000 ___i_pte_modify_mask
400518cc g     F .vmlinux	000001dc generic_file_aio_read
401072ec g     F .vmlinux	00000034 input_flush_device
4006e4f8 g     F .vmlinux	00000020 get_task_comm
4004834c g     F .vmlinux	00000068 hrtimer_get_remaining
401551a8 g     F .vmlinux	00000018 devices_init
400457fc  w    F .vmlinux	00000008 sys_socketpair
40111c3c g     F .vmlinux	000000e4 __wait_on_bit
4006194c g     F .vmlinux	00000558 do_mremap
40135418 g       .vmlinux	00000000 ___fs_free_pmd_fast
403042e0 g     O .bss	00000004 pfn_base
4004146c g     F .vmlinux	00000020 delayed_work_timer_fn
4003b044 g     F .vmlinux	0000005c sys_sysinfo
400aea78 g     F .vmlinux	0000002c cap_vm_enough_memory
40014da8 g     F .vmlinux	0000008c get_wchan
400f1934 g     F .vmlinux	00000084 set_console
400bb274 g     F .vmlinux	0000012c find_next_bit
4007ee24 g     F .vmlinux	000000f0 generic_delete_inode
40041c88 g     F .vmlinux	0000001c schedule_work
40054cdc g     F .vmlinux	00000028 __set_page_dirty_no_writeback
400ecc88 g     F .vmlinux	00000054 clear_selection
400fb10c g     F .vmlinux	0000005c sysdev_resume
400cf7f4 g     F .vmlinux	00000008 fb_parse_edid
400447c0 g     F .vmlinux	00000130 sys_timer_delete
4001387c g     F .vmlinux	00000148 sun4d_free_irq
400c6154 g     F .vmlinux	000003c0 half_md4_transform
400b1020 g     F .vmlinux	000000d4 blk_dump_rq_flags
40053d08 g     F .vmlinux	000002bc show_free_areas
4007e12c g     F .vmlinux	00000160 touch_atime
4004c8ec g     F .vmlinux	00000024 __rt_mutex_init
4008c50c g     F .vmlinux	00000070 write_boundary_block
40136d24 g       .vmlinux	00000000 __start___ex_table
40302c6c g     O .bss	00000004 last_task_used_math
400bf83c g     F .vmlinux	0000018c simple_strtoul
40304364 g     O .bss	00000004 srmmu_name
40012100 g       .vmlinux	00000000 srmmu_rett_stackchk
40111794 g     F .vmlinux	00000094 interruptible_sleep_on
4000e000 g     O .vmlinux	00002000 init_thread_union
4012be74 g     O .vmlinux	00000160 of_bus_type
400168b8 g     F .vmlinux	00000014 of_iounmap
40134108 g       .vmlinux	00000000 ___fs_enable_pil_irq
401340b8 g       .vmlinux	00000000 ___fs_disable_irq
400f4e60 g     F .vmlinux	000002e8 tioclinux
40131144 g     O .vmlinux	00000400 func_table
40134f98 g       .vmlinux	00000000 ___fs_pte_clear
40045588 g     F .vmlinux	00000080 __kfifo_put
40136d24 g       .vmlinux	00000000 __stop___fixup
403043a4 g     O .bss	00000004 srmmu_nocache_npages
4008acc0 g     F .vmlinux	0000003c __lock_buffer
4007a2ac g     F .vmlinux	00000170 sys_flock
400c24bc g       .vmlinux	00000000 ___xchg32_sun4c
40134354 g       .vmlinux	00000000 ___fs_bus_do_settimeofday
4002ea30 g     F .vmlinux	00000024 free_task
401584d0 g     O .vmlinux	00000018 logo_linux_mono
400c60d4 g     F .vmlinux	00000014 match_hex
4004e75c g     F .vmlinux	00000050 filemap_write_and_wait
4006ec90 g     F .vmlinux	00000088 compute_creds
40035908 g     F .vmlinux	00000094 sys_adjtimex
400c3de8 g       .vmlinux	00000000 __memcmp
4004d2a0 g     F .vmlinux	0000002c sys_geteuid16
40303030 g     O .bss	00000004 fsr_storage
40041cc8 g     F .vmlinux	00000024 schedule_delayed_work_on
400dd2f8 g     F .vmlinux	00000100 leonuart_tx_chars
4013584c g       .vmlinux	00000000 ___f_pmd_clear
400a2c58 g     F .vmlinux	00000188 sysfs_rename_dir
400112a0 g       .vmlinux	00000000 sunos_syscall
4030d7d8 g     O .bss	00000004 time_freq
40054e20 g     F .vmlinux	00000048 set_page_dirty_lock
40063770 g     F .vmlinux	0000006c remove_vm_area
4012947c g       .vmlinux	00000000 __start_pci_fixups_final
4008c3dc g     F .vmlinux	00000130 ll_rw_block
400d0968 g     F .vmlinux	0000009c fb_init_device
403179a8 g     O .bss	00000004 LEON3_GpTimer_Regs
400c510c g       .vmlinux	00000000 __strncmp
40135854 g       .vmlinux	00000000 _edata
4012972c g       .vmlinux	00000000 __start___param
4008df14 g     F .vmlinux	00000270 cont_prepare_write
4005dda4 g     F .vmlinux	00000090 make_pages_present
4010062c g     F .vmlinux	00000014 attribute_container_add_class_device_adapter
40068a38 g     F .vmlinux	00000098 sys_statfs
40035dd4 g     F .vmlinux	00000040 usecs_to_jiffies
400121b4 g     F .vmlinux	0000004c sun4m_nmi
4004ea60 g     F .vmlinux	00000084 __lock_page
400d15c8 g     F .vmlinux	000000dc fb_add_videomode
400374d8 g     F .vmlinux	00000068 sysctl_head_next
4005d928 g     F .vmlinux	0000047c copy_page_range
4002110c g       .vmlinux	00000000 swift_flush_page_to_ram
40011118 g       .vmlinux	00000000 linux_sparc_syscall
4003d0d0 g     F .vmlinux	000003fc get_signal_to_deliver
4006c9cc g     F .vmlinux	0000008c vfs_kern_mount
400c5264 g       .vmlinux	00000000 _Udiv
4004b5d8 g     F .vmlinux	00000088 handle_futex_death
f031ae0c g       *ABS*	00000000 _end
40319154 g     O .bss	0000013b kbd_table
40143370 g     F .vmlinux	00000164 pcibios_fixup_bus
400946ac g     F .vmlinux	00000034 inotify_init_watch
4013572c g       .vmlinux	00000000 ___fs_pgprot_noncached
400ed924 g     F .vmlinux	000000a8 kbd_rate
400554d0 g     F .vmlinux	00000160 test_set_page_writeback
4007da80 g     F .vmlinux	00000040 find_inode_number
4006a1e0 g     F .vmlinux	00000060 vfs_llseek
4007dd30 g     F .vmlinux	0000008c __iget
40072e38 g     F .vmlinux	00000050 __user_walk_fd
40011b14 g       .vmlinux	00000000 tsetup_7win_patch1
4001fa2c g     F .vmlinux	000000c0 leon_flush_needed
4005e77c g     F .vmlinux	000000d4 sys_mlock
4030e070 g     O .bss	00000004 nr_swap_pages
4008f5fc g     F .vmlinux	0000005c bio_unmap_user
40056cd0 g     F .vmlinux	000000a4 pagevec_strip
4002f1c4 g     F .vmlinux	00000038 __cleanup_sighand
4003096c g     F .vmlinux	00000048 sys_personality
4002e454 g     F .vmlinux	000000cc sys_sched_setaffinity
40112a18 g     F .vmlinux	00000014 __down_write
4014e40c g     F .vmlinux	00000018 init_rootfs
4006a13c g     F .vmlinux	0000000c no_llseek
4008a42c g     F .vmlinux	00000014 sys_sync
4005c508 g     F .vmlinux	000000c8 vmtruncate_range
4013584c g       .vmlinux	00000000 ___f_mmu_get_scsi_sgl
4001e508 g     F .vmlinux	0000002c sparc_flush_page_to_ram
40031a7c g     F .vmlinux	0000001c console_print
4014c4dc g     F .vmlinux	0000000c set_dma_reserve
40113040 g     O .vmlinux	00000065 linux_banner
400b62ec g     F .vmlinux	00000050 invalidate_partition
4010d418 g     F .vmlinux	000000c0 hidinput_find_field
400350b0 g     F .vmlinux	00000304 do_setitimer
40105ff4 g     F .vmlinux	00000098 ps2_handle_response
40086324 g     F .vmlinux	00000040 simple_lookup
40010860 g       .vmlinux	00000000 fpe_trap_handler
4012bfd4 g     O .vmlinux	00000160 sbus_bus_type
40313cc8 g     O .bss	00000004 aio_nr
40036708 g     F .vmlinux	00000084 __tasklet_hi_schedule
400433e4 g     F .vmlinux	00000044 param_set_long
40063720 g     F .vmlinux	00000020 get_vm_area_node
400c6118 g     F .vmlinux	0000003c match_strdup
4014d70c g     F .vmlinux	0000009c inode_init_early
40157868 g       .vmlinux	00000000 _einittext
4006d9d0 g     F .vmlinux	0000003c sys_stat64
400fcec0 g     F .vmlinux	0000002c class_device_create_bin_file
40062194 g     F .vmlinux	0000002c anon_vma_link
40056508 g     F .vmlinux	000000f4 rotate_reclaimable_page
40069f3c g     F .vmlinux	00000048 generic_file_open
4003fe44 g     F .vmlinux	00000044 sys_getsid
400b2c7c g     F .vmlinux	00000040 blk_put_request
40057068 g     F .vmlinux	000003b4 truncate_inode_pages_range
400113fc g       .vmlinux	00000000 fpload
4001ecac g     F .vmlinux	00000030 srmmu_get_nocache
00000000 g       *ABS*	00000000 ___a_pte_filei
4010589c g     F .vmlinux	0000011c ps2_sendbyte
40054c90 g     F .vmlinux	0000004c writeback_set_ratelimit
400488a4 g     F .vmlinux	00000010 downgrade_write
4012d20c g     O .vmlinux	00000004 fs_overflowuid
40086b68 g     F .vmlinux	0000009c simple_commit_write
401434d4 g     F .vmlinux	00000020 pcibios_update_irq
4004278c g     F .vmlinux	0000000c rcu_batches_completed
400424f0 g     F .vmlinux	0000001c find_task_by_pid_type
400e08a8 g     F .vmlinux	0000001c tty_hung_up_p
400d1728 g     F .vmlinux	00000060 fb_destroy_modelist
400457fc g     F .vmlinux	00000008 sys_ni_syscall
4006c034 g     F .vmlinux	00000138 sync_filesystems
40074e3c g     F .vmlinux	00000020 sys_rename
403146f8 g     O .bss	00000300 prom_reg_tmp
40043448 g     F .vmlinux	00000044 param_set_ulong
400c6a7c g     F .vmlinux	00000058 pcim_iomap
40010ef8 g       .vmlinux	00000000 sys_sigreturn
400457fc  w    F .vmlinux	00000008 sys_shmget
40048318 g     F .vmlinux	00000034 hrtimer_cancel
4004ccd8 g     F .vmlinux	00000074 sys_setresuid16
400c92dc g     F .vmlinux	000000ac pci_disable_device
4001cd7c g     F .vmlinux	0000009c set_auxio
40020c6c g       .vmlinux	00000000 hypersparc_flush_tlb_mm
40134384 g       .vmlinux	00000000 ___ss_pgdir_shift
4013584c g       .vmlinux	00000000 ___f_pmd_alloc_one
403029fc g     O .bss	00000004 linux_smp_still_initting
00000000 g       *ABS*	00000000 ___s_ptrs_per_pmd
400b3e50 g     F .vmlinux	00000104 end_that_request_last
4006b934 g     F .vmlinux	00000074 fs_may_remount_ro
4010608c g     F .vmlinux	000000d0 ps2_handle_ack
40135590 g       .vmlinux	00000000 ___fs_pte_mkyoung
40313dd4 g     O .bss	00000004 blk_max_pfn
40020dac g       .vmlinux	00000000 viking_mxcc_flush_page
400b2a48 g     F .vmlinux	0000004c blkdev_issue_flush
40035b04 g     F .vmlinux	00000038 getnstimeofday
401323f0 g     O .vmlinux	00000200 shift_map
40304354 g     O .bss	00000004 vac_line_size
4003c428 g     F .vmlinux	0000004c lock_task_sighand
400ca730 g     F .vmlinux	0000013c pci_match_id
400e3f60 g     F .vmlinux	00000044 alloc_tty_driver
40134c04 g       .vmlinux	00000000 ___fs_flush_page_for_dma
400b45d8 g     F .vmlinux	00000018 kblockd_flush
40300068 g     O .bss	00000004 ROOT_DEV
40157e54 g     O .vmlinux	00000004 boot_flags
4012b2ec g     O .vmlinux	0000001c sparc_iomap
4009fb6c g     F .vmlinux	000001f4 register_disk
400bab34 g     F .vmlinux	00000160 bitmap_remap
40110590 g     F .vmlinux	00000028 klist_iter_exit
400d9aa4 g     F .vmlinux	00000270 soft_cursor
4001521c g     F .vmlinux	00000248 do_rt_sigreturn
40086730 g     F .vmlinux	0000015c get_sb_pseudo
40017428 g     F .vmlinux	0000002c pci_dma_sync_single_for_cpu
40035708 g     F .vmlinux	0000010c do_sys_settimeofday
4007f9a0 g     F .vmlinux	0000001c is_bad_inode
4007e018 g     F .vmlinux	00000034 remove_inode_hash
4006b8b0 g     F .vmlinux	0000004c put_filp
40135798 g       .vmlinux	00000000 ___is_page_readonly
400dcccc g     F .vmlinux	00000610 amba_read_procmem
401092dc g     F .vmlinux	000000b0 input_ff_event
40135280 g       .vmlinux	00000000 ___fs_update_mmu_cache
403041ac g     O .bss	00000004 invalid_segment
40038270 g     F .vmlinux	00000030 proc_dointvec
40045290 g     F .vmlinux	00000044 remove_wait_queue
40074478 g     F .vmlinux	00000034 sys_unlinkat
400851f8 g     F .vmlinux	0000005c seq_puts
400801d0 g     F .vmlinux	00000088 __lookup_mnt
400b2490 g     F .vmlinux	000000c8 blk_rq_bio_prep
4004b4e4 g     F .vmlinux	00000024 sys_set_robust_list
4002e6e0 g     F .vmlinux	00000048 sys_sched_get_priority_max
40064190 g     F .vmlinux	0000039c blk_queue_bounce
40093f74 g     F .vmlinux	0000006c put_inotify_watch
40010eb8 g       .vmlinux	00000000 sys_execve
40041e40 g     F .vmlinux	00000014 keventd_up
4012dd7c g     O .vmlinux	000000c0 malloc_sizes
4002e574 g     F .vmlinux	00000074 sys_sched_getaffinity
4010366c g     F .vmlinux	00000098 uhci_reset_hc
4001b44c g     F .vmlinux	00000034 of_dev_get
40129674 g       .vmlinux	00000000 __end_pci_fixups_enable
401434f4 g     F .vmlinux	00000008 pcibios_setup
40100c08 g     F .vmlinux	000000c4 device_shutdown
400d17d0 g     F .vmlinux	0000012c fb_find_best_display
40010a48 g       .vmlinux	00000000 do_flush_windows
400fe2c0 g     F .vmlinux	0000006c platform_device_register_simple
4001df6c g     F .vmlinux	00000244 window_ret_fault
4012972c g       .vmlinux	00000000 __start___kcrctab_gpl
4003077c g     F .vmlinux	00000050 unregister_exec_domain
4012972c g       .vmlinux	00000000 __stop___kcrctab
400eff24 g     F .vmlinux	00000204 invert_screen
400caf74 g     F .vmlinux	0000009c pci_get_slot
4008ab44 g     F .vmlinux	0000001c sys_utimes
402ff520 g       .vmlinux	00000000 __per_cpu_start
4003b1ac g     F .vmlinux	00000090 free_uid
400fd730 g     F .vmlinux	000000a8 class_device_create
4010466c g     F .vmlinux	00000070 serio_unregister_driver
40085178 g     F .vmlinux	00000030 single_release
400004f0 g     O .stage2	00000008 amba_ioarea
40020760 g     F .vmlinux	0000016c iounit_map_dma_init
400ce9a0 g     F .vmlinux	0000016c fb_pan_display
40033b50 g     F .vmlinux	00000014 sys_exit
40036640 g     F .vmlinux	00000014 irq_enter
40119094 g     O .vmlinux	0000006c random_fops
4012f5f8 g     O .vmlinux	0000000c pci_bus_sem
4006caf4 g     F .vmlinux	00000070 chrdev_show
403041b8 g     O .bss	00000004 vac_linesize
400c14e4 g     F .vmlinux	00000038 prom_reboot
4014bc28 g     F .vmlinux	00000090 __free_pages_bootmem
40044c64 g     F .vmlinux	00000128 sys_clock_getres
40016bd8 g     F .vmlinux	00000070 dma_map_sg
40018548 g       .vmlinux	00000000 sunos_execv
4001e35c g     F .vmlinux	00000070 map_high_region
40040b78 g     F .vmlinux	000001d8 sys_prctl
400457fc  w    F .vmlinux	00000008 compat_sys_get_mempolicy
00000000 g       *ABS*	00000000 ___h_pgdir_mask
4014ba50 g     F .vmlinux	00000024 reserve_bootmem
40094414 g     F .vmlinux	0000001c inotify_get_cookie
400168f8 g     F .vmlinux	0000004c dma_set_mask
4003599c g     F .vmlinux	00000058 current_kernel_time
40089730 g     F .vmlinux	00000018 generic_splice_sendpage
40083434 g     F .vmlinux	000000d8 kick_iocb
400f5a14 g     F .vmlinux	00000050 screen_pos
400954ac g     F .vmlinux	00000078 sys_inotify_rm_watch
40032adc g     F .vmlinux	00000028 get_files_struct
4004ee9c g     F .vmlinux	000000c8 grab_cache_page_nowait
400fd984 g     F .vmlinux	00000098 class_device_destroy
400662e8 g     F .vmlinux	00000088 shmem_zero_setup
400df410 g     F .vmlinux	0000002c get_random_bytes
40084e3c g     F .vmlinux	000000f0 seq_escape
401004b0 g     F .vmlinux	0000017c attribute_container_add_device
40031cdc g     F .vmlinux	00000254 register_console
4012c134 g     O .vmlinux	00000160 ebus_bus_type
4013584c g       .vmlinux	00000000 ___f_clear_clock_irq
4014ae64 g     F .vmlinux	00000024 hrtimers_init
4002db0c g     F .vmlinux	00000048 __wake_up_sync
4005b078 g     F .vmlinux	000000c8 __pte_alloc
400ffa14 g     F .vmlinux	00000048 devres_find
40032804 g     F .vmlinux	00000050 session_of_pgrp
4004e300 g     F .vmlinux	000000dc add_to_page_cache
4012dccc g     O .vmlinux	00000004 vm_swappiness
40059d54 g     F .vmlinux	00000044 congestion_end
400c7aac g     F .vmlinux	000000c0 pci_walk_bus
40017b60 g     F .vmlinux	00000028 sparc_pipe
4003c4b4 g     F .vmlinux	0000001c send_sig
40085f8c g     F .vmlinux	00000048 sys_removexattr
400457fc  w    F .vmlinux	00000008 compat_sys_mq_notify
40055a2c g     F .vmlinux	00000018 file_ra_state_init
403152f8 g     O .bss	0000000c prom_memlist
40035650 g     F .vmlinux	000000b8 sys_gettimeofday
40036020 g     F .vmlinux	000000fc jiffies_to_timeval
4013584c g       .vmlinux	00000000 ___f_free_pgd_fast
40020dec g       .vmlinux	00000000 viking_flush_cache_mm
400b27d8 g     F .vmlinux	000000b0 blk_rq_map_user_iov
4010bbf8 g     F .vmlinux	00000330 hid_parse_report
403143f8 g     O .bss	00000300 prom_reg_memlist
4003f7dc g     F .vmlinux	000000ac sys_getresuid
400bea64 g     F .vmlinux	00000048 __down_read_trylock
40060cf8 g     F .vmlinux	000000bc insert_vm_struct
40069404 g     F .vmlinux	000000cc sys_fchmod
4002e278 g     F .vmlinux	00000014 sys_sched_setparam
400109a0 g       .vmlinux	00000000 do_cp_disabled
40304324 g     O .bss	00000004 ctx_list_pool
40004000 g       .vmlinux	00000000 start
4008bb44 g     F .vmlinux	00000110 block_invalidatepage
40086e48 g     F .vmlinux	0000004c simple_release_fs
4004619c g     F .vmlinux	00000028 posix_cpu_timers_exit
400fb3c4 g     F .vmlinux	00000014 put_bus
40074680 g     F .vmlinux	00000134 vfs_link
401109bc g     F .vmlinux	0000010c __down_interruptible
40077480 g     F .vmlinux	000001ec sys_select
400457fc  w    F .vmlinux	00000008 sys_delete_module
40093d5c g     F .vmlinux	00000200 sys_ioprio_get
400453f0 g     F .vmlinux	00000044 autoremove_wake_function
4004844c g     F .vmlinux	000001cc hrtimer_run_queues
400afbc8 g     F .vmlinux	000000d4 elv_completed_request
401341c8 g       .vmlinux	00000000 ___fs_flush_sig_insns
4012e118 g     O .vmlinux	00000004 aio_max_nr
400355d8 g     F .vmlinux	00000078 sys_stime
40061ea4 g     F .vmlinux	0000004c sys_mremap
4006d490 g     F .vmlinux	0000001c vfs_stat
40086364 g     F .vmlinux	00000008 simple_sync_file
4015d2f0 g       .vmlinux	00000000 __con_initcall_end
4001e20c g     F .vmlinux	000000a0 calc_highpages
401144f8 g     O .vmlinux	0000006c proc_smaps_operations
4003543c g     F .vmlinux	000000e4 sys_setitimer
400f0d44 g     F .vmlinux	000003cc vc_resize
40313d6c g     O .bss	00000000 proc_subdir_lock
400c5078 g       .vmlinux	00000000 __strlen_user
400b47e8 g     F .vmlinux	00000040 copy_io_context
400851a8 g     F .vmlinux	00000020 seq_release_private
40087ec0 g     F .vmlinux	000001cc change_mnt_propagation
40132fc8 g     O .vmlinux	0000000c mtd_table_mutex
40013be8 g     F .vmlinux	0000003c sun4d_sbint_to_irq
400b62b8 g     F .vmlinux	00000034 bdev_read_only
40113c24 g     O .vmlinux	0000006c def_chr_fops
400ae598 g     F .vmlinux	00000014 cap_netlink_send
400bc988 g     F .vmlinux	00000024 subsystem_unregister
40319820 g     O .bss	00001000 con_buf
400cfc0c g     F .vmlinux	000001e8 fb_cmap_to_user
4008ae10 g     F .vmlinux	000000ac end_buffer_write_sync
4001787c g     F .vmlinux	0000029c arch_get_unmapped_area
4008478c g     F .vmlinux	00000080 seq_open
40059c14 g     F .vmlinux	00000090 congestion_wait
400883b0 g     F .vmlinux	000000c8 propagate_umount
401344a0 g       .vmlinux	00000000 ___fs_pgd_present
400e0924 g     F .vmlinux	0000008c get_current_tty
400c60c0 g     F .vmlinux	00000014 match_octal
403143e0 g     O .bss	00000004 prom_prev
4006c658 g     F .vmlinux	00000028 kill_anon_super
400deecc g     F .vmlinux	00000048 add_input_randomness
4013a5d4 g     F .vmlinux	00000114 change_floppy
40030b20 g     F .vmlinux	000000e8 print_tainted
40100000 g     F .vmlinux	00000064 devm_kzalloc
4004ed58 g     F .vmlinux	000000a4 find_get_pages_contig
403074d0 g     O .bss	00000004 panic_on_oops
4006d720 g     F .vmlinux	00000040 sys_newstat
40090600 g     F .vmlinux	0000003c bd_release
4012acd0 g     O .vmlinux	00000184 init_mm
40047ed4 g     F .vmlinux	000001bc hrtimer_forward
400c6a18 g     F .vmlinux	00000064 pcim_iomap_table
4013584c g       .vmlinux	00000000 ___f_flush_tlb_mm
40010a10 g       .vmlinux	00000000 do_hw_divzero
400a7380 g     F .vmlinux	00000078 ext2_count_free_inodes
4014ba74 g     F .vmlinux	00000024 free_bootmem
4007e884 g     F .vmlinux	00000158 iget5_locked
4007b48c g     F .vmlinux	000000fc get_locks_status
400cd978 g     F .vmlinux	000000b8 fb_get_buffer_offset
4014b9f4 g     F .vmlinux	00000014 free_bootmem_node
400b19b0 g     F .vmlinux	00000084 blk_plug_device
4004cb58 g     F .vmlinux	00000058 sys_fchown16
401071f4 g     F .vmlinux	0000006c input_release_device
4006edb0 g     F .vmlinux	00000120 search_binary_handler
400457fc  w    F .vmlinux	00000008 sys_getpeername
400870cc g     F .vmlinux	00000014 simple_attr_close
40020ef4 g       .vmlinux	00000000 tsunami_flush_cache_mm
40134210 g       .vmlinux	00000000 ___fs_sparc_unmapiorange
400189cc g     F .vmlinux	00000044 do_settimeofday
400a6968 g     F .vmlinux	00000210 ext2_delete_entry
40031a50 g     F .vmlinux	0000002c suspend_console
40040b28 g     F .vmlinux	0000002c sys_getrusage
4014d7a8 g     F .vmlinux	000000d8 inode_init
4007ed20 g     F .vmlinux	00000104 invalidate_inodes
403179b0 g     O .bss	00000004 amba_system_id
400c3490 g       .vmlinux	00000000 __copy_user_begin
4006ce00 g     F .vmlinux	000000bc register_chrdev_region
4004e698 g     F .vmlinux	00000084 filemap_write_and_wait_range
4014f6ec g     F .vmlinux	00000080 pci_device_add
40043cf0 g     F .vmlinux	00000390 sys_timer_create
400766c0 g     F .vmlinux	0000005c old_readdir
400cc48c g     F .vmlinux	00000044 pci_unmap_rom
40115a5c g     O .vmlinux	0000003c ext2_aops_xip
4002e28c g     F .vmlinux	00000050 sys_sched_getscheduler
4005a3cc g     F .vmlinux	000000d4 page_address
4009c134 g     F .vmlinux	000000b0 proc_lookup
40111d9c g     F .vmlinux	000000ac __wait_on_bit_lock
400d99c8 g     F .vmlinux	00000050 fbcon_set_bitops
40020e68 g       .vmlinux	00000000 viking_flush_tlb_range
400bc85c g     F .vmlinux	00000028 kset_register
400457fc  w    F .vmlinux	00000008 compat_sys_mq_timedreceive
40149648 g     F .vmlinux	0000010c sched_init
40062938 g     F .vmlinux	00000130 page_remove_rmap
40063df8 g     F .vmlinux	000000a8 remap_vmalloc_range
400bf224 g     F .vmlinux	00000090 strspn
400c48b4 g       .vmlinux	00000000 __muldi3
400711c4 g     F .vmlinux	00000038 deny_write_access
400d028c g     F .vmlinux	00000010 framebuffer_release
400ecd34 g     F .vmlinux	00000684 set_selection
400427dc g     F .vmlinux	00000090 rcu_barrier
4004e71c g     F .vmlinux	00000040 filemap_fdatawait
400b5954 g     F .vmlinux	00000024 blk_unregister_region
400c174c g     F .vmlinux	0000000c prom_getprev
4006cf74 g     F .vmlinux	00000024 cdev_put
4001c6a0 g     F .vmlinux	0000004c insw
40015464 g     F .vmlinux	00000168 svr4_getcontext
40040488 g     F .vmlinux	0000002c in_egroup_p
40053398 g     F .vmlinux	00000014 free_cold_page
4007e0f8 g     F .vmlinux	00000034 bmap
400c1a1c g     F .vmlinux	000000ac prom_apply_generic_ranges
401357b4 g       .vmlinux	00000000 ___is_page_shared
40307080 g     O .bss	00000004 sighand_cachep
400565fc g     F .vmlinux	000000fc activate_page
4011089c g     F .vmlinux	00000040 sha_init
400fc50c g     F .vmlinux	0000005c device_release_driver
40011a84 g       .vmlinux	00000000 srmmu_fwin_stackchk
40036e28 g     F .vmlinux	00000044 release_resource
4003a070 g     F .vmlinux	00000028 __round_jiffies_relative
40313610 g     O .bss	00000004 vmalloc_earlyreserve
400ecb4c g     F .vmlinux	000000f0 con_get_unimap
40142038 g     F .vmlinux	000000a4 device_scan
400f8a84 g     F .vmlinux	00000094 uart_match_port
40004000 g       .vmlinux	00000000 _stext
40302b9c g     O .bss	00000004 interrupt_enable
400cd7b4 g     F .vmlinux	0000001c fb_register_client
40111c20 g     F .vmlinux	0000001c schedule_timeout_uninterruptible
4004ddc0 g     F .vmlinux	00000040 acct_process
4013584c g       .vmlinux	00000000 ___f_pmd_page
400457fc  w    F .vmlinux	00000008 compat_sys_mq_open
4004d2cc g     F .vmlinux	0000002c sys_getgid16
4004c9c0 g     F .vmlinux	00000064 free_dma
4013584c g       .vmlinux	00000000 ___f_pgd_none
4002ddc8 g     F .vmlinux	00000048 can_nice
400c4f98 g       .vmlinux	00000000 strlen
4007fa44 g     F .vmlinux	00000074 free_fdtable_rcu
400906b8 g     F .vmlinux	00000240 bd_claim_by_disk
4009c688 g     F .vmlinux	00000098 proc_symlink
4012c4fc g     O .vmlinux	0000001c iomem_resource
40084430 g     F .vmlinux	0000035c sys_io_getevents
40032c40 g     F .vmlinux	000000ac put_fs_struct
400f542c g     F .vmlinux	0000002c con_get_cmap
40045560 g     F .vmlinux	00000028 wake_up_bit
4003a1d4 g     F .vmlinux	00000064 del_timer
40130e44 g     O .vmlinux	00000300 accent_table
4013584c g       .vmlinux	00000000 ___f_mmu_info
400f8694 g     F .vmlinux	000002cc uart_add_one_port
40117b00 g     O .vmlinux	00000064 dummy_con
40010ec8 g       .vmlinux	00000000 sys_pipe
400ffa5c g     F .vmlinux	00000058 devres_get
40035a18 g     F .vmlinux	00000078 timespec_trunc
40130db8 g     O .vmlinux	00000004 want_console
4012966c g       .vmlinux	00000000 __start_pci_fixups_enable
400a4420 g     F .vmlinux	00000050 devpts_get_tty
4003d7b8 g     F .vmlinux	0000024c copy_siginfo_to_user
400c2e48 g       .vmlinux	00000000 __csum_partial_copy_sparc_generic
40074264 g     F .vmlinux	00000018 sys_rmdir
40018ec0 g       .vmlinux	00000000 sunosgdtsize_low
40011df0 g       .vmlinux	00000000 ret_trap_lockless_ipi
40134698 g       .vmlinux	00000000 ___fs_flush_cache_range
4004250c g     F .vmlinux	00000034 get_task_pid
40112878 g     F .vmlinux	00000020 rt_mutex_lock_interruptible
40075358 g     F .vmlinux	000001a8 __page_symlink
4003a098 g     F .vmlinux	00000014 round_jiffies
40055e48 g     F .vmlinux	0000004c do_page_cache_readahead
4031ab28 g     O .bss	00000004 platform_notify
40313b20 g     O .bss	00000004 suid_dumpable
40017b88 g     F .vmlinux	0000028c sys_ipc
4014bb54 g     F .vmlinux	00000040 __alloc_bootmem_node
4012b19c g     O .vmlinux	00000004 irq_rcvreg
40011b1c g       .vmlinux	00000000 tsetup_7win_patch3
4006c2b4 g     F .vmlinux	000000d8 sys_ustat
400ba13c g     F .vmlinux	0000013c __bitmap_shift_right
400c78d4 g     F .vmlinux	00000038 pci_block_user_cfg_access
40071230 g     F .vmlinux	0000001c path_release_on_umount
400c5840 g       .vmlinux	00000000 .umul
40050368 g     F .vmlinux	00000304 generic_write_checks
40134e04 g       .vmlinux	00000000 ___fs_free_pgd_fast
4012dc50 g     O .vmlinux	00000004 min_free_kbytes
40063c34 g     F .vmlinux	00000044 vmalloc_32_user
400b5a4c g     F .vmlinux	00000030 get_gendisk
40074668 g     F .vmlinux	00000018 sys_symlink
40043360 g     F .vmlinux	00000020 param_get_int
4002d488 g     F .vmlinux	00000014 nr_context_switches
40094810 g     F .vmlinux	00000090 inotify_find_update_watch
4012d204 g     O .vmlinux	00000004 C_A_D
40076538 g     F .vmlinux	00000094 vfs_readdir
40020c54 g       .vmlinux	00000000 hypersparc_flush_page_for_dma
400488b4 g     F .vmlinux	00000104 set_acceptable_latency
400b0f4c g     F .vmlinux	000000d4 blk_queue_invalidate_tags
40019ea8 g     F .vmlinux	0000027c safe_compute_effective_address
40306688 g     O .bss	000000c0 per_cpu__kstat
40012a10 g     F .vmlinux	0000002c trap_init
400b0ab0 g     F .vmlinux	00000018 blk_queue_free_tags
00000000 g       *ABS*	00000000 ___i_page_copy
400850ec g     F .vmlinux	0000008c single_open
40062128 g     F .vmlinux	00000040 __anon_vma_merge
400c9174 g     F .vmlinux	000000e0 pcim_enable_device
4008ea40 g     F .vmlinux	00000034 bio_alloc
4005f8fc g     F .vmlinux	00000024 may_expand_vm
40079b6c g     F .vmlinux	00000064 lease_get_mtime
40037a30 g     F .vmlinux	00000074 register_sysctl_table
4030bbf4 g     O .bss	00000004 securebits
400bf020 g     F .vmlinux	00000050 strchr
4003ee0c g     F .vmlinux	00000064 kernel_restart
40313614 g     O .bss	00000004 vm_committed_space
4014beac g     F .vmlinux	0000008c memmap_init_zone
40134660 g       .vmlinux	00000000 ___fs___flush_page_to_ram
40010708 g       .vmlinux	00000000 patch_handler_irq
40017480 g     F .vmlinux	00000058 pci_dma_sync_sg_for_cpu
4012f370 g     O .vmlinux	00000004 pci_cardbus_mem_size
4014010c g     F .vmlinux	00000320 sun4m_init_IRQ
40115d50 g     O .vmlinux	00000054 ramfs_file_inode_operations
4001c22c g     F .vmlinux	000000d8 gptimer_connect
400bb058 g     F .vmlinux	000000a0 memparse
4005c6c8 g     F .vmlinux	00000008 __pud_alloc
40063b7c g     F .vmlinux	0000001c vmalloc
400e0a3c g     F .vmlinux	000000a4 start_tty
40016fdc g     F .vmlinux	0000001c sbus_map_sg
40069380 g     F .vmlinux	00000084 sys_chroot
40018b0c g     F .vmlinux	00000110 synchronize_user_stack
4003d014 g     F .vmlinux	00000074 ptrace_notify
40054d04 g     F .vmlinux	000000fc __set_page_dirty_nobuffers
40016ff8 g     F .vmlinux	00000020 sbus_unmap_sg
4012d610 g     O .vmlinux	0000000c acct_parm
4008688c g     F .vmlinux	00000078 simple_link
40313600 g     O .bss	00000004 mem_map
40135624 g       .vmlinux	00000000 ___as_pte_mkcleani
403042f0 g     O .bss	00000004 highend_pfn
40313d64 g     O .bss	00000004 proc_bus
4007c5b8 g     F .vmlinux	000000c0 d_invalidate
4006f73c g     F .vmlinux	000000d8 pipe_wait
4013584c g       .vmlinux	00000000 ___f_destroy_context
40035ea4 g     F .vmlinux	000000f0 jiffies_to_timespec
40112854 g     F .vmlinux	00000024 rt_mutex_lock
40117bc8 g     O .vmlinux	00000018 font_vga_8x16
4003b9e0 g     F .vmlinux	00000158 dequeue_signal
40083a54 g     F .vmlinux	0000002c sys_io_destroy
4012972c g       .vmlinux	00000000 __start___ksymtab
4008725c g     F .vmlinux	00000178 __mark_inode_dirty
4001415c g     F .vmlinux	00000004 leon_sbint_to_irq
40100220 g     F .vmlinux	00000148 attribute_container_device_trigger
4012fe98 g     O .vmlinux	0000000c tty_mutex
400e7638 g     F .vmlinux	00001038 n_tty_ioctl
400c7258 g     F .vmlinux	00000028 ___change_bit
4005eb90 g     F .vmlinux	00000120 __vm_enough_memory
4004db08 g     F .vmlinux	0000010c sys_acct
40134cc4 g       .vmlinux	00000000 ___fs_pte_pfn
40039a44 g     F .vmlinux	0000001c ptrace_may_attach
400f8b18 g     F .vmlinux	000003f4 sunserial_console_termios
4031365c g     O .bss	00000004 anon_vma_cachep
400f5b08 g     F .vmlinux	0000003c uart_write_wakeup
4012947c g       .vmlinux	00000000 __end_pci_fixups_header
40069f98 g     F .vmlinux	000000dc generic_file_llseek
40031454 g     F .vmlinux	0000004c wake_up_klogd
400c94b8 g     F .vmlinux	000000e4 pci_release_region
400817d8 g     F .vmlinux	000000fc copy_mount_options
4004119c g     F .vmlinux	000000e4 call_usermodehelper_pipe
4007f948 g     F .vmlinux	00000058 make_bad_inode
400f1280 g     F .vmlinux	00000030 scrollfront
400c6800 g     F .vmlinux	00000070 devm_ioremap_nocache
40012a80 g     F .vmlinux	00000020 local_irq_enable
400c507c g       .vmlinux	00000000 __strnlen_user
40059f88 g     F .vmlinux	000000a8 install_file_pte
40140e2c g     F .vmlinux	00000018 sbus_arch_preinit
4012e934 g     O .vmlinux	0000000c sysfs_rename_sem
400ddac0 g     F .vmlinux	0000003c leon3_rs_put_char
40016c48 g     F .vmlinux	0000002c dma_unmap_sg
400b02bc g     F .vmlinux	00000008 blk_queue_prep_rq
40062c08 g     F .vmlinux	000004ec try_to_unmap
40017058 g     F .vmlinux	00000074 register_proc_sparc_ioport
400a3dd8 g     F .vmlinux	00000044 sysfs_remove_bin_file
4008f0a0 g     F .vmlinux	00000290 bio_copy_user
4003ae5c g     F .vmlinux	0000000c sys_getpid
4003cd74 g     F .vmlinux	00000198 do_notify_parent
4008e8e8 g     F .vmlinux	00000158 bio_alloc_bioset
40079458 g     F .vmlinux	00000018 posix_lock_file_conf
40086e94 g     F .vmlinux	000000e4 simple_read_from_buffer
40035520 g     F .vmlinux	0000005c set_normalized_timespec
4006b4b4 g     F .vmlinux	0000000c get_max_files
4001c5f4 g     F .vmlinux	00000050 pmc_leon_need_fixup
400457fc  w    F .vmlinux	00000008 sys_lookup_dcookie
4012f290 g     O .vmlinux	00000014 class_device_attr_cpuaffinity
40302e6c g     O .bss	00000004 sparc_ttable
400107bc g       .vmlinux	00000000 mna_handler
40302f78 g     O .bss	00000050 fake_swapper_regs
4013584c g       .vmlinux	00000000 ___f_pte_mkdirty
40157b28 g     O .vmlinux	00000100 boot_command_line
40307084 g     O .bss	00000004 fs_cachep
400377c0 g     F .vmlinux	0000019c do_sysctl
4004dc14 g     F .vmlinux	00000020 acct_init_pacct
400af8a4 g     F .vmlinux	00000030 elv_add_request
4004cfbc g     F .vmlinux	0000003c sys_setfsgid16
40053344 g     F .vmlinux	00000014 free_hot_page
4005a27c g     F .vmlinux	00000150 set_page_address
400a0e94 g     F .vmlinux	000001d0 sysfs_setattr
40036654 g     F .vmlinux	0000004c irq_exit
40044494 g     F .vmlinux	00000030 sys_timer_getoverrun
4003ae68 g     F .vmlinux	00000010 sys_getppid
40010b8c g       .vmlinux	00000000 invalid_segment_patch1_1ff
400a1120 g     F .vmlinux	000000fc sysfs_create
4014d538 g     F .vmlinux	0000019c vfs_caches_init
4008e688 g     F .vmlinux	000000ec __bread
40055630 g     F .vmlinux	00000134 test_clear_page_writeback
400b6164 g     F .vmlinux	000000a0 alloc_disk_node
4012a0a4 g       .vmlinux	00000000 prom_vector_p
400823e0 g     F .vmlinux	000003c4 sys_pivot_root
401000ec g     F .vmlinux	00000008 attribute_container_classdev_to_container
401194f8 g     O .vmlinux	00000004 NR_TYPES
40048884 g     F .vmlinux	00000010 up_read
400b1b88 g     F .vmlinux	00000050 blk_cleanup_queue
4031598c g     O .bss	00000004 pcie_mch_quirk
400fb384 g     F .vmlinux	00000040 get_bus
400af410 g     F .vmlinux	00000060 elv_merged_request
4031ac90 g     O .bss	00000004 dma_chain
4003bfbc g     F .vmlinux	000000ac force_sig_info
400ae5ac g     F .vmlinux	0000001c cap_netlink_recv
4001c65c g     F .vmlinux	0000000c pmc_leon_idle
40018e9c g       .vmlinux	00000000 sunosmctl_low
4008b878 g     F .vmlinux	0000007c mark_buffer_dirty_inode
40011f70 g       .vmlinux	00000000 rtrap_patch4
4006929c g     F .vmlinux	00000064 sys_chdir
400fc9c4 g     F .vmlinux	000000bc driver_register
400ae614 g     F .vmlinux	000000a4 cap_inode_removexattr
40307078 g     O .bss	00000000 mmlist_lock
40115e10 g     O .vmlinux	0000003c ramfs_aops
400fab1c g     F .vmlinux	000000f0 sysdev_unregister
4005ee64 g     F .vmlinux	0000002c __vma_link_rb
40041ec0 g     F .vmlinux	00000058 put_pid
4006c868 g     F .vmlinux	0000008c get_sb_nodev
401471e0 g     F .vmlinux	000001f0 iommu_init
400860f0 g     F .vmlinux	00000050 generic_getxattr
4006d444 g     F .vmlinux	0000004c vfs_stat_fd
4013584c g       .vmlinux	00000000 ___f_mmu_lockarea
400116d0 g       .vmlinux	00000000 spnwin_patch3
4006ed18 g     F .vmlinux	00000098 remove_arg_zero
4001461c g     F .vmlinux	00000068 show_stack
40012230 g     F .vmlinux	00000064 instruction_dump
40154d74 g     F .vmlinux	00000128 vty_init
40033b2c g     F .vmlinux	00000024 complete_and_exit
4009e4cc g     F .vmlinux	0000002c create_seq_entry
4014f76c g     F .vmlinux	00000438 pci_scan_single_device
40313d60 g     O .bss	00000004 proc_net_stat
400a64e4 g     F .vmlinux	00000484 ext2_add_link
400fcc28 g     F .vmlinux	00000128 class_register
4008fea4 g     F .vmlinux	00000044 sb_min_blocksize
400b6204 g     F .vmlinux	00000014 alloc_disk
40020de8 g       .vmlinux	00000000 viking_flush_cache_page
40070c58 g     F .vmlinux	000000ac create_read_pipe
4006c5c0 g     F .vmlinux	00000098 set_anon_super
40129674 g       .vmlinux	00000000 __start_pci_fixups_resume
4009f7b0 g     F .vmlinux	0000002c __bdevname
40053b94 g     F .vmlinux	00000068 get_zeroed_page
400bcaa4 g     F .vmlinux	000000b4 kref_put
403041cc g     O .bss	00000108 sp_banks
4012d61c g     O .vmlinux	0000005c kernel_subsys
4003b0a0 g     F .vmlinux	00000048 msleep
4010c050 g     F .vmlinux	000004e4 hid_input_field
4003f100 g     F .vmlinux	00000044 ctrl_alt_del
40041f2c g     F .vmlinux	00000094 free_pid
4008ab60 g     F .vmlinux	00000014 fsstack_copy_inode_size
4006d338 g     F .vmlinux	0000003c cdev_init
40039a60 g     F .vmlinux	000000d8 ptrace_attach
400e1518 g     F .vmlinux	00000184 disassociate_ctty
400b5664 g     F .vmlinux	00000048 compat_blkdev_ioctl
4000d010 g       .vmlinux	00000000 sparc_ramdisk_image
400b4d80 g     F .vmlinux	000008e4 blkdev_ioctl
4007f144 g     F .vmlinux	00000054 inode_double_unlock
400457fc  w    F .vmlinux	00000008 compat_sys_set_mempolicy
40046f00 g     F .vmlinux	00000854 run_posix_cpu_timers
400dd460 g     F .vmlinux	0000022c leonuart_rx_chars
400c1ccc g     F .vmlinux	00000034 prom_getint
4012d7f4 g     O .vmlinux	00000018 generic_file_vm_ops
4003a238 g     F .vmlinux	00000090 __mod_timer
40089a50 g     F .vmlinux	0000028c sys_vmsplice
400676b0 g     F .vmlinux	000000ac __kmalloc
4003795c g     F .vmlinux	00000060 sys_sysctl
400457fc  w    F .vmlinux	00000008 sys_keyctl
40106aec g     F .vmlinux	0000002c leon3ps2_close
40145d18 g     F .vmlinux	000002d0 leon_inherit_prom_mappings
4006b620 g     F .vmlinux	00000168 __fput
400f8148 g     F .vmlinux	00000078 uart_console_write
4012f388 g     O .vmlinux	00000160 pci_bus_type
40114564 g     O .vmlinux	0000006c proc_maps_operations
4013584c g       .vmlinux	00000000 ___f_load_profile_irq
40041dec g     F .vmlinux	00000054 execute_in_process_context
40089544 g     F .vmlinux	000000d0 generic_file_splice_write_nolock
400fe820 g     F .vmlinux	0000014c kobj_map
40319120 g     O .bss	00000004 sel_cons
400c7390 g     F .vmlinux	00000050 pci_bus_read_config_byte
400bc1bc g     F .vmlinux	00000024 kobject_get
40062334 g     F .vmlinux	000000cc page_check_address
40085c5c g     F .vmlinux	00000050 sys_getxattr
4014b220 g     F .vmlinux	00000014 bootmem_bootmap_pages
400e9438 g     F .vmlinux	00001eb8 vt_ioctl
40038348 g     F .vmlinux	00000074 proc_dointvec_bset
4012972c g       .vmlinux	00000000 __stop___ksymtab_unused_gpl
40020fb4 g       .vmlinux	00000000 tsunami_copy_1page
4001d7e4 g     F .vmlinux	000001cc do_sun4c_fault
4006d16c g     F .vmlinux	00000024 cdev_del
400f9588 g     F .vmlinux	00000028 device_remove_bin_file
4003719c g     F .vmlinux	0000007c __request_region
4009f6e8 g     F .vmlinux	00000098 disk_name
40035e14 g     F .vmlinux	00000090 timespec_to_jiffies
40088100 g     F .vmlinux	000001dc propagate_mnt
400c72d0 g     F .vmlinux	0000001c atomic_set
400f9464 g     F .vmlinux	00000038 device_remove_file
4003f9d4 g     F .vmlinux	000000ac sys_getresgid
401156c0 g     O .vmlinux	00000054 sysfs_symlink_inode_operations
40313d9c g     O .bss	00000004 sysfs_mount
40086dac g     F .vmlinux	0000009c simple_pin_fs
4014f2b0 g     F .vmlinux	000002bc pci_read_bridge_bases
4004ecdc g     F .vmlinux	0000007c find_get_pages
4005f920 g     F .vmlinux	00000030 arch_unmap_area
40115798 g     O .vmlinux	0000006c bin_fops
40078674 g     F .vmlinux	0000003c locks_copy_lock
400fbc00 g     F .vmlinux	000001b0 bus_register
40140a7c g     F .vmlinux	00000140 leon_init_IRQ
40066df0 g     F .vmlinux	000000e8 kmem_cache_destroy
400dc0e4 g     F .vmlinux	000002d4 amba_print_config
40142838 g     F .vmlinux	00000080 prom_build_devicetree
403179ac g     O .bss	00000004 LEON3_IrqCtrl_Regs
4008b424 g     F .vmlinux	00000018 inode_has_buffers
400bf328 g     F .vmlinux	00000070 strpbrk
4014c9b0 g     F .vmlinux	00000028 swap_setup
4004e180 g     F .vmlinux	0000002c remove_from_page_cache
4030418c g     O .bss	00000004 leon_pci_iobase
40021148 g       .vmlinux	00000000 swift_flush_tlb_all
400c8798 g     F .vmlinux	00000040 pci_find_ht_capability
4030430c g     O .bss	00000014 per_cpu__mmu_gathers
4008fae0 g     F .vmlinux	00000118 bio_split
4005480c g     F .vmlinux	00000048 set_page_dirty_balance
4001bb38 g     F .vmlinux	00000014 of_unregister_driver
4002f218 g     F .vmlinux	00000014 sys_set_tid_address
4006bf64 g     F .vmlinux	000000d0 sync_supers
400a2c40 g     F .vmlinux	00000018 sysfs_remove_dir
40073e54 g     F .vmlinux	00000024 sys_mknod
40052050 g     F .vmlinux	00000064 mempool_alloc_pages
4007d710 g     F .vmlinux	0000009c d_path
400e5a30 g     F .vmlinux	0000005c is_ignored
401502d8 g     F .vmlinux	00000038 pci_scan_bus_parented
4012dc60 g     O .vmlinux	00000004 node_online_map
4030bc20 g     O .bss	00000008 wall_to_monotonic
4006d200 g     F .vmlinux	00000048 cdev_alloc
400e0310 g     F .vmlinux	00000054 tty_prepare_flip_string_flags
400c9460 g     F .vmlinux	00000058 pci_get_interrupt_pin
4012972c g       .vmlinux	00000000 __end_rio_route_ops
4009d41c g     F .vmlinux	00000088 proc_pid_statm
401009d4 g     F .vmlinux	00000010 transport_class_register
40155248 g     F .vmlinux	00000068 platform_driver_probe
400bc254 g     F .vmlinux	00000030 kobject_put
400b1dc0 g     F .vmlinux	00000014 blk_init_queue
4003fe34 g     F .vmlinux	00000010 sys_getpgrp
400bfa00 g     F .vmlinux	000001a8 simple_strtoull
401366f0 g       .vmlinux	00000000 __copy_user_end
4003d4f0 g     F .vmlinux	000000e0 sigprocmask
400b02c4 g     F .vmlinux	00000008 blk_queue_merge_bvec
40141ee0 g     F .vmlinux	00000010 time_init
40302e78 g     O .bss	00000100 reboot_command
40020e38 g       .vmlinux	00000000 viking_flush_tlb_mm
40073104 g     F .vmlinux	000000b8 vfs_create
40304358 g     O .bss	00000004 srmmu_modtype
40042db4 g     F .vmlinux	00000028 search_exception_tables
40304378 g     O .bss	00000004 srmmu_cache_pagetables
400384c0 g     F .vmlinux	00000054 proc_dointvec_minmax
4013584c g       .vmlinux	00000000 ___f_flush_tlb_all


