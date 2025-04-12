#pragma once

#include <cstdint>
#include "hex_stream.h"
#include "field.h"



// ----------------------------------------------------------------------------------------------
enum class MESSAGE_TYPE_ENUM : uint32_t {
    MBIM_OPEN_MSG = 1,
    MBIM_CLOSE_MSG,
    MBIM_COMMAND_MSG,
    MBIM_HOST_ERROR_MSG
};

inline const char* message_type_desc(MESSAGE_TYPE_ENUM type) {
    switch (type) {
        case MESSAGE_TYPE_ENUM::MBIM_OPEN_MSG:       return "Open message (establish link)";
        case MESSAGE_TYPE_ENUM::MBIM_CLOSE_MSG:      return "Close message (tear down)";
        case MESSAGE_TYPE_ENUM::MBIM_COMMAND_MSG:    return "Command from host";
        case MESSAGE_TYPE_ENUM::MBIM_HOST_ERROR_MSG: return "Host error notification";
        default: return "Unknown message type";
    }
}
// ----------------------------------------------------------------------------------------------

struct MBIM_MESSAGE_HEADER {
    Field<MESSAGE_TYPE_ENUM> MESSAGE_TYPE   { "MESSAGE_TYPE",   "Type of the message" };
    Field<uint32_t> MESSAGE_LENGTH          { "MESSAGE_LENGTH", "Total length of the message in bytes" };
    Field<uint32_t> TRANSACTION_ID          { "TRANSACTION_ID", "Message ID used to map queries to responses"};

    MBIM_MESSAGE_HEADER(hexStream& hs);
};

struct MBIM_FRAGMENT_HEADER {
    Field<uint32_t> TOTAL_FRAGMENTS         { "TOTAL_FRAGMENTS", "Number of fragments this message is split into" };
    Field<uint32_t> CURRENT_FRAGMENT        { "CURRENT_FRAGMENT", "ID of the current fragment"};

    MBIM_FRAGMENT_HEADER(hexStream& hs);
};
