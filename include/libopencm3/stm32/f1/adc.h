/** @defgroup adc_defines ADC Defines

@brief <b>Defined Constants and Types for the STM32F1xx Analog to Digital
Converters</b>

@ingroup STM32F1xx_defines

@version 1.0.0

@author @htmlonly &copy; @endhtmlonly 2009
Edward Cheeseman <evbuilder@users.sourceforge.net>

@date 18 August 2012

LGPL License Terms @ref lgpl_license
 */
/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2009 Edward Cheeseman <evbuilder@users.sourceforge.net>
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

/**@{*/

#ifndef LIBOPENCM3_ADC_H
#define LIBOPENCM3_ADC_H

#include <libopencm3/stm32/memorymap.h>
#include <libopencm3/cm3/common.h>
#include <libopencm3/stm32/adc_common_l1f123b4.h>

/*****************************************************************************/
/* Module definitions                                                        */
/*****************************************************************************/

/* ADC port base addresses (for convenience) */
/****************************************************************************/
/** @defgroup adc_reg_base ADC register base addresses
@ingroup adc_defines

@{*/
#define ADC1				ADC1_BASE
#define ADC2				ADC2_BASE
#define ADC3				ADC3_BASE
/**@}*/

/*****************************************************************************/
/* Register definitions                                                      */
/*****************************************************************************/

/*****************************************************************************/
/* Register values                                                           */
/*****************************************************************************/

/* --- ADC Channels -------------------------------------------------------- */

/*****************************************************************************/
/** @defgroup adc_channel ADC Channel Numbers
@ingroup adc_defines

@{*/
#define ADC_CHANNEL0		0x00
#define ADC_CHANNEL1		0x01
#define ADC_CHANNEL2		0x02
#define ADC_CHANNEL3		0x03
#define ADC_CHANNEL4		0x04
#define ADC_CHANNEL5		0x05
#define ADC_CHANNEL6		0x06
#define ADC_CHANNEL7		0x07
#define ADC_CHANNEL8		0x08
#define ADC_CHANNEL9		0x09
#define ADC_CHANNEL10		0x0A
#define ADC_CHANNEL11		0x0B
#define ADC_CHANNEL12		0x0C
#define ADC_CHANNEL13		0x0D
#define ADC_CHANNEL14		0x0E
#define ADC_CHANNEL15		0x0F
#define ADC_CHANNEL16		0x10
#define ADC_CHANNEL17		0x11
/**@}*/
#define ADC_MASK		    0x1F
#define ADC_SHIFT		    0

/* --- ADC_CR1 values ------------------------------------------------------ */



/* Note: Bits [21:20] are reserved, and must be kept at reset value. */

/* DUALMOD[3:0]: Dual mode selection. (ADC1 only) */
/* Legend:
 * IND: Independent mode.
 * CRSISM: Combined regular simultaneous + injected simultaneous mode.
 * CRSATM: Combined regular simultaneous + alternate trigger mode.
 * CISFIM: Combined injected simultaneous + fast interleaved mode.
 * CISSIM: Combined injected simultaneous + slow interleaved mode.
 * ISM: Injected simultaneous mode only.
 * RSM: Regular simultaneous mode only.
 * FIM: Fast interleaved mode only.
 * SIM: Slow interleaved mode only.
 * ATM: Alternate trigger mode only.
 */
/*****************************************************************************/
/* ADC_CR1 DUALMOD[3:0] ADC Mode Selection */
/** @defgroup adc_cr1_dualmod ADC Mode Selection
@ingroup adc_defines

@{*/
/** Independent (non-dual) mode */
#define ADC_CR1_DUALMOD_IND             (0x0 << 16)
/** Combined regular simultaneous + injected simultaneous mode. */
#define ADC_CR1_DUALMOD_CRSISM          (0x1 << 16)
/** Combined regular simultaneous + alternate trigger mode. */
#define ADC_CR1_DUALMOD_CRSATM          (0x2 << 16)
/** Combined injected simultaneous + fast interleaved mode. */
#define ADC_CR1_DUALMOD_CISFIM          (0x3 << 16)
/** Combined injected simultaneous + slow interleaved mode. */
#define ADC_CR1_DUALMOD_CISSIM          (0x4 << 16)
/** Injected simultaneous mode only. */
#define ADC_CR1_DUALMOD_ISM             (0x5 << 16)
/** Regular simultaneous mode only. */
#define ADC_CR1_DUALMOD_RSM             (0x6 << 16)
/** Fast interleaved mode only. */
#define ADC_CR1_DUALMOD_FIM             (0x7 << 16)
/** Slow interleaved mode only. */
#define ADC_CR1_DUALMOD_SIM             (0x8 << 16)
/** Alternate trigger mode only. */
#define ADC_CR1_DUALMOD_ATM             (0x9 << 16)
/**@}*/
#define ADC_CR1_DUALMOD_MASK		(0xF << 16)
#define ADC_CR1_DUALMOD_SHIFT		16

/* --- ADC_CR2 values ------------------------------------------------------- */

/* TSVREFE: */ /** Temperature sensor and V_REFINT enable. (ADC1 only!) */
#define ADC_CR2_TSVREFE			(1 << 23)

/* SWSTART: */ /** Start conversion of regular channels. */
#define ADC_CR2_SWSTART			(1 << 22)

/* JSWSTART: */ /** Start conversion of injected channels. */
#define ADC_CR2_JSWSTART		(1 << 21)

/* EXTTRIG: */ /** External trigger conversion mode for regular channels. */
#define ADC_CR2_EXTTRIG			(1 << 20)

/* EXTSEL[2:0]: External event select for regular group. */
/* The following are only valid for ADC1 and ADC2. */
/*****************************************************************************/
/* ADC_CR2 EXTSEL[2:0] ADC Trigger Identifier for ADC1 and ADC2 */
/** @defgroup adc_trigger_regular_12 ADC Trigger Identifier for ADC1 and ADC2
@ingroup adc_defines

@{*/
/** Timer 1 Compare Output 1 */
#define ADC_CR2_EXTSEL_TIM1_CC1		(0x0 << 17)
/** Timer 1 Compare Output 2 */
#define ADC_CR2_EXTSEL_TIM1_CC2		(0x1 << 17)
/** Timer 1 Compare Output 3 */
#define ADC_CR2_EXTSEL_TIM1_CC3		(0x2 << 17)
/** Timer 2 Compare Output 2 */
#define ADC_CR2_EXTSEL_TIM2_CC2		(0x3 << 17)
/** Timer 3 Trigger Output */
#define ADC_CR2_EXTSEL_TIM3_TRGO	(0x4 << 17)
/** Timer 4 Compare Output 4 */
#define ADC_CR2_EXTSEL_TIM4_CC4		(0x5 << 17)
/** External Interrupt 11 */
#define ADC_CR2_EXTSEL_EXTI11		(0x6 << 17)
/** Software Trigger */
#define ADC_CR2_EXTSEL_SWSTART		(0x7 << 17)
/**@}*/

/* The following are only valid for ADC3 */
/*****************************************************************************/
/* ADC_CR2 EXTSEL[2:0] ADC Trigger Identifier for ADC3 */
/** @defgroup adc_trigger_regular_3 ADC Trigger Identifier for ADC3
@ingroup adc_defines

@{*/
/** Timer 2 Compare Output 1 */
#define ADC_CR2_EXTSEL_TIM3_CC1		(0x0 << 17)
/** Timer 2 Compare Output 3 */
#define ADC_CR2_EXTSEL_TIM2_CC3		(0x1 << 17)
/** Timer 1 Compare Output 3 */
#define ADC_CR2_EXTSEL_TIM1_CC3		(0x2 << 17)
/** Timer 8 Compare Output 1 */
#define ADC_CR2_EXTSEL_TIM8_CC1		(0x3 << 17)
/** Timer 8 Trigger Output */
#define ADC_CR2_EXTSEL_TIM8_TRGO	(0x4 << 17)
/** Timer 5 Compare Output 1 */
#define ADC_CR2_EXTSEL_TIM5_CC1		(0x5 << 17)
/** Timer 5 Compare Output 3 */
#define ADC_CR2_EXTSEL_TIM5_CC3		(0x6 << 17)
/**@}*/

#define ADC_CR2_EXTSEL_MASK		(0x7 << 17)
#define ADC_CR2_EXTSEL_SHIFT		17

/* Note: Bit 16 is reserved, must be kept at reset value. */

/* JEXTTRIG: External trigger conversion mode for injected channels. */
#define ADC_CR2_JEXTTRIG		(1 << 15)

/* JEXTSEL[2:0]: External event selection for injected group. */
/* The following are only valid for ADC1 and ADC2. */
/*****************************************************************************/
/* ADC_CR2 JEXTSEL[2:0] ADC Injected Trigger Identifier for ADC1 and ADC2 */
/** @defgroup adc_trigger_injected_12 ADC Injected Trigger Identifier for ADC1
and ADC2
@ingroup adc_defines

@{*/
/** Timer 1 Trigger Output */
#define ADC_CR2_JEXTSEL_TIM1_TRGO	(0x0 << 12)
/** Timer 1 Compare Output 4 */
#define ADC_CR2_JEXTSEL_TIM1_CC4	(0x1 << 12)
/** Timer 2 Trigger Output */
#define ADC_CR2_JEXTSEL_TIM2_TRGO	(0x2 << 12)
/** Timer 2 Compare Output 1 */
#define ADC_CR2_JEXTSEL_TIM2_CC1	(0x3 << 12)
/** Timer 3 Compare Output 4 */
#define ADC_CR2_JEXTSEL_TIM3_CC4	(0x4 << 12)
/** Timer 4 Trigger Output */
#define ADC_CR2_JEXTSEL_TIM4_TRGO	(0x5 << 12)
/** External Interrupt 15 */
#define ADC_CR2_JEXTSEL_EXTI15		(0x6 << 12)
/** Injected Software Trigger */
#define ADC_CR2_JEXTSEL_JSWSTART	(0x7 << 12) /* Software start. */
/**@}*/

/* The following are the different meanings for ADC3 only. */
/*****************************************************************************/
/* ADC_CR2 JEXTSEL[2:0] ADC Injected Trigger Identifier for ADC3 */
/** @defgroup adc_trigger_injected_3 ADC Injected Trigger Identifier for ADC3
@ingroup adc_defines

@{*/
/** Timer 1 Trigger Output */
#define ADC_CR2_JEXTSEL_TIM1_TRGO	(0x0 << 12)
/** Timer 1 Compare Output 4 */
#define ADC_CR2_JEXTSEL_TIM1_CC4	(0x1 << 12)
/** Timer 4 Compare Output 3 */
#define ADC_CR2_JEXTSEL_TIM4_CC3	(0x2 << 12)
/** Timer 8 Compare Output 2 */
#define ADC_CR2_JEXTSEL_TIM8_CC2	(0x3 << 12)
/** Timer 8 Compare Output 4 */
#define ADC_CR2_JEXTSEL_TIM8_CC4	(0x4 << 12)
/** Timer 5 Trigger Output */
#define ADC_CR2_JEXTSEL_TIM5_TRGO	(0x5 << 12)
/** Timer 5 Compare Output 4 */
#define ADC_CR2_JEXTSEL_TIM5_CC4	(0x6 << 12)
/** Injected Software Trigger */
#define ADC_CR2_JEXTSEL_JSWSTART	(0x7 << 12) /* Software start. */
/**@}*/

#define ADC_CR2_JEXTSEL_MASK		(0x7 << 12)
#define ADC_CR2_JEXTSEL_SHIFT		12

/* RSTCAL: Reset calibration. */
#define ADC_CR2_RSTCAL			(1 << 3)

/* CAL: A/D Calibration. */
#define ADC_CR2_CAL			(1 << 2)


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

/* --- ADC_SMPRx values ---------------------------------------------------- */
/*****************************************************************************/
/* ADC_SMPRG ADC Sample Time Selection for Channels */
/** @defgroup adc_sample_rg ADC Sample Time Selection for All Channels
@ingroup adc_defines

@{*/
#define ADC_SMPR_SMP_1DOT5CYC		0x0
#define ADC_SMPR_SMP_7DOT5CYC		0x1
#define ADC_SMPR_SMP_13DOT5CYC		0x2
#define ADC_SMPR_SMP_28DOT5CYC		0x3
#define ADC_SMPR_SMP_41DOT5CYC		0x4
#define ADC_SMPR_SMP_55DOT5CYC		0x5
#define ADC_SMPR_SMP_71DOT5CYC		0x6
#define ADC_SMPR_SMP_239DOT5CYC		0x7
/**@}*/

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
#define ADC_JSQR_JSQ4_LSB		15
#define ADC_JSQR_JSQ3_LSB		10
#define ADC_JSQR_JSQ2_LSB		5
#define ADC_JSQR_JSQ1_LSB		0

/* JL[2:0]: Discontinuous mode channel count injected channels. */
/*****************************************************************************/
/** @defgroup adc_jsqr_jl ADC Number of channels in discontinuous mode from
injected channels.
@ingroup adc_defines

@{*/
#define ADC_JSQR_JL_1CHANNELS       (0x0 << ADC_JSQR_JL_LSB)
#define ADC_JSQR_JL_2CHANNELS       (0x1 << ADC_JSQR_JL_LSB)
#define ADC_JSQR_JL_3CHANNELS       (0x2 << ADC_JSQR_JL_LSB)
#define ADC_JSQR_JL_4CHANNELS       (0x3 << ADC_JSQR_JL_LSB)
/**@}*/
#define ADC_JSQR_JL_SHIFT		20
#define ADC_JSQR_JL_MSK			(0x2 << ADC_JSQR_JL_LSB)
#define ADC_JSQR_JSQ4_MSK		(0x1f << ADC_JSQR_JSQ4_LSB)
#define ADC_JSQR_JSQ3_MSK		(0x1f << ADC_JSQR_JSQ3_LSB)
#define ADC_JSQR_JSQ2_MSK		(0x1f << ADC_JSQR_JSQ2_LSB)
#define ADC_JSQR_JSQ1_MSK		(0x1f << ADC_JSQR_JSQ1_LSB)

#define ADC_JSQR_JSQ_VAL(n,val)		((val) << (((n) - 1) * 5))
#define ADC_JSQR_JL_VAL(val)		(((val) - 1) << ADC_JSQR_JL_SHIFT)

/* --- ADC_JDRx, ADC_DR values --------------------------------------------- */

#define ADC_JDATA_LSB			0
#define ADC_DATA_LSB			0
#define ADC_ADC2DATA_LSB		16 /* ADC1 only (dual mode) */
#define ADC_JDATA_MSK			(0xffff << ADC_JDATA_LSB)
#define ADC_DATA_MSK			(0xffff << ADC_DA)
#define ADC_ADC2DATA_MSK		(0xffff << ADC_ADC2DATA_LSB)
					/* ADC1 only (dual mode) */

/*****************************************************************************/
/* API definitions                                                           */
/*****************************************************************************/

/*****************************************************************************/
/* API Functions                                                             */
/*****************************************************************************/

BEGIN_DECLS

void adc_power_on(uint32_t adc);
void adc_start_conversion_direct(uint32_t adc);
void adc_set_single_channel(uint32_t adc, uint8_t channel);
void adc_set_dual_mode(uint32_t mode);
bool adc_eoc(uint32_t adc);
bool adc_eoc_injected(uint32_t adc);
uint32_t adc_read_regular(uint32_t adc);
uint32_t adc_read_injected(uint32_t adc, uint8_t reg);
void adc_set_injected_offset(uint32_t adc, uint8_t reg, uint32_t offset);
void adc_enable_analog_watchdog_regular(uint32_t adc);
void adc_disable_analog_watchdog_regular(uint32_t adc);
void adc_enable_analog_watchdog_injected(uint32_t adc);
void adc_disable_analog_watchdog_injected(uint32_t adc);
void adc_enable_discontinuous_mode_regular(uint32_t adc, uint8_t length);
void adc_disable_discontinuous_mode_regular(uint32_t adc);
void adc_enable_discontinuous_mode_injected(uint32_t adc);
void adc_disable_discontinuous_mode_injected(uint32_t adc);
void adc_enable_automatic_injected_group_conversion(uint32_t adc);
void adc_disable_automatic_injected_group_conversion(uint32_t adc);
void adc_enable_analog_watchdog_on_all_channels(uint32_t adc);
void adc_enable_analog_watchdog_on_selected_channel(uint32_t adc,
						    uint8_t channel);
void adc_enable_scan_mode(uint32_t adc);
void adc_disable_scan_mode(uint32_t adc);
void adc_enable_eoc_interrupt_injected(uint32_t adc);
void adc_disable_eoc_interrupt_injected(uint32_t adc);
void adc_enable_awd_interrupt(uint32_t adc);
void adc_disable_awd_interrupt(uint32_t adc);
void adc_enable_eoc_interrupt(uint32_t adc);
void adc_disable_eoc_interrupt(uint32_t adc);
void adc_enable_temperature_sensor(uint32_t adc);
void adc_disable_temperature_sensor(uint32_t adc);
void adc_start_conversion_regular(uint32_t adc);
void adc_start_conversion_injected(uint32_t adc);
void adc_enable_external_trigger_regular(uint32_t adc, uint32_t trigger);
void adc_disable_external_trigger_regular(uint32_t adc);
void adc_enable_external_trigger_injected(uint32_t adc, uint32_t trigger);
void adc_disable_external_trigger_injected(uint32_t adc);
void adc_set_left_aligned(uint32_t adc);
void adc_set_right_aligned(uint32_t adc);
void adc_enable_dma(uint32_t adc);
void adc_disable_dma(uint32_t adc);
void adc_reset_calibration(uint32_t adc);
void adc_calibration(uint32_t adc);
void adc_set_continuous_conversion_mode(uint32_t adc);
void adc_set_single_conversion_mode(uint32_t adc);
void adc_on(uint32_t adc)
	LIBOPENCM3_DEPRECATED("will be removed in the first release");
void adc_off(uint32_t adc);
void adc_set_sample_time(uint32_t adc, uint8_t channel, uint8_t time);
void adc_set_sample_time_on_all_channels(uint32_t adc, uint8_t time);
void adc_set_watchdog_high_threshold(uint32_t adc, uint16_t threshold);
void adc_set_watchdog_low_threshold(uint32_t adc, uint16_t threshold);
void adc_set_regular_sequence(uint32_t adc, uint8_t length, uint8_t channel[]);
void adc_set_injected_sequence(uint32_t adc, uint8_t length, uint8_t channel[]);

void adc_set_continous_conversion_mode(uint32_t adc)
	LIBOPENCM3_DEPRECATED("change to adc_set_continuous_conversion_mode");
void adc_set_conversion_time(uint32_t adc, uint8_t channel, uint8_t time)
	LIBOPENCM3_DEPRECATED("change to adc_set_sample_time");
void adc_set_conversion_time_on_all_channels(uint32_t adc, uint8_t time)
	LIBOPENCM3_DEPRECATED("change to adc_set_sample_time_on_all_channels");
void adc_enable_jeoc_interrupt(uint32_t adc)
	LIBOPENCM3_DEPRECATED("change to adc_enable_eoc_interrupt_injected");
void adc_disable_jeoc_interrupt(uint32_t adc)
	LIBOPENCM3_DEPRECATED("change to adc_disable_eoc_interrupt_injected");
END_DECLS

#endif
/**@}*/

