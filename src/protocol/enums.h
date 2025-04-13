#pragma once

#include <cstdint>

enum class MESSAGE_TYPE_ENUM : uint32_t {
    MBIM_OPEN_MSG = 1,
    MBIM_CLOSE_MSG,
    MBIM_COMMAND_MSG,
    MBIM_HOST_ERROR_MSG
};

enum class MESSAGE_QUERY_OR_SET_ENUM : uint32_t {
    QUERY,
    SET 
};

enum class MBIM_PROTOCOL_ERROR_CODES_ENUM : uint32_t {
    MBIM_ERROR_TIMEOUT_FRAGMENT = 1,
    MBIM_ERROR_FRAGMENT_OUT_OF_SEQUENCE,
    MBIM_ERROR_LENGTH_MISMATCH,
    MBIM_ERROR_DUPLICATED_TID,
    MBIM_ERROR_NOT_OPENED,
    MBIM_ERROR_UNKNOW,
    MBIM_ERROR_CANCEL,
    MBIM_ERROR_MAX_TRANSFER
};