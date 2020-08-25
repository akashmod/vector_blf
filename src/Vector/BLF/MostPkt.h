/*
 * Copyright (C) 2013-2020 Tobias Lorenz.
 * Contact: tobias.lorenz@gmx.net
 *
 * This file is part of Tobias Lorenz's Toolkit.
 *
 * Commercial License Usage
 * Licensees holding valid commercial licenses may use this file in
 * accordance with the commercial license agreement provided with the
 * Software or, alternatively, in accordance with the terms contained in
 * a written agreement between you and Tobias Lorenz.
 *
 * GNU General Public License 3.0 Usage
 * Alternatively, this file may be used under the terms of the GNU
 * General Public License version 3.0 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU General Public License version 3.0 requirements will be
 * met: http://www.gnu.org/copyleft/gpl.html.
 */

#pragma once

#include <Vector/BLF/platform.h>

#include <vector>

#include <Vector/BLF/AbstractFile.h>
#include <Vector/BLF/ObjectHeader.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief MOST_PKT
 *
 * This event structure was never and should never be used. Use MostPkt2
 * instead.
 */
struct VECTOR_BLF_EXPORT MostPkt final : ObjectHeader {
    MostPkt();

    void read(AbstractFile & is) override;
    void write(AbstractFile & os) override;
    uint32_t calculateObjectSize() const override;

    /**
     * @brief application channel
     *
     * Application channel
     */
    uint16_t channel {};

    /**
     * Direction of message events:
     *   - 0: Rx (received)
     *   - 1: Tx (transmit receipt)
     *   - 2: Tx Request (transmit request)
     */
    uint8_t dir {};

    /** reserved */
    uint8_t reservedMostPkt1 {};

    /**
     * Source address
     */
    uint32_t sourceAdr {};

    /**
     * Target address
     */
    uint32_t destAdr {};

    /**
     * Arbitration byte
     */
    uint8_t arbitration {};

    /**
     * Obsolete member; read/write 0
     */
    uint8_t timeRes {};

    /**
     * Number of quadlets
     */
    uint8_t quadsToFollow {};

    /** reserved */
    uint8_t reservedMostPkt2 {};

    /**
     * Cyclic Redundancy Check
     */
    uint16_t crc {};

    /**
     * Priority
     */
    uint8_t priority {};

    /**
     * @brief Tranfer type
     *
     * Message-like events can either be recorded through the MOST transceiver chip or through a
     * separate network spy.
     *   - 1: Node
     *     MOST transceiver reported the message (either due to a successful reception or
     *     as acknowledgment for a transmit request).
     *   - 2: Spy
     *     Message was reported by the network spy. The Spy sees all messages
     *     independently of the desti-nation address.
     */
    uint8_t transferType {};

    /**
     * Transmission state
     *   - 0 for Rx
     *   - 0x40 for TxOk (transmit request)
     */
    uint8_t state {};

    /** reserved */
    uint8_t reservedMostPkt3 {};

    /** reserved */
    uint16_t reservedMostPkt4 {};

    /**
     * @brief length of variable data in bytes
     *
     * Length of variable data in bytes (1014 max)
     */
    uint32_t pktDataLength {};

    /** reserved */
    uint32_t reservedMostPkt5 {};

    /**
     * @brief variable data
     *
     * Variable data
     */
    std::vector<uint8_t> pktData {};
};

}
}
