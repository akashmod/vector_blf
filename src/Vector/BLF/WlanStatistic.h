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

#include <Vector/BLF/AbstractFile.h>
#include <Vector/BLF/ObjectHeader.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief WLAN_STATISTIC
 *
 * WLAN statistic.
 */
struct VECTOR_BLF_EXPORT WlanStatistic final : ObjectHeader {
    WlanStatistic();

    void read(AbstractFile & is) override;
    void write(AbstractFile & os) override;
    uint32_t calculateObjectSize() const override;

    /**
     * @brief application channel
     *
     * The channel of the frame.
     */
    uint16_t channel {};

    /** enumeration for flags */
    enum Flags : uint16_t {
        /** Valid Rx/Tx Counter */
        ValidRxTxCounter = 0x01,

        /** Valid Error Counter */
        ValidErrorCounter = 0x02
    };

    /** flags */
    uint16_t flags {};

    /**
     * Number of Rx packets since last statistic event.
     */
    uint32_t rxPacketCount {};

    /**
     * Number of Rx bytes since last statistic event.
     */
    uint32_t rxByteCount {};

    /**
     * Number of Tx packets since last statistic event.
     */
    uint32_t txPacketCount {};

    /**
     * Number of Tx bytes since last statistic event.
     */
    uint32_t txByteCount {};

    /**
     * Number of collisions since last statistic event.
     */
    uint32_t collisionCount {};

    /**
     * Number of errors since last statistic event.
     */
    uint32_t errorCount {};

    /** reserved */
    uint32_t reservedWlanStatistic {};
};

}
}
