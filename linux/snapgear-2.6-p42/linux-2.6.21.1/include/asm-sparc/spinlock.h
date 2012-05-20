/* spinlock.h: 32-bit Sparc spinlock support.
 *
 * Copyright (C) 1997 David S. Miller (davem@caip.rutgers.edu)
 */

#ifndef __SPARC_SPINLOCK_H
#define __SPARC_SPINLOCK_H

#include <linux/threads.h>	/* For NR_CPUS */

#ifndef __ASSEMBLY__

#include <asm/psr.h>

#define __raw_spin_is_locked(lock) (*((volatile unsigned char *)(lock)) != 0)

#define __raw_spin_unlock_wait(lock) \
	do { while (__raw_spin_is_locked(lock)) cpu_relax(); } while (0)

static inline void __raw_spin_lock(raw_spinlock_t *lock)
{
	__asm__ __volatile__(
	"\n1:\n\t"
#if !(defined(CONFIG_SMP) && (defined CONFIG_LEON || defined CONFIG_LEON_3))
	"ldstub	[%0], %%g2\n\t"
#else	
	"ldstuba	[%0]1, %%g2\n\t" /* ASI_LEON23_DCACHE_MISS */
#endif	
	"orcc	%%g2, 0x0, %%g0\n\t"
	"bne,a	2f\n\t"
	" ldub	[%0], %%g2\n\t"
	".subsection	2\n"
	"2:\n\t"
	"orcc	%%g2, 0x0, %%g0\n\t"
	"bne,a	2b\n\t"
	" ldub	[%0], %%g2\n\t"
	"b,a	1b\n\t"
	".previous\n"
	: /* no outputs */
	: "r" (lock)
	: "g2", "memory", "cc");
}

static inline int __raw_spin_trylock(raw_spinlock_t *lock)
{
	unsigned int result;
#if !(defined(CONFIG_SMP) && (defined CONFIG_LEON || defined CONFIG_LEON_3))
	__asm__ __volatile__("ldstub [%1], %0"
#else			     
	__asm__ __volatile__("ldstuba [%1]1, %0" /* ASI_LEON23_DCACHE_MISS */
#endif			     
			     : "=r" (result)
			     : "r" (lock)
			     : "memory");
	return (result == 0);
}

static inline void __raw_spin_unlock(raw_spinlock_t *lock)
{
	__asm__ __volatile__("stb %%g0, [%0]" : : "r" (lock) : "memory");
}

/* Read-write spinlocks, allowing multiple readers
 * but only one writer.
 *
 * NOTE! it is quite common to have readers in interrupts
 * but no interrupt writers. For those circumstances we
 * can "mix" irq-safe locks - any writer needs to get a
 * irq-safe write-lock, but readers can get non-irqsafe
 * read-locks.
 *
 * XXX This might create some problems with my dual spinlock
 * XXX scheme, deadlocks etc. -DaveM
 *
 * Sort of like atomic_t's on Sparc, but even more clever.
 *
 *	------------------------------------
 *	| 24-bit counter           | wlock |  raw_rwlock_t
 *	------------------------------------
 *	 31                       8 7     0
 *
 * wlock signifies the one writer is in or somebody is updating
 * counter. For a writer, if he successfully acquires the wlock,
 * but counter is non-zero, he has to release the lock and wait,
 * till both counter and wlock are zero.
 *
 * Unfortunately this scheme limits us to ~16,000,000 cpus.
 */
static inline void __read_lock(raw_rwlock_t *rw)
{
	register raw_rwlock_t *lp asm("g1");
	lp = rw;
#if !(defined(CONFIG_SMP) && (defined CONFIG_LEON || defined CONFIG_LEON_3))
	__asm__ __volatile__(
	"mov	%%o7, %%g4\n\t"
	"call	___rw_read_enter\n\t"
	" ldstub	[%%g1 + 3], %%g2\n"
	: /* no outputs */
	: "r" (lp)
	: "g2", "g4", "memory", "cc");
#else
	__asm__ __volatile__(
	"mov	%%o7, %%g4\n\t"
	"set	3, %%g3\n\t" /* ___rw_read_enter assumes g3 is three! */
	"call	___rw_read_enter\n\t"
	" ldstuba	[%%g1 + %%g3]1, %%g2\n"  /* ASI_LEON23_DCACHE_MISS */
	: /* no outputs */
	: "r" (lp)
	: "g2", "g3", "g4", "memory", "cc");
#endif	
}

#define __raw_read_lock(lock) \
do {	unsigned long flags; \
	local_irq_save(flags); \
	__read_lock(lock); \
	local_irq_restore(flags); \
} while(0)

static inline void __read_unlock(raw_rwlock_t *rw)
{
	register raw_rwlock_t *lp asm("g1");
	lp = rw;
#if !(defined(CONFIG_SMP) && (defined CONFIG_LEON || defined CONFIG_LEON_3))
	__asm__ __volatile__(
	"mov	%%o7, %%g4\n\t"
	"call	___rw_read_exit\n\t"
	" ldstub	[%%g1 + 3], %%g2\n"
	: /* no outputs */
	: "r" (lp)
	: "g2", "g4", "memory", "cc");
#else	
	__asm__ __volatile__(
	"mov	%%o7, %%g4\n\t"
	"set	3, %%g3\n\t" /* ___rw_read_exit assumes g3 is three! */
	"call	___rw_read_exit\n\t"
	" ldstuba	[%%g1 + %%g3]1, %%g2\n" /* ASI_LEON23_DCACHE_MISS */
	: /* no outputs */
	: "r" (lp)
	: "g2", "g3", "g4", "memory", "cc");
#endif	
}

#define __raw_read_unlock(lock) \
do {	unsigned long flags; \
	local_irq_save(flags); \
	__read_unlock(lock); \
	local_irq_restore(flags); \
} while(0)

static inline void __raw_write_lock(raw_rwlock_t *rw)
{
	register raw_rwlock_t *lp asm("g1");
	lp = rw;
#if !(defined(CONFIG_SMP) && (defined CONFIG_LEON || defined CONFIG_LEON_3))
	__asm__ __volatile__(
	"mov	%%o7, %%g4\n\t"
	"call	___rw_write_enter\n\t"
	" ldstub	[%%g1 + 3], %%g2\n"
	: /* no outputs */
	: "r" (lp)
	: "g2", "g4", "memory", "cc");
#else	
	__asm__ __volatile__(
	"mov	%%o7, %%g4\n\t"
	"set	3, %%g3\n\t" /* ___rw_write_enter assumes g3 is three! */
	"call	___rw_write_enter\n\t"
	" ldstuba	[%%g1 + %%g3]1, %%g2\n" /* ASI_LEON23_DCACHE_MISS */
	: /* no outputs */
	: "r" (lp)
	: "g2", "g3", "g4", "memory", "cc");
#endif
	*(volatile __u32 *)&lp->lock = ~0U;
}

static inline int __raw_write_trylock(raw_rwlock_t *rw)
{
	unsigned int val;

#if !(defined(CONFIG_SMP) && (defined CONFIG_LEON || defined CONFIG_LEON_3))
	__asm__ __volatile__("ldstub [%1 + 3], %0"
			     : "=r" (val)
			     : "r" (&rw->lock)
			     : "memory");
#else			     
	__asm__ __volatile__("set	3, %%g3\n\t"
			     "ldstuba [%1 + %%g3]1, %0" /* ASI_LEON23_DCACHE_MISS */
			     : "=r" (val)
			     : "r" (&rw->lock)
			     : "g3", "memory");
#endif			     

	if (val == 0) {
		val = rw->lock & ~0xff;
		if (val)
			((volatile u8*)&rw->lock)[3] = 0;
		else
			*(volatile u32*)&rw->lock = ~0U;
	}

	return (val == 0);
}

static inline int __read_trylock(raw_rwlock_t *rw)
{
	register raw_rwlock_t *lp asm("g1");
	register int res asm("o0");
	lp = rw;
#if !(defined(CONFIG_SMP) && (defined CONFIG_LEON || defined CONFIG_LEON_3))
	__asm__ __volatile__(
	"mov	%%o7, %%g4\n\t"
	"call	___rw_read_try\n\t"
	" ldstub	[%%g1 + 3], %%g2\n"
	: "=r" (res)
	: "r" (lp)
	: "g2", "g4", "memory", "cc");
#else
	__asm__ __volatile__(
	"mov	%%o7, %%g4\n\t"
	"set 3, %%g3\n\t" /* __rw_read_try assumes g3 is three! */
	"call	___rw_read_try\n\t"
	" ldstuba	[%%g1 + %%g3]1, %%g2\n"
	: "=r" (res)
	: "r" (lp)
	: "g2", "g3", "g4", "memory", "cc");
#endif
	return res;
}

#define __raw_read_trylock(lock) \
({	unsigned long flags; \
	int res; \
	local_irq_save(flags); \
	res = __read_trylock(lock); \
	local_irq_restore(flags); \
	res; \
})

#define __raw_write_unlock(rw)	do { (rw)->lock = 0; } while(0)

#define __raw_spin_lock_flags(lock, flags) __raw_spin_lock(lock)

#define _raw_spin_relax(lock)	cpu_relax()
#define _raw_read_relax(lock)	cpu_relax()
#define _raw_write_relax(lock)	cpu_relax()

#define __raw_read_can_lock(rw) (!((rw)->lock & 0xff))
#define __raw_write_can_lock(rw) (!(rw)->lock)

#endif /* !(__ASSEMBLY__) */

#endif /* __SPARC_SPINLOCK_H */
