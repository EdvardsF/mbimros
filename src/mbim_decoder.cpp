#include "parser.h"
#include "mbim_decoder.h"

MBIM_MESSAGE_HEADER::MBIM_MESSAGE_HEADER(hexStream& hs) {
    bindField(MESSAGE_TYPE);
    bindField(MESSAGE_LENGTH);
    bindField(TRANSACTION_ID);
    MESSAGE_TYPE.set(static_cast<MESSAGE_TYPE_ENUM>(hs.read4_le()));
    MESSAGE_LENGTH.set(hs.read4_le());
    TRANSACTION_ID.set(hs.read4_le());
}


MBIM_FRAGMENT_HEADER::MBIM_FRAGMENT_HEADER(hexStream& hs) {
    bindField(TOTAL_FRAGMENTS);
    bindField(CURRENT_FRAGMENT);
    TOTAL_FRAGMENTS.set(hs.read4_le());
    CURRENT_FRAGMENT.set(hs.read4_le());
}