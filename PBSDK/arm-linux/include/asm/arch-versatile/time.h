/*
 *  linux/include/asm-arm/arch-versatile/time.h
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#include <asm/system.h>
#include <asm/leds.h>

/*
 * Where is the timer (VA)?
 */
#define TIMER0_VA_BASE		 IO_ADDRESS(VERSATILE_TIMER0_1_BASE)
#define TIMER1_VA_BASE		(IO_ADDRESS(VERSATILE_TIMER0_1_BASE) + 0x20)
#define TIMER2_VA_BASE		 IO_ADDRESS(VERSATILE_TIMER2_3_BASE)
#define TIMER3_VA_BASE		(IO_ADDRESS(VERSATILE_TIMER2_3_BASE) + 0x20)
#define VA_IC_BASE		 IO_ADDRESS(VERSATILE_VIC_BASE) 

/*
 * How long is the timer interval?
 */
#define TIMER_INTERVAL	(TICKS_PER_uSEC * mSEC_10)
#if TIMER_INTERVAL >= 0x100000
#define TIMER_RELOAD	(TIMER_INTERVAL >> 8)		/* Divide by 256 */
#define TIMER_CTRL	0x88				/* Enable, Clock / 256 */
#define TICKS2USECS(x)	(256 * (x) / TICKS_PER_uSEC)
#elif TIMER_INTERVAL >= 0x10000
#define TIMER_RELOAD	(TIMER_INTERVAL >> 4)		/* Divide by 16 */
#define TIMER_CTRL	0x84				/* Enable, Clock / 16 */
#define TICKS2USECS(x)	(16 * (x) / TICKS_PER_uSEC)
#else
#define TIMER_RELOAD	(TIMER_INTERVAL)
#define TIMER_CTRL	0x80				/* Enable */
#define TICKS2USECS(x)	((x) / TICKS_PER_uSEC)
#endif

#define TIMER_CTRL_IE	(1 << 5)	/* Interrupt Enable */

/*
 * What does it look like?
 */
typedef struct TimerStruct {
	unsigned long TimerLoad;
	unsigned long TimerValue;
	unsigned long TimerControl;
	unsigned long TimerClear;
} TimerStruct_t;

extern unsigned long (*gettimeoffset)(void);

/*
 * Returns number of ms since last clock interrupt.  Note that interrupts
 * will have been disabled by do_gettimeoffset()
 */
static unsigned long versatile_gettimeoffset(void)
{
	volatile TimerStruct_t *timer0 = (TimerStruct_t *)TIMER0_VA_BASE;
	unsigned long ticks1, ticks2, status;

	/*
	 * Get the current number of ticks.  Note that there is a race
	 * condition between us reading the timer and checking for
	 * an interrupt.  We get around this by ensuring that the
	 * counter has not reloaded between our two reads.
	 */
	ticks2 = timer0->TimerValue & 0xffff;
	do {
		ticks1 = ticks2;
		status = __raw_readl(VA_IC_BASE + VIC_IRQ_RAW_STATUS);
		ticks2 = timer0->TimerValue & 0xffff;
	} while (ticks2 > ticks1);

	/*
	 * Number of ticks since last interrupt.
	 */
	ticks1 = TIMER_RELOAD - ticks2;

	/*
	 * Interrupt pending?  If so, we've reloaded once already.
	 *
	 * FIXME: Need to check this is effectively timer 0 that expires
	 */
	if (status & IRQMASK_TIMERINT0_1)
		ticks1 += TIMER_RELOAD;

	/*
	 * Convert the ticks to usecs
	 */
	return TICKS2USECS(ticks1);
}

/*
 * IRQ handler for the timer
 */
static irqreturn_t versatile_timer_interrupt(int irq, void *dev_id, struct pt_regs *regs)
{
	volatile TimerStruct_t *timer0 = (volatile TimerStruct_t *)TIMER0_VA_BASE;

	// ...clear the interrupt
	timer0->TimerClear = 1;

	do_leds();
	do_timer(regs);
	do_profile(regs);

	return IRQ_HANDLED;
}

/*
 * Set up timer interrupt, and return the current time in seconds.
 */
void __init time_init(void)
{
	volatile TimerStruct_t *timer0 = (volatile TimerStruct_t *)TIMER0_VA_BASE;
	volatile TimerStruct_t *timer1 = (volatile TimerStruct_t *)TIMER1_VA_BASE;
	volatile TimerStruct_t *timer2 = (volatile TimerStruct_t *)TIMER2_VA_BASE;
	volatile TimerStruct_t *timer3 = (volatile TimerStruct_t *)TIMER3_VA_BASE;

	/* 
	 * set clock frequency: 
	 *	VERSATILE_REFCLK is 32KHz
	 *	VERSATILE_TIMCLK is 1MHz
	 */
	*(volatile unsigned int *)IO_ADDRESS(VERSATILE_SCTL_BASE) |= 
	  ((VERSATILE_TIMCLK << VERSATILE_TIMER1_EnSel) | (VERSATILE_TIMCLK << VERSATILE_TIMER2_EnSel) | 
	   (VERSATILE_TIMCLK << VERSATILE_TIMER3_EnSel) | (VERSATILE_TIMCLK << VERSATILE_TIMER4_EnSel));

	timer_irq.handler = versatile_timer_interrupt;

	/*
	 * Initialise to a known state (all timers off)
	 */
	timer0->TimerControl = 0;
	timer1->TimerControl = 0;
	timer2->TimerControl = 0;
	timer3->TimerControl = 0;

	timer0->TimerLoad    = TIMER_RELOAD;
	timer0->TimerValue   = TIMER_RELOAD;
	timer0->TimerControl = TIMER_CTRL | 0x40 | TIMER_CTRL_IE;  /* periodic + IE */

	/* 
	 * Make irqs happen for the system timer
	 */
	setup_irq(IRQ_TIMERINT0_1, &timer_irq);
	gettimeoffset = versatile_gettimeoffset;
}
