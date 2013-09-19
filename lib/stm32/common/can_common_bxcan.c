/** @addtogroup can_file
 *
 * @author @htmlonly &copy; @endhtmlonly 2010 Piotr Esden-Tempski
 * <piotr@esden.net>
 *
 * @date 12 November 2012
 *
 * Devices can have up to two CAN peripherals. The peripherals support up to
 * 1MBit transmission rate. The peripheral has several filters for incoming
 * messages that can be distributed between two FIFOs and three transmit
 * mailboxes.
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

#include <libopencm3/stm32/can.h>
#include <libopencm3/stm32/rcc.h>

/**@{*/

/* Timeout for CAN INIT acknowledge
 * this value is difficult to define.
 * INIT is set latest after finishing the current transfer.
 * Assuming the lowest CAN speed of 100kbps one CAN frame may take about 1.6ms
 * WAIT loop timeout varies on compiler switches, optimization, CPU architecture
 * and CPU speed
 *
 * The same timeout value is used for leaving INIT where the longest time is
 * 11 bits(110 us on 100 kbps).
 */
#define CAN_MSR_INAK_TIMEOUT 0x0000FFFF

/*----------------------------------------------------------------------------*/
/** @brief CAN Reset
 *
 * The CAN peripheral and all its associated configuration registers are placed
 * in the reset condition. The reset is effective via the RCC peripheral reset
 * system.
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 */
void can_reset(uint32_t canport)
{
	if (canport == CAN1) {
		rcc_peripheral_reset(&RCC_APB1RSTR, RCC_APB1RSTR_CAN1RST);
		rcc_peripheral_clear_reset(&RCC_APB1RSTR, RCC_APB1RSTR_CAN1RST);
	} else {
		rcc_peripheral_reset(&RCC_APB1RSTR, RCC_APB1RSTR_CAN2RST);
		rcc_peripheral_clear_reset(&RCC_APB1RSTR, RCC_APB1RSTR_CAN2RST);
	}
}

/*----------------------------------------------------------------------------*/
/** @brief Enter the core into the Init mode
 *
 * In this mode, the CAN communication is stopped, and all initialization
 * operation commands are allowed.
 *
 * Note there can be some delay between set Initialization mode and mode set
 * due to clock domains synchronization. User must test, if the init mode has
 * been set before any init commands.
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 */
void can_enter_init_mode(uint32_t canport)
{
	CAN_MCR(canport) |= CAN_MCR_INRQ;
}

/*----------------------------------------------------------------------------*/
/** @brief Leave the core from the Init mode
 *
 * In this mode, All initialization operation commands are prohibited, the bus
 * is in the operational state, and messages can be received and transmitted.
 *
 * Note there can be some delay between exit Initialization mode and mode exit
 * due to clock domains synchronization. User must test, if the init mode has
 * been exit before any message transmission.
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 */
void can_leave_init_mode(uint32_t canport)
{
	CAN_MCR(canport) &= ~CAN_MCR_INRQ;
}

/*----------------------------------------------------------------------------*/
/** @brief Enter the core into the Sleep mode
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 */
void can_enter_sleep_mode(uint32_t canport)
{
	CAN_MCR(canport) |= CAN_MCR_SLEEP;
}

/*----------------------------------------------------------------------------*/
/** @brief Leave the core from the Sleep mode
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 */
void can_leave_sleep_mode(uint32_t canport)
{
	CAN_MCR(canport) &= ~CAN_MCR_SLEEP;
}

/*----------------------------------------------------------------------------*/
/** @brief Enter the core into the Init mode
 *
 * In this mode, the CAN communication is stopped, and all initialization
 * operation commands are allowed.
 *
 * This blocking call automatically waits for the finish of the operation and
 * the user can send any init command safely after this call.
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @returns true on success, false on failure
 */
bool can_enter_init_mode_blocking(uint32_t canport)
{
	volatile uint32_t wait_ack;

	CAN_MCR(canport) |= CAN_MCR_INRQ;

	/* Wait for acknowledge. */
	wait_ack = CAN_MSR_INAK_TIMEOUT;
	while ((--wait_ack) && !can_is_init_mode(canport));

	/* Check the acknowledge. */
	return can_is_init_mode(canport);
}

/*----------------------------------------------------------------------------*/
/** @brief Exit the core from the Init mode
 *
 * In this mode, all initialization operation commands are prohibited, the bus
 * is in the operational state, and messages can be received and transmitted.
 *
 * This blocking call automatically waits for the finish of the operation and
 * the user can send any init command safely after this call.
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @returns true on success, false on failure
 */
bool can_leave_init_mode_blocking(uint32_t canport)
{
	volatile uint32_t wait_ack;

	CAN_MCR(canport) &= ~CAN_MCR_INRQ;

	/* Wait for acknowledge. */
	wait_ack = CAN_MSR_INAK_TIMEOUT;
	while ((--wait_ack) && can_is_init_mode(canport));

	/* Check the acknowledge. */
	return !can_is_init_mode(canport);
}

/*----------------------------------------------------------------------------*/
/** @brief Is the core in Init mode ?
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @returns true, if the core is in the initialization mode
 */
bool can_is_init_mode(uint32_t canport)
{
	return (CAN_MSR(canport) & CAN_MSR_INAK) != 0;
}

/*----------------------------------------------------------------------------*/
/** @brief Is the core in Sleep mode ?
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @returns true, if the core is in the sleeping mode
 */
bool can_is_sleep_mode(uint32_t canport)
{
	return (CAN_MSR(canport) & CAN_MSR_SLAK) != 0;
}

/*----------------------------------------------------------------------------*/
/** @brief Init mode - Time Triggered Communication
 *
 * If enabled, a two-byte timestamp is added at the end to each transmitted
 * frame
 *
 * This function can be called only in the Init mode.
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] enable bool The desired state of the mode.
 */
void can_mode_set_timetriggered(uint32_t canport, bool enable)
{
	if (enable) {
		CAN_MCR(canport) |= CAN_MCR_TTCM;
	} else {
		CAN_MCR(canport) &= ~CAN_MCR_TTCM;
	}
}

/*----------------------------------------------------------------------------*/
/** @brief Init mode - Automatic Bus-Off
 *
 * If enabled, The bus-off state is automatically acknowledged, and restored on
 * the correct bus operation.
 *
 * This function can be called only in the Init mode.
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] enable bool The desired state of the mode.
 */
void can_mode_set_autobusoff(uint32_t canport, bool enable)
{
	if (enable) {
		CAN_MCR(canport) |= CAN_MCR_ABOM;
	} else {
		CAN_MCR(canport) &= ~CAN_MCR_ABOM;
	}
}

/*----------------------------------------------------------------------------*/
/** @brief Init mode - Automatic wake-up
 *
 * If enabled, The core will be automatically woken in presence of bus activity.
 *
 * This function can be called only in the Init mode.
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] enable bool The desired state of the mode.
 */
void can_mode_set_autowakeup(uint32_t canport, bool enable)
{
	if (enable) {
		CAN_MCR(canport) |= CAN_MCR_AWUM;
	} else {
		CAN_MCR(canport) &= ~CAN_MCR_AWUM;
	}
}

/*----------------------------------------------------------------------------*/
/** @brief Init mode - No retransmit frames
 *
 * If enabled, The core will not retransmit frames, that will cause error on the
 * bus (collision errors...). Otherwise, the frames will be retransmitted on the
 * next bus idle state.
 *
 * This function can be called only in the Init mode.
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] enable bool The desired state of the mode.
 */
void can_mode_set_noretransmit(uint32_t canport, bool enable)
{
	if (enable) {
		CAN_MCR(canport) |= CAN_MCR_NART;
	} else {
		CAN_MCR(canport) &= ~CAN_MCR_NART;
	}
}

/*----------------------------------------------------------------------------*/
/** @brief Init mode - RX FIFO Locked
 *
 * If enabled,
 *
 * This function can be called only in the Init mode.
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] enable bool The desired state of the mode.
 */
void can_mode_set_rxfifo_locked(uint32_t canport, bool enable)
{
	if (enable) {
		CAN_MCR(canport) |= CAN_MCR_RFLM;
	} else {
		CAN_MCR(canport) &= ~CAN_MCR_RFLM;
	}
}

/*----------------------------------------------------------------------------*/
/** @brief Init mode - TX frame priority
 *
 * If enabled, the order of transmitted frames on the bus is computed from the
 * frame ID (lower ID has higher priority and be served first). Otherwise, the
 * transmitted frames are sent exactly in order they was written to the transmit
 * FIFO.
 *
 * This function can be called only in the Init mode.
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] enable bool The desired state of the mode.
 */
void can_mode_set_txframe_priority(uint32_t canport, bool enable)
{
	if (enable) {
		CAN_MCR(canport) |= CAN_MCR_TXFP;
	} else {
		CAN_MCR(canport) &= ~CAN_MCR_TXFP;
	}
}

/*----------------------------------------------------------------------------*/
/** @brief Init mode - Debug set silent mode
 *
 * If enabled, the TX port is disconnected from the bus, and the transmitted
 * frames are not propagated to the external bus.
 *
 * This function can be called only in the Init mode.
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] enable bool The desired state of the mode.
 */
void can_debug_set_silent(uint32_t canport, bool enable)
{
	if (enable) {
		CAN_BTR(canport) |= CAN_BTR_SILM;
	} else {
		CAN_BTR(canport) &= ~CAN_BTR_SILM;
	}
}

/*----------------------------------------------------------------------------*/
/** @brief Init mode - Debug set loopback mode
 *
 * If enabled, the RX port from the bus is disabled, and the CAN core is
 * receiving only transmitted frames.
 *
 * This function can be called only in the Init mode.
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] enable bool The desired state of the mode.
 */
void can_debug_set_loopback(uint32_t canport, bool enable)
{
	if (enable) {
		CAN_BTR(canport) |= CAN_BTR_LBKM;
	} else {
		CAN_BTR(canport) &= ~CAN_BTR_LBKM;
	}
}

/*----------------------------------------------------------------------------*/
/** @brief Init mode - Debug set freeze mode
 *
 * If enabled, the CAN reception and transmission is freezed during debug
 * session (in situation of code stopped due to breakpoint / stepping)
 *
 * This function can be called only in the Init mode.
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] enable bool The desired state of the mode.
 */
void can_debug_set_freeze(uint32_t canport, bool enable)
{
	if (enable) {
		CAN_MCR(canport) |= CAN_MCR_DBF;
	} else {
		CAN_MCR(canport) &= ~CAN_MCR_DBF;
	}
}

/*----------------------------------------------------------------------------*/
/** @brief CAN Init
 *
 * Initialize the selected CAN peripheral block.
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] ttcm bool. Time triggered communication mode.
 * @param[in] abom bool. Automatic bus-off management.
 * @param[in] awum bool. Automatic wakeup mode.
 * @param[in] nart bool. No automatic retransmission.
 * @param[in] rflm bool. Receive FIFO locked mode.
 * @param[in] txfp bool. Transmit FIFO priority.
 * @param[in] sjw Unsigned int32. Resynchronization time quanta jump width.
 * @param[in] ts1 Unsigned int32. Time segment 1 time quanta width.
 * @param[in] ts2 Unsigned int32. Time segment 2 time quanta width.
 * @param[in] brp Unsigned int32. Baud rate prescaler.
 * @param[in] loopback bool. Debug loopback mode (no receive from bus).
 * @param[in] silent bool. Debug silent mode (no transmit to bus).
 * @returns int 0 on success, 1 on initialization failure.
 */
int can_init(uint32_t canport, bool ttcm, bool abom, bool awum, bool nart,
	     bool rflm, bool txfp, uint32_t sjw, uint32_t ts1, uint32_t ts2,
	     uint32_t brp, bool loopback, bool silent)
{
	can_leave_sleep_mode(canport);

	if (!can_enter_init_mode_blocking(canport)) {
		return 1;
	}

	/* clear can timing bits */
	CAN_BTR(canport) = 0;

	/* set the desired mode */
	can_mode_set_timetriggered(canport, ttcm);
	can_mode_set_autobusoff(canport, abom);
	can_mode_set_autowakeup(canport, awum);
	can_mode_set_noretransmit(canport, nart);
	can_mode_set_rxfifo_locked(canport, rflm);
	can_mode_set_txframe_priority(canport, txfp);
	can_debug_set_silent(canport, silent);
	can_debug_set_loopback(canport, loopback);

	/* Set bit timings. */
	CAN_BTR(canport) |= sjw | ts2 | ts1 |
		(CAN_BTR_BRP_VAL(brp) & CAN_BTR_BRP);

	return can_leave_init_mode_blocking(canport) ? 0 : 1;
}

/*----------------------------------------------------------------------------*/
/** @brief CAN Enable IRQ
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] irq Unsigned int32. IRQ bit(s). (mask of CAN_IER_xxx values)
 */
void can_enable_irq(uint32_t canport, uint32_t irq)
{
	CAN_IER(canport) |= irq;
}

/*----------------------------------------------------------------------------*/
/** @brief CAN Disable IRQ
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] irq Unsigned int32. IRQ bit(s). (mask of CAN_IER_xxx values)
 */
void can_disable_irq(uint32_t canport, uint32_t irq)
{
	CAN_IER(canport) &= ~irq;
}

/*----------------------------------------------------------------------------*/
/** @brief CAN Test, if status IRQ is pending
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] irq Unsigned int32. (mask of CAN_IER_SLKIE, CAN_IER_WKUIE,
 *    CAN_IER_ERRIE values)
 * @returns true, if any of the interrupt in the mask is pending
 */
bool can_status_irq_is_pending(uint32_t canport, uint32_t irq)
{
	uint32_t msr = CAN_MSR(canport);
	bool pending = false;

	pending |= (irq & CAN_IER_SLKIE) && (msr & CAN_MSR_SLAKI);
	pending |= (irq & CAN_IER_WKUIE) && (msr & CAN_MSR_WKUI);
	pending |= (irq & CAN_IER_ERRIE) && (msr & CAN_MSR_ERRI);

	return pending;
}

/*----------------------------------------------------------------------------*/
/** @brief CAN Test, if error IRQ is pending
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] irq Unsigned int32. (mask of CAN_IER_LECIE, CAN_IER_BOFIE,
 *    CAN_IER_EPVIE, CAN_IER_EWGIE values)
 * @returns true, if any of the interrupt in the mask is pending
 */
bool can_error_irq_is_pending(uint32_t canport, uint32_t irq)
{
	uint32_t esr = CAN_ESR(canport);
	bool pending = false;

	pending |= (irq & CAN_IER_LECIE) && (esr & CAN_ESR_LEC);
	pending |= (irq & CAN_IER_BOFIE) && (esr & CAN_ESR_BOFF);
	pending |= (irq & CAN_IER_EPVIE) && (esr & CAN_ESR_EPVF);
	pending |= (irq & CAN_IER_EWGIE) && (esr & CAN_ESR_EWGF);

	return pending;
}


/*----------------------------------------------------------------------------*/
/** @brief CAN Test, if FIFO IRQ is pending
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] irq Unsigned int32. (mask of CAN_IER_FMPIE(x), CAN_IER_FFIE(x) and
 *    CAN_IER_FOVIE(x) values)
 * @returns true, if any of the interrupt in the mask is pending
 */
bool can_fifo_irq_is_pending(uint32_t canport, uint32_t irq)
{
	uint32_t rf0 = CAN_RF0R(canport);
	uint32_t rf1 = CAN_RF1R(canport);
	bool pending = false;

	/* FIFO 0 */
	pending |= (irq & CAN_IER_FMPIE0) && (rf0 & CAN_RF0R_FMP0);
	pending |= (irq & CAN_IER_FFIE0)  && (rf0 & CAN_RF0R_FULL0);
	pending |= (irq & CAN_IER_FOVIE0) && (rf0 & CAN_RF0R_FOVR0);

	/* FIFO 1 */
	pending |= (irq & CAN_IER_FMPIE1) && (rf1 & CAN_RF1R_FMP1);
	pending |= (irq & CAN_IER_FFIE1)  && (rf1 & CAN_RF1R_FULL1);
	pending |= (irq & CAN_IER_FOVIE1) && (rf1 & CAN_RF1R_FOVR1);

	return pending;
}

/*----------------------------------------------------------------------------*/
/** @brief CAN Clear the pending status IRQ and return if any was pending
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] irq Unsigned int32. (mask of CAN_IER_SLKIE, CAN_IER_WKUIE,
 *    CAN_IER_ERRIE values)
 * @returns true, if any of the interrupt in the mask was pending
 */
bool can_status_irq_clear_pending(uint32_t canport, uint32_t irq)
{
	uint32_t msr = CAN_MSR(canport);
	bool pending = false;

	if ((irq & CAN_IER_SLKIE) && (msr & CAN_MSR_SLAKI)) {
		CAN_MSR(canport) = CAN_MSR_SLAKI;
		pending = true;
	}

	if ((irq & CAN_IER_WKUIE) && (msr & CAN_MSR_WKUI)) {
		CAN_MSR(canport) = CAN_MSR_WKUI;
		pending = true;
	}

	if ((irq & CAN_IER_ERRIE) && (msr & CAN_MSR_ERRI)) {
		CAN_MSR(canport) = CAN_MSR_ERRI;
		pending = true;
	}

	return pending;
}

/*----------------------------------------------------------------------------*/
/** @brief CAN Clear the pending FIFO IRQ and return if any was pending
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] irq Unsigned int32. (mask of CAN_IER_FFIE(x), CAN_IER_FOVIE(x)
 *    values)
 * @returns true, if any of the interrupt in the mask is pending
 */
bool can_fifo_irq_clear_pending(uint32_t canport, uint32_t irq)
{
	uint32_t rf0 = CAN_RF0R(canport);
	uint32_t rf1 = CAN_RF1R(canport);
	bool pending = false;

	/* FIFO 0 */
	if ((irq & CAN_IER_FFIE0)  && (rf0 & CAN_RF0R_FULL0)) {
		CAN_RF0R(canport) = CAN_RF0R_FULL0;
		pending = true;
	}
	if ((irq & CAN_IER_FOVIE0) && (rf0 & CAN_RF0R_FOVR0)) {
		CAN_RF0R(canport) = CAN_RF0R_FOVR0;
		pending = true;
	}

	/* FIFO 1 */
	if ((irq & CAN_IER_FFIE1)  && (rf1 & CAN_RF1R_FULL1)) {
		CAN_RF1R(canport) = CAN_RF1R_FULL1;
		pending = true;
	}
	if ((irq & CAN_IER_FOVIE1) && (rf1 & CAN_RF1R_FOVR1)) {
		CAN_RF1R(canport) = CAN_RF1R_FOVR1;
		pending = true;
	}

	return pending;
}

/*----------------------------------------------------------------------------*/
/** @brief Get the actual error code
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @returns The actual error code.
 */
uint32_t can_errorcode(uint32_t canport)
{
	return CAN_ESR(canport) & CAN_ESR_LEC;
}

/******************************************************************************/
/** @defgroup can_mailbox_api CAN Transmit Mailbox API
 * @ingroup can_file
 *
 *@{*/

/*----------------------------------------------------------------------------*/
/** @brief Test, if there is any free transmit mailbox
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @returns  true, if there is any free transmit mailbox.
 */
bool can_mailbox_is_available(uint32_t canport)
{
	return CAN_TSR(canport) & (CAN_TSR_TME0 | CAN_TSR_TME1 | CAN_TSR_TME2);
}

/*----------------------------------------------------------------------------*/
/** @brief Get index of the empty or lowest priority transmit mailbox
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @returns int32_t 0..2: The index of the empty transmit mailbox.
 */
int32_t can_mailbox_get_lowprio(uint32_t canport)
{
	return (CAN_TSR(canport) & CAN_TSR_CODE) >> CAN_TSR_CODE_SHIFT;
}

/*----------------------------------------------------------------------------*/
/** @brief Get the timestamp of the transmitted packet
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] mailbox Unsined int32. CAN mailbox id 0..2
 */
uint16_t can_mailbox_get_timestamp(uint32_t canport, uint32_t mailbox)
{
	return (CAN_TDTxR(canport, mailbox) & CAN_TDTxR_TIME) >>
			CAN_TDTxR_TIME_SHIFT;
}

/*----------------------------------------------------------------------------*/
/** @brief CAN Write data to specified mailbox
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] mailbox Unsined int32 CAN mailbox id 0..2
 * @param[in] data Unsigned int8[]. Message payload data.
 * @param[in] length Unsigned int8. Message payload length.
 */
void can_mailbox_write_data(uint32_t canport, uint32_t mailbox, uint8_t *data,
			    uint8_t length)
{
	union {
		uint8_t data8[4];
		uint32_t data32;
	} tdlxr, tdhxr;

	/* Set the DLC. */
	CAN_TDTxR(canport, mailbox) = (length & CAN_TDTxR_DLC) |
		(CAN_TDTxR(canport, mailbox) & ~CAN_TDTxR_DLC);

	switch (length) {
	case 8:
		tdhxr.data8[3] = data[7];
		/* no break */
	case 7:
		tdhxr.data8[2] = data[6];
		/* no break */
	case 6:
		tdhxr.data8[1] = data[5];
		/* no break */
	case 5:
		tdhxr.data8[0] = data[4];
		/* no break */
	case 4:
		tdlxr.data8[3] = data[3];
		/* no break */
	case 3:
		tdlxr.data8[2] = data[2];
		/* no break */
	case 2:
		tdlxr.data8[1] = data[1];
		/* no break */
	case 1:
		tdlxr.data8[0] = data[0];
		/* no break */
	default:
		break;
	}
	/* Set the data. */

	CAN_TDLxR(canport, mailbox) = tdlxr.data32;
	CAN_TDHxR(canport, mailbox) = tdhxr.data32;
}

/*----------------------------------------------------------------------------*/
/** @brief Set the Message object ID for transmit
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] mailbox Unsined int32 CAN mailbox id 0..2
 * @param[in] mobid Unsined int32 Message Object ID
 */
void can_mailbox_set_mobid(uint32_t canport, uint32_t mailbox,
			      uint32_t mobid)
{
	CAN_TIxR(canport, mailbox) =
		(CAN_ID_ISEXT(mobid) ? CAN_TIxR_IDE : 0) |
		(CAN_ID_ISREMOTE(mobid) ? CAN_TIxR_RTR : 0) |
		(CAN_ID_GETSTD(mobid) << CAN_TIxR_STID_SHIFT) |
		(CAN_ID_GETEXT(mobid) << CAN_TIxR_EXID_SHIFT);
}

/*----------------------------------------------------------------------------*/
/** @brief Transmit global time at the end of message
 *
 * If enabled, the current timestamp is transmitted at last two bytes of
 * transmitted message. Note that the message must be configured to the
 * transmission length of 8 bytes
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] mailbox Unsined int32. CAN mailbox id 0..2
 * @param[in] enable bool. Desired state of the function
 */
void can_mailbox_set_tx_time(uint32_t canport, uint32_t mailbox, bool enable)
{
	if (enable) {
		CAN_TDTxR(canport, mailbox) |= CAN_TDTxR_TGT;
	} else {
		CAN_TDTxR(canport, mailbox) &= ~CAN_TDTxR_TGT;
	}
}

/*----------------------------------------------------------------------------*/
/** @brief Start the transmission on the mailbox
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] mailbox Unsined int32 CAN mailbox id 0..2
 */
void can_mailbox_transmit(uint32_t canport, uint32_t mailbox)
{
	CAN_TIxR(canport, mailbox) |= CAN_TIxR_TXRQ;
}

/*----------------------------------------------------------------------------*/
/** @brief CAN Transmit Message
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] mobid Unsigned int32. Message object identifier
 * @param[in] length Unsigned int8. Message payload length.
 * @param[in] data Unsigned int8[]. Message payload data.
 * @returns int 0, 1 or 2 on success and depending on which outgoing mailbox got
 * selected. -1 if no mailbox was available and no transmission got queued.
 */
int can_transmit(uint32_t canport, uint32_t mobid, uint8_t *data,
		uint8_t length)
{
	uint32_t mailbox = 0;

	if (!can_mailbox_is_available(canport)) {
		return -1;
	}

	/* Check which transmit mailbox is empty */
	mailbox = can_mailbox_get_lowprio(canport);

	/* Transmit message to found mailbox */
	can_mailbox_set_mobid(canport, mailbox, mobid);
	can_mailbox_write_data(canport, mailbox, data, length);
	can_mailbox_transmit(canport, mailbox);

	return mailbox;
}
/**@}*/ /* end of can_mailbox_api group */

/******************************************************************************/
/** @defgroup can_fifo_api CAN Receive FIFO API
 * @ingroup can_file
 *
 *@{*/

 /*---------------------------------------------------------------------------*/
/** @brief CAN FIFO Release
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] fifo Unsigned int8. FIFO id.
 */
void can_fifo_release(uint32_t canport, uint8_t fifo)
{
	CAN_RFxR(canport, fifo) |= CAN_RF1R_RFOM1;
}

/*---------------------------------------------------------------------------*/
/** @brief CAN FIFO Read data
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] fifo Unsigned int8. FIFO id.
 * @param[out] data Unsigned int8[]. Message payload data.
 * @param[out] length Unsigned int8 pointer. Length of message payload.
 */
void can_fifo_read_data(uint32_t canport, uint8_t fifo, uint8_t *data,
			uint8_t *length)
{
	union {
		uint8_t data8[4];
		uint32_t data32;
	} rdlxr, rdhxr;

	/* Get data length. */
	*length = CAN_RDTxR(canport, fifo) & CAN_RDTxR_DLC_MASK;
	/* accelerate reception by copying the CAN data from the controller
	 * memory to the fast internal RAM
	 */

	rdlxr.data32 = CAN_RDLxR(canport, fifo);
	rdhxr.data32 = CAN_RDHxR(canport, fifo);
	/* */
	/* Get data.
	 * Byte wise copy is needed because we do not know the alignment
	 * of the input buffer.
	 * Here copying 8 bytes unconditionally is faster than using loop
	 *
	 * It is OK to copy all 8 bytes because the upper layer must be
	 * prepared for data length bigger expected.
	 * In contrary the driver has no information about the intended size.
	 * This could be different if the max length would be handed over
	 * to the function, but it is not the case
	 */
	data[0] = rdlxr.data8[0];
	data[1] = rdlxr.data8[1];
	data[2] = rdlxr.data8[2];
	data[3] = rdlxr.data8[3];
	data[4] = rdhxr.data8[0];
	data[5] = rdhxr.data8[1];
	data[6] = rdhxr.data8[2];
	data[7] = rdhxr.data8[3];
}

/*----------------------------------------------------------------------------*/
/** @brief Get the Message object identifier
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] fifo Unsined int32. CAN fifo id 0..1
 */
uint32_t can_fifo_get_mobid(uint32_t canport, uint8_t fifo)
{
	uint32_t id = CAN_RIxR(canport, fifo);

	return ((id & CAN_RIxR_IDE) ? CAN_MOBID_IDE : 0) |
		((id & CAN_RIxR_RTR) ? CAN_MOBID_RTR : 0) |
		(CAN_MOBID_STD_VAL(id >> CAN_RIxR_STID_SHIFT) & CAN_MOBID_STD) |
		(CAN_MOBID_EXT_VAL(id >> CAN_RIxR_EXID_SHIFT) & CAN_MOBID_EXT);
}

/*----------------------------------------------------------------------------*/
/** @brief Get the filter index
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] fifo Unsined int32. CAN fifo id 0..1
 */
uint32_t can_fifo_get_filter_id(uint32_t canport, uint8_t fifo)
{
	return (CAN_RDTxR(canport, fifo) & CAN_RDTxR_FMI) >>
			CAN_RDTxR_FMI_SHIFT;
}

/*----------------------------------------------------------------------------*/
/** @brief Get the timestamp of the SOF bit of the packet
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] fifo Unsined int32. CAN fifo id 0..1
 */
uint16_t can_fifo_get_timestamp(uint32_t canport, uint8_t fifo)
{
	return (CAN_RDTxR(canport, fifo) & CAN_RDTxR_TIME) >>
			CAN_RDTxR_TIME_SHIFT;
}

/*----------------------------------------------------------------------------*/
/** @brief CAN Receive Message
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] fifo Unsigned int8. FIFO id.
 * @param[in] release bool. Release the FIFO automatically
 * @param[in] mobid Unsigned int32. Message object identifier
 * @param[out] fmi Unsigned int32 pointer. ID of the matched filter.
 * @param[out] data Unsigned int8[]. Message payload data.
 * @param[out] length Unsigned int8 pointer. Length of message payload.
 */
void can_receive(uint32_t canport, uint8_t fifo, bool release, uint32_t *mobid,
		 uint32_t *fmi, uint8_t *data, uint8_t *length)
{
	*mobid = can_fifo_get_mobid(canport, fifo);
	*fmi = can_fifo_get_filter_id(canport, fifo);
	can_fifo_read_data(canport, fifo, data, length);

	if (release) {
		can_fifo_release(canport, fifo);
	}
}

/**@}*/ /* end of can_fifo_api group */

/******************************************************************************/
/** @defgroup can_filter_api CAN Filter manipulation
 * @ingroup can_file
 *
 * @note There can be specified in the parameter canport only CAN1 value. CAN2
 * is slave and has no filters available. The index of first acceptance filter
 * of the CAN2 device must be set by call to can_filter_set_slave_start.
 *
 * @note On STM32F4, the filter setup must be done in the CAN initialization
 * mode. On STM32F1, from the examples seems, that this isn't needed.
 *
 * Usage:
 *
 * @code
 * can_filter_init_enter(CAN1);
 * can_filter_set_list32(CAN1, 1, 0, MOB_SYNC, MCOB_TIME);
 * can_filter_set_list16(CAN1, 2, 0, MOB_TPDO0, MOB_TPDO1, MOB_TPDO2, MOB_TPDO3);
 * can_filter_disable(CAN1, 3);
 * can_filter_set_mask32(CAN1, 4, 1, CAN_ADDR_ALL, CAN_ADDR_ALL);
 * can_filter_init_leave(CAN1);
 * @endcode
 *
 *@{*/

 /*----------------------------------------------------------------------------*/
/** @brief CAN Filter Set slave index
 *
 * Initialize first filter index for the slave peripheral.
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] nr Unsigned int32. ID number of the first filter of slave block.
 */
void can_filter_set_slave_start(uint32_t canport, uint32_t nr)
{
	CAN_FMR(canport) = (CAN_FMR(canport) & ~CAN_FMR_CAN2SB) |
			   (nr << CAN_FMR_CAN2SB_SHIFT);
}

/*----------------------------------------------------------------------------*/
/** @brief Enter filter initialization mode
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 */
void can_filter_init_enter(uint32_t canport)
{
	CAN_FMR(canport) |= CAN_FMR_FINIT;
}

/*----------------------------------------------------------------------------*/
/** @brief Leave the filter initialization mode
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 */
void can_filter_init_leave(uint32_t canport)
{
	CAN_FMR(canport) &= ~CAN_FMR_FINIT;
}

/*----------------------------------------------------------------------------*/
/** @brief Enable the filter
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] nr Unsined int32. CAN filter id 0..28
 */
void can_filter_enable(uint32_t canport, uint32_t nr)
{
	CAN_FA1R(canport) |= (1 << nr);
}

/*----------------------------------------------------------------------------*/
/** @brief Disable the filter
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] nr Unsined int32. CAN filter id 0..28
 */
void can_filter_disable(uint32_t canport, uint32_t nr)
{
	CAN_FA1R(canport) &= ~(1 << nr);
}

/** @cond private */

static inline
void can_filter_set(const uint32_t canport, const uint32_t nr,
	const uint8_t fifo, const bool mask, const bool b32,
	const uint32_t fir1, uint32_t fir2)
{
	uint32_t bit = (1 << nr);

	CAN_FA1R(canport) &= ~bit;	/* Deactivate the filter. */
	if (b32) {
		CAN_FS1R(canport) |= bit;	/* 32-bit */
	} else {
		CAN_FS1R(canport) &= ~bit;	/* 16-bit */
	}

	if (mask) {
		CAN_FM1R(canport) &= ~bit;	/* ID mask mode. */
	} else {
		CAN_FM1R(canport) |= bit;	/* ID list mode. */
	}

	CAN_FiR1(canport, nr) = fir1;
	CAN_FiR2(canport, nr) = fir2;

	/* Select FIFO0 or FIFO1 as filter assignement. */
	if (fifo) {
		CAN_FFA1R(canport) |= bit;  /* FIFO1 */
	} else {
		CAN_FFA1R(canport) &= ~bit; /* FIFO0 */
	}

	CAN_FA1R(canport) |= bit;	/* Activate filter. */
}

#define __CANFILT32(addr)			\
	((addr) & 0xFFFFFFFE)

#define __CANFILT16(addr)			\
	((CAN_ID_GETSTD(addr) << 6) |		\
	 (CAN_ID_GETEXT(addr) >> 15) |		\
	 (CAN_ID_ISEXT(addr) ? 0x08 : 0) |	\
	 (CAN_ID_ISREMOTE(addr) ? 0x10 : 0))

/** @endcond private */

/*----------------------------------------------------------------------------*/
/** @brief
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] nr Unsined int32. CAN filter id 0..28
 */
void can_filter_set_list32(uint32_t canport, uint32_t nr, uint8_t fifo,
	uint32_t mobid1, uint32_t mobid2)
{
	can_filter_set(canport, nr, fifo, false, true,
			__CANFILT32(mobid1),
			__CANFILT32(mobid2));
}

/*----------------------------------------------------------------------------*/
/** @brief
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] nr Unsined int32. CAN filter id 0..28
 */
void can_filter_set_list16(uint32_t canport, uint32_t nr, uint8_t fifo,
	uint32_t mobid1, uint32_t mobid2, uint32_t mobid3, uint32_t mobid4)
{
	can_filter_set(canport, nr, fifo, false, false,
			__CANFILT16(mobid1) | (__CANFILT16(mobid2) << 16),
			__CANFILT16(mobid3) | (__CANFILT16(mobid4) << 16));
}

/*----------------------------------------------------------------------------*/
/** @brief
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] nr Unsined int32. CAN filter id 0..28
 */
void can_filter_set_mask32(uint32_t canport, uint32_t nr, uint8_t fifo,
	uint32_t mobid, uint32_t mask)
{
	can_filter_set(canport, nr, fifo, true, true,
			__CANFILT32(mobid),
			__CANFILT32(mask));
}

/*----------------------------------------------------------------------------*/
/** @brief
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] nr Unsined int32. CAN filter id 0..28
 */
void can_filter_set_mask16(uint32_t canport, uint32_t nr, uint8_t fifo,
	uint32_t mobid1, uint32_t mask1, uint32_t mobid2, uint32_t mask2)
{
	can_filter_set(canport, nr, fifo, true, false,
			__CANFILT16(mobid1) | (__CANFILT16(mask1) << 16),
			__CANFILT16(mobid2) | (__CANFILT16(mask2) << 16));
}


/* FUNCTIONS BELOW INSIDE DOXYGEN BLOCK WILL BE DEPRECATED !!!
   KEEP ONLY FOR COMPATIBILITY WITH OLD SW*/

/*----------------------------------------------------------------------------*/
/** @brief CAN Filter Init
 *
 * Initialize incoming message filter and assign to FIFO.
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] nr Unsigned int32. ID number of the filter.
 * @param[in] scale_32bit bool. 32-bit scale for the filter?
 * @param[in] id_list_mode bool. ID list filter mode?
 * @param[in] fr1 Unsigned int32. First filter register content.
 * @param[in] fr2 Unsigned int32. Second filter register content.
 * @param[in] fifo Unsigned int32. FIFO id.
 * @param[in] enable bool. Enable filter?
 */
void can_filter_init(uint32_t canport, uint32_t nr, bool scale_32bit,
		     bool id_list_mode, uint32_t fr1, uint32_t fr2,
		     uint32_t fifo, bool enable)
{
	/* Request initialization "enter". */
	can_filter_init_enter(canport);

	can_filter_set(canport, nr, fifo, !id_list_mode, scale_32bit, fr1, fr2);

	if (!enable) {
		can_filter_disable(canport, nr);
	}

	can_filter_init_leave(canport);
}

/*----------------------------------------------------------------------------*/
/** @brief CAN Initialize a 16bit Message ID Mask Filter
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] nr Unsigned int32. ID number of the filter.
 * @param[in] id1 Unsigned int16. First message ID to filter.
 * @param[in] mask1 Unsigned int16. First message ID bit mask.
 * @param[in] id2 Unsigned int16. Second message ID to filter.
 * @param[in] mask2 Unsigned int16. Second message ID bit mask.
 * @param[in] fifo Unsigned int32. FIFO id.
 * @param[in] enable bool. Enable filter?
 */
void can_filter_id_mask_16bit_init(uint32_t canport, uint32_t nr, uint16_t id1,
				   uint16_t mask1, uint16_t id2,
				   uint16_t mask2, uint32_t fifo, bool enable)
{
	can_filter_init(canport, nr, false, false,
			((uint32_t)id1 << 16) | (uint32_t)mask1,
			((uint32_t)id2 << 16) | (uint32_t)mask2, fifo, enable);
}

/*----------------------------------------------------------------------------*/
/** @brief CAN Initialize a 32bit Message ID Mask Filter
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] nr Unsigned int32. ID number of the filter.
 * @param[in] id Unsigned int32. Message ID to filter.
 * @param[in] mask Unsigned int32. Message ID bit mask.
 * @param[in] fifo Unsigned int32. FIFO id.
 * @param[in] enable bool. Enable filter?
 */
void can_filter_id_mask_32bit_init(uint32_t canport, uint32_t nr, uint32_t id,
				   uint32_t mask, uint32_t fifo, bool enable)
{
	can_filter_init(canport, nr, true, false, id, mask, fifo, enable);
}

/*----------------------------------------------------------------------------*/
/** @brief CAN Initialize a 16bit Message ID List Filter
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] nr Unsigned int32. ID number of the filter.
 * @param[in] id1 Unsigned int16. First message ID to match.
 * @param[in] id2 Unsigned int16. Second message ID to match.
 * @param[in] id3 Unsigned int16. Third message ID to match.
 * @param[in] id4 Unsigned int16. Fourth message ID to match.
 * @param[in] fifo Unsigned int32. FIFO id.
 * @param[in] enable bool. Enable filter?
 */
void can_filter_id_list_16bit_init(uint32_t canport, uint32_t nr,
				   uint16_t id1, uint16_t id2,
				   uint16_t id3, uint16_t id4,
				   uint32_t fifo, bool enable)
{
	can_filter_init(canport, nr, false, true,
			((uint32_t)id1 << 16) | (uint32_t)id2,
			((uint32_t)id3 << 16) | (uint32_t)id4, fifo, enable);
}

/*----------------------------------------------------------------------------*/
/** @brief CAN Initialize a 32bit Message ID List Filter
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] nr Unsigned int32. ID number of the filter.
 * @param[in] id1 Unsigned int32. First message ID to match.
 * @param[in] id2 Unsigned int32. Second message ID to match.
 * @param[in] fifo Unsigned int32. FIFO id.
 * @param[in] enable bool. Enable filter?
 */
void can_filter_id_list_32bit_init(uint32_t canport, uint32_t nr,
				   uint32_t id1, uint32_t id2,
				   uint32_t fifo, bool enable)
{
	can_filter_init(canport, nr, true, true, id1, id2, fifo, enable);
}

/**@}*/ /* end of can_filter_api group */

/******************************************************************************/
/** @defgroup can_timing_api CAN Timing manipulation
 * @ingroup can_file
 *
 * @section CAN Timing API
 * The timing of the CAN bus is adaptive to meet different requirements of
 * different applications of CAN bus. This API is constructed to ease
 * configuration of the bus, and to provide some standard configurations
 * of the bus.
 *
 * All of timing are specified in the number of Time Quanta's (TQ). This is the
 * master clock of the CAN controller.
 *
 * Clock reconstruction (X means sampling point)
 *
 * @code
 * |<------- prolonged bit time -------->|
 * +-----+--------------+-----X----------+
 * | SYN |    PHASE1    | SJW X  PHASE2  | <-- slower clock on the bus
 * +-----+--------------+-----X----------+
 *
 * |<----- nominal bit time ------>|
 * +-----+--------------X----------+
 * | SYN |    PHASE1    X  PHASE2  |       <-- normal clock on the bus
 * +-----+--------------X----------+
 *
 *                           | SJW |
 * +-----+--------------X----+-----+
 * | SYN |    PHASE1    X P2 |   <-- faster clock on the bus (P2 = PHASE2 - SJW)
 * +-----+--------------X----+
 * |<- shortened bit time -->|
 * @endcode
 *
 * At the SYN (length is always 1 TQ) is detected edge on the bus.

 * The PHASE1 time is stabilization phase, the bus input is ignored. In the
 * configuration, it represents the time propagation of the signal via the bus,
 * including any delays in optocouplers and CAN drivers.
 *
 * After PHASE1, the sampling of value of the bus is started, and the
 * arbitration can occur. The edge detection of the next bit is started too.
 *
 * At the nominal clock rate, the edge comes exactly after PHASE2 time. But the
 * edge can come sooner (the PHASE2 will be shortened) or later (the PHASE1 will
 * be prolonged and sample point delayed) for a maximm SJW time quanta's. This
 * defines need, that PHASE2 must be always greater than SJW.
 *
 * The longest possible SJW will make the bus more tolerant to clock skew
 * between devices, but may need to move sample point nearer the center of the
 * bit.
 *
 * The sample positon defines immunity to the propagation delays of cabling and
 * reflections on the cable, but moving sample point near the end will make the
 * bus less tolerant to clock skew. In industrial applications, the sample point
 * is near 75% of the bit time (SP = 0.75)
 *
 *  @f[ SP= \frac{SYN + PHASE_1}{SYN + PHASE_1 + PHASE_2} @f]
 *
 * The final baud rate of the CAN bus is defined by the nominal bit time as the
 * sum of all time quantas in each bit
 *
 *  @f[ f_{CAN} = \frac{f_{TQ}}{SYN + PHASE_1 + PHASE_2} @f]
 *
 * The final tolerance to clock skew is defined by the maximum resynchronization
 * jump width (SJW) respective to the total bit time (SYN + PHASE1 + PHASE2).
 * Due to two ends of the bus, the final tolerance of single endpoint must be
 * divided by two. The Resynchronization edge is there each 6th bit due to bit
 * stuffing, therefore resulting skew must be 6x less.
 *
 * @f[
 * \Delta f_{CAN} = \frac{1}{2} \frac{1}{6} \frac{SJW}{SYN + PHASE_1 + PHASE_2}
 * @f]
 *
 * For the some standard settings, the clocks between nodes can vary between 1%
 * and 2% of the nominal bit time.
 *
 * @warning Be warned that enabling "spread spectrum" feature on the target host
 * clock management unit will raise the oscillator clock skew appropriatedly,
 * and the CAN bus settings must be adapted to work correctly.
 *
 *@{*/

/*----------------------------------------------------------------------------*/
/** @brief Initialize timing structure
 *
 * Compute the values in the timing structure to match the desired communication
 * speed and sample point.
 *
 * Sample point is a fraction of 8-bit value. Ie. 255 is 100% 128 is 50% ...
 *
 * @param[inout] timing struct can_timing* The timing structure
 * @param[in] freq uint32_t Desired communication speed in bps @ref can_freq
 * @param[in] sample uint32_t Desired position of sampling @ref can_samplepoint
 * @returns true, if finding succesfull.
 */
bool can_timing_init(struct can_timing *timing, uint32_t freq, uint32_t sample)
{
	uint32_t quantas = rcc_ppre1_frequency / freq;

	/* TODO this is for fixed 75 % - make initial value a computed ! */

	timing->ts1 = 14;
	timing->ts2 = 5;

	uint32_t tqs = (1 + timing->ts1 + timing->ts2);

	while (quantas % tqs) {
		/* this timing combination will not generate correct TQ
		 * Try new, shorter combination */
		if (tqs * sample > (timing->ts1 + 1) * 0x100) {
			timing->ts2--;
		} else {
			timing->ts1--;
		}

		if ((timing->ts1 == 0) || (timing->ts2 == 0)) {
			/* Well no combination can be found ! Make it invalid */
			timing->ts1 = 0;
			timing->ts2 = 0;
			timing->brp = 0;
			timing->sjw = 0;
			return false;
		}

		tqs = (1 + timing->ts1 + timing->ts2);
	}
	timing->brp = quantas / tqs;
	timing->sjw = (timing->ts2 > 4) ? 4 : timing->ts2;

	return true;
}

/*----------------------------------------------------------------------------*/
/** @brief Set the timing to the CAN core
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] timing struct can_timing* The timing structure to set
 */
void can_timing_set(uint32_t canport, struct can_timing *timing)
{
	CAN_BTR(canport) = (CAN_BTR(canport) &
		~(CAN_BTR_SJW | CAN_BTR_TS2 | CAN_BTR_TS1 | CAN_BTR_BRP)) |
		(CAN_BTR_SJW_VAL(timing->sjw) & CAN_BTR_SJW) |
		(CAN_BTR_TS2_VAL(timing->ts2) & CAN_BTR_TS2) |
		(CAN_BTR_TS1_VAL(timing->ts1) & CAN_BTR_TS1) |
		(CAN_BTR_BRP_VAL(timing->brp) & CAN_BTR_BRP);
}

/*----------------------------------------------------------------------------*/
/** @brief Compute the frequency that is defined in the timing.
 *
 * @param[in] timing struct can_timing* The timing structure to get info about.
 * @returns uint32_t Frequency of the CAN bus in Hz.
 */
uint32_t can_timing_getfreq(struct can_timing *timing)
{
	uint32_t N = 1 + timing->ts1 + timing->ts2;
	return rcc_ppre1_frequency / (N * timing->brp);
}

/**@}*/ /* can_timing_api doxygen group */

/******************************************************************************/
/** @defgroup can_addr_api CAN Address manipulation
 * @ingroup can_file
 *
 * According to the standard CAN 2.0, there is two addressing schemes available.
 *
 * The CAN2.0A (or older CAN1.0) is using standard 11-bit message object
 * identifier (MOB-ID) The CAN2.0B is using extended 29-bit identifier for
 * the message.
 *
 * The higher-level protocols, such as CanOpen, DeviceNet ..., defines the
 * compatibility between CAN2.0A and CAN2.0B using highest 11 bits of the
 * extended identifier in same way as standard MOB-ID, and rest 18 bits is
 * using as extension to this standard MOB. The MOB-ID can be therefore printed
 * as (0x7FF) for CAN2.0A frame, and (7FF.3FFFF) for CAN2.0B frame.
 *
 * @code
 *  31       20                   2     0
 *  +--------+--------------------+-----+
 *  | STD-ID |       EXT-ID       | 100 |  <- the extended Message ID
 *  +--------+--------------------+-----+
 *  | STD-ID | 000000000000000000 | 000 |  <- the standard Message ID
 *  +--------+--------------------+-----+
 * @endcode
 *
 * For this situation to describe, the can_addr structure has the 11-bit
 * standard object identifier in the cobid value and the 18bit extension of the
 * identifier is stripped out to the extid param.
 *
 * There is also defined conversion functions to convert between can_addr
 * structure and left-aligned 32-bit unsigned integer representation of the
 * Message Object ID
 *
 *@{*/


/*----------------------------------------------------------------------------*/
/** @brief CAN Address Compare
 *
 * @param[in] mobid1 uint32_t First MOB-ID to compare
 * @param[in] mobid2 uint32_t Second MOB-ID to compare
 * @return bool true, if both MOB-IDs are same
 */
bool can_mobid_compare(uint32_t mobid1, uint32_t mobid2)
{
	uint32_t diff = mobid1 ^ mobid2;

	if (!CAN_ID_ISEXT(mobid2)) {
		diff &= ~CAN_MOBID_EXT;	/* Ignore ext field on STD ID */
	}
	return !diff;
}

/*----------------------------------------------------------------------------*/
/** @brief CAN Address Compare Masked
 *
 * @param[in] mobid1 uint32_t First MOB-ID to compare
 * @param[in] mobid2 uint32_t Second MOB-ID value compare
 * @param[in] mask2 uint32_t Second MOB-ID mask compare
 * @return bool true, if addr1 is inside group addr2
 */
bool can_mobid_compare_masked(uint32_t mobid1, uint32_t mobid2, uint32_t mask2)
{
	uint32_t diff = mobid1 ^ mobid2;

	if (!CAN_ID_ISEXT(mobid2)) {
		diff &= ~CAN_MOBID_EXT;	/* Ignore ext field on STD ID */
	}
	return !(diff & mask2);
}

/*----------------------------------------------------------------------------*/
/** @brief CAN Address Compare COB-ID
 *
 * This comparsion compares only the COB-ID value of both adresses. It is useful
 * for mangling with higher protocols, that treats higher 11 bits of extended
 * COB-ID same way as it was standard ID.
 *
 * @param[in] mobid1 uint32_t First MOB-ID to compare
 * @param[in] mobid2 uint32_t Second MOB-ID to compare
 * @return bool true, if addresses are same
 */
bool can_mobid_compare_stdid(uint32_t mobid1, uint32_t mobid2)
{
	return !((mobid1 ^ mobid2) & CAN_MOBID_STD);
}

/*----------------------------------------------------------------------------*/
/** @brief CAN Address Compare COB-ID Masked
 *
 * This comparsion compares only the COB-ID value of both adresses. It is useful
 * for mangling with higher protocols, that treats higher 11 bits of extended
 * COB-ID same way as it was standard ID.
 *
 * @param[in] mobid1 uint32_t First MOB-ID to compare
 * @param[in] mobid2 uint32_t Second MOB-ID value compare
 * @param[in] mask2 uint32_t Second MOB-ID mask compare
 * @return bool true, if addr1 is inside group addr2
 */
bool can_mobid_compare_stdid_masked(uint32_t mobid1, uint32_t mobid2,
				   uint32_t mask2)
{
	return !((mobid1 ^ mobid2) & (CAN_MOBID_STD & mask2));
}

/**@}*/ /* can_addr_api doxygen group */

/**@}*/
