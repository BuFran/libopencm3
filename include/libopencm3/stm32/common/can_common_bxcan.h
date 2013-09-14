/** @addtogroup can_defines
 *
 * @author @htmlonly &copy; @endhtmlonly 2010 Piotr Esden-Tempski
 * <piotr@esden.net>
 *
 * @date 12 November 2012
 *
 * LGPL License Terms @ref lgpl_license
 */
/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2010 Piotr Esden-Tempski <piotr@esden.net>
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

/** @cond */
#ifdef LIBOPENCM3_CAN_H
/** @endcond */

#ifndef LIBOPENCM3_CAN_COMMON_BXCAN_H
#define LIBOPENCM3_CAN_COMMON_BXCAN_H

#include <libopencm3/stm32/memorymap.h>
#include <libopencm3/cm3/common.h>

/**@{*/

/* --- Convenience macros --------------------------------------------------- */

/* CAN register base addresses (for convenience) */
/******************************************************************************/
/** @defgroup can_reg_base CAN register base address
 * @ingroup can_defines
 *
 *@{*/
#define CAN1				BX_CAN1_BASE
#define CAN2				BX_CAN2_BASE
/**@}*/

/* --- CAN registers -------------------------------------------------------- */

/* CAN master control register (CAN_MCR) */
#define CAN_MCR(can_base)		MMIO32(can_base + 0x000)
/* CAN master status register (CAN_MSR) */
#define CAN_MSR(can_base)		MMIO32(can_base + 0x004)
/* CAN transmit status register (CAN_TSR) */
#define CAN_TSR(can_base)		MMIO32(can_base + 0x008)

/* CAN receive FIFO registers (CAN_RF0R, CAN_RF1R) */
#define CAN_RFxR(can_base, fifoid)	MMIO32(can_base + 0x00C + (fifoid) * 4)
#define CAN_RF0R(can_base)		CAN_RFxR(can_base, 0)
#define CAN_RF1R(can_base)		CAN_RFxR(can_base, 1)

/* CAN interrupt enable register (CAN_IER) */
#define CAN_IER(can_base)		MMIO32(can_base + 0x014)
/* CAN error status register (CAN_ESR) */
#define CAN_ESR(can_base)		MMIO32(can_base + 0x018)
/* CAN bit timing register (CAN_BTR) */
#define CAN_BTR(can_base)		MMIO32(can_base + 0x01C)

/* Registers in the offset range 0x020 to 0x17F are reserved. */

/* --- CAN mailbox registers ------------------------------------------------ */

/* CAN mailbox / FIFO register offsets */
#define CAN_MBOX(mbox)			(0x180 + 0x10 * (mbox))
#define CAN_MBOX0			CAN_MBOX(0)
#define CAN_MBOX1			CAN_MBOX(1)
#define CAN_MBOX2			CAN_MBOX(2)

#define CAN_FIFO(fifo)			(0x1B0 + 0x10 * (fifo))
#define CAN_FIFO0			CAN_FIFO(0)
#define CAN_FIFO1			CAN_FIFO(1)

/* CAN TX mailbox identifier register (CAN_TIxR) */
#define CAN_TIxR(can_base, mbox)	MMIO32(can_base + mbox + 0x0)
#define CAN_TI0R(can_base)		CAN_TIxR(can_base, CAN_MBOX0)
#define CAN_TI1R(can_base)		CAN_TIxR(can_base, CAN_MBOX1)
#define CAN_TI2R(can_base)		CAN_TIxR(can_base, CAN_MBOX2)

/* CAN mailbox data length control and time stamp register (CAN_TDTxR) */
#define CAN_TDTxR(can_base, mbox)	MMIO32(can_base + mbox + 0x4)
#define CAN_TDT0R(can_base)		CAN_TDTxR(can_base, CAN_MBOX0)
#define CAN_TDT1R(can_base)		CAN_TDTxR(can_base, CAN_MBOX1)
#define CAN_TDT2R(can_base)		CAN_TDTxR(can_base, CAN_MBOX2)

/* CAN mailbox data low register (CAN_TDLxR) */
#define CAN_TDLxR(can_base, mbox)	MMIO32(can_base + mbox + 0x8)
#define CAN_TDL0R(can_base)		CAN_TDLxR(can_base, CAN_MBOX0)
#define CAN_TDL1R(can_base)		CAN_TDLxR(can_base, CAN_MBOX1)
#define CAN_TDL2R(can_base)		CAN_TDLxR(can_base, CAN_MBOX2)

/* CAN mailbox data high register (CAN_TDHxR) */
#define CAN_TDHxR(can_base, mbox)	MMIO32(can_base + mbox + 0xC)
#define CAN_TDH0R(can_base)		CAN_TDHxR(can_base, CAN_MBOX0)
#define CAN_TDH1R(can_base)		CAN_TDHxR(can_base, CAN_MBOX1)
#define CAN_TDH2R(can_base)		CAN_TDHxR(can_base, CAN_MBOX2)

/* CAN RX FIFO identifier register (CAN_RIxR) */
#define CAN_RIxR(can_base, fifo)	MMIO32(can_base + fifo + 0x0)
#define CAN_RI0R(can_base)		CAN_RIxR(can_base, CAN_FIFO0)
#define CAN_RI1R(can_base)		CAN_RIxR(can_base, CAN_FIFO1)

/* CAN RX FIFO mailbox data length control & time stamp register (CAN_RDTxR) */
#define CAN_RDTxR(can_base, fifo)	MMIO32(can_base + fifo + 0x4)
#define CAN_RDT0R(can_base)		CAN_RDTxR(can_base, CAN_FIFO0)
#define CAN_RDT1R(can_base)		CAN_RDTxR(can_base, CAN_FIFO1)

/* CAN RX FIFO mailbox data low register (CAN_RDLxR) */
#define CAN_RDLxR(can_base, fifo)	MMIO32(can_base + fifo + 0x8)
#define CAN_RDL0R(can_base)		CAN_RDLxR(can_base, CAN_FIFO0)
#define CAN_RDL1R(can_base)		CAN_RDLxR(can_base, CAN_FIFO1)

/* CAN RX FIFO mailbox data high register (CAN_RDHxR) */
#define CAN_RDHxR(can_base, fifo)	MMIO32(can_base + fifo + 0xC)
#define CAN_RDH0R(can_base)		CAN_RDHxR(can_base, CAN_FIFO0)
#define CAN_RDH1R(can_base)		CAN_RDHxR(can_base, CAN_FIFO1)

/* --- CAN filter registers ------------------------------------------------- */
/* Not available on CAN2 !*/
/* CAN filter master register (CAN_FMR) */
#define CAN_FMR(can_base)		MMIO32(can_base + 0x200)

/* CAN filter mode register (CAN_FM1R) */
#define CAN_FM1R(can_base)		MMIO32(can_base + 0x204)

/* Register offset 0x208 is reserved. */

/* CAN filter scale register (CAN_FS1R) */
#define CAN_FS1R(can_base)		MMIO32(can_base + 0x20C)

/* Register offset 0x210 is reserved. */

/* CAN filter FIFO assignement register (CAN_FFA1R) */
#define CAN_FFA1R(can_base)		MMIO32(can_base + 0x214)

/* Register offset 0x218 is reserved. */

/* CAN filter activation register (CAN_FA1R) */
#define CAN_FA1R(can_base)		MMIO32(can_base + 0x21C)

/* Register offset 0x220 is reserved. */

/* Registers with offset 0x224 to 0x23F are reserved. */

/* CAN filter bank registers (CAN_FiRx) */
/*
 * Connectivity line devices have 28 banks so the bank ID spans 0..27
 * all other devices have 14 banks so the bank ID spans 0..13.
 */
#define CAN_FiR1(can_base, bank)	MMIO32(can_base + 0x240 + \
						(bank * 0x8) + 0x0)
#define CAN_FiR2(can_base, bank)	MMIO32(can_base + 0x240 + \
						(bank * 0x8) + 0x4)

/* --- CAN_MCR values ------------------------------------------------------- */

/* 31:17 Reserved, forced by hardware to 0 */

/* DBF: Debug freeze */
#define CAN_MCR_DBF			(1 << 16)

/* RESET: bxCAN software master reset */
#define CAN_MCR_RESET			(1 << 15)

/* 14:8 Reserved, forced by hardware to 0 */

/* TTCM: Time triggered communication mode */
#define CAN_MCR_TTCM			(1 << 7)

/* ABOM: Automatic bus-off management */
#define CAN_MCR_ABOM			(1 << 6)

/* AWUM: Automatic wakeup mode */
#define CAN_MCR_AWUM			(1 << 5)

/* NART: No automatic retransmission */
#define CAN_MCR_NART			(1 << 4)

/* RFLM: Receive FIFO locked mode */
#define CAN_MCR_RFLM			(1 << 3)

/* TXFP: Transmit FIFO priority */
#define CAN_MCR_TXFP			(1 << 2)

/* SLEEP: Sleep mode request */
#define CAN_MCR_SLEEP			(1 << 1)

/* INRQ: Initialization request */
#define CAN_MCR_INRQ			(1 << 0)

/* --- CAN_MSR values ------------------------------------------------------- */

/* 31:12 Reserved, forced by hardware to 0 */

/* RX: CAN Rx signal */
#define CAN_MSR_RX			(1 << 11)

/* SAMP: Last sample point */
#define CAN_MSR_SAMP			(1 << 10)

/* RXM: Receive mode */
#define CAN_MSR_RXM			(1 << 9)

/* TXM: Transmit mode */
#define CAN_MSR_TXM			(1 << 8)

/* 7:5 Reserved, forced by hardware to 0 */

/* SLAKI: Sleep acknowledge interrupt */
#define CAN_MSR_SLAKI			(1 << 4)

/* WKUI: Wakeup interrupt */
#define CAN_MSR_WKUI			(1 << 3)

/* ERRI: Error interrupt */
#define CAN_MSR_ERRI			(1 << 2)

/* SLAK: Sleep acknowledge */
#define CAN_MSR_SLAK			(1 << 1)

/* INAK: Initialization acknowledge */
#define CAN_MSR_INAK			(1 << 0)

/* --- CAN_TSR values ------------------------------------------------------- */

/* LOW: Lowest priority flag for mailbox*/
#define CAN_TSR_LOW(mbox)		(1 << (29 + mbox))
#define CAN_TSR_LOW2			CAN_TSR_LOW(2)
#define CAN_TSR_LOW1			CAN_TSR_LOW(1)
#define CAN_TSR_LOW0			CAN_TSR_LOW(0)

/* TME: Transmit mailbox empty */
#define CAN_TSR_TME(mbox)		(1 << (26 + mbox))
#define CAN_TSR_TME2			CAN_TSR_TME(2)
#define CAN_TSR_TME1			CAN_TSR_TME(1)
#define CAN_TSR_TME0			CAN_TSR_TME(0)

/* CODE[1:0]: Mailbox code */
#define CAN_TSR_CODE_SHIFT		24
#define CAN_TSR_CODE_MASK		(0x3 << CAN_TSR_CODE_SHIFT)
#define CAN_TSR_CODE			(0x3 << CAN_TSR_CODE_SHIFT)

/* ABRQ0: Abort request for mailbox */
#define CAN_TSR_ABRQ(mbox)		(1 << (7 + (mbox)*8))
#define CAN_TSR_ABRQ2			CAN_TSR_ABRQ(2)
#define CAN_TSR_ABRQ1			CAN_TSR_ABRQ(1)
#define CAN_TSR_ABRQ0			CAN_TSR_ABRQ(0)

/* 6:4 Reserved, forced by hardware to 0 */

/* TERR0: Transmission error for mailbox */
#define CAN_TSR_TERR(mbox)		(1 << (3 + (mbox)*8))
#define CAN_TSR_TERR2			CAN_TSR_TERR(2)
#define CAN_TSR_TERR1			CAN_TSR_TERR(1)
#define CAN_TSR_TERR0			CAN_TSR_TERR(0)

/* ALST0: Arbitration lost for mailbox */
#define CAN_TSR_ALST(mbox)		(1 << (2 + (mbox)*8))
#define CAN_TSR_ALST2			CAN_TSR_ALST(2)
#define CAN_TSR_ALST1			CAN_TSR_ALST(1)
#define CAN_TSR_ALST0			CAN_TSR_ALST(0)

/* TXOK0: Transmission OK for mailbox*/
#define CAN_TSR_TXOK(mbox)		(1 << (1 + (mbox)*8))
#define CAN_TSR_TXOK2			CAN_TSR_TXOK(2)
#define CAN_TSR_TXOK1			CAN_TSR_TXOK(1)
#define CAN_TSR_TXOK0			CAN_TSR_TXOK(0)


/* RQCP0: Request completed mailbox */
#define CAN_TSR_RQCP(mbox)		(1 << (0 + (mbox)*8))
#define CAN_TSR_RQCP2			CAN_TSR_RQCP(2)
#define CAN_TSR_RQCP1			CAN_TSR_RQCP(1)
#define CAN_TSR_RQCP0			CAN_TSR_RQCP(0)

/* --- CAN_RFxR values ------------------------------------------------------ */

/* 31:6 Reserved, forced by hardware to 0 */

/* RFOM0: Release FIFO x output mailbox */
#define CAN_RFxR_RFOM			(1 << 5)
#define CAN_RF0R_RFOM0			CAN_RFxR_RFOM
#define CAN_RF1R_RFOM1			CAN_RFxR_RFOM

/* FOVR0: FIFO 0 overrun */
#define CAN_RFxR_FOVR			(1 << 4)
#define CAN_RF0R_FOVR0			CAN_RFxR_FOVR
#define CAN_RF1R_FOVR1			CAN_RFxR_FOVR
#define CAN_RF0R_FAVR0			CAN_RFxR_FOVR /* TODO typo fix ? */
#define CAN_RF0R_FAVR1			CAN_RFxR_FOVR /* TODO typo fix ? */

/* FULL0: FIFO 0 full */
#define CAN_RFxR_FULL			(1 << 3)
#define CAN_RF0R_FULL0			CAN_RFxR_FULL
#define CAN_RF1R_FULL1			CAN_RFxR_FULL

/* 2 Reserved, forced by hardware to 0 */

/* FMP0[1:0]: FIFO 0 message pending */
#define CAN_RFxR_FMP			(0x3 << 0)
#define CAN_RF0R_FMP0			CAN_RFxR_FMP
#define CAN_RF1R_FMP1			CAN_RFxR_FMP
#define CAN_RF0R_FMP0_MASK		CAN_RFxR_FMP
#define CAN_RF1R_FMP1_MASK		CAN_RFxR_FMP

/* --- CAN_IER values ------------------------------------------------------- */

/* 32:18 Reserved, forced by hardware to 0 */

/* SLKIE: Sleep interrupt enable */
#define CAN_IER_SLKIE			(1 << 17)

/* WKUIE: Wakeup interrupt enable */
#define CAN_IER_WKUIE			(1 << 16)

/* ERRIE: Error interrupt enable */
#define CAN_IER_ERRIE			(1 << 15)

/* 14:12 Reserved, forced by hardware to 0 */

/* LECIE: Last error code interrupt enable */
#define CAN_IER_LECIE			(1 << 11)

/* BOFIE: Bus-off interrupt enable */
#define CAN_IER_BOFIE			(1 << 10)

/* EPVIE: Error passive interrupt enable */
#define CAN_IER_EPVIE			(1 << 9)

/* EWGIE: Error warning interrupt enable */
#define CAN_IER_EWGIE			(1 << 8)

/* 7 Reserved, forced by hardware to 0 */

/* FOVIE: FIFO overrun interrupt enable */
#define CAN_IER_FOVIE(fifo)		(1 << (3 + (fifo)*3))
#define CAN_IER_FOVIE1			CAN_IER_FOVIE(1)
#define CAN_IER_FOVIE0			CAN_IER_FOVIE(0)

/* FFIE: FIFO full interrupt enable */
#define CAN_IER_FFIE(fifo)		(1 << (2 + (fifo)*3))
#define CAN_IER_FFIE1			CAN_IER_FFIE(1)
#define CAN_IER_FFIE0			CAN_IER_FFIE(0)

/* FMPIE: FIFO message pending interrupt enable */
#define CAN_IER_FMPIE(fifo)		(1 << (1 + (fifo)*3))
#define CAN_IER_FMPIE1			CAN_IER_FMPIE(1)
#define CAN_IER_FMPIE0			CAN_IER_FMPIE(0)

/* TMEIE: Transmit mailbox empty interrupt enable */
#define CAN_IER_TMEIE			(1 << 0)

/* --- CAN_ESR values ------------------------------------------------------- */

/* REC[7:0]: Receive error counter */
#define CAN_ESR_REC_MASK		(0xF << 24)
#define CAN_ESR_REC			(0xF << 24)

/* TEC[7:0]: Least significant byte of the 9-bit transmit error counter */
#define CAN_ESR_TEC_MASK		(0xF << 16)
#define CAN_ESR_TEC			(0xF << 16)

/* 15:7 Reserved, forced by hardware to 0 */

/* LEC[2:0]: Last error code */
#define CAN_ESR_LEC_SHIFT		4
#define CAN_ESR_LEC_MASK		(0x7 << CAN_ESR_LEC_SHIFT)
#define CAN_ESR_LEC			(0x7 << CAN_ESR_LEC_SHIFT)

/******************************************************************************/
/** @defgroup can_esr_values CAN Last Error Codes
 * @ingroup can_defines
 *
 *@{*/
#define CAN_ESR_LEC_NO_ERROR		(0x0 << CAN_ESR_LEC_SHIFT)
#define CAN_ESR_LEC_STUFF_ERROR		(0x1 << CAN_ESR_LEC_SHIFT)
#define CAN_ESR_LEC_FORM_ERROR		(0x2 << CAN_ESR_LEC_SHIFT)
#define CAN_ESR_LEC_ACK_ERROR		(0x3 << CAN_ESR_LEC_SHIFT)
#define CAN_ESR_LEC_REC_ERROR		(0x4 << CAN_ESR_LEC_SHIFT)
#define CAN_ESR_LEC_DOM_ERROR		(0x5 << CAN_ESR_LEC_SHIFT)
#define CAN_ESR_LEC_CRC_ERROR		(0x6 << CAN_ESR_LEC_SHIFT)
#define CAN_ESR_LEC_SOFT_ERROR		(0x7 << CAN_ESR_LEC_SHIFT)
/**@}*/

/* 3 Reserved, forced by hardware to 0 */

/* BOFF: Bus-off flag */
#define CAN_ESR_BOFF			(1 << 2)

/* EPVF: Error passive flag */
#define CAN_ESR_EPVF			(1 << 1)

/* EWGF: Error warning flag */
#define CAN_ESR_EWGF			(1 << 0)

/* --- CAN_BTR values ------------------------------------------------------- */

/* SILM: Silent mode (debug) */
#define CAN_BTR_SILM			(1 << 31)

/* LBKM: Loop back mode (debug) */
#define CAN_BTR_LBKM			(1 << 30)

/* 29:26 Reserved, forced by hardware to 0 */

/* SJW[1:0]: Resynchronization jump width */
#define CAN_BTR_SJW_SHIFT		24
#define CAN_BTR_SJW			(0x3 << CAN_BTR_SJW_SHIFT)
#define CAN_BTR_SJW_MASK		(0x3 << CAN_BTR_SJW_SHIFT)
#define CAN_BTR_SJW_VAL(tq)		(((tq) - 1) << CAN_BTR_SJW_SHIFT)

/******************************************************************************/
/** @defgroup can_sjw_values CAN Resynchronization Jump Width values
 * @ingroup can_defines
 *
 *@{*/
#define CAN_BTR_SJW_1TQ			CAN_BTR_SJW_VAL(1)
#define CAN_BTR_SJW_2TQ			CAN_BTR_SJW_VAL(2)
#define CAN_BTR_SJW_3TQ			CAN_BTR_SJW_VAL(3)
#define CAN_BTR_SJW_4TQ			CAN_BTR_SJW_VAL(4)
/**@}*/


/* 23 Reserved, forced by hardware to 0 */

/* TS2[2:0]: Time segment 2 */
#define CAN_BTR_TS2_SHIFT		20
#define CAN_BTR_TS2_MASK		(0x7 << CAN_BTR_TS2_SHIFT)
#define CAN_BTR_TS2			(0x7 << CAN_BTR_TS2_SHIFT)
#define CAN_BTR_TS2_VAL(tq)		(((tq) - 1) << CAN_BTR_TS2_SHIFT)

/******************************************************************************/
/** @defgroup can_ts2_values CAN Time Segment 2 values
 * @ingroup can_defines
 *
 *@{*/
#define CAN_BTR_TS2_1TQ			CAN_BTR_TS2_VAL(1)
#define CAN_BTR_TS2_2TQ			CAN_BTR_TS2_VAL(2)
#define CAN_BTR_TS2_3TQ			CAN_BTR_TS2_VAL(3)
#define CAN_BTR_TS2_4TQ			CAN_BTR_TS2_VAL(4)
#define CAN_BTR_TS2_5TQ			CAN_BTR_TS2_VAL(5)
#define CAN_BTR_TS2_6TQ			CAN_BTR_TS2_VAL(6)
#define CAN_BTR_TS2_7TQ			CAN_BTR_TS2_VAL(7)
#define CAN_BTR_TS2_8TQ			CAN_BTR_TS2_VAL(8)
/**@}*/

/* TS1[3:0]: Time segment 1 */
#define CAN_BTR_TS1_SHIFT		16
#define CAN_BTR_TS1_MASK		(0xF << CAN_BTR_TS1_SHIFT)
#define CAN_BTR_TS1			(0xF << CAN_BTR_TS1_SHIFT)
#define CAN_BTR_TS1_VAL(tq)		(((tq) - 1) << CAN_BTR_TS1_SHIFT)

/******************************************************************************/
/** @defgroup can_ts1_values CAN Time Segment 1 values
 * @ingroup can_defines
 *
 *@{*/
#define CAN_BTR_TS1_1TQ			CAN_BTR_TS1_VAL(1)
#define CAN_BTR_TS1_2TQ			CAN_BTR_TS1_VAL(2)
#define CAN_BTR_TS1_3TQ			CAN_BTR_TS1_VAL(3)
#define CAN_BTR_TS1_4TQ			CAN_BTR_TS1_VAL(4)
#define CAN_BTR_TS1_5TQ			CAN_BTR_TS1_VAL(5)
#define CAN_BTR_TS1_6TQ			CAN_BTR_TS1_VAL(6)
#define CAN_BTR_TS1_7TQ			CAN_BTR_TS1_VAL(7)
#define CAN_BTR_TS1_8TQ			CAN_BTR_TS1_VAL(8)
#define CAN_BTR_TS1_9TQ			CAN_BTR_TS1_VAL(9)
#define CAN_BTR_TS1_10TQ		CAN_BTR_TS1_VAL(10)
#define CAN_BTR_TS1_11TQ		CAN_BTR_TS1_VAL(11)
#define CAN_BTR_TS1_12TQ		CAN_BTR_TS1_VAL(12)
#define CAN_BTR_TS1_13TQ		CAN_BTR_TS1_VAL(13)
#define CAN_BTR_TS1_14TQ		CAN_BTR_TS1_VAL(14)
#define CAN_BTR_TS1_15TQ		CAN_BTR_TS1_VAL(15)
#define CAN_BTR_TS1_16TQ		CAN_BTR_TS1_VAL(16)
/**@}*/



/* 15:10 Reserved, forced by hardware to 0 */

/* BRP[9:0]: Baud rate prescaler */
#define CAN_BTR_BRP_SHIFT		0
#define CAN_BTR_BRP_MASK		(0x1FFUL << CAN_BTR_BRP_SHIFT)
#define CAN_BTR_BRP			(0x1FFUL << CAN_BTR_BRP_SHIFT)
#define CAN_BTR_BRP_VAL(brp)		(((brp) - 1ul) << CAN_BTR_BRP_SHIFT)

/* --- CAN_TIxR values ------------------------------------------------------ */

/* STID[10:0]: Standard identifier */
#define CAN_TIxR_STID_SHIFT		21
#define CAN_TIxR_STID_MASK		(0x7FF << CAN_TIxR_STID_SHIFT)
#define CAN_TIxR_STID			(0x7FF << CAN_TIxR_STID_SHIFT)
#define CAN_TIxR_STID_VAL(id)		((id) << CAN_TIxR_STID_SHIFT)

/* EXID[15:0]: Extended identifier */
#define CAN_TIxR_EXID_SHIFT		3
#define CAN_TIxR_EXID_MASK		(0x1FFFFFF << CAN_TIxR_EXID_SHIFT)
#define CAN_TIxR_EXID			(0x1FFFFFF << CAN_TIxR_EXID_SHIFT)
#define CAN_TIxR_EXID_VAL(id)		((id) << CAN_TIxR_EXID_SHIFT)

/* IDE: Identifier extension */
#define CAN_TIxR_IDE			(1 << 2)

/* RTR: Remote transmission request */
#define CAN_TIxR_RTR			(1 << 1)

/* TXRQ: Transmit mailbox request */
#define CAN_TIxR_TXRQ			(1 << 0)

/* --- CAN_TDTxR values ----------------------------------------------------- */

/* TIME[15:0]: Message time stamp */
#define CAN_TDTxR_TIME_SHIFT		15
#define CAN_TDTxR_TIME_MASK		(0xFFFF << CAN_TDTxR_TIME_SHIFT)
#define CAN_TDTxR_TIME			(0xFFFF << CAN_TDTxR_TIME_SHIFT)


/* 15:6 Reserved, forced by hardware to 0 */

/* TGT: Transmit global time */
#define CAN_TDTxR_TGT			(1 << 5)

/* 7:4 Reserved, forced by hardware to 0 */

/* DLC[3:0]: Data length code */
#define CAN_TDTxR_DLC_SHIFT		0
#define CAN_TDTxR_DLC_MASK		(0xF << CAN_TDTxR_DLC_SHIFT)
#define CAN_TDTxR_DLC			(0xF << CAN_TDTxR_DLC_SHIFT)


/* --- CAN_TDLxR values ----------------------------------------------------- */

/* DATA3[7:0]: Data byte 3 */
/* DATA2[7:0]: Data byte 2 */
/* DATA1[7:0]: Data byte 1 */
/* DATA0[7:0]: Data byte 0 */

/* --- CAN_TDHxR values ----------------------------------------------------- */

/* DATA7[7:0]: Data byte 7 */
/* DATA6[7:0]: Data byte 6 */
/* DATA5[7:0]: Data byte 5 */
/* DATA4[7:0]: Data byte 4 */

/* --- CAN_RIxR values ------------------------------------------------------ */

/* TODO: BUG ? Missing shift in _MASK ??? */
/* STID[10:0]: Standard identifier */
#define CAN_RIxR_STID_SHIFT		21
#define CAN_RIxR_STID_MASK		(0x7FF)
#define CAN_RIxR_STID			(0x7FF << CAN_RIxR_STID_SHIFT)


/* EXID[15:0]: Extended identifier */
#define CAN_RIxR_EXID_SHIFT		3
#define CAN_RIxR_EXID_MASK		(0x1FFFFFFF)
#define CAN_RIxR_EXID			(0x1FFFFFFF << CAN_RIxR_EXID_SHIFT)

/* IDE: Identifier extension */
#define CAN_RIxR_IDE			(1 << 2)

/* RTR: Remote transmission request */
#define CAN_RIxR_RTR			(1 << 1)

/* 0 Reserved */

/* --- CAN_RDTxR values ----------------------------------------------------- */

/* TIME[15:0]: Message time stamp */
#define CAN_RDTxR_TIME_SHIFT		15
#define CAN_RDTxR_TIME_MASK		(0xFFFF << CAN_RDTxR_TIME_SHIFT)
#define CAN_RDTxR_TIME			(0xFFFF << CAN_RDTxR_TIME_SHIFT)


/* FMI[7:0]: Filter match index */
#define CAN_RDTxR_FMI_SHIFT		8
#define CAN_RDTxR_FMI_MASK		(0xFF << CAN_RDTxR_FMI_SHIFT)
#define CAN_RDTxR_FMI			(0xFF << CAN_RDTxR_FMI_SHIFT)


/* 7:4 Reserved, forced by hardware to 0 */

/* DLC[3:0]: Data length code */
#define CAN_RDTxR_DLC_SHIFT		0
#define CAN_RDTxR_DLC_MASK		(0xF << CAN_RDTxR_DLC_SHIFT)
#define CAN_RDTxR_DLC			(0xF << CAN_RDTxR_DLC_SHIFT)


/* --- CAN_RDLxR values ----------------------------------------------------- */

/* DATA3[7:0]: Data byte 3 */
/* DATA2[7:0]: Data byte 2 */
/* DATA1[7:0]: Data byte 1 */
/* DATA0[7:0]: Data byte 0 */

/* --- CAN_RDHxR values ----------------------------------------------------- */

/* DATA7[7:0]: Data byte 7 */
/* DATA6[7:0]: Data byte 6 */
/* DATA5[7:0]: Data byte 5 */
/* DATA4[7:0]: Data byte 4 */

/* --- CAN_FMR values ------------------------------------------------------- */

/* 31:14 Reserved, forced to reset value */

/*
 * CAN2SB[5:0]: CAN2 start bank
 * (only on connectivity line devices otherwise reserved)
 */
// #define CAN_FMR_CAN2SB_SHIFT		15
#define CAN_FMR_CAN2SB_SHIFT		8
#define CAN_FMR_CAN2SB_MASK		(0x3F << CAN_FMR_CAN2SB_SHIFT)
#define CAN_FMR_CAN2SB			(0x3F << CAN_FMR_CAN2SB_SHIFT)

/* 7:1 Reserved, forced to reset value */

/* FINIT: Filter init mode */
#define CAN_FMR_FINIT			(1 << 0)

/* --- CAN_FM1R values ------------------------------------------------------ */

/* 31:28 Reserved, forced by hardware to 0 */

/*
 * FBMx: Filter mode
 * x is 0..27 should be calculated by a helper function making so many macros
 * seems like an overkill?
 */

/* --- CAN_FS1R values ------------------------------------------------------ */

/* 31:28 Reserved, forced by hardware to 0 */

/*
 * FSCx: Filter scale configuration
 * x is 0..27 should be calculated by a helper function making so many macros
 * seems like an overkill?
 */

/* --- CAN_FFA1R values ----------------------------------------------------- */

/* 31:28 Reserved, forced by hardware to 0 */

/*
 * FFAx: Filter scale configuration
 * x is 0..27 should be calculated by a helper function making so many macros
 * seems like an overkill?
 */

/* --- CAN_FA1R values ------------------------------------------------------ */

/* 31:28 Reserved, forced by hardware to 0 */

/*
 * FACTx: Filter active
 * x is 0..27 should be calculated by a helper function making so many macros
 * seems like an overkill?
 */

/* --- CAN_FiRx values ------------------------------------------------------ */

/* FB[31:0]: Filter bits */

/* --- CAN functions -------------------------------------------------------- */

/** @brief Can Bit timing description
 *
 * All values are in Time Quantas.
 *
 * One bit time = $ TQ * (1 + ts1 + ts2) $
 * Sample Point = $ (1 + ts1) / (1 + ts1 + ts2) $
 *
 * Resynchronization jump width must be less than time segment2 to work properly
 *
 * For the exact correct setting, consult the BOSCH appnote:
 *
 * http://www.bosch-semiconductors.de/media/pdf_1/canliteratur/cia99paper.pdf
 *
 */
struct can_timing {
	/** @brief Baud Rate Prescaler value
	 *
	 * This defines resolution of the time quanta (TQ)
	 *
	 * 1 TQ = apb_clock / brp
	 */
	uint32_t brp;

	/** @brief Time segment 1
	 *
	 * This defines the number of TQ's in the time segment1
	 */
	uint32_t ts1;

	/** @brief Time segment 2
	 *
	 * This defines the number of TQ's in the time segment2
	 */
	uint32_t ts2;

	/** @brief Synchronization jump
	 *
	 * This defines the number of TQ's, which can shring time segment 2 or
	 * grow time segment 1 in the case of clock speed mismatch.
	 *
	 * The bigger values is intended for worser clocks and better cabling.
	 */
	uint32_t sjw;
};

/******************************************************************************/
/** @defgroup can_freq CAN Bit frequency
 * @ingroup can_defines
 *
 *@{*/
#define CAN_FREQ_1M		1000000
#define CAN_FREQ_500K		500000
#define CAN_FREQ_250K		250000
#define CAN_FREQ_125K		125000
#define CAN_FREQ_50K		50000
#define CAN_FREQ_10K		10000
/**@}*/

/******************************************************************************/
/** @defgroup can_samplepoint CAN Sample point values
 * @ingroup can_defines
 *
 *@{*/
#define CAN_SAMPLE_75		(3 * 0x100 / 4)
#define CAN_SAMPLE_66		(2 * 0x100 / 3)
#define CAN_SAMPLE_50		(1 * 0x100 / 2)
/**@}*/

BEGIN_DECLS

void can_reset(uint32_t canport);

/* Operation modes */
void can_enter_init_mode(uint32_t canport);
void can_leave_init_mode(uint32_t canport);
void can_enter_sleep_mode(uint32_t canport);
void can_leave_sleep_mode(uint32_t canport);

bool can_enter_init_mode_blocking(uint32_t canport);
bool can_leave_init_mode_blocking(uint32_t canport);

bool can_is_init_mode(uint32_t canport);
bool can_is_sleep_mode(uint32_t canport);

/* Operation flags */
void can_mode_set_timetriggered(uint32_t canport, bool enable);
void can_mode_set_autobusoff(uint32_t canport, bool enable);
void can_mode_set_autowakeup(uint32_t canport, bool enable);
void can_mode_set_noretransmit(uint32_t canport, bool enable);
void can_mode_set_rxfifo_locked(uint32_t canport, bool enable);
void can_mode_set_txframe_priority(uint32_t canport, bool enable);
void can_mode_set_silent(uint32_t canport, bool enable);
void can_mode_set_loopback(uint32_t canport, bool enable);

int can_init(uint32_t canport, bool ttcm, bool abom, bool awum, bool nart,
	     bool rflm, bool txfp, uint32_t sjw, uint32_t ts1, uint32_t ts2,
	     uint32_t brp, bool loopback, bool silent);

void can_filter_set_slave_start(uint32_t canport, uint32_t nr);
void can_filter_init(uint32_t canport, uint32_t nr, bool scale_32bit,
		     bool id_list_mode, uint32_t fr1, uint32_t fr2,
		     uint32_t fifo, bool enable);
void can_filter_id_mask_16bit_init(uint32_t canport, uint32_t nr, uint16_t id1,
				   uint16_t mask1, uint16_t id2,
				   uint16_t mask2, uint32_t fifo, bool enable);
void can_filter_id_mask_32bit_init(uint32_t canport, uint32_t nr, uint32_t id,
				   uint32_t mask, uint32_t fifo, bool enable);
void can_filter_id_list_16bit_init(uint32_t canport, uint32_t nr, uint16_t id1,
				   uint16_t id2, uint16_t id3, uint16_t id4,
				   uint32_t fifo, bool enable);
void can_filter_id_list_32bit_init(uint32_t canport, uint32_t nr, uint32_t id1,
				   uint32_t id2, uint32_t fifo, bool enable);

/* irq operations */
void can_enable_irq(uint32_t canport, uint32_t irq);
void can_disable_irq(uint32_t canport, uint32_t irq);
bool can_status_irq_is_pending(uint32_t canport, uint32_t irq);
bool can_error_irq_is_pending(uint32_t canport, uint32_t irq);
bool can_fifo_irq_is_pending(uint32_t canport, uint32_t irq);
bool can_transmit_irq_is_pending(uint32_t canport, uint32_t irq);
bool can_status_irq_clear_pending(uint32_t canport, uint32_t irq);
bool can_fifo_irq_clear_pending(uint32_t canport, uint32_t irq);

bool can_transmit_mbox(uint32_t canport, uint32_t mailbox, uint32_t id,
		bool ext, bool rtr, uint8_t *data, uint8_t length);

int can_transmit(uint32_t canport, uint32_t id, bool ext, bool rtr,
		 uint8_t length, uint8_t *data);
void can_receive(uint32_t canport, uint8_t fifo, bool release, uint32_t *id,
		 bool *ext, bool *rtr, uint32_t *fmi, uint8_t *length,
		 uint8_t *data);

void can_fifo_release(uint32_t canport, uint8_t fifo);

/* mailbox operations */
bool can_available_mailbox(uint32_t canport);
int32_t can_get_empty_mailbox(uint32_t canport);

/* error operations */
uint32_t can_errorcode(uint32_t canport);

/* timing operations */
void can_timing_set(uint32_t canport, struct can_timing *timing);
bool can_timing_init(struct can_timing *timing, uint32_t freq, uint32_t sample);
uint32_t can_timing_getfreq(struct can_timing *timing);

END_DECLS

#endif
/** @cond */
#else
#warning "can_common_bxcan.h should not be included explicitly, only via can.h"
#endif
/** @endcond */

