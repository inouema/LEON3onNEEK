# $Id: Makefile,v 1.62 2000/12/15 00:41:17 davem Exp $
# Makefile for the linux kernel.
#

extra-y		:= head.o init_task.o vmlinux.lds

EXTRA_AFLAGS	:= -ansi

IRQ_OBJS := irq.o sun4m_irq.o sun4c_irq.o sun4d_irq.o leon_irq.o
obj-y    := entry.o wof.o wuf.o etrap.o rtrap.o traps.o $(IRQ_OBJS) \
	    process.o signal.o ioport.o setup.o idprom.o \
	    sys_sparc.o sunos_asm.o systbls.o \
	    time.o windows.o cpu.o devices.o sclow.o \
	    tadpole.o tick14.o ptrace.o sys_solaris.o \
	    unaligned.o muldiv.o semaphore.o prom.o of_device.o devres.o

devres-y = ../../../kernel/irq/devres.o

ifdef CONFIG_LEON_3
obj-y += leon_timer.o
obj-y += leon_pmc.o
obj-$(CONFIG_USB) += leon_usbhc.o
endif

ifndef CONFIG_LEON
obj-$(CONFIG_PCI) += pcic.o
else
obj-$(CONFIG_PCI) += leon_pci.o
obj-$(CONFIG_I2C_OCORES) += leon_i2c.o
obj-$(CONFIG_SPI_GRSPI) += leon_spic.o
obj-$(CONFIG_XILINX_SYSACE) += leon_sysace.o
endif

obj-$(CONFIG_SUN4) += sun4setup.o
obj-$(CONFIG_SMP) += trampoline.o smp.o sun4m_smp.o sun4d_smp.o leon_smp.o
obj-$(CONFIG_SUN_AUXIO) += auxio.o
ifndef CONFIG_LEON
obj-$(CONFIG_PCI) += ebus.o
endif
obj-$(CONFIG_SUN_PM) += apc.o pmc.o
obj-$(CONFIG_MODULES) += module.o sparc_ksyms.o
obj-$(CONFIG_SPARC_LED) += led.o

ifdef CONFIG_SUNOS_EMUL
obj-y += sys_sunos.o sunos_ioctl.o
endif
