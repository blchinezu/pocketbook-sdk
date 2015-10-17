#ifndef __ASMARM_ELF_H
#define __ASMARM_ELF_H

#ifndef __ASSEMBLY__
/*
 * ELF register definitions..
 */
#include <asm/ptrace.h>
#include <asm/user.h>

typedef unsigned long elf_greg_t;
typedef unsigned long elf_freg_t[3];

#define ELF_NGREG (sizeof (struct pt_regs) / sizeof(elf_greg_t))
typedef elf_greg_t elf_gregset_t[ELF_NGREG];

typedef struct user_fp elf_fpregset_t;
#endif

#define EM_ARM	40
#define EF_ARM_APCS26 0x08
#define EF_ARM_SOFT_FLOAT 0x200
#define EF_ARM_EABI_MASK 0xFF000000

#define R_ARM_NONE	0
#define R_ARM_PC24	1
#define R_ARM_ABS32	2
#define R_ARM_CALL	28
#define R_ARM_JUMP24	29

/*
 * These are used to set parameters in the core dumps.
 */
#define ELF_CLASS	ELFCLASS32
#ifdef __ARMEB__
#define ELF_DATA	ELFDATA2MSB
#else
#define ELF_DATA	ELFDATA2LSB
#endif
#define ELF_ARCH	EM_ARM

/*
 * HWCAP flags - for elf_hwcap (in kernel) and AT_HWCAP
 */
#define HWCAP_SWP	1
#define HWCAP_HALF	2
#define HWCAP_THUMB	4
#define HWCAP_26BIT	8	/* Play it safe */
#define HWCAP_FAST_MULT	16
#define HWCAP_FPA	32
#define HWCAP_VFP	64
#define HWCAP_EDSP	128
#define HWCAP_JAVA	256
#define HWCAP_IWMMXT	512
#define HWCAP_CRUNCH	1024


#endif
