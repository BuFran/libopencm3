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