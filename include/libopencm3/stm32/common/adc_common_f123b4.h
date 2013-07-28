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

/* ADC sample time register 1 (ADC_SMPR1) */
#define ADC_SMPR1(block)		MMIO32(block + 0x0c)
#define ADC1_SMPR1			ADC_SMPR1(ADC1)
#define ADC2_SMPR1			ADC_SMPR1(ADC2)
#define ADC3_SMPR1			ADC_SMPR1(ADC3)

/* ADC sample time register 2 (ADC_SMPR2) */
#define ADC_SMPR2(block)		MMIO32(block + 0x10)
#define ADC1_SMPR2			ADC_SMPR2(ADC1)
#define ADC2_SMPR2			ADC_SMPR2(ADC2)
#define ADC3_SMPR2			ADC_SMPR2(ADC3)

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

/* --- ADC_SMPR1 values ---------------------------------------------------- */

#define ADC_SMPR1_SMP17_LSB		21
#define ADC_SMPR1_SMP16_LSB		18
#define ADC_SMPR1_SMP15_LSB		15
#define ADC_SMPR1_SMP14_LSB		12
#define ADC_SMPR1_SMP13_LSB		9
#define ADC_SMPR1_SMP12_LSB		6
#define ADC_SMPR1_SMP11_LSB		3
#define ADC_SMPR1_SMP10_LSB		0
#define ADC_SMPR1_SMP17_MSK		(0x7 << ADC_SMP17_LSB)
#define ADC_SMPR1_SMP16_MSK		(0x7 << ADC_SMP16_LSB)
#define ADC_SMPR1_SMP15_MSK		(0x7 << ADC_SMP15_LSB)
#define ADC_SMPR1_SMP14_MSK		(0x7 << ADC_SMP14_LSB)
#define ADC_SMPR1_SMP13_MSK		(0x7 << ADC_SMP13_LSB)
#define ADC_SMPR1_SMP12_MSK		(0x7 << ADC_SMP12_LSB)
#define ADC_SMPR1_SMP11_MSK		(0x7 << ADC_SMP11_LSB)
#define ADC_SMPR1_SMP10_MSK		(0x7 << ADC_SMP10_LSB)

/* --- ADC_SMPR2 values ---------------------------------------------------- */

#define ADC_SMPR2_SMP9_LSB		27
#define ADC_SMPR2_SMP8_LSB		24
#define ADC_SMPR2_SMP7_LSB		21
#define ADC_SMPR2_SMP6_LSB		18
#define ADC_SMPR2_SMP5_LSB		15
#define ADC_SMPR2_SMP4_LSB		12
#define ADC_SMPR2_SMP3_LSB		9
#define ADC_SMPR2_SMP2_LSB		6
#define ADC_SMPR2_SMP1_LSB		3
#define ADC_SMPR2_SMP0_LSB		0
#define ADC_SMPR2_SMP9_MSK		(0x7 << ADC_SMP9_LSB)
#define ADC_SMPR2_SMP8_MSK		(0x7 << ADC_SMP8_LSB)
#define ADC_SMPR2_SMP7_MSK		(0x7 << ADC_SMP7_LSB)
#define ADC_SMPR2_SMP6_MSK		(0x7 << ADC_SMP6_LSB)
#define ADC_SMPR2_SMP5_MSK		(0x7 << ADC_SMP5_LSB)
#define ADC_SMPR2_SMP4_MSK		(0x7 << ADC_SMP4_LSB)
#define ADC_SMPR2_SMP3_MSK		(0x7 << ADC_SMP3_LSB)
#define ADC_SMPR2_SMP2_MSK		(0x7 << ADC_SMP2_LSB)
#define ADC_SMPR2_SMP1_MSK		(0x7 << ADC_SMP1_LSB)
#define ADC_SMPR2_SMP0_MSK		(0x7 << ADC_SMP0_LSB)

/* --- ADC_JOFRx, ADC_HTR, ADC_LTR values ---------------------------------- */

#define ADC_JOFFSET_LSB			0
#define ADC_JOFFSET_MSK			(0x7ff << 0)
#define ADC_HT_LSB			0
#define ADC_HT_MSK			(0x7ff << 0)
#define ADC_LT_LSB			0
#define ADC_LT_MSK			(0x7ff << 0)

/* --- ADC_SQR1 values ----------------------------------------------------- */

#define ADC_SQR1_L_LSB			20
#define ADC_SQR1_SQ16_LSB		15
#define ADC_SQR1_SQ15_LSB		10
#define ADC_SQR1_SQ14_LSB		5
#define ADC_SQR1_SQ13_LSB		0
#define ADC_SQR1_L_MSK			(0xf << ADC_SQR1_L_LSB)
#define ADC_SQR1_SQ16_MSK		(0x1f << ADC_SQR1_SQ16_LSB)
#define ADC_SQR1_SQ15_MSK		(0x1f << ADC_SQR1_SQ15_LSB)
#define ADC_SQR1_SQ14_MSK		(0x1f << ADC_SQR1_SQ14_LSB)
#define ADC_SQR1_SQ13_MSK		(0x1f << ADC_SQR1_SQ13_LSB)

/* --- ADC_SQR2 values ----------------------------------------------------- */

#define ADC_SQR2_SQ12_LSB		25
#define ADC_SQR2_SQ11_LSB		20
#define ADC_SQR2_SQ10_LSB		15
#define ADC_SQR2_SQ9_LSB		10
#define ADC_SQR2_SQ8_LSB		5
#define ADC_SQR2_SQ7_LSB		0
#define ADC_SQR2_SQ12_MSK		(0x1f << ADC_SQR2_SQ12_LSB)
#define ADC_SQR2_SQ11_MSK		(0x1f << ADC_SQR2_SQ11_LSB)
#define ADC_SQR2_SQ10_MSK		(0x1f << ADC_SQR2_SQ10_LSB)
#define ADC_SQR2_SQ9_MSK		(0x1f << ADC_SQR2_SQ9_LSB)
#define ADC_SQR2_SQ8_MSK		(0x1f << ADC_SQR2_SQ8_LSB)
#define ADC_SQR2_SQ7_MSK		(0x1f << ADC_SQR2_SQ7_LSB)

/* --- ADC_SQR3 values ----------------------------------------------------- */

#define ADC_SQR3_SQ6_LSB		25
#define ADC_SQR3_SQ5_LSB		20
#define ADC_SQR3_SQ4_LSB		15
#define ADC_SQR3_SQ3_LSB		10
#define ADC_SQR3_SQ2_LSB		5
#define ADC_SQR3_SQ1_LSB		0
#define ADC_SQR3_SQ6_MSK		(0x1f << ADC_SQR3_SQ6_LSB)
#define ADC_SQR3_SQ5_MSK		(0x1f << ADC_SQR3_SQ5_LSB)
#define ADC_SQR3_SQ4_MSK		(0x1f << ADC_SQR3_SQ4_LSB)
#define ADC_SQR3_SQ3_MSK		(0x1f << ADC_SQR3_SQ3_LSB)
#define ADC_SQR3_SQ2_MSK		(0x1f << ADC_SQR3_SQ2_LSB)
#define ADC_SQR3_SQ1_MSK		(0x1f << ADC_SQR3_SQ1_LSB)

/* --- ADC_JSQR values ----------------------------------------------------- */

#define ADC_JSQR_JL_LSB			20
#define ADC_JSQR_JL_SHIFT		20
#define ADC_JSQR_JL_VAL(val)		(((val) - 1) << ADC_JSQR_JL_LSB)

#define ADC_JSQR_JSQ_LSB(n)		(((n) - 1) * 5)
#define ADC_JSQR_JSQ_VAL(n,val)		((val) << ADC_JSQR_JSQ_LSB(n))

#define ADC_JSQR_JSQ4_LSB		ADC_JSQR_JSQ_LSB(3)
#define ADC_JSQR_JSQ3_LSB		ADC_JSQR_JSQ_LSB(2)
#define ADC_JSQR_JSQ2_LSB		ADC_JSQR_JSQ_LSB(1)
#define ADC_JSQR_JSQ1_LSB		ADC_JSQR_JSQ_LSB(0)

/* TODO: Remove the _MSK postfix */
#define ADC_JSQR_JL_MSK			ADC_JSQR_JL_VAL(3)
#define ADC_JSQR_JSQ4_MSK		ADC_JSQR_JSQ_VAL(4, 0x1f)
#define ADC_JSQR_JSQ3_MSK		ADC_JSQR_JSQ_VAL(3, 0x1f)
#define ADC_JSQR_JSQ2_MSK		ADC_JSQR_JSQ_VAL(2, 0x1f)
#define ADC_JSQR_JSQ1_MSK		ADC_JSQR_JSQ_VAL(1, 0x1f)

/** @defgroup adc_jsqr_jl ADC Number of channels in discontinuous mode from
 * injected channels.
 * @ingroup adc_defines
 *
 *@{*/
#define ADC_JSQR_JL_1CHANNELS		ADC_JSQR_JL_VAL(0)
#define ADC_JSQR_JL_2CHANNELS		ADC_JSQR_JL_VAL(1)
#define ADC_JSQR_JL_3CHANNELS		ADC_JSQR_JL_VAL(2)
#define ADC_JSQR_JL_4CHANNELS		ADC_JSQR_JL_VAL(3)
/**@}*/

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