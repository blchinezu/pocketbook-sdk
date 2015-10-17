/*
 * linux/include/asm-arm/arch-nexuspci/io.h
 *
 * Copyright (C) 1997-1999 Russell King
 * Copyright (C) 2000 FutureTV Labs Ltd.
 */
#ifndef __ASM_ARM_ARCH_IO_H
#define __ASM_ARM_ARCH_IO_H

#define IO_SPACE_LIMIT 0xffff

/*
 * Translation of various region addresses to virtual addresses
 */
#define __io(a)			(PCIO_BASE + (a))
#if 1
#define __mem_pci(a)		((unsigned long)(a))
#define __mem_isa(a)		(PCIMEM_BASE + (unsigned long)(a))
#else

static inline unsigned long ___mem_pci(unsigned long a)
{
	/* PCI addresses must have been ioremapped */
	if (a <= 0xc0000000 || a >= 0xe0000000)
		*((int *)0) = 0;
	return a;
}

static inline unsigned long ___mem_isa(unsigned long a)
{
	BUG_ON(a >= 16*1048576);
	return PCIMEM_BASE + a;
}
#define __mem_pci(a)		___mem_pci((unsigned long)(a))
#define __mem_isa(a)		___mem_isa((unsigned long)(a))
#endif

/*
 * ioremap support - validate a PCI memory address,
 * and convert a PCI memory address to a physical
 * address for the page tables.
 */
#define iomem_valid_addr(iomem,sz)	\
	((iomem) < 0x80000000 && (iomem) + (sz) <= 0x80000000)
#define iomem_to_phys(iomem)	((iomem) + PLX_MEM_START)

#define __arch_ioremap(off,sz,nocache)				\
 ({								\
	unsigned long _off = (off), _size = (sz);		\
	void *_ret = (void *)0;					\
	if (iomem_valid_addr(_off, _size))			\
		_ret = __ioremap(iomem_to_phys(_off),_size,0);	\
	_ret;							\
 })

#define __arch_iounmap __iounmap

#endif
