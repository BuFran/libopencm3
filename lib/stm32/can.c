/** @defgroup can_file CAN
 *
 * @ingroup STM32F_files
 *
 * @brief <b>libopencm3 STM32Fxxx CAN</b>
 *
 * @version 1.0.0
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
void can_mode_set_silent(uint32_t canport, bool enable)
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
void can_mode_set_loopback(uint32_t canport, bool enable)
{
	if (enable) {
		CAN_BTR(canport) |= CAN_BTR_LBKM;
	} else {
		CAN_BTR(canport) &= ~CAN_BTR_LBKM;
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
	can_mode_set_silent(canport, silent);
	can_mode_set_loopback(canport, loopback);

	/* Set bit timings. */
	CAN_BTR(canport) |= sjw | ts2 | ts1 |
		(CAN_BTR_BRP_VAL(brp) & CAN_BTR_BRP);

	return can_leave_init_mode_blocking(canport) ? 0 : 1;
}



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
	uint32_t filter_select_bit = 0x00000001 << nr;

	/* Request initialization "enter". */
	CAN_FMR(canport) |= CAN_FMR_FINIT;

	/* Deactivate the filter. */
	CAN_FA1R(canport) &= ~filter_select_bit;

	if (scale_32bit) {
		/* Set 32-bit scale for the filter. */
		CAN_FS1R(canport) |= filter_select_bit;
	} else {
		/* Set 16-bit scale for the filter. */
		CAN_FS1R(canport) &= ~filter_select_bit;
	}

	if (id_list_mode) {
		/* Set filter mode to ID list mode. */
		CAN_FM1R(canport) |= filter_select_bit;
	} else {
		/* Set filter mode to id/mask mode. */
		CAN_FM1R(canport) &= ~filter_select_bit;
	}

	/* Set the first filter register. */
	CAN_FiR1(canport, nr) = fr1;

	/* Set the second filter register. */
	CAN_FiR2(canport, nr) = fr2;

	/* Select FIFO0 or FIFO1 as filter assignement. */
	if (fifo) {
		CAN_FFA1R(canport) |= filter_select_bit;  /* FIFO1 */
	} else {
		CAN_FFA1R(canport) &= ~filter_select_bit; /* FIFO0 */
	}

	if (enable) {
		CAN_FA1R(canport) |= filter_select_bit; /* Activate filter. */
	}

	/* Request initialization "leave". */
	CAN_FMR(canport) &= ~CAN_FMR_FINIT;
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

/*----------------------------------------------------------------------------*/
/** @brief CAN Enable IRQ
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] irq Unsigned int32. IRQ bit(s).
 */
void can_enable_irq(uint32_t canport, uint32_t irq)
{
	CAN_IER(canport) |= irq;
}

/*----------------------------------------------------------------------------*/
/** @brief CAN Disable IRQ
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] irq Unsigned int32. IRQ bit(s).
 */
void can_disable_irq(uint32_t canport, uint32_t irq)
{
	CAN_IER(canport) &= ~irq;
}

/*----------------------------------------------------------------------------*/
/** @brief CAN Transmit Message
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] id Unsigned int32. Message ID.
 * @param[in] ext bool. Extended message ID?
 * @param[in] rtr bool. Request transmit?
 * @param[in] length Unsigned int8. Message payload length.
 * @param[in] data Unsigned int8[]. Message payload data.
 * @returns int 0, 1 or 2 on success and depending on which outgoing mailbox got
 * selected. -1 if no mailbox was available and no transmission got queued.
 */
int can_transmit(uint32_t canport, uint32_t id, bool ext, bool rtr,
		 uint8_t length, uint8_t *data)
{
	int ret = 0;
	uint32_t mailbox = 0;
	union {
		uint8_t data8[4];
		uint32_t data32;
	} tdlxr, tdhxr;

	/* Check which transmit mailbox is empty if any. */
	ret = can_get_empty_mailbox(canport);

	/* If we have no empty mailbox return with an error. */
	if (ret == -1) {
		return ret;
	}

	mailbox = CAN_MBOX(ret);

	if (ext) {
		/* Set extended ID. */
		CAN_TIxR(canport, mailbox) = CAN_TIxR_EXID_VAL(id) |
			CAN_TIxR_IDE;
	} else {
		/* Set standard ID. */
		CAN_TIxR(canport, mailbox) = CAN_TIxR_STID_VAL(id);
	}

	/* Set/clear remote transmission request bit. */
	if (rtr) {
		CAN_TIxR(canport, mailbox) |= CAN_TIxR_RTR; /* Set */
	}

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

	/* Request transmission. */
	CAN_TIxR(canport, mailbox) |= CAN_TIxR_TXRQ;

	return ret;
}

/*---------------------------------------------------------------------------*/
/** @brief CAN Release FIFO
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] fifo Unsigned int8. FIFO id.
 */
void can_fifo_release(uint32_t canport, uint8_t fifo)
{
	CAN_RFxR(canport, fifo) |= CAN_RF1R_RFOM1;
}

/*----------------------------------------------------------------------------*/
/** @brief CAN Receive Message
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @param[in] fifo Unsigned int8. FIFO id.
 * @param[in] release bool. Release the FIFO automatically after coping data
 * out.
 * @param[out] id Unsigned int32 pointer. Message ID.
 * @param[out] ext bool pointer. The message ID is extended?
 * @param[out] rtr bool pointer. Request of transmission?
 * @param[out] fmi Unsigned int32 pointer. ID of the matched filter.
 * @param[out] length Unsigned int8 pointer. Length of message payload.
 * @param[out] data Unsigned int8[]. Message payload data.
 */
void can_receive(uint32_t canport, uint8_t fifo, bool release, uint32_t *id,
		 bool *ext, bool *rtr, uint32_t *fmi, uint8_t *length,
		 uint8_t *data)
{
	uint32_t fifo_id = 0;
	union {
		uint8_t data8[4];
		uint32_t data32;
	} rdlxr, rdhxr;

	fifo_id = CAN_FIFO(fifo);

	/* Get type of CAN ID and CAN ID. */
	if (CAN_RIxR(canport, fifo_id) & CAN_RIxR_IDE) {
		*ext = true;
		/* Get extended CAN ID. */
		*id = (CAN_RIxR(canport, fifo_id) & CAN_RIxR_EXID) >>
			CAN_RIxR_EXID_SHIFT;
	} else {
		*ext = false;
		/* Get standard CAN ID. */
		*id = (CAN_RIxR(canport, fifo_id) & CAN_RIxR_STID) >>
			CAN_RIxR_STID_SHIFT;
	}

	/* Get remote transmit flag. */
	if (CAN_RIxR(canport, fifo_id) & CAN_RIxR_RTR) {
		*rtr = true;
	} else {
		*rtr = false;
	}

	/* Get filter match ID. */
	*fmi = (CAN_RDTxR(canport, fifo_id) & CAN_RDTxR_FMI) >>
		CAN_RDTxR_FMI_SHIFT;

	/* Get data length. */
	*length = CAN_RDTxR(canport, fifo_id) & CAN_RDTxR_DLC_MASK;
	/* accelerate reception by copying the CAN data from the controller
	 * memory to the fast internal RAM
	 */

	rdlxr.data32 = CAN_RDLxR(canport, fifo_id);
	rdhxr.data32 = CAN_RDHxR(canport, fifo_id);
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

	/* Release the FIFO. */
	if (release) {
		can_fifo_release(canport, fifo);
	}
}

/*----------------------------------------------------------------------------*/
/** @brief Test, if there is any free transmit mailbox
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @returns  true, if there is any free transmit mailbox.
 */
bool can_available_mailbox(uint32_t canport)
{
	return CAN_TSR(canport) & (CAN_TSR_TME0 | CAN_TSR_TME1 | CAN_TSR_TME2);
}

/*----------------------------------------------------------------------------*/
/** @brief Get index of the empty transmit mailbox
 *
 * @param[in] canport Unsigned int32. CAN block register base @ref can_reg_base.
 * @returns int32_t 0..2: The index of the empty transmit mailbox.
 *		   -1 if there is no empty transmit mailbox
 */
int32_t can_get_empty_mailbox(uint32_t canport)
{
	int32_t i = 0;
	for (i = 0; i < 3; i++) {
		if ((CAN_TSR(canport) & CAN_TSR_TME(i)) != 0) {
			return i;
		}
	}
	/* no free mailbox found */
	return -1;
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
 * \param[in] timing struct can_timing* The timing structure to set
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

/**@}*/
