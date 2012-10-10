/*
 * type.h
 *
 *  Created on: Oct 10, 2012
 *      Author: sihai
 */

#ifndef MM_H_
#define MM_H_

#if TARGET == x86
#include "arch/x86/inc/mmu.h"
#elif TARGET == ARM
#include "arch/arm/inc/mmu.h"
#endif

#endif /* MM_H_ */
