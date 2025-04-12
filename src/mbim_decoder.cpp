#include "parser.h"
#include "mbim_decoder.h"

MBIM_MESSAGE_HEADER::MBIM_MESSAGE_HEADER(hexStream& hexStream) {
    MESSAGE_TYPE    = static_cast<MESSAGE_TYPE_ENUM>(hexStream.read4_le());
    MESSAGE_LENGTH  = hexStream.read4_le();
    TRANSACTION_ID  = hexStream.read4_le();
}
