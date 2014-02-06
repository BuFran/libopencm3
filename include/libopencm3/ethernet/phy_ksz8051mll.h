/** @defgroup ethernet_phy_ksz8051mll_defines PHY KSZ8051mll Defines
 *
 * @brief <b>Defined Constants and Types for the Ethernet PHY KSZ8051mll
 * chips</b>
 *
 * @ingroup ETH
 *
 * @version 1.0.0
 *
 * @author @htmlonly &copy; @endhtmlonly 2013 Frantisek Burian <BuFran@seznam.cz>
 *
 * @date 1 September 2013
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

#ifndef LIBOPENCM3_PHY_KSZ8051_H
#define LIBOPENCM3_PHY_KSZ8051_H

#include <libopencm3/ethernet/phy.h>

/**@{*/

/*
 * Architecture availability:
 *
 * M stands for KSZ8051MLL only
 * R stands for KSZ8051RNL only
 * No sign marks available for both
 */

/*****************************************************************************/
/* Register definitions                                                      */
/*****************************************************************************/

#define KSZ8051_BCR				0x00
#define KSZ8051_BSR				0x01
#define KSZ8051_ID1				0x02
#define KSZ8051_ID2				0x03
#define KSZ8051_ANTX				0x04
#define KSZ8051_ANRX				0x05
#define KSZ8051_ANEXP				0x06
#define KSZ8051_ANNPTX				0x07
#define KSZ8051_ANNPRX				0x08

#define KSZ8051_AFECTRL				0x11
#define KSZ8051_RXERCTR				0x15
#define KSZ8051_STRAPOVRD			0x16
#define KSZ8051_STRAPSTAT			0x17
#define KSZ8051_ECR				0x18

#define KSZ8051_ICSR				0x1B

#define KSZ8051_LINKMD				0x1D
#define KSZ8051_CR1				0x1E
#define KSZ8051_CR2				0x1F

/*****************************************************************************/
/* Register values                                                           */
/*****************************************************************************/

/* KSZ8051_BCR --------------------------------------------------------------*/
/* KSZ8051_BSR --------------------------------------------------------------*/
/* KSZ8051_ID1 --------------------------------------------------------------*/
/* KSZ8051_ID2 --------------------------------------------------------------*/
/* KSZ8051_ANTX -------------------------------------------------------------*/
/* KSZ8051_ANRX -------------------------------------------------------------*/
/* KSZ8051_ANEXP ------------------------------------------------------------*/
/* KSZ8051_ANNPTX -----------------------------------------------------------*/
/* KSZ8051_ANNPRX -----------------------------------------------------------*/

/* KSZ8051_AFECTRL ----------------------------------------------------------*/

#define KSZ8051_AFECTRL_SLOWOSC			(1 << 5)

/* KSZ8051_STRAPOVRD --------------------------------------------------------*/

#define KSZ8051_STRAPOVRD_BCASTOFF		(1 << 9)
#define KSZ8051_STRAPOVRD_MIIBTOB		(1 << 7)
#define KSZ8051_STRAPOVRD_RMIIBTOB		(1 << 6) /* R */
#define KSZ8051_STRAPOVRD_NANDTREE		(1 << 5)
#define KSZ8051_STRAPOVRD_RMIIOVRD		(1 << 1) /* R */
#define KSZ8051_STRAPOVRD_MIIOVRD		(1 << 0)

/* KSZ8051_STRAPSTAT --------------------------------------------------------*/

#define KSZ8051_STRAPSTAT_PHYAD_SHIFT		13
#define KSZ8051_STRAPSTAT_PHYAD		(7 << KSZ8051_STRAPSTAT_PHYAD_SHIFT)
			

#define KSZ8051_STRAPSTAT_BCASTOFF		(1 << 9)
#define KSZ8051_STRAPSTAT_MIIBTOB		(1 << 7)
#define KSZ8051_STRAPSTAT_RMIIBTOB		(1 << 6) /* R */
#define KSZ8051_STRAPSTAT_NANDTREE		(1 << 5)
#define KSZ8051_STRAPSTAT_RMII			(1 << 1) /* R */
#define KSZ8051_STRAPSTAT_MII			(1 << 0)

/* KSZ8051_ECR --------------------------------------------------------------*/

#define KSZ8051_ECR_EDPDDIS			(1 << 11)
#define KSZ8051_ECR_100TXPREAMBLE		(1 << 10)
#define KSZ8051_ECR_10TXPREAMBLE		(1 << 6)

/* KSZ8051_ICSR -------------------------------------------------------------*/

#define KSZ8051_ICSR_JABIE			(1 << 15)
#define KSZ8051_ICSR_RERRIE			(1 << 14)
#define KSZ8051_ICSR_PRIE			(1 << 13)
#define KSZ8051_ICSR_PDFLTIE			(1 << 12)
#define KSZ8051_ICSR_LPACKIE			(1 << 11)
#define KSZ8051_ICSR_LDIE			(1 << 10)
#define KSZ8051_ICSR_RFAULTIE			(1 << 9)
#define KSZ8051_ICSR_LINKUPIE			(1 << 8)

#define KSZ8051_ICSR_JABIF			(1 << 7)
#define KSZ8051_ICSR_RERRIF			(1 << 6)
#define KSZ8051_ICSR_PRIF			(1 << 5)
#define KSZ8051_ICSR_PDFLTIF			(1 << 4)
#define KSZ8051_ICSR_LPACKIF			(1 << 3)
#define KSZ8051_ICSR_LDIF			(1 << 2)
#define KSZ8051_ICSR_RFAULTIF			(1 << 1)
#define KSZ8051_ICSR_LINKUPIF			(1 << 0)

/* KSZ8051_LINKMD -----------------------------------------------------------*/

#define KSZ8051_LINKMD_TESTEN			(1 << 15)

#define KSZ8051_LINKMD_TESTRES			(3 << 13)
#define KSZ8051_LINKMD_TESTRES_NORMAL		(0 << 13)
#define KSZ8051_LINKMD_TESTRES_OPEN		(1 << 13)
#define KSZ8051_LINKMD_TESTRES_SHORT		(2 << 13)
#define KSZ8051_LINKMD_TESTRES_FAILED		(3 << 13)

#define KSZ8051_LINKMD_SHORTCABLE		(1 << 12)
#define KSZ8051_LINKMD_DISTANCE			(0x1FF << 0)

/* KSZ8051_CR ---------------------------------------------------------------*/

#define KSZ8051_CR1_FLOWCTRL			(1 << 9)
#define KSZ8051_CR1_LINK			(1 << 8)
#define KSZ8051_CR1_POLARITY			(1 << 7)
#define KSZ8051_CR1_MDIX			(1 << 5)
#define KSZ8051_CR1_ENERGY			(1 << 4)
#define KSZ8051_CR1_ISOLATE			(1 << 3)

#define KSZ8051_CR1_MODE			(7 << 0)
#define KSZ8051_CR1_MODE_AUTONEG		(0 << 0)
#define KSZ8051_CR1_MODE_10HD			(1 << 0)
#define KSZ8051_CR1_MODE_100HD			(2 << 0)
#define KSZ8051_CR1_MODE_10FD			(5 << 0)
#define KSZ8051_CR1_MODE_100FD			(6 << 0)

/* KSZ8051_CR2 --------------------------------------------------------------*/

#define KSZ8051_CR2_HPMDIX			(1 << 15)
#define KSZ8051_CR2_MDIXSEL			(1 << 14)
#define KSZ8051_CR2_MDIXEN			(1 << 13)
#define KSZ8051_CR2_FORCE			(1 << 11)
#define KSZ8051_CR2_POWERSAVE			(1 << 10)
#define KSZ8051_CR2_IRQLVL			(1 << 9)
#define KSZ8051_CR2_JABEN			(1 << 8)
#define KSZ8051_CR2_REFCLK			(1 << 7) /* R */
#define KSZ8051_CR2_REFCLK_25MHZ		(0 << 7) /* R */
#define KSZ8051_CR2_REFCLK_50MHZ		(1 << 7) /* R */

#define KSZ8051_CR2_LED				(3 << 4)
#define KSZ8051_CR2_LED_SPD_LNKACT		(0 << 4)
#define KSZ8051_CR2_LED_ACT_LNK			(1 << 4)

#define KSZ8051_CR2_TXDIS			(1 << 3)
#define KSZ8051_CR2_REMLPB			(1 << 2)
#define KSZ8051_CR2_SQEEN			(1 << 1)
#define KSZ8051_CR2_SCRAMBEN			(1 << 0)

/*****************************************************************************/
/* API definitions                                                           */
/*****************************************************************************/

/*****************************************************************************/
/* API Functions                                                             */
/*****************************************************************************/

/**@}*/


#endif /* LIBOPENCM3_PHY_KSZ8051_H__ */
