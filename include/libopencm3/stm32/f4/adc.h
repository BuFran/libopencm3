/** @defgroup STM32F4xx_adc_defines ADC Defines

@brief <b>Defined Constants and Types for the STM32F4xx Analog to Digital
Converters</b>

@ingroup STM32F4xx_defines

@version 1.0.0

@author @htmlonly &copy; @endhtmlonly 2012
Matthew Lai <m@matthewlai.ca>
@author @htmlonly &copy; @endhtmlonly 2009
Edward Cheeseman <evbuilder@users.sourceforge.net>

@date 31 August 2012

LGPL License Terms @ref lgpl_license
 */
/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2012 Matthew Lai <m@matthewlai.ca>
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

#ifndef LIBOPENCM3_ADC_H
#define LIBOPENCM3_ADC_H

#include <libopencm3/cm3/common.h>
#include <libopencm3/stm32/memorymap.h>
#include <libopencm3/stm32/common/adc_common_l1f123b4.h>

/* --- Convenience macros -------------------------------------------------- */

/* ADC port base addresses (for convenience) */
/****************************************************************************/
/** @defgroup adc_reg_base ADC register base addresses
@ingroup STM32F4xx_adc_defines

@{*/
#define ADC1				ADC1_BASE
#define ADC2				ADC2_BASE
#define ADC3				ADC3_BASE
/**@}*/

/* --- ADC registers ------------------------------------------------------- */

/* ADC common (shared) registers */
#define	ADC_COMMON_REGISTERS_BASE	(ADC1_BASE+0x300)
#define ADC_CSR				MMIO32(ADC_COMMON_REGISTERS_BASE + 0x0)
#define ADC_CCR				MMIO32(ADC_COMMON_REGISTERS_BASE + 0x4)
#define ADC_CDR				MMIO32(ADC_COMMON_REGISTERS_BASE + 0x8)

/* --- ADC Channels ------------------------------------------------------- */

#define ADC_MASK		    0x1F
#define ADC_SHIFT		    0


/* --- ADC_SR values ------------------------------------------------------- */

#define ADC_SR_OVR			(1 << 5)

/* --- ADC_CR1 values specific to STM32F2,4--------------------------------- */

/* OVRIE: Overrun interrupt enable */
#define ADC_CR1_OVRIE			(1 << 26)

/* RES[1:0]: Resolution */
/****************************************************************************/
/** @defgroup adc_cr1_res ADC Resolution.
@ingroup STM32F4xx_adc_defines

@{*/
#define ADC_CR1_RES_12BIT		(0x0 << 24)
#define ADC_CR1_RES_10BIT		(0x1 << 24)
#define ADC_CR1_RES_8BIT		(0x2 << 24)
#define ADC_CR1_RES_6BIT		(0x3 << 24)
/**@}*/
#define ADC_CR1_RES_MASK		(0x3 << 24)
#define ADC_CR1_RES_SHIFT		24

/* Note: Bits [21:16] are reserved, and must be kept at reset value. */

/* --- ADC_CR2 values ------------------------------------------------------ */

/* SWSTART: Start conversion of regular channels. */
#define ADC_CR2_SWSTART			(1 << 30)

/* EXTEN[1:0]: External trigger enable for regular channels. */
/****************************************************************************/
/** @defgroup adc_trigger_polarity_regular ADC Trigger Polarity
@ingroup STM32F4xx_adc_defines

@{*/
#define ADC_CR2_EXTEN_DISABLED		(0x0 << 28)
#define ADC_CR2_EXTEN_RISING_EDGE	(0x1 << 28)
#define ADC_CR2_EXTEN_FALLING_EDGE	(0x2 << 28)
#define ADC_CR2_EXTEN_BOTH_EDGES	(0x3 << 28)
/**@}*/
#define ADC_CR2_EXTEN_MASK			(0x3 << 28)
#define ADC_CR2_EXTEN_SHIFT			28

/* EXTSEL[3:0]: External event selection for regular group. */
/****************************************************************************/
/** @defgroup adc_trigger_regular ADC Trigger Identifier for Regular group
@ingroup STM32F4xx_adc_defines

@{*/
/** Timer 1 Compare Output 1 */
#define ADC_CR2_EXTSEL_TIM1_CC1		(0x0 << 24)
/** Timer 1 Compare Output 2 */
#define ADC_CR2_EXTSEL_TIM1_CC2		(0x1 << 24)
/** Timer 1 Compare Output 3 */
#define ADC_CR2_EXTSEL_TIM1_CC3		(0x2 << 24)
/** Timer 2 Compare Output 2 */
#define ADC_CR2_EXTSEL_TIM2_CC2		(0x3 << 24)
/** Timer 2 Compare Output 3 */
#define ADC_CR2_EXTSEL_TIM2_CC3		(0x4 << 24)
/** Timer 2 Compare Output 4 */
#define ADC_CR2_EXTSEL_TIM2_CC4		(0x5 << 24)
/** Timer 2 TRGO Event */
#define ADC_CR2_EXTSEL_TIM2_TRGO	(0x6 << 24)
/** Timer 3 Compare Output 1 */
#define ADC_CR2_EXTSEL_TIM3_CC1		(0x7 << 24)
/** Timer 3 TRGO Event */
#define ADC_CR2_EXTSEL_TIM3_TRGO	(0x8 << 24)
/** Timer 4 Compare Output 4 */
#define ADC_CR2_EXTSEL_TIM4_CC4		(0x9 << 24)
/** Timer 5 Compare Output 1 */
#define ADC_CR2_EXTSEL_TIM5_CC1		(0xA << 24)
/** Timer 5 Compare Output 2 */
#define ADC_CR2_EXTSEL_TIM5_CC2		(0xB << 24)
/** Timer 5 Compare Output 3 */
#define ADC_CR2_EXTSEL_TIM5_CC3		(0xC << 24)
/** Timer 8 Compare Output 1 */
#define ADC_CR2_EXTSEL_TIM8_CC1		(0xD << 24)
/** Timer 8 TRGO Event */
#define ADC_CR2_EXTSEL_TIM8_TRGO	(0xE << 24)
/** EXTI Line 11 Event */
#define ADC_CR2_EXTSEL_EXTI_LINE_11	(0xF << 24)
/**@}*/
#define ADC_CR2_EXTSEL_MASK			(0xF << 24)
#define ADC_CR2_EXTSEL_SHIFT		24

/* Bit 23 is reserved */

/* JSWSTART: Start conversion of injected channels. */
#define ADC_CR2_JSWSTART		(1 << 22)

/* JEXTEN[1:0]: External trigger enable for injected channels. */
/****************************************************************************/
/** @defgroup adc_trigger_polarity_injected ADC Injected Trigger Polarity
@ingroup STM32F4xx_adc_defines

@{*/
#define ADC_CR2_JEXTEN_DISABLED		(0x0 << 20)
#define ADC_CR2_JEXTEN_RISING_EDGE	(0x1 << 20)
#define ADC_CR2_JEXTEN_FALLING_EDGE	(0x2 << 20)
#define ADC_CR2_JEXTEN_BOTH_EDGES	(0x3 << 20)
/**@}*/
#define ADC_CR2_JEXTEN_MASK			(0x3 << 20)
#define ADC_CR2_JEXTEN_SHIFT		20

/* JEXTSEL[3:0]: External event selection for injected group. */
/****************************************************************************/
/** @defgroup adc_trigger_injected ADC Trigger Identifier for Injected group
@ingroup STM32F4xx_adc_defines

@{*/
#define ADC_CR2_JEXTSEL_TIM1_CC4	(0x0 << 16)
#define ADC_CR2_JEXTSEL_TIM1_TRGO	(0x1 << 16)
#define ADC_CR2_JEXTSEL_TIM2_CC1	(0x2 << 16)
#define ADC_CR2_JEXTSEL_TIM2_TRGO	(0x3 << 16)
#define ADC_CR2_JEXTSEL_TIM3_CC2	(0x4 << 16)
#define ADC_CR2_JEXTSEL_TIM3_CC4	(0x5 << 16)
#define ADC_CR2_JEXTSEL_TIM4_CC1	(0x6 << 16)
#define ADC_CR2_JEXTSEL_TIM4_CC2	(0x7 << 16)
#define ADC_CR2_JEXTSEL_TIM4_CC3	(0x8 << 16)
#define ADC_CR2_JEXTSEL_TIM4_TRGO	(0x9 << 16)
#define ADC_CR2_JEXTSEL_TIM5_CC4	(0xA << 16)
#define ADC_CR2_JEXTSEL_TIM5_TRGO	(0xB << 16)
#define ADC_CR2_JEXTSEL_TIM8_CC2	(0xC << 16)
#define ADC_CR2_JEXTSEL_TIM8_CC3	(0xD << 16)
#define ADC_CR2_JEXTSEL_TIM8_CC4	(0xE << 16)
#define ADC_CR2_JEXTSEL_EXTI_LINE_15	(0xF << 16)
/**@}*/
#define ADC_CR2_JEXTSEL_MASK		(0xF << 16)
#define ADC_CR2_JEXTSEL_SHIFT		16

/* EOCS: End of conversion selection. */
#define ADC_CR2_EOCS			(1 << 10)

/* DDS: DMA disable selection */
#define ADC_CR2_DDS			(1 << 9)


/* --- ADC_SMPRx values --------------------------------------------------- */
/****************************************************************************/
/* ADC_SMPRG ADC Sample Time Selection for Channels */
/** @defgroup adc_sample_rg ADC Sample Time Selection for All Channels
@ingroup STM32F4xx_adc_defines

@{*/
#define ADC_SMPR_SMP_3CYC		0x0
#define ADC_SMPR_SMP_15CYC		0x1
#define ADC_SMPR_SMP_28CYC		0x2
#define ADC_SMPR_SMP_56CYC		0x3
#define ADC_SMPR_SMP_84CYC		0x4
#define ADC_SMPR_SMP_112CYC		0x5
#define ADC_SMPR_SMP_144CYC		0x6
#define ADC_SMPR_SMP_480CYC		0x7
/**@}*/

/* --- ADC_JOFRx, ADC_HTR, ADC_LTR values ---------------------------------- */

#define ADC_JOFFSET_LSB			0
#define ADC_JOFFSET_MSK			(0x7ff << 0)
#define ADC_HT_LSB			0
#define ADC_HT_MSK			(0x7ff << 0)
#define ADC_LT_LSB			0
#define ADC_LT_MSK			(0x7ff << 0)

/* JL[2:0]: Discontinous mode channel count injected channels. */
/****************************************************************************/
/** @defgroup adc_jsqr_jl ADC Number of channels in discontinuous mode fro
injected channels.
@ingroup STM32F4xx_adc_defines

@{*/
/**@}*/
#define ADC_JSQR_JL_SHIFT		20
#define ADC_JSQR_JL_MSK			(0x2 << ADC_JSQR_JL_LSB)
#define ADC_JSQR_JSQ4_MSK		(0x1f << ADC_JSQR_JSQ4_LSB)
#define ADC_JSQR_JSQ3_MSK		(0x1f << ADC_JSQR_JSQ3_LSB)
#define ADC_JSQR_JSQ2_MSK		(0x1f << ADC_JSQR_JSQ2_LSB)
#define ADC_JSQR_JSQ1_MSK		(0x1f << ADC_JSQR_JSQ1_LSB)


/* --- ADC_JDRx, ADC_DR values --------------------------------------------- */

#define ADC_JDATA_LSB			0
#define ADC_DATA_LSB			0
#define ADC_JDATA_MSK			(0xffff << ADC_JDATA_LSB)
#define ADC_DATA_MSK			(0xffff << ADC_DA)

/* --- Common Registers ---------------------------------------------------- */

/* --- ADC_CSR values (read only images) ------------------------------------ */

/* OVR3: Overrun ADC3. */
#define ADC_CSR_OVR3				(1 << 21)

/* STRT3: Regular channel start ADC3. */
#define ADC_CSR_STRT3				(1 << 20)

/* JSTRT3: Injected channel start ADC3. */
#define ADC_CSR_JSTRT3				(1 << 19)

/* JEOC3: Injected channel end of conversion ADC3. */
#define ADC_CSR_JEOC3				(1 << 18)

/* EOC3: Regular channel end of conversion ADC3. */
#define ADC_CSR_EOC3				(1 << 17)

/* EOC3: Regular channel end of conversion ADC3. */
#define ADC_CSR_AWD3				(1 << 16)

/* Bits 15:14 Reserved, must be kept at reset value */

/* OVR2: Overrun ADC2. */
#define ADC_CSR_OVR2				(1 << 13)

/* STRT2: Regular channel start ADC2. */
#define ADC_CSR_STRT2				(1 << 12)

/* JSTRT2: Injected channel start ADC2. */
#define ADC_CSR_JSTRT2				(1 << 11)

/* JEOC2: Injected channel end of conversion ADC2. */
#define ADC_CSR_JEOC2				(1 << 10)

/* EOC2: Regular channel end of conversion ADC2. */
#define ADC_CSR_EOC2				(1 << 9)

/* EOC2: Regular channel end of conversion ADC2. */
#define ADC_CSR_AWD2				(1 << 8)

/* Bits 7:6 Reserved, must be kept at reset value */

/* OVR1: Overrun ADC1. */
#define ADC_CSR_OVR1				(1 << 5)

/* STRT1: Regular channel start ADC1. */
#define ADC_CSR_STRT1				(1 << 4)

/* JSTRT1: Injected channel start ADC1. */
#define ADC_CSR_JSTRT1				(1 << 3)

/* JEOC1: Injected channel end of conversion ADC1. */
#define ADC_CSR_JEOC1				(1 << 2)

/* EOC1: Regular channel end of conversion ADC1. */
#define ADC_CSR_EOC1				(1 << 1)

/* EOC1: Regular channel end of conversion ADC1. */
#define ADC_CSR_AWD1				(1 << 0)

/* --- ADC_CCR values ------------------------------------------------------ */

/* TSVREFE: Temperature sensor and Vrefint enable. */
#define ADC_CCR_TSVREFE				(1 << 23)

/* VBATE: VBat enable. */
#define ADC_CCR_VBATE				(1 << 22)

/* Bit 18:21 reserved, must be kept at reset value. */

/* ADCPRE: ADC prescaler. */
/****************************************************************************/
/** @defgroup adc_ccr_adcpre ADC Prescale
@ingroup STM32F4xx_adc_defines

@{*/
#define ADC_CCR_ADCPRE_BY2		(0x0 << 16)
#define ADC_CCR_ADCPRE_BY4		(0x1 << 16)
#define ADC_CCR_ADCPRE_BY6		(0x2 << 16)
#define ADC_CCR_ADCPRE_BY8		(0x3 << 16)
/**@}*/
#define ADC_CCR_ADCPRE_MASK		(0x3 << 16)
#define ADC_CCR_ADCPRE_SHIFT		16

/* DMA: Direct memory access mode for multi ADC mode. */
/****************************************************************************/
/** @defgroup adc_dma_mode ADC DMA mode for multi ADC mode
@ingroup STM32F4xx_adc_defines

@{*/
#define ADC_CCR_DMA_DISABLE		(0x0 << 14)
#define ADC_CCR_DMA_MODE_1		(0x1 << 14)
#define ADC_CCR_DMA_MODE_2		(0x2 << 14)
#define ADC_CCR_DMA_MODE_3		(0x3 << 14)
/**@}*/
#define ADC_CCR_DMA_MASK		(0x3 << 14)
#define ADC_CCR_DMA_SHIFT		14

/* DDS: DMA disable selection (for multi-ADC mode). */
#define ADC_CCR_DDS				(1 << 13)

/* Bit 12 reserved, must be kept at reset value */

/* DELAY: Delay between 2 sampling phases. */
/****************************************************************************/
/** @defgroup adc_delay ADC Delay between 2 sampling phases
@ingroup STM32F4xx_adc_defines

@{*/
#define ADC_CCR_DELAY_5ADCCLK		(0x0 << 8)
#define ADC_CCR_DELAY_6ADCCLK		(0x1 << 8)
#define ADC_CCR_DELAY_7ADCCLK		(0x2 << 8)
#define ADC_CCR_DELAY_8ADCCLK		(0x3 << 8)
#define ADC_CCR_DELAY_9ADCCLK		(0x4 << 8)
#define ADC_CCR_DELAY_10ADCCLK		(0x5 << 8)
#define ADC_CCR_DELAY_11ADCCLK		(0x6 << 8)
#define ADC_CCR_DELAY_12ADCCLK		(0x7 << 8)
#define ADC_CCR_DELAY_13ADCCLK		(0x8 << 8)
#define ADC_CCR_DELAY_14ADCCLK		(0x9 << 8)
#define ADC_CCR_DELAY_15ADCCLK		(0xa << 8)
#define ADC_CCR_DELAY_16ADCCLK		(0xb << 8)
#define ADC_CCR_DELAY_17ADCCLK		(0xc << 8)
#define ADC_CCR_DELAY_18ADCCLK		(0xd << 8)
#define ADC_CCR_DELAY_19ADCCLK		(0xe << 8)
#define ADC_CCR_DELAY_20ADCCLK		(0xf << 8)
/**@}*/
#define ADC_CCR_DELAY_MASK		(0xf << 8)
#define ADC_CCR_DELAY_SHIFT		8

/* Bit 7:5 reserved, must be kept at reset value */

/* MULTI: Multi ADC mode selection. */
/****************************************************************************/
/** @defgroup adc_multi_mode ADC Multi mode selection
@ingroup STM32F4xx_adc_defines

@{*/

/** All ADCs independent */
#define ADC_CCR_MULTI_INDEPENDENT	(0x00 << 0)

/* Dual modes (ADC1 + ADC2) */
/**
 * Dual modes (ADC1 + ADC2) Combined regular simultaneous +
 * injected simultaneous mode.
 */
#define ADC_CCR_MULTI_DUAL_REG_SIMUL_AND_INJECTED_SIMUL		(0x01 << 0)
/**
 * Dual modes (ADC1 + ADC2) Combined regular simultaneous +
 * alternate trigger mode.
 */
#define ADC_CCR_MULTI_DUAL_REG_SIMUL_AND_ALTERNATE_TRIG		(0x02 << 0)
/** Dual modes (ADC1 + ADC2) Injected simultaneous mode only. */
#define ADC_CCR_MULTI_DUAL_INJECTED_SIMUL			(0x05 << 0)
/** Dual modes (ADC1 + ADC2) Regular simultaneous mode only. */
#define ADC_CCR_MULTI_DUAL_REGULAR_SIMUL			(0x06 << 0)
/** Dual modes (ADC1 + ADC2) Interleaved mode only. */
#define ADC_CCR_MULTI_DUAL_INTERLEAVED				(0x07 << 0)
/** Dual modes (ADC1 + ADC2) Alternate trigger mode only. */
#define ADC_CCR_MULTI_DUAL_ALTERNATE_TRIG			(0x09 << 0)

/* Triple modes (ADC1 + ADC2 + ADC3) */
/**
 * Triple modes (ADC1 + ADC2 + ADC3) Combined regular simultaneous +
 * injected simultaneous mode.
 */
#define ADC_CCR_MULTI_TRIPLE_REG_SIMUL_AND_INJECTED_SIMUL	(0x11 << 0)
/**
 * Triple modes (ADC1 + ADC2 + ADC3) Combined regular simultaneous +
 * alternate trigger mode.
 */
#define ADC_CCR_MULTI_TRIPLE_REG_SIMUL_AND_ALTERNATE_TRIG	(0x12 << 0)
/** Triple modes (ADC1 + ADC2 + ADC3) Injected simultaneous mode only. */
#define ADC_CCR_MULTI_TRIPLE_INJECTED_SIMUL			(0x15 << 0)
/** Triple modes (ADC1 + ADC2 + ADC3) Regular simultaneous mode only. */
#define ADC_CCR_MULTI_TRIPLE_REGULAR_SIMUL			(0x16 << 0)
/** Triple modes (ADC1 + ADC2 + ADC3) Interleaved mode only. */
#define ADC_CCR_MULTI_TRIPLE_INTERLEAVED			(0x17 << 0)
/** Triple modes (ADC1 + ADC2 + ADC3) Alternate trigger mode only. */
#define ADC_CCR_MULTI_TRIPLE_ALTERNATE_TRIG			(0x19 << 0)
/**@}*/

#define ADC_CCR_MULTI_MASK		(0x1f << 0)
#define ADC_CCR_MULTI_SHIFT		0

/* --- ADC_CDR values ------------------------------------------------------ */

#define ADC_CDR_DATA2_MASK		(0xffff << 16)
#define ADC_CDR_DATA2_SHIFT		16

#define ADC_CDR_DATA1_MASK		(0xffff << 0)
#define ADC_CDR_DATA1_SHIFT		0

BEGIN_DECLS

void adc_power_on(uint32_t adc);
void adc_off(uint32_t adc);
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
void adc_start_conversion_regular(uint32_t adc);
void adc_start_conversion_injected(uint32_t adc);
void adc_disable_external_trigger_regular(uint32_t adc);
void adc_disable_external_trigger_injected(uint32_t adc);
void adc_set_left_aligned(uint32_t adc);
void adc_set_right_aligned(uint32_t adc);
void adc_enable_dma(uint32_t adc);
void adc_disable_dma(uint32_t adc);
void adc_set_continuous_conversion_mode(uint32_t adc);
void adc_set_single_conversion_mode(uint32_t adc);
void adc_set_sample_time(uint32_t adc, uint8_t channel, uint8_t time);
void adc_set_sample_time_on_all_channels(uint32_t adc, uint8_t time);
void adc_set_watchdog_high_threshold(uint32_t adc, uint16_t threshold);
void adc_set_watchdog_low_threshold(uint32_t adc, uint16_t threshold);
void adc_set_regular_sequence(uint32_t adc, uint8_t length, uint8_t channel[]);
void adc_set_injected_sequence(uint32_t adc, uint8_t length, uint8_t channel[]);
bool adc_eoc(uint32_t adc);
bool adc_eoc_injected(uint32_t adc);
uint32_t adc_read_regular(uint32_t adc);
uint32_t adc_read_injected(uint32_t adc, uint8_t reg);
void adc_set_injected_offset(uint32_t adc, uint8_t reg, uint32_t offset);

void adc_set_clk_prescale(uint32_t prescaler);
void adc_set_multi_mode(uint32_t mode);
void adc_enable_external_trigger_regular(uint32_t adc, uint32_t trigger,
					 uint32_t polarity);
void adc_enable_external_trigger_injected(uint32_t adc, uint32_t trigger,
					  uint32_t polarity);
void adc_set_resolution(uint32_t adc, uint32_t resolution);
void adc_enable_overrun_interrupt(uint32_t adc);
void adc_disable_overrun_interrupt(uint32_t adc);
bool adc_get_overrun_flag(uint32_t adc);
void adc_clear_overrun_flag(uint32_t adc);
bool adc_awd(uint32_t adc);
void adc_eoc_after_each(uint32_t adc);
void adc_eoc_after_group(uint32_t adc);
void adc_set_dma_continue(uint32_t adc);
void adc_set_dma_terminate(uint32_t adc);
void adc_enable_temperature_sensor(void);
void adc_disable_temperature_sensor(void);

END_DECLS

/**@}*/

#endif
