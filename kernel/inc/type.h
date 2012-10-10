/*
 * type.h
 *
 *  Created on: Oct 10, 2012
 *      Author: sihai
 */

#ifndef TYPE_H_
#define TYPE_H_

#ifndef TARGET
#error TARGET NOT DEFINED
#endif

#if TARGET == x86
#include "arch/x86/inc/type.h"
#elif TARGET == ARM
#include "arch/arm/inc/type.h"
#else
#endif

#endif /* TYPE_H_ */
