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
#ifndef LIBOPENCM3_ADC_COMMON_ALL_H
#define LIBOPENCM3_ADC_COMMON_ALL_H

/**@{*/

#include <libopencm3/cm3/common.h>

/*****************************************************************************/
/* Module definitions                                                        */
/*****************************************************************************/

/*****************************************************************************/
/* Register definitions                                                      */
/*****************************************************************************/

/*****************************************************************************/
/* Register values                                                           */
/*****************************************************************************/

/*****************************************************************************/
/* API definitions                                                           */
/*****************************************************************************/

#define ADC_CH(i)		(i)
/** @defgroup adc_channel ADC Channel Numbers
 * @ingroup adc_defines
 *
 * @{*/
#define ADC_CHANNEL0		ADC_CH(0)
#define ADC_CHANNEL1		ADC_CH(1)
#define ADC_CHANNEL2		ADC_CH(2)
#define ADC_CHANNEL3		ADC_CH(3)
#define ADC_CHANNEL4		ADC_CH(4)
#define ADC_CHANNEL5		ADC_CH(5)
#define ADC_CHANNEL6		ADC_CH(6)
#define ADC_CHANNEL7		ADC_CH(7)
#define ADC_CHANNEL8		ADC_CH(8)
#define ADC_CHANNEL9		ADC_CH(9)
#define ADC_CHANNEL10		ADC_CH(10)
#define ADC_CHANNEL11		ADC_CH(11)
#define ADC_CHANNEL12		ADC_CH(12)
#define ADC_CHANNEL13		ADC_CH(13)
#define ADC_CHANNEL14		ADC_CH(14)
#define ADC_CHANNEL15		ADC_CH(15)
#define ADC_CHANNEL16		ADC_CH(16)
#define ADC_CHANNEL17		ADC_CH(17)
#define ADC_CHANNEL18		ADC_CH(18)

#define ADC_CH_TEMP		ADC_CH(16)
#define ADC_CH_VREFINT		ADC_CH(17)
/**@}*/

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