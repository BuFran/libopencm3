/** @addtogroup adc_defines
 */

/*
 * This file is part of the libopencm3 project.
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

/* THIS FILE SHOULD NOT BE INCLUDED DIRECTLY, BUT ONLY VIA ADC.H
The order of header inclusion is important. adc.h includes the device
specific memorymap.h header before including this header file.*/

/** @cond */
#ifdef LIBOPENCM3_ADC_H
/** @endcond */
#ifndef LIBOPENCM3_ADC_COMMON_F123B4_H
#define LIBOPENCM3_ADC_COMMON_F123B4_H

/**@{*/

#include <libopencm3/cm3/common.h>

/*****************************************************************************/
/* Module definitions                                                        */
/*****************************************************************************/

/*****************************************************************************/
/* Register definitions                                                      */
/*****************************************************************************/

/* ADC injected channel data offset register x (ADC_JOFRx) (x=1..4) */
#define ADC_JOFR1(block)		MMIO32(block + 0x14)
#define ADC_JOFR2(block)		MMIO32(block + 0x18)
#define ADC_JOFR3(block)		MMIO32(block + 0x1c)
#define ADC_JOFR4(block)		MMIO32(block + 0x20)
#define ADC1_JOFR1			ADC_JOFR1(ADC1)
#define ADC2_JOFR1			ADC_JOFR1(ADC2)
#define ADC3_JOFR1			ADC_JOFR1(ADC3)
#define ADC1_JOFR2			ADC_JOFR2(ADC1)
#define ADC2_JOFR2			ADC_JOFR2(ADC2)
#define ADC3_JOFR2			ADC_JOFR2(ADC3)
#define ADC1_JOFR3			ADC_JOFR3(ADC1)
#define ADC2_JOFR3			ADC_JOFR3(ADC2)
#define ADC3_JOFR3			ADC_JOFR3(ADC3)
#define ADC1_JOFR4			ADC_JOFR4(ADC1)
#define ADC2_JOFR4			ADC_JOFR4(ADC2)
#define ADC3_JOFR4			ADC_JOFR4(ADC3)

/* ADC watchdog high threshold register (ADC_HTR) */
#define ADC_HTR(block)			MMIO32(block + 0x24)
#define ADC1_HTR			ADC_HTR(ADC1)
#define ADC2_HTR			ADC_HTR(ADC2)
#define ADC3_HTR			ADC_HTR(ADC3)

/* ADC watchdog low threshold register (ADC_LTR) */
#define ADC_LTR(block)			MMIO32(block + 0x28)
#define ADC1_LTR			ADC_LTR(ADC1_BASE)
#define ADC2_LTR			ADC_LTR(ADC2_BASE)
#define ADC3_LTR			ADC_LTR(ADC3_BASE)


/* ADC regular sequence register 1 (ADC_SQR1) */
#define ADC_SQR1(block)			MMIO32(block + 0x2c)
#define ADC1_SQR1			ADC_SQR1(ADC1)
#define ADC2_SQR1			ADC_SQR1(ADC2)
#define ADC3_SQR1			ADC_SQR1(ADC3)

/* ADC regular sequence register 2 (ADC_SQR2) */
#define ADC_SQR2(block)			MMIO32(block + 0x30)
#define ADC1_SQR2			ADC_SQR2(ADC1)
#define ADC2_SQR2			ADC_SQR2(ADC2)
#define ADC3_SQR2			ADC_SQR2(ADC3)

/* ADC regular sequence register 3 (ADC_SQR3) */
#define ADC_SQR3(block)			MMIO32(block + 0x34)
#define ADC1_SQR3			ADC_SQR3(ADC1)
#define ADC2_SQR3			ADC_SQR3(ADC2)
#define ADC3_SQR3			ADC_SQR3(ADC3)

/* ADC injected sequence register (ADC_JSQR) */
#define ADC_JSQR(block)			MMIO32(block + 0x38)
#define ADC1_JSQR			ADC_JSQR(ADC1_BASE)
#define ADC2_JSQR			ADC_JSQR(ADC2_BASE)
#define ADC3_JSQR			ADC_JSQR(ADC3_BASE)

/* ADC injected data register x (ADC_JDRx) (x=1..4) */
#define ADC_JDR1(block)			MMIO32(block + 0x3c)
#define ADC_JDR2(block)			MMIO32(block + 0x40)
#define ADC_JDR3(block)			MMIO32(block + 0x44)
#define ADC_JDR4(block)			MMIO32(block + 0x48)
#define ADC1_JDR1			ADC_JDR1(ADC1)
#define ADC2_JDR1			ADC_JDR1(ADC2)
#define ADC3_JDR1			ADC_JDR1(ADC3)
#define ADC1_JDR2			ADC_JDR2(ADC1)
#define ADC2_JDR2			ADC_JDR2(ADC2)
#define ADC3_JDR2			ADC_JDR2(ADC3)
#define ADC1_JDR3			ADC_JDR3(ADC1)
#define ADC2_JDR3			ADC_JDR3(ADC2)
#define ADC3_JDR3			ADC_JDR3(ADC3)
#define ADC1_JDR4			ADC_JDR4(ADC1)
#define ADC2_JDR4			ADC_JDR4(ADC2)
#define ADC3_JDR4			ADC_JDR4(ADC3)

/* ADC regular data register (ADC_DR) */
#define ADC_DR(block)			MMIO32(block + 0x4c)
#define ADC1_DR				ADC_DR(ADC1)
#define ADC2_DR				ADC_DR(ADC2)
#define ADC3_DR				ADC_DR(ADC3)

/*****************************************************************************/
/* Register values                                                           */
/*****************************************************************************/

/*****************************************************************************/
/* API definitions                                                           */
/*****************************************************************************/

/*****************************************************************************/
/* API Functions                                                             */
/*****************************************************************************/

BEGIN_DECLS

END_DECLS



/**@}*/

#endif
/** @cond */
#else
#warning "adc_common_all.h should not be included explicitly, only via adc.h"
#endif
/** @endcond */