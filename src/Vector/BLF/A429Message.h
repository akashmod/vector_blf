/*
 * Copyright (C) 2013 Tobias Lorenz.
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

#include "platform.h"

#include <array>

#include "AbstractFile.h"
#include "ObjectHeader.h"
#include "VectorTypes.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief A429_MESSAGE
 *
 * A429 message object
 */
class VECTOR_BLF_EXPORT A429Message final : public ObjectHeader
{
public:
    A429Message();

    virtual void read(AbstractFile & is) override;
    virtual void write(AbstractFile & os) override;
    virtual DWORD calculateObjectSize() const override;

    /** data */
    std::array<BYTE, 4> a429Data;

    /** application channel */
    WORD channel;

    /** direction flag: 0=Rx, 1=Tx */
    BYTE dir;

    /** bitrate */
    ULONG bitrate;

    /** error reason */
    ULONG errReason;

    /** error position */
    USHORT errPosition;

    /** frame gap */
    ULONGLONG frameGap;

    /** frame length */
    ULONG frameLength;

    /** message control */
    WORD msgCtrl;

    /** cycle time */
    ULONG cycleTime;

    /** error */
    ULONG error;

    /** bit length of last bit */
    ULONG bitLenOfLastBit;
};

}
}
