/** @defgroup ethernet_phy_ste100_file PHY STE100
 *
 * @ingroup ETH
 *
 * @brief <b>Ethernet PHY STM32Fxx7 Drivers</b>
 *
 * @version 1.0.0
 * @author @htmlonly &copy; @endhtmlonly 2014 Frantisek Burian <BuFran@seznam.cz>
 *
 * @date 5 February 2014
 *
 * LGPL License Terms @ref lgpl_license
 */

/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2014 Frantisek Burian <BuFran@seznam.cz>
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

#include <libopencm3/ethernet/mac.h>
#include <libopencm3/ethernet/phy.h>
#include <libopencm3/ethernet/phy_ste100.h>


/**@{*/

struct phy_driver ste100_driver = {
	.link_status = ste100_link_status,
};

/*---------------------------------------------------------------------------*/
/** @brief Get the current link status
 *
 * Retrieve the link speed and duplex status of the link.
 *
 * @returns ::phy_status Link status
 */
enum phy_status ste100_link_status(void)
{
	switch (eth_smi_read(1, STE100_100CTR) & STE100_100CTR_CMODE) {
		case STE100_100CTR_CMODE_10HD:
			return LINK_HD_10M;

		case STE100_100CTR_CMODE_100HD:
			return LINK_HD_100M;

		case STE100_100CTR_CMODE_10FD:
			return LINK_FD_10M;

		case STE100_100CTR_CMODE_100FD:
			return LINK_FD_100M;

		default:
			return LINK_DOWN;
	}
}

/**@}*/
