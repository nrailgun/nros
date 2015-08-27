/*
 * Memory Management Unit related macros and variables.
 *
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#ifndef __NROS_MEMORY_H
#define __NROS_MEMORY_H

#ifndef __ASSEMBLER__

#include <types.h>

#endif /* ifndef __ASSEMBLER__ */

#define SEG_NULL_ASM                                            \
	.word 0, 0;                                             \
	.byte 0, 0, 0, 0

// The 0xC0 means the limit is in 4096-byte units
// and (for executable segments) 32-bit mode.
#define SEG_ASM(type,base,lim)                                  \
	.word (((lim) >> 12) & 0xffff), ((base) & 0xffff);      \
	.byte (((base) >> 16) & 0xff), (0x90 | (type)),         \
	(0xC0 | (((lim) >> 28) & 0xf)), (((base) >> 24) & 0xff)

#define STA_X     0x8       // Executable segment
#define STA_E     0x4       // Expand down (non-executable segments)
#define STA_C     0x4       // Conforming code segment (executable only)
#define STA_W     0x2       // Writeable (non-executable segments)
#define STA_R     0x2       // Readable (executable segments)
#define STA_A     0x1       // Accessed

// Eflags register
#define FL_CF           0x00000001      // Carry Flag
#define FL_PF           0x00000004      // Parity Flag
#define FL_AF           0x00000010      // Auxiliary carry Flag
#define FL_ZF           0x00000040      // Zero Flag
#define FL_SF           0x00000080      // Sign Flag
#define FL_TF           0x00000100      // Trap Flag
#define FL_IF           0x00000200      // Interrupt Enable
#define FL_DF           0x00000400      // Direction Flag
#define FL_OF           0x00000800      // Overflow Flag
#define FL_IOPL_MASK    0x00003000      // I/O Privilege Level bitmask
#define FL_IOPL_0       0x00000000      //   IOPL == 0
#define FL_IOPL_1       0x00001000      //   IOPL == 1
#define FL_IOPL_2       0x00002000      //   IOPL == 2
#define FL_IOPL_3       0x00003000      //   IOPL == 3
#define FL_NT           0x00004000      // Nested Task
#define FL_RF           0x00010000      // Resume Flag
#define FL_VM           0x00020000      // Virtual 8086 mode
#define FL_AC           0x00040000      // Alignment Check
#define FL_VIF          0x00080000      // Virtual Interrupt Flag
#define FL_VIP          0x00100000      // Virtual Interrupt Pending
#define FL_ID           0x00200000      // ID flag

// Control Register flags
#define CR0_PE          0x00000001      // Protection Enable
#define CR0_MP          0x00000002      // Monitor coProcessor
#define CR0_EM          0x00000004      // Emulation
#define CR0_TS          0x00000008      // Task Switched
#define CR0_ET          0x00000010      // Extension Type
#define CR0_NE          0x00000020      // Numeric Errror
#define CR0_WP          0x00010000      // Write Protect
#define CR0_AM          0x00040000      // Alignment Mask
#define CR0_NW          0x20000000      // Not Writethrough
#define CR0_CD          0x40000000      // Cache Disable
#define CR0_PG          0x80000000      // Paging

#define CR4_PSE         0x00000010      // Page size extension

#define SEG_KCODE 1  // kernel code
#define SEG_KDATA 2  // kernel data+stack
#define SEG_KCPU  3  // kernel per-cpu data
#define SEG_UCODE 4  // user code
#define SEG_UDATA 5  // user data+stack
#define SEG_TSS   6  // this process's task state

#ifndef __ASSEMBLER__

// Segment Descriptor
struct segdesc {
	u32_t lim_15_0 : 16;  // Low bits of segment limit
	u32_t base_15_0 : 16; // Low bits of segment base address
	u32_t base_23_16 : 8; // Middle bits of segment base address
	u32_t type : 4;       // Segment type (see STS_ constants)
	u32_t s : 1;          // 0 = system, 1 = application
	u32_t dpl : 2;        // Descriptor Privilege Level
	u32_t p : 1;          // Present
	u32_t lim_19_16 : 4;  // High bits of segment limit
	u32_t avl : 1;        // Unused (available for software use)
	u32_t rsv1 : 1;       // Reserved
	u32_t db : 1;         // 0 = 16-bit segment, 1 = 32-bit segment
	u32_t g : 1;          // Granularity: limit scaled by 4K when set
	u32_t base_31_24 : 8; // High bits of segment base address
};

// Normal segment
#define SEG(type, base, lim, dpl) (struct segdesc)    \
{ ((lim) >> 12) & 0xffff, (u32_t)(base) & 0xffff,      \
	((u32_t)(base) >> 16) & 0xff, type, 1, dpl, 1,       \
	(u32_t)(lim) >> 28, 0, 0, 1, 1, (u32_t)(base) >> 24 }
#define SEG16(type, base, lim, dpl) (struct segdesc)  \
{ (lim) & 0xffff, (u32_t)(base) & 0xffff,              \
	((u32_t)(base) >> 16) & 0xff, type, 1, dpl, 1,       \
	(u32_t)(lim) >> 16, 0, 0, 1, 0, (u32_t)(base) >> 24 }

#endif /* ifndef __ASSEMBLER__ */

#define DPL_USER    0x3     // User DPL

// Application segment type bits
#define STA_X       0x8     // Executable segment
#define STA_E       0x4     // Expand down (non-executable segments)
#define STA_C       0x4     // Conforming code segment (executable only)
#define STA_W       0x2     // Writeable (non-executable segments)
#define STA_R       0x2     // Readable (executable segments)
#define STA_A       0x1     // Accessed

// System segment type bits
#define STS_T16A    0x1     // Available 16-bit TSS
#define STS_LDT     0x2     // Local Descriptor Table
#define STS_T16B    0x3     // Busy 16-bit TSS
#define STS_CG16    0x4     // 16-bit Call Gate
#define STS_TG      0x5     // Task Gate / Coum Transmitions
#define STS_IG16    0x6     // 16-bit Interrupt Gate
#define STS_TG16    0x7     // 16-bit Trap Gate
#define STS_T32A    0x9     // Available 32-bit TSS
#define STS_T32B    0xB     // Busy 32-bit TSS
#define STS_CG32    0xC     // 32-bit Call Gate
#define STS_IG32    0xE     // 32-bit Interrupt Gate
#define STS_TG32    0xF     // 32-bit Trap Gate

// A virtual address 'la' has a three-part structure as follows:
//
// +--------10------+-------10-------+---------12----------+
// | Page Directory |   Page Table   | Offset within Page  |
// |      Index     |      Index     |                     |
// +----------------+----------------+---------------------+
//  \--- PDIDX(va) --/ \--- PTIDX(va) --/ 

// page directory index
#define PDIDX(va)         (((u32_t)(va) >> PDIDX_SHFT) & 0x3FF)

// page table index
#define PTIDX(va)         (((u32_t)(va) >> PTIDX_SHFT) & 0x3FF)

// construct virtual address from indexes and offset
#define PGADDR(d, t, o) ((u32_t)((d) << PDIDX_SHFT | (t) << PTIDX_SHFT | (o)))

// Page directory and page table constants.
#define N_PDENT         1024    // # directory entries per page directory
#define N_PTENT         1024    // # PTEs per page table
#define PG_SIZE         4096    // bytes mapped by a page

#define PG_SHFT         12      // log2(PG_SIZE)
#define PTIDX_SHFT        12      // offset of PTIDX in a linear address
#define PDIDX_SHFT        22      // offset of PDIDX in a linear address

#define PAGE_ROUND_UP(sz)  (((sz)+PG_SIZE-1) & ~(PG_SIZE-1))
#define PAGE_ROUND_DOWN(a) (((a)) & ~(PG_SIZE-1))

// Page table/directory entry flags.
#define PTE_P           0x001   // Present
#define PTE_W           0x002   // Writeable
#define PTE_U           0x004   // User
#define PTE_PWT         0x008   // Write-Through
#define PTE_PCD         0x010   // Cache-Disable
#define PTE_A           0x020   // Accessed
#define PTE_D           0x040   // Dirty
#define PTE_PS          0x080   // Page Size
#define PTE_MBZ         0x180   // Bits must be zero

// Address in page table or page directory entry
#define PTE_ADDR(pte)   ((u32_t)(pte) & ~0xFFF)
#define PTE_FLAGS(pte)  ((u32_t)(pte) &  0xFFF)

#ifndef __ASSEMBLER__

// Task state segment format
struct taskstate {
	u32_t link;         // Old ts selector
	u32_t esp0;         // Stack pointers and segment selectors
	u16_t ss0;        //   after an increase in privilege level
	u16_t padding1;
	u32_t *esp1;
	u16_t ss1;
	u16_t padding2;
	u32_t *esp2;
	u16_t ss2;
	u16_t padding3;
	void *cr3;         // Page directory base
	u32_t *eip;         // Saved state from last task switch
	u32_t eflags;
	u32_t eax;          // More saved state (registers)
	u32_t ecx;
	u32_t edx;
	u32_t ebx;
	u32_t *esp;
	u32_t *ebp;
	u32_t esi;
	u32_t edi;
	u16_t es;         // Even more saved state (segment selectors)
	u16_t padding4;
	u16_t cs;
	u16_t padding5;
	u16_t ss;
	u16_t padding6;
	u16_t ds;
	u16_t padding7;
	u16_t fs;
	u16_t padding8;
	u16_t gs;
	u16_t padding9;
	u16_t ldt;
	u16_t padding10;
	u16_t t;          // Trap on task switch
	u16_t iomb;       // I/O map base address
};

// PAGEBREAK: 12
// Gate descriptors for interrupts and traps
struct gatedesc {
	u32_t off_15_0 : 16;   // low 16 bits of offset in segment
	u32_t cs : 16;         // code segment selector
	u32_t args : 5;        // # args, 0 for interrupt/trap gates
	u32_t rsv1 : 3;        // reserved(should be zero I guess)
	u32_t type : 4;        // type(STS_{TG,IG32,TG32})
	u32_t s : 1;           // must be 0 (system)
	u32_t dpl : 2;         // descriptor(meaning new) privilege level
	u32_t p : 1;           // Present
	u32_t off_31_16 : 16;  // high bits of offset in segment
};

// Set up a normal interrupt/trap gate descriptor.
// - istrap: 1 for a trap (= exception) gate, 0 for an interrupt gate.
//   interrupt gate clears FL_IF, trap gate leaves FL_IF alone
// - sel: Code segment selector for interrupt/trap handler
// - off: Offset in code segment for interrupt/trap handler
// - dpl: Descriptor Privilege Level -
//        the privilege level required for software to invoke
//        this interrupt/trap gate explicitly using an int instruction.
#define SETGATE(gate, istrap, sel, off, d)                \
{                                                         \
	(gate).off_15_0 = (u32_t)(off) & 0xffff;                \
	(gate).cs = (sel);                                      \
	(gate).args = 0;                                        \
	(gate).rsv1 = 0;                                        \
	(gate).type = (istrap) ? STS_TG32 : STS_IG32;           \
	(gate).s = 0;                                           \
	(gate).dpl = (d);                                       \
	(gate).p = 1;                                           \
	(gate).off_31_16 = (u32_t)(off) >> 16;                  \
}

#endif /* ifndef __ASSEMBLER__ */

#endif /* end of include guard: __NROS_MEMORY_H */
