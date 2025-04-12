#pragma once

#include <cstdint>
#include "hex_stream.h"
#include "field.h"

enum class MESSAGE_TYPE_ENUM : uint32_t {
    MBIM_OPEN_MSG = 1,
    MBIM_CLOSE_MSG,
    MBIM_COMMAND_MSG,
    MBIM_HOST_ERROR_MSG
};

struct MBIM_MESSAGE_HEADER {
    Field<MESSAGE_TYPE_ENUM> MESSAGE_TYPE   { "MESSAGE_TYPE",   "Type of the message" };
    Field<uint32_t> MESSAGE_LENGTH          { "MESSAGE_LENGTH", "Total length of the message in bytes." };
    Field<uint32_t> TRANSACTION_ID          { "TRANSACTION_ID", "Message ID used to map queries to responses."};

    MBIM_MESSAGE_HEADER(hexStream& hs);
};