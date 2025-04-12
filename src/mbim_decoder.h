#pragma once


#include <cstdint>

#include "hex_stream.h"

enum class MESSAGE_TYPE_ENUM : uint32_t {
    MBIM_OPEN_MSG = 1,
    MBIM_CLOSE_MSG,
    MBIM_COMMAND_MSG,
    MBIM_HOST_ERROR_MSG
};

struct MBIM_MESSAGE_HEADER {
    MESSAGE_TYPE_ENUM MESSAGE_TYPE;
    uint32_t MESSAGE_LENGTH;
    uint32_t TRANSACTION_ID;

    MBIM_MESSAGE_HEADER(hexStream& hexStream);
};