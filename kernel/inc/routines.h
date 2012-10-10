/*
 * type.h
 *
 *  Created on: Oct 10, 2012
 *      Author: sihai
 */

#ifndef ROUTINES_H_
#define ROUTINES_H_

#ifndef TARGET
#error TARGET NOT DEFINED
#endif

#if TARGET == x86
#include "arch/x86/inc/routines.h"
#elif TARGET == ARM
#include "arch/arm/inc/routines.h"
#else
#endif

#endif /* ROUTINES_H_ */
