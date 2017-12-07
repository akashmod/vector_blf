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

#include "A429Error.h"

namespace Vector {
namespace BLF {

A429Error::A429Error() :
    ObjectHeader(),
    channel(),
    errorType(),
    sourceIdentifier(),
    errReason(),
    errorText(),
    errorAttributes()
{
    objectType = ObjectType::A429_ERROR;
}

void A429Error::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&errorType), sizeof(errorType));
    is.read(reinterpret_cast<char *>(&sourceIdentifier), sizeof(sourceIdentifier));
    is.read(reinterpret_cast<char *>(&errReason), sizeof(errReason));
    is.read(reinterpret_cast<char *>(errorText.data()), static_cast<std::streamsize>(errorText.size()));
    is.read(reinterpret_cast<char *>(errorAttributes.data()), static_cast<std::streamsize>(errorAttributes.size()));
}

void A429Error::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&errorType), sizeof(errorType));
    os.write(reinterpret_cast<char *>(&sourceIdentifier), sizeof(sourceIdentifier));
    os.write(reinterpret_cast<char *>(&errReason), sizeof(errReason));
    os.write(reinterpret_cast<char *>(errorText.data()), static_cast<std::streamsize>(errorText.size()));
    os.write(reinterpret_cast<char *>(errorAttributes.data()), static_cast<std::streamsize>(errorAttributes.size()));
}

DWORD A429Error::calculateObjectSize() const
{
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(errorType) +
        sizeof(sourceIdentifier) +
        sizeof(errReason) +
        errorText.size() +
        errorAttributes.size();
}

}
}
