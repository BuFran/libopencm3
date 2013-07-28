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