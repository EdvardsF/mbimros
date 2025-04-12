#include "parser.h"
#include "mbim_decoder.h"

MBIM_MESSAGE_HEADER::MBIM_MESSAGE_HEADER(hexStream& hs) {
    MESSAGE_TYPE.set(static_cast<MESSAGE_TYPE_ENUM>(hs.read4_le()));
    MESSAGE_LENGTH.set(hs.read4_le());
    TRANSACTION_ID.set(hs.read4_le());
}