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