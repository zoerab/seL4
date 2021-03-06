/*
 * Copyright 2019, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */

#ifndef __ARCH_MACHINE_PLIC_H
#define __ARCH_MACHINE_PLIC_H

/*
 * RISC-V defines a Platform-level interrupt controller (PLIC) (priv-1.10).
 * It is responsible for managing global interrupts in a RISC-V system.
 *
 * A PLIC takes multiple interrupt sources from external devices and delivers
 * them to different HART contexts depending on per IRQ configuration registers.
 * A HART context is a given privilege level on a given HART. If an IRQ is pending
 * for a particular HART context, the PLIC will raise an interrupt on that HART context's
 * External interrupt pending(EIP) pin and trigger an interrupt. The HART can then claim
 * the IRQ message by communicating with the PLIC where it will receive the highest
 * priority pending interrupt. The PLIC will deassert the EIP pin when there are
 * no more pending interrupts for that HART. When the HART has finished processing
 * the IRQ it completes the claim by notifying the PLIC. Until an IRQ claim has
 * completed, the PLIC won't generate futher interrupts for that IRQ.  In multicore
 * systems, if an IRQ is routed to multiple HARTs, the first HART to claim the IRQ
 * gets to process the IRQ and subsequent HARTs won't receive a claim for the same IRQ.
 *
 * We require each platform to provide the following functions:
 *   interrupt_t plic_get_claim(void): If called when an IRQ is pending, returns
 *     the pending priority and starts a claim process.  Will return irqInvalid
 *     if no IRQs are pending.
 *   void plic_complete_claim(interrupt_t irq): Complete a claim process for an
 *     interrupt.
 *   void plic_mask_irq(bool_t disable, interrupt_t irq): Disables or enables an
 *     IRQ at the PLIC.
 *   void plic_irq_set_trigger(interrupt_t irq, bool_t edge_triggered): Configure
 *     an IRQ source on the PLIC to be edge or level triggered. This function does
 *     not need to be implemented if the PLIC doesn't support configuring this.
 *   void plic_init_controller(void): Perform PLIC initialisation during boot.
 */
typedef uint32_t interrupt_t;

static inline interrupt_t plic_get_claim(void)
{
    return irqInvalid;
}

static inline void plic_complete_claim(interrupt_t irq)
{
}

static inline void plic_mask_irq(bool_t disable, interrupt_t irq)
{
}

#ifdef HAVE_SET_TRIGGER
static inline void plic_irq_set_trigger(interrupt_t irq, bool_t edge_triggered);
#endif

static inline void plic_init_controller(void)
{
}

#endif /* __ARCH_MACHINE_PLIC_H */
