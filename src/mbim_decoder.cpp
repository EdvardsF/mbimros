#include "parser.h"
#include "mbim_decoder.h"

#include <iostream>

MBIM_MESSAGE_HEADER::MBIM_MESSAGE_HEADER(hexStream& hs) {
    MESSAGE_TYPE.bind(this);
    MESSAGE_TYPE.setFormatter(map_type);

    MESSAGE_LENGTH.bind(this);
    TRANSACTION_ID.bind(this);

    MESSAGE_TYPE.set(static_cast<MESSAGE_TYPE_ENUM>(hs.read4_le()));
    MESSAGE_LENGTH.set(hs.read4_le());
    TRANSACTION_ID.set(hs.read4_le());
}


MBIM_FRAGMENT_HEADER::MBIM_FRAGMENT_HEADER(hexStream& hs) {
    TOTAL_FRAGMENTS.bind(this);
    CURRENT_FRAGMENT.bind(this);
    TOTAL_FRAGMENTS.set(hs.read4_le());
    CURRENT_FRAGMENT.set(hs.read4_le());
}


MBIM_OPEN_MSG::MBIM_OPEN_MSG(hexStream& hs) : MESSAGE_HEADER(hs) {
    includeHeader(&MESSAGE_HEADER);
    MAX_CONTROL_TRANSFER.bind(this);
    MAX_CONTROL_TRANSFER.set(hs.read4_le());
}

MBIM_CLOSE_MSG::MBIM_CLOSE_MSG(hexStream& hs) : MESSAGE_HEADER(hs) {
    includeHeader(&MESSAGE_HEADER);
}