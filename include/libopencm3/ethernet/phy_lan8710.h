/** @defgroup ethernet_phy_lan8710_defines PHY LAN8710 Defines
 *
 * @brief <b>Defined Constants and Types for the Ethernet PHY LAN8710 chip</b>
 *
 * @ingroup ETH
 *
 * @version 1.0.0
 *
 * @author @htmlonly &copy; @endhtmlonly 2014 Frantisek Burian <BuFran@seznam.cz>
 *
 * @date 6 February 2014
 *
 * LGPL License Terms @ref lgpl_license
 */
/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2013 Frantisek Burian <BuFran@seznam.cz>
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

#ifndef LIBOPENCM3_PHY_LAN8710_H
#define LIBOPENCM3_PHY_LAN8710_H

#include <libopencm3/ethernet/phy.h>

/**@{*/

/*
 * Architecture availability:
 *
 */

/*****************************************************************************/
/* Register definitions                                                      */
/*****************************************************************************/

#define LAN8710_BCR				0x00
#define LAN8710_BSR				0x01
#define LAN8710_PID1				0x02
#define LAN8710_PID2				0x03
#define LAN8710_ANA				0x04
#define LAN8710_ANLPA				0x05
#define LAN8710_ANE				0x06

#define LAN8710_MCS				0x11
#define LAN8710_SM				0x12
#define LAN8710_ERRCNT				0x1A
#define LAN8710_CSR				0x1B
#define LAN8710_ISR				0x1D
#define LAN8710_IMR				0x1E
#define LAN8710_SCSR				0x1F


/*****************************************************************************/
/* Register values                                                           */
/*****************************************************************************/

/* LAN8710_BCR --------------------------------------------------------------*/
/* LAN8710_BSR --------------------------------------------------------------*/
/* LAN8710_PID1 -------------------------------------------------------------*/
/* LAN8710_PID2 -------------------------------------------------------------*/
/* LAN8710_ANA --------------------------------------------------------------*/
/* LAN8710_ANLPA ------------------------------------------------------------*/
/* LAN8710_ANE --------------------------------------------------------------*/

/* LAN8710_MCS --------------------------------------------------------------*/

#define LAN8710_MCS_EDPWRDOWN			(1 << 13)
#define LAN8710_MCS_FARLOOPBACK			(1 << 9)
#define LAN8710_MCS_ALTINT			(1 << 6)
#define LAN8710_MCS_ENERGYON			(1 << 1)

/* LAN8710_SM ---------------------------------------------------------------*/

#define LAN8710_SM_MIIMODE			(1 << 14)
#define LAN8710_SM_MIIMODE_MII			(0 << 14)
#define LAN8710_SM_MIIMODE_RMII			(1 << 14)

#define LAN8710_SM_MODE_SHIFT			5
#define LAN8710_SM_MODE				(7 << LAN8710_SM_MODE_SHIFT)
#define LAN8710_SM_MODE_10HD			(0 << LAN8710_SM_MODE_SHIFT)
#define LAN8710_SM_MODE_10FD			(1 << LAN8710_SM_MODE_SHIFT)
#define LAN8710_SM_MODE_100HD			(2 << LAN8710_SM_MODE_SHIFT)
#define LAN8710_SM_MODE_100FD			(3 << LAN8710_SM_MODE_SHIFT)
#define LAN8710_SM_MODE_100HD_AN		(4 << LAN8710_SM_MODE_SHIFT)
#define LAN8710_SM_MODE_REPEATER		(5 << LAN8710_SM_MODE_SHIFT)
#define LAN8710_SM_MODE_POWERDOWN		(6 << LAN8710_SM_MODE_SHIFT)
#define LAN8710_SM_MODE_ALL			(7 << LAN8710_SM_MODE_SHIFT)

#define LAN8710_SM_PHYAD			(0x1F << 0)

/* LAN8710_ERRCNT -----------------------------------------------------------*/

/* LAN8710_CSR --------------------------------------------------------------*/

#define LAN8710_CSR_AMDIXCTRL			(1 << 15)
#define LAN8710_CSR_CH_SELECT			(1 << 13)
#define LAN8710_CSR_SQEOFF			(1 << 11)
#define LAN8710_CSR_XPOL			(1 << 4)

/* LAN8710_ISR --------------------------------------------------------------*/

#define LAN8710_ISR_ENERGYONF			(1 << 7)
#define LAN8710_ISR_ANCOMPF			(1 << 6)
#define LAN8710_ISR_RFAULTF			(1 << 5)
#define LAN8710_ISR_LINKDOWNF			(1 << 4)
#define LAN8710_ISR_ANLPACKF			(1 << 3)
#define LAN8710_ISR_PDFAULTF			(1 << 2)
#define LAN8710_ISR_ANPAGEF			(1 << 1)

/* LAN8710_IMR --------------------------------------------------------------*/

#define LAN8710_IMR_ENERGYONE			(1 << 7)
#define LAN8710_IMR_ANCOMPE			(1 << 6)
#define LAN8710_IMR_RFAULTE			(1 << 5)
#define LAN8710_IMR_LINKDOWNE			(1 << 4)
#define LAN8710_IMR_ANLPACKE			(1 << 3)
#define LAN8710_IMR_PDFAULTE			(1 << 2)
#define LAN8710_IMR_ANPAGEE			(1 << 1)

/* LAN8710_SCSR -------------------------------------------------------------*/

#define LAN8710_SCSR_AUTODONE			(1 << 12)
#define LAN8710_SCSR_ENABLE4B5B			(1 << 6)

#define LAN8710_SCSR_SPEED_SHIFT		2
#define LAN8710_SCSR_SPEED			(7 << LAN8710_SCSR_SPEED_SHIFT)
#define LAN8710_SCSR_SPEED_10HD			(1 << LAN8710_SCSR_SPEED_SHIFT)
#define LAN8710_SCSR_SPEED_100HD		(2 << LAN8710_SCSR_SPEED_SHIFT)
#define LAN8710_SCSR_SPEED_10FD			(5 << LAN8710_SCSR_SPEED_SHIFT)
#define LAN8710_SCSR_SPEED_100FD		(6 << LAN8710_SCSR_SPEED_SHIFT)

/*****************************************************************************/
/* API definitions                                                           */
/*****************************************************************************/

extern struct phy_driver lan8710_driver;

/*****************************************************************************/
/* API Functions                                                             */
/*****************************************************************************/

BEGIN_DECLS

enum phy_status lan8710_link_status(void);

END_DECLS

/**@}*/


#endif /* LIBOPENCM3_PHY_LAN8710_H__ */
