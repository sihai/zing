/*
 * asm.h
 *
 *  Created on: Jan 24, 2012
 *      Author: sihai
 */

#ifndef ASM_H_
#define ASM_H_

//
// 	macros to create x86 segment descriptor from assembler
//

/**
 *	Layout of segment descriptor
 *	Bits 63-56: Bits 31-24 of the base address 
 *	Bit 55: Granularity bit (set means the limit gets multiplied by 4K) 
 *	Bit 54: 16/32-bit segment (0=16-bit, 1=32-bit) 
 *	Bit 53: Reserved, should be zero 
 *	Bit 52: Reserved for OS 
 *	Bits 51-48: Bits 19-16 of the segment limit 
 *	Bit 47: The segment is present in memory (used for virtual memory stuff) 
 *	Bits 46-45: Descriptor privilege level (0=highest, 3=lowest) 
 *	Bit 44: Descriptor bit (0=system descriptor, 1=code/data descriptor) 
 *	Bits 43-41: The descriptor type (see below for an enumeration of the types) 
 *	Bit 40: Accessed bit (again, for use with virtual memory) 
 *	Bits 39-16: Bits 23-0 of the base address 
 *	Bits 15-0: Bits 15-0 of the segment limit 
 *
 */
// ¿Õ¶ÎÃèÊö·û
#define NULL_SEGMENT_DESCRIPTOR		\
	.word 0, 0;						\
	.byte 0, 0, 0, 0

//
#define DEFINE_SEGMENT_DESCRIPTOR(type, base, limit)					\
	.word (((limit) >> 12) & 0xffff), ((base) & 0xffff); 		\
	.byte (((base) >> 16) & 0xff), (0x90 | (type)), 			\
	(0xC0 | (((limit) >> 28) & 0xf)), (((base) >> 24) & 0xff)

// 
#define STA_X 0x8 		// Executable segment
#define STA_E 0x4 		// Expand down (non?executable segments)
#define STA_C 0x4 		// Conforming code segment (executable only)
#define STA_W 0x2 		// Writeable (non?executable segments)
#define STA_R 0x2 		// Readable (executable segments)
#define STA_A 0x1 		// Accessed

#endif /* ASM_H_ */