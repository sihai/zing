/*
 * type.h
 *
 *  Created on: Oct 10, 2012
 *      Author: sihai
 */

#ifndef ASM_H_
#define ASM_H_

#if TARGET == x86
#include "arch/x86/inc/asm.h"
#elif TARGET == ARM
#include "arch/arm/inc/asm.h"
#endif

#endif /* ASM_H_ */
