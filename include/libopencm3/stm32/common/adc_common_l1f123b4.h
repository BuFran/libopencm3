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
#ifndef LIBOPENCM3_ADC_COMMON_L1F123B4_H
#define LIBOPENCM3_ADC_COMMON_L1F123B4_H

/**@{*/

#include <libopencm3/cm3/common.h>

/*****************************************************************************/
/* Module definitions                                                        */
/*****************************************************************************/

/*****************************************************************************/
/* Register definitions                                                      */
/*****************************************************************************/

/* ADC status register (ADC_SR) */
#define ADC_SR(block)			MMIO32(block + 0x00)
#define ADC1_SR				ADC_SR(ADC1)
#define ADC2_SR				ADC_SR(ADC2)
#define ADC3_SR				ADC_SR(ADC3)

/* ADC control register 1 (ADC_CR1) */
#define ADC_CR1(block)			MMIO32(block + 0x04)
#define ADC1_CR1			ADC_CR1(ADC1)
#define ADC2_CR1			ADC_CR1(ADC2)
#define ADC3_CR1			ADC_CR1(ADC3)

/* ADC control register 2 (ADC_CR2) */
#define ADC_CR2(block)			MMIO32(block + 0x08)
#define ADC1_CR2			ADC_CR2(ADC1)
#define ADC2_CR2			ADC_CR2(ADC2)
#define ADC3_CR2			ADC_CR2(ADC3)

/* ADC sample time registers (ADC_SMPRx, x=1..3) */
#define ADC_SMPR(n, block)		MMIO32(block + 0x08 + (n) * 4)
#define ADC_SMPR1(block)		ADC_SMPR(1, block)
#define ADC_SMPR2(block)		ADC_SMPR(2, block)
#define ADC_SMPR3(block)		ADC_SMPR(3, block)
#define ADC1_SMPR(n)			ADC_SMPR(n, ADC1)
#define ADC2_SMPR(n)			ADC_SMPR(n, ADC2)
#define ADC3_SMPR(n)			ADC_SMPR(n, ADC3)
#define ADC1_SMPR1			ADC_SMPR(1, ADC1)
#define ADC2_SMPR1			ADC_SMPR(1, ADC2)
#define ADC3_SMPR1			ADC_SMPR(1, ADC3)
#define ADC1_SMPR2			ADC_SMPR(2, ADC1)
#define ADC2_SMPR2			ADC_SMPR(2, ADC2)
#define ADC3_SMPR2			ADC_SMPR(2, ADC3)
#if defined(STM32L1)
#define ADC1_SMPR3			ADC_SMPR(3, ADC1)
#define ADC2_SMPR3			ADC_SMPR(3, ADC2)
#define ADC3_SMPR3			ADC_SMPR(3, ADC3)
#endif

#if defined(STM32L1)
#undef _ADC_SKIP
#define _ADC_SKIP			0x04
#define _ADC_SKIP2			0x0c
#else
#define _ADC_SKIP			0x00
#define _ADC_SKIP2			0x00
#endif

/* ADC injected channel data offset register x (ADC_JOFRx) (x=1..4) */
#define ADC_JOFR(n, block)		MMIO32(block + 0x10 + n * 4 + _ADC_SKIP)
#define ADC_JOFR1(block)		ADC_JOFR(1, block)
#define ADC_JOFR2(block)		ADC_JOFR(2, block)
#define ADC_JOFR3(block)		ADC_JOFR(3, block)
#define ADC_JOFR4(block)		ADC_JOFR(4, block)
#define ADC1_JOFR1			ADC_JOFR(1, ADC1)
#define ADC2_JOFR1			ADC_JOFR(1, ADC2)
#define ADC3_JOFR1			ADC_JOFR(1, ADC3)
#define ADC1_JOFR2			ADC_JOFR(2, ADC1)
#define ADC2_JOFR2			ADC_JOFR(2, ADC2)
#define ADC3_JOFR2			ADC_JOFR(2, ADC3)
#define ADC1_JOFR3			ADC_JOFR(3, ADC1)
#define ADC2_JOFR3			ADC_JOFR(3, ADC2)
#define ADC3_JOFR3			ADC_JOFR(3, ADC3)
#define ADC1_JOFR4			ADC_JOFR(4, ADC1)
#define ADC2_JOFR4			ADC_JOFR(4, ADC2)
#define ADC3_JOFR4			ADC_JOFR(4, ADC3)

/* ADC watchdog high threshold register (ADC_HTR) */
#define ADC_HTR(block)			MMIO32(block + 0x24 + _ADC_SKIP)
#define ADC1_HTR			ADC_HTR(ADC1)
#define ADC2_HTR			ADC_HTR(ADC2)
#define ADC3_HTR			ADC_HTR(ADC3)

/* ADC watchdog low threshold register (ADC_LTR) */
#define ADC_LTR(block)			MMIO32(block + 0x28 + _ADC_SKIP)
#define ADC1_LTR			ADC_LTR(ADC1_BASE)
#define ADC2_LTR			ADC_LTR(ADC2_BASE)
#define ADC3_LTR			ADC_LTR(ADC3_BASE)

#define ADC_SQR(n, block)		MMIO32(block + 0x28 + n * 4 + _ADC_SKIP)

/* ADC regular sequence register */
#define ADC_SQR1(block)			ADC_SQR(1, block)
#define ADC_SQR2(block)			ADC_SQR(2, block)
#define ADC_SQR3(block)			ADC_SQR(3, block)
#if defined(STM32L1)
#define ADC_SQR4(block)			ADC_SQR(4, block)
#define ADC_SQR5(block)			ADC_SQR(5, block)
#endif

#define ADC1_SQR1			ADC_SQR(1, ADC1)
#define ADC2_SQR1			ADC_SQR(1, ADC2)
#define ADC3_SQR1			ADC_SQR(1, ADC3)
#define ADC1_SQR2			ADC_SQR(2, ADC1)
#define ADC2_SQR2			ADC_SQR(2, ADC2)
#define ADC3_SQR2			ADC_SQR(2, ADC3)
#define ADC1_SQR3			ADC_SQR(3, ADC1)
#define ADC2_SQR3			ADC_SQR(3, ADC2)
#define ADC3_SQR3			ADC_SQR(3, ADC3)
#if defined(STM32L1)
#define ADC1_SQR4			ADC_SQR(4, ADC1)
#define ADC2_SQR4			ADC_SQR(4, ADC2)
#define ADC3_SQR4			ADC_SQR(4, ADC3)
#define ADC1_SQR5			ADC_SQR(5, ADC1)
#define ADC2_SQR5			ADC_SQR(5, ADC2)
#define ADC3_SQR5			ADC_SQR(5, ADC3)
#endif

/* ADC injected sequence register (ADC_JSQR) */
#define ADC_JSQR(block)			MMIO32(block + 0x38 + _ADC_SKIP2)
#define ADC1_JSQR			ADC_JSQR(ADC1)
#define ADC2_JSQR			ADC_JSQR(ADC2)
#define ADC3_JSQR			ADC_JSQR(ADC3)

/* ADC injected data register x (ADC_JDRx) (x=1..4) */
#define ADC_JDR(n, block)		MMIO32(block + 0x38 + n * 4 + _ADC_SKIP2)
#define ADC_JDR1(block)			ADC_JDR(1, block)
#define ADC_JDR2(block)			ADC_JDR(2, block)
#define ADC_JDR3(block)			ADC_JDR(3, block)
#define ADC_JDR4(block)			ADC_JDR(4, block)
#define ADC1_JDR1			ADC_JDR(1, ADC1)
#define ADC2_JDR1			ADC_JDR(1, ADC2)
#define ADC3_JDR1			ADC_JDR(1, ADC3)
#define ADC1_JDR2			ADC_JDR(2, ADC1)
#define ADC2_JDR2			ADC_JDR(2, ADC2)
#define ADC3_JDR2			ADC_JDR(2, ADC3)
#define ADC1_JDR3			ADC_JDR(3, ADC1)
#define ADC2_JDR3			ADC_JDR(3, ADC2)
#define ADC3_JDR3			ADC_JDR(3, ADC3)
#define ADC1_JDR4			ADC_JDR(4, ADC1)
#define ADC2_JDR4			ADC_JDR(4, ADC2)
#define ADC3_JDR4			ADC_JDR(4, ADC3)

/* ADC regular data register (ADC_DR) */
#define ADC_DR(block)			MMIO32(block + 0x4c + _ADC_SKIP2)
#define ADC1_DR				ADC_DR(ADC1)
#define ADC2_DR				ADC_DR(ADC2)
#define ADC3_DR				ADC_DR(ADC3)



/*****************************************************************************/
/* Register values                                                           */
/*****************************************************************************/

/* ADC_SR values ----------------------------------------------------------- */

#define ADC_SR_STRT			(1 << 4)
#define ADC_SR_JSTRT			(1 << 3)
#define ADC_SR_JEOC			(1 << 2)
#define ADC_SR_EOC			(1 << 1)
#define ADC_SR_AWD			(1 << 0)

/* ADC_CR1 values ---------------------------------------------------------- */

#define ADC_CR1_AWDEN			(1 << 23)
#define ADC_CR1_JAWDEN			(1 << 22)

#define ADC_CR1_DISCNUM_SHIFT		13
#define ADC_CR1_DISCNUM_VAL(x)		(((x)-1) << ADC_CR1_DISCNUM_SHIFT)
#define ADC_CR1_DISCNUM			ADC_CR1_DISCNUM_VAL(8)

/** @defgroup adc_cr1_discnum ADC Number of channels in discontinuous mode.
 * @ingroup adc_defines
 *
 *@{*/
#define ADC_CR1_DISCNUM_1CHANNELS	ADC_CR1_DISCNUM_VAL(1)
#define ADC_CR1_DISCNUM_2CHANNELS	ADC_CR1_DISCNUM_VAL(2)
#define ADC_CR1_DISCNUM_3CHANNELS	ADC_CR1_DISCNUM_VAL(3)
#define ADC_CR1_DISCNUM_4CHANNELS	ADC_CR1_DISCNUM_VAL(4)
#define ADC_CR1_DISCNUM_5CHANNELS	ADC_CR1_DISCNUM_VAL(5)
#define ADC_CR1_DISCNUM_6CHANNELS	ADC_CR1_DISCNUM_VAL(6)
#define ADC_CR1_DISCNUM_7CHANNELS	ADC_CR1_DISCNUM_VAL(7)
#define ADC_CR1_DISCNUM_8CHANNELS	ADC_CR1_DISCNUM_VAL(8)
/**@}*/

#define ADC_CR1_JDISCEN			(1 << 12)
#define ADC_CR1_DISCEN			(1 << 11)
#define ADC_CR1_JAUTO			(1 << 10)
#define ADC_CR1_AWDSGL			(1 << 9)
#define ADC_CR1_SCAN			(1 << 8)
#define ADC_CR1_JEOCIE			(1 << 7)
#define ADC_CR1_AWDIE			(1 << 6)
#define ADC_CR1_EOCIE			(1 << 5)

#define ADC_CR1_AWDCH_SHIFT		0
#define ADC_CR1_AWDCH			(0x1F << ADC_CR1_AWDCH_SHIFT)
#define ADC_CR1_AWDCH_CHANNEL(x)	((x) << ADC_CR1_AWDCH_SHIFT)


/* Notes:
 * ADC1: CH16 connected to the temperature sensor
 * ADC1: CH17 connected to the V_REFINT.
 * ADC2: CH16 and CH17 are internally connected to V_SS.
 * ADC3: CH9, CH14, CH15, CH16 and CH17 are internally connected to V_SS.
 */
/** @defgroup adc_watchdog_channel ADC watchdog channel
 * @ingroup adc_defines
 *
 *@{*/
#define ADC_CR1_AWDCH_CHANNEL0		ADC_CR1_AWDCH_CHANNEL(0)
#define ADC_CR1_AWDCH_CHANNEL1		ADC_CR1_AWDCH_CHANNEL(1)
#define ADC_CR1_AWDCH_CHANNEL2		ADC_CR1_AWDCH_CHANNEL(2)
#define ADC_CR1_AWDCH_CHANNEL3		ADC_CR1_AWDCH_CHANNEL(3)
#define ADC_CR1_AWDCH_CHANNEL4		ADC_CR1_AWDCH_CHANNEL(4)
#define ADC_CR1_AWDCH_CHANNEL5		ADC_CR1_AWDCH_CHANNEL(5)
#define ADC_CR1_AWDCH_CHANNEL6		ADC_CR1_AWDCH_CHANNEL(6)
#define ADC_CR1_AWDCH_CHANNEL7		ADC_CR1_AWDCH_CHANNEL(7)
#define ADC_CR1_AWDCH_CHANNEL8		ADC_CR1_AWDCH_CHANNEL(8)
#define ADC_CR1_AWDCH_CHANNEL9		ADC_CR1_AWDCH_CHANNEL(9)
#define ADC_CR1_AWDCH_CHANNEL10		ADC_CR1_AWDCH_CHANNEL(10)
#define ADC_CR1_AWDCH_CHANNEL11		ADC_CR1_AWDCH_CHANNEL(11)
#define ADC_CR1_AWDCH_CHANNEL12		ADC_CR1_AWDCH_CHANNEL(12)
#define ADC_CR1_AWDCH_CHANNEL13		ADC_CR1_AWDCH_CHANNEL(13)
#define ADC_CR1_AWDCH_CHANNEL14		ADC_CR1_AWDCH_CHANNEL(14)
#define ADC_CR1_AWDCH_CHANNEL15		ADC_CR1_AWDCH_CHANNEL(15)
#define ADC_CR1_AWDCH_CHANNEL16		ADC_CR1_AWDCH_CHANNEL(16)
#define ADC_CR1_AWDCH_CHANNEL17		ADC_CR1_AWDCH_CHANNEL(17)
#define ADC_CR1_AWDCH_CHANNEL18		ADC_CR1_AWDCH_CHANNEL(18)
#define ADC_CR1_AWDCH_TEMP		ADC_CR1_AWDCH_CHANNEL(16)
#define ADC_CR1_AWDCH_VREFINT		ADC_CR1_AWDCH_CHANNEL(17)
/**@}*/

/* ADC_CR1 values ---------------------------------------------------------- */

/* ALIGN: Data alignment. */
#define ADC_CR2_ALIGN_RIGHT		(0 << 11)
#define ADC_CR2_ALIGN_LEFT		(1 << 11)
#define ADC_CR2_ALIGN			(1 << 11)

/* DMA: Direct memory access mode. (ADC1 and ADC3 only!) */
#define ADC_CR2_DMA			(1 << 8)

#define ADC_CR2_CONT			(1 << 1)

/* ADON: A/D converter On/Off. */
/* Note: If any other bit in this register apart from ADON is changed at the
 * same time, then conversion is not triggered. This is to prevent triggering
 * an erroneous conversion.
 * Conclusion: Must be separately written.
 */
#define ADC_CR2_ADON			(1 << 0)

/* ADC_SMPR values --------------------------------------------------------- */

#define ADC_SMPR_SMP_LSB(chan)		((chan % 10) * 3)
#define ADC_SMPR_SMP_VAL(chan, val)	((val) << ADC_SMPR_SMP_LSB(chan))
#define ADC_SMPR_SMP(chan)		(0x07 << ADC_SMPR_SMP_LSB(chan))

#if !defined(STM32L1)
#define ADC_SMPR_SMP_REG(chan)		(2 - (chan / 10))
#else
#define ADC_SMPR_SMP_REG(chan)		(3 - (chan / 10))
#endif
/*
ADC1_SMPR(ADC_SMPR_SMP_REG(chan)) = ADC_SMPR_SMP_VAL(chan, val)
*/


#if !defined(STM32L1)
/* TODO in platform - specific file ? */

#define ADC_SMPR1_SMP18_LSB		ADC_SMPR_SMP_LSB(18)
#define ADC_SMPR1_SMP17_LSB		ADC_SMPR_SMP_LSB(17)
#define ADC_SMPR1_SMP16_LSB		ADC_SMPR_SMP_LSB(16)
#define ADC_SMPR1_SMP15_LSB		ADC_SMPR_SMP_LSB(15)
#define ADC_SMPR1_SMP14_LSB		ADC_SMPR_SMP_LSB(14)
#define ADC_SMPR1_SMP13_LSB		ADC_SMPR_SMP_LSB(13)
#define ADC_SMPR1_SMP12_LSB		ADC_SMPR_SMP_LSB(12)
#define ADC_SMPR1_SMP11_LSB		ADC_SMPR_SMP_LSB(11)
#define ADC_SMPR1_SMP10_LSB		ADC_SMPR_SMP_LSB(10)
#define ADC_SMPR2_SMP9_LSB		ADC_SMPR_SMP_LSB(9)
#define ADC_SMPR2_SMP8_LSB		ADC_SMPR_SMP_LSB(8)
#define ADC_SMPR2_SMP7_LSB		ADC_SMPR_SMP_LSB(7)
#define ADC_SMPR2_SMP6_LSB		ADC_SMPR_SMP_LSB(6)
#define ADC_SMPR2_SMP5_LSB		ADC_SMPR_SMP_LSB(5)
#define ADC_SMPR2_SMP4_LSB		ADC_SMPR_SMP_LSB(4)
#define ADC_SMPR2_SMP3_LSB		ADC_SMPR_SMP_LSB(3)
#define ADC_SMPR2_SMP2_LSB		ADC_SMPR_SMP_LSB(2)
#define ADC_SMPR2_SMP1_LSB		ADC_SMPR_SMP_LSB(1)
#define ADC_SMPR2_SMP0_LSB		ADC_SMPR_SMP_LSB(0)

#define ADC_SMPR1_SMP18			ADC_SMPR_SMP(18)
#define ADC_SMPR1_SMP17			ADC_SMPR_SMP(17)
#define ADC_SMPR1_SMP16			ADC_SMPR_SMP(16)
#define ADC_SMPR1_SMP15			ADC_SMPR_SMP(15)
#define ADC_SMPR1_SMP14			ADC_SMPR_SMP(14)
#define ADC_SMPR1_SMP13			ADC_SMPR_SMP(13)
#define ADC_SMPR1_SMP12			ADC_SMPR_SMP(12)
#define ADC_SMPR1_SMP11			ADC_SMPR_SMP(11)
#define ADC_SMPR1_SMP10			ADC_SMPR_SMP(10)
#define ADC_SMPR2_SMP9			ADC_SMPR_SMP(9)
#define ADC_SMPR2_SMP8			ADC_SMPR_SMP(8)
#define ADC_SMPR2_SMP7			ADC_SMPR_SMP(7)
#define ADC_SMPR2_SMP6			ADC_SMPR_SMP(6)
#define ADC_SMPR2_SMP5			ADC_SMPR_SMP(5)
#define ADC_SMPR2_SMP4			ADC_SMPR_SMP(4)
#define ADC_SMPR2_SMP3			ADC_SMPR_SMP(3)
#define ADC_SMPR2_SMP2			ADC_SMPR_SMP(2)
#define ADC_SMPR2_SMP1			ADC_SMPR_SMP(1)
#define ADC_SMPR2_SMP0			ADC_SMPR_SMP(0)

#else

#define ADC_SMPR1_SMP29_LSB		ADC_SMPR_SMP_LSB(29)
#define ADC_SMPR1_SMP28_LSB		ADC_SMPR_SMP_LSB(28)
#define ADC_SMPR1_SMP27_LSB		ADC_SMPR_SMP_LSB(27)
#define ADC_SMPR1_SMP26_LSB		ADC_SMPR_SMP_LSB(26)
#define ADC_SMPR1_SMP25_LSB		ADC_SMPR_SMP_LSB(25)
#define ADC_SMPR1_SMP24_LSB		ADC_SMPR_SMP_LSB(24)
#define ADC_SMPR1_SMP23_LSB		ADC_SMPR_SMP_LSB(23)
#define ADC_SMPR1_SMP22_LSB		ADC_SMPR_SMP_LSB(22)
#define ADC_SMPR1_SMP21_LSB		ADC_SMPR_SMP_LSB(21)
#define ADC_SMPR1_SMP20_LSB		ADC_SMPR_SMP_LSB(20)
#define ADC_SMPR2_SMP19_LSB		ADC_SMPR_SMP_LSB(19)
#define ADC_SMPR2_SMP18_LSB		ADC_SMPR_SMP_LSB(18)
#define ADC_SMPR2_SMP17_LSB		ADC_SMPR_SMP_LSB(17)
#define ADC_SMPR2_SMP16_LSB		ADC_SMPR_SMP_LSB(16)
#define ADC_SMPR2_SMP15_LSB		ADC_SMPR_SMP_LSB(15)
#define ADC_SMPR2_SMP14_LSB		ADC_SMPR_SMP_LSB(14)
#define ADC_SMPR2_SMP13_LSB		ADC_SMPR_SMP_LSB(13)
#define ADC_SMPR2_SMP12_LSB		ADC_SMPR_SMP_LSB(12)
#define ADC_SMPR2_SMP11_LSB		ADC_SMPR_SMP_LSB(11)
#define ADC_SMPR2_SMP10_LSB		ADC_SMPR_SMP_LSB(10)
#define ADC_SMPR3_SMP9_LSB		ADC_SMPR_SMP_LSB(9)
#define ADC_SMPR3_SMP8_LSB		ADC_SMPR_SMP_LSB(8)
#define ADC_SMPR3_SMP7_LSB		ADC_SMPR_SMP_LSB(7)
#define ADC_SMPR3_SMP6_LSB		ADC_SMPR_SMP_LSB(6)
#define ADC_SMPR3_SMP5_LSB		ADC_SMPR_SMP_LSB(5)
#define ADC_SMPR3_SMP4_LSB		ADC_SMPR_SMP_LSB(4)
#define ADC_SMPR3_SMP3_LSB		ADC_SMPR_SMP_LSB(3)
#define ADC_SMPR3_SMP2_LSB		ADC_SMPR_SMP_LSB(2)
#define ADC_SMPR3_SMP1_LSB		ADC_SMPR_SMP_LSB(1)
#define ADC_SMPR3_SMP0_LSB		ADC_SMPR_SMP_LSB(0)

#define ADC_SMPR1_SMP29			ADC_SMPR_SMP(29)
#define ADC_SMPR1_SMP28			ADC_SMPR_SMP(28)
#define ADC_SMPR1_SMP27			ADC_SMPR_SMP(27)
#define ADC_SMPR1_SMP26			ADC_SMPR_SMP(26)
#define ADC_SMPR1_SMP25			ADC_SMPR_SMP(25)
#define ADC_SMPR1_SMP24			ADC_SMPR_SMP(24)
#define ADC_SMPR1_SMP23			ADC_SMPR_SMP(23)
#define ADC_SMPR1_SMP22			ADC_SMPR_SMP(22)
#define ADC_SMPR1_SMP21			ADC_SMPR_SMP(21)
#define ADC_SMPR1_SMP20			ADC_SMPR_SMP(20)
#define ADC_SMPR2_SMP19			ADC_SMPR_SMP(19)
#define ADC_SMPR2_SMP18			ADC_SMPR_SMP(18)
#define ADC_SMPR2_SMP17			ADC_SMPR_SMP(17)
#define ADC_SMPR2_SMP16			ADC_SMPR_SMP(16)
#define ADC_SMPR2_SMP15			ADC_SMPR_SMP(15)
#define ADC_SMPR2_SMP14			ADC_SMPR_SMP(14)
#define ADC_SMPR2_SMP13			ADC_SMPR_SMP(13)
#define ADC_SMPR2_SMP12			ADC_SMPR_SMP(12)
#define ADC_SMPR2_SMP11			ADC_SMPR_SMP(11)
#define ADC_SMPR2_SMP10			ADC_SMPR_SMP(10)
#define ADC_SMPR3_SMP9			ADC_SMPR_SMP(9)
#define ADC_SMPR3_SMP8			ADC_SMPR_SMP(8)
#define ADC_SMPR3_SMP7			ADC_SMPR_SMP(7)
#define ADC_SMPR3_SMP6			ADC_SMPR_SMP(6)
#define ADC_SMPR3_SMP5			ADC_SMPR_SMP(5)
#define ADC_SMPR3_SMP4			ADC_SMPR_SMP(4)
#define ADC_SMPR3_SMP3			ADC_SMPR_SMP(3)
#define ADC_SMPR3_SMP2			ADC_SMPR_SMP(2)
#define ADC_SMPR3_SMP1			ADC_SMPR_SMP(1)
#define ADC_SMPR3_SMP0			ADC_SMPR_SMP(0)

#endif

/* ADC_JOFRx values -------------------------------------------------------- */

#define ADC_JOFR_JOFFSET		(0xfff << 0)

/* ADC_HTR_HT values ------------------------------------------------------- */

#define ADC_HTR_HT			(0xfff << 0)

/* ADC_LTR_LT values ------------------------------------------------------- */

#define ADC_LTR_LT			(0xfff << 0)

/* ADC_SQR values ---------------------------------------------------------- */

#define ADC_SQR_SQ_LSB(n)		(((n - 1) % 7) * 5)
#define ADC_SQR_SQ_VAL(n, val)		((val) << ADC_SQR_SQ_LSB(n))
#define ADC_SQR_SQ(n)			(0x1F << ADC_SQR_SQ_LSB(n))

#if !defined(STM32L1)
#define ADC_SQR_SQ_REG(n)		(3 - (n / 7))
#else
#define ADC_SQR_SQ_REG(n)		(5 - (n / 7))
#endif

/*
ADC1_SQR(ADC_SQR_SQ_REG(n)) = ADC_SQR_SQ_VAL(chan, val)
*/

#define ADC_SQR1_L_LSB			20

#if !defined(STM32L1)
#define ADC_SQR1_L			(0xf << ADC_SQR1_L_LSB)
#else
#define ADC_SQR1_L			(0x1f << ADC_SQR1_L_LSB)
#endif


#if !defined(STM32F1)

#define ADC_SQR1_SQ16_LSB		ADC_SQR_SQ_LSB(16)
#define ADC_SQR1_SQ15_LSB		ADC_SQR_SQ_LSB(15)
#define ADC_SQR1_SQ14_LSB		ADC_SQR_SQ_LSB(14)
#define ADC_SQR1_SQ13_LSB		ADC_SQR_SQ_LSB(13)
#define ADC_SQR2_SQ12_LSB		ADC_SQR_SQ_LSB(12)
#define ADC_SQR2_SQ11_LSB		ADC_SQR_SQ_LSB(11)
#define ADC_SQR2_SQ10_LSB		ADC_SQR_SQ_LSB(10)
#define ADC_SQR2_SQ9_LSB		ADC_SQR_SQ_LSB(9)
#define ADC_SQR2_SQ8_LSB		ADC_SQR_SQ_LSB(8)
#define ADC_SQR2_SQ7_LSB		ADC_SQR_SQ_LSB(7)
#define ADC_SQR3_SQ6_LSB		ADC_SQR_SQ_LSB(6)
#define ADC_SQR3_SQ5_LSB		ADC_SQR_SQ_LSB(5)
#define ADC_SQR3_SQ4_LSB		ADC_SQR_SQ_LSB(4)
#define ADC_SQR3_SQ3_LSB		ADC_SQR_SQ_LSB(3)
#define ADC_SQR3_SQ2_LSB		ADC_SQR_SQ_LSB(2)
#define ADC_SQR3_SQ1_LSB		ADC_SQR_SQ_LSB(1)

#define ADC_SQR1_SQ16			ADC_SQR_SQ(16)
#define ADC_SQR1_SQ15			ADC_SQR_SQ(15)
#define ADC_SQR1_SQ14			ADC_SQR_SQ(14)
#define ADC_SQR1_SQ13			ADC_SQR_SQ(13)
#define ADC_SQR2_SQ12			ADC_SQR_SQ(12)
#define ADC_SQR2_SQ11			ADC_SQR_SQ(11)
#define ADC_SQR2_SQ10			ADC_SQR_SQ(10)
#define ADC_SQR2_SQ9			ADC_SQR_SQ(9)
#define ADC_SQR2_SQ8			ADC_SQR_SQ(8)
#define ADC_SQR2_SQ7			ADC_SQR_SQ(7)
#define ADC_SQR3_SQ6			ADC_SQR_SQ(6)
#define ADC_SQR3_SQ5			ADC_SQR_SQ(5)
#define ADC_SQR3_SQ4			ADC_SQR_SQ(4)
#define ADC_SQR3_SQ3			ADC_SQR_SQ(3)
#define ADC_SQR3_SQ2			ADC_SQR_SQ(2)
#define ADC_SQR3_SQ1			ADC_SQR_SQ(1)

#define ADC_SQR1_SQ16_VAL(x)		ADC_SQR_SQ_VAL(16, x)
#define ADC_SQR1_SQ15_VAL(x)		ADC_SQR_SQ_VAL(15, x)
#define ADC_SQR1_SQ14_VAL(x)		ADC_SQR_SQ_VAL(14, x)
#define ADC_SQR1_SQ13_VAL(x)		ADC_SQR_SQ_VAL(13, x)
#define ADC_SQR2_SQ12_VAL(x)		ADC_SQR_SQ_VAL(12, x)
#define ADC_SQR2_SQ11_VAL(x)		ADC_SQR_SQ_VAL(11, x)
#define ADC_SQR2_SQ10_VAL(x)		ADC_SQR_SQ_VAL(10, x)
#define ADC_SQR2_SQ9_VAL(x)		ADC_SQR_SQ_VAL(9, x)
#define ADC_SQR2_SQ8_VAL(x)		ADC_SQR_SQ_VAL(8, x)
#define ADC_SQR2_SQ7_VAL(x)		ADC_SQR_SQ_VAL(7, x)
#define ADC_SQR3_SQ6_VAL(x)		ADC_SQR_SQ_VAL(6, x)
#define ADC_SQR3_SQ5_VAL(x)		ADC_SQR_SQ_VAL(5, x)
#define ADC_SQR3_SQ4_VAL(x)		ADC_SQR_SQ_VAL(4, x)
#define ADC_SQR3_SQ3_VAL(x)		ADC_SQR_SQ_VAL(3, x)
#define ADC_SQR3_SQ2_VAL(x)		ADC_SQR_SQ_VAL(2, x)
#define ADC_SQR3_SQ1_VAL(x)		ADC_SQR_SQ_VAL(1, x)

#else

#define ADC_SQR1_SQ28_LSB		ADC_SQR_SQ_LSB(28)
#define ADC_SQR1_SQ27_LSB		ADC_SQR_SQ_LSB(27)
#define ADC_SQR1_SQ26_LSB		ADC_SQR_SQ_LSB(26)
#define ADC_SQR1_SQ25_LSB		ADC_SQR_SQ_LSB(25)
#define ADC_SQR2_SQ24_LSB		ADC_SQR_SQ_LSB(24)
#define ADC_SQR2_SQ23_LSB		ADC_SQR_SQ_LSB(23)
#define ADC_SQR2_SQ22_LSB		ADC_SQR_SQ_LSB(22)
#define ADC_SQR2_SQ21_LSB		ADC_SQR_SQ_LSB(21)
#define ADC_SQR2_SQ20_LSB		ADC_SQR_SQ_LSB(20)
#define ADC_SQR2_SQ19_LSB		ADC_SQR_SQ_LSB(19)
#define ADC_SQR3_SQ18_LSB		ADC_SQR_SQ_LSB(18)
#define ADC_SQR3_SQ17_LSB		ADC_SQR_SQ_LSB(17)
#define ADC_SQR3_SQ16_LSB		ADC_SQR_SQ_LSB(16)
#define ADC_SQR3_SQ15_LSB		ADC_SQR_SQ_LSB(15)
#define ADC_SQR3_SQ14_LSB		ADC_SQR_SQ_LSB(14)
#define ADC_SQR3_SQ13_LSB		ADC_SQR_SQ_LSB(13)
#define ADC_SQR4_SQ12_LSB		ADC_SQR_SQ_LSB(12)
#define ADC_SQR4_SQ11_LSB		ADC_SQR_SQ_LSB(11)
#define ADC_SQR4_SQ10_LSB		ADC_SQR_SQ_LSB(10)
#define ADC_SQR4_SQ9_LSB		ADC_SQR_SQ_LSB(9)
#define ADC_SQR4_SQ8_LSB		ADC_SQR_SQ_LSB(8)
#define ADC_SQR4_SQ7_LSB		ADC_SQR_SQ_LSB(7)
#define ADC_SQR5_SQ6_LSB		ADC_SQR_SQ_LSB(6)
#define ADC_SQR5_SQ5_LSB		ADC_SQR_SQ_LSB(5)
#define ADC_SQR5_SQ4_LSB		ADC_SQR_SQ_LSB(4)
#define ADC_SQR5_SQ3_LSB		ADC_SQR_SQ_LSB(3)
#define ADC_SQR5_SQ2_LSB		ADC_SQR_SQ_LSB(2)
#define ADC_SQR5_SQ1_LSB		ADC_SQR_SQ_LSB(1)

#define ADC_SQR1_SQ28			ADC_SQR_SQ(28)
#define ADC_SQR1_SQ27			ADC_SQR_SQ(27)
#define ADC_SQR1_SQ26			ADC_SQR_SQ(26)
#define ADC_SQR1_SQ25			ADC_SQR_SQ(25)
#define ADC_SQR2_SQ24			ADC_SQR_SQ(24)
#define ADC_SQR2_SQ23			ADC_SQR_SQ(23)
#define ADC_SQR2_SQ22			ADC_SQR_SQ(22)
#define ADC_SQR2_SQ21			ADC_SQR_SQ(21)
#define ADC_SQR2_SQ20			ADC_SQR_SQ(20)
#define ADC_SQR2_SQ19			ADC_SQR_SQ(19)
#define ADC_SQR3_SQ18			ADC_SQR_SQ(18)
#define ADC_SQR3_SQ17			ADC_SQR_SQ(17)
#define ADC_SQR3_SQ16			ADC_SQR_SQ(16)
#define ADC_SQR3_SQ15			ADC_SQR_SQ(15)
#define ADC_SQR3_SQ14			ADC_SQR_SQ(14)
#define ADC_SQR3_SQ13			ADC_SQR_SQ(13)
#define ADC_SQR4_SQ12			ADC_SQR_SQ(12)
#define ADC_SQR4_SQ11			ADC_SQR_SQ(11)
#define ADC_SQR4_SQ10			ADC_SQR_SQ(10)
#define ADC_SQR4_SQ9			ADC_SQR_SQ(9)
#define ADC_SQR4_SQ8			ADC_SQR_SQ(8)
#define ADC_SQR4_SQ7			ADC_SQR_SQ(7)
#define ADC_SQR5_SQ6			ADC_SQR_SQ(6)
#define ADC_SQR5_SQ5			ADC_SQR_SQ(5)
#define ADC_SQR5_SQ4			ADC_SQR_SQ(4)
#define ADC_SQR5_SQ3			ADC_SQR_SQ(3)
#define ADC_SQR5_SQ2			ADC_SQR_SQ(2)
#define ADC_SQR5_SQ1			ADC_SQR_SQ(1)

#define ADC_SQR1_SQ28_VAL(x)		ADC_SQR_SQ_VAL(28, x)
#define ADC_SQR1_SQ27_VAL(x)		ADC_SQR_SQ_VAL(27, x)
#define ADC_SQR1_SQ26_VAL(x)		ADC_SQR_SQ_VAL(26, x)
#define ADC_SQR1_SQ25_VAL(x)		ADC_SQR_SQ_VAL(25, x)
#define ADC_SQR2_SQ24_VAL(x)		ADC_SQR_SQ_VAL(24, x)
#define ADC_SQR2_SQ23_VAL(x)		ADC_SQR_SQ_VAL(23, x)
#define ADC_SQR2_SQ22_VAL(x)		ADC_SQR_SQ_VAL(22, x)
#define ADC_SQR2_SQ21_VAL(x)		ADC_SQR_SQ_VAL(21, x)
#define ADC_SQR2_SQ20_VAL(x)		ADC_SQR_SQ_VAL(20, x)
#define ADC_SQR2_SQ19_VAL(x)		ADC_SQR_SQ_VAL(19, x)
#define ADC_SQR3_SQ18_VAL(x)		ADC_SQR_SQ_VAL(18, x)
#define ADC_SQR3_SQ17_VAL(x)		ADC_SQR_SQ_VAL(17, x)
#define ADC_SQR3_SQ16_VAL(x)		ADC_SQR_SQ_VAL(16, x)
#define ADC_SQR3_SQ15_VAL(x)		ADC_SQR_SQ_VAL(15, x)
#define ADC_SQR3_SQ14_VAL(x)		ADC_SQR_SQ_VAL(14, x)
#define ADC_SQR3_SQ13_VAL(x)		ADC_SQR_SQ_VAL(13, x)
#define ADC_SQR4_SQ12_VAL(x)		ADC_SQR_SQ_VAL(12, x)
#define ADC_SQR4_SQ11_VAL(x)		ADC_SQR_SQ_VAL(11, x)
#define ADC_SQR4_SQ10_VAL(x)		ADC_SQR_SQ_VAL(10, x)
#define ADC_SQR4_SQ9_VAL(x)		ADC_SQR_SQ_VAL(9, x)
#define ADC_SQR4_SQ8_VAL(x)		ADC_SQR_SQ_VAL(8, x)
#define ADC_SQR4_SQ7_VAL(x)		ADC_SQR_SQ_VAL(7, x)
#define ADC_SQR5_SQ6_VAL(x)		ADC_SQR_SQ_VAL(6, x)
#define ADC_SQR5_SQ5_VAL(x)		ADC_SQR_SQ_VAL(5, x)
#define ADC_SQR5_SQ4_VAL(x)		ADC_SQR_SQ_VAL(4, x)
#define ADC_SQR5_SQ3_VAL(x)		ADC_SQR_SQ_VAL(3, x)
#define ADC_SQR5_SQ2_VAL(x)		ADC_SQR_SQ_VAL(2, x)
#define ADC_SQR5_SQ1_VAL(x)		ADC_SQR_SQ_VAL(1, x)

#endif

/* --- ADC_JSQR values ----------------------------------------------------- */

#define ADC_JSQR_JL_LSB			20
#define ADC_JSQR_JL_VAL(val)		(((val) - 1) << ADC_JSQR_JL_LSB)
#define ADC_JSQR_JL(val)		(3 << ADC_JSQR_JL_LSB)

#define ADC_JSQR_JSQ_LSB(n)		(((n) - 1) * 5)
#define ADC_JSQR_JSQ_VAL(n,val)		((val) << ADC_JSQR_JSQ_LSB(n))

#define ADC_JSQR_JSQ4_LSB		ADC_JSQR_JSQ_LSB(3)
#define ADC_JSQR_JSQ3_LSB		ADC_JSQR_JSQ_LSB(2)
#define ADC_JSQR_JSQ2_LSB		ADC_JSQR_JSQ_LSB(1)
#define ADC_JSQR_JSQ1_LSB		ADC_JSQR_JSQ_LSB(0)

#define ADC_JSQR_JSQ4			ADC_JSQR_JSQ_VAL(4, 0x1f)
#define ADC_JSQR_JSQ3			ADC_JSQR_JSQ_VAL(3, 0x1f)
#define ADC_JSQR_JSQ2			ADC_JSQR_JSQ_VAL(2, 0x1f)
#define ADC_JSQR_JSQ1			ADC_JSQR_JSQ_VAL(1, 0x1f)

#define ADC_JSQR_JSQ4_VAL(x)		ADC_JSQR_JSQ_VAL(4, x)
#define ADC_JSQR_JSQ3_VAL(x)		ADC_JSQR_JSQ_VAL(3, x)
#define ADC_JSQR_JSQ2_VAL(x)		ADC_JSQR_JSQ_VAL(2, x)
#define ADC_JSQR_JSQ1_VAL(x)		ADC_JSQR_JSQ_VAL(1, x)

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