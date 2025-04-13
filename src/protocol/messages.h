#pragma once

#include <cstdint>
#include <unordered_map>

#include "../core/hex_stream.h"
#include "../core/field.h"
#include "../core/serializable.h"

#include "enums.h"
#include "maps.h"


struct MBIM_MESSAGE_HEADER : public Serializable {
    Field<MESSAGE_TYPE_ENUM> MESSAGE_TYPE   { "MESSAGE_TYPE",   "Type of the message" };
    Field<uint32_t> MESSAGE_LENGTH          { "MESSAGE_LENGTH", "Total length of the message in bytes" };
    Field<uint32_t> TRANSACTION_ID          { "TRANSACTION_ID", "Message ID used to map queries to responses"};

    MBIM_MESSAGE_HEADER(hexStream& hs);
};

struct MBIM_FRAGMENT_HEADER : public Serializable {
    Field<uint32_t> TOTAL_FRAGMENTS         { "TOTAL_FRAGMENTS", "Number of fragments this message is split into" };
    Field<uint32_t> CURRENT_FRAGMENT        { "CURRENT_FRAGMENT", "ID of the current fragment"};

    MBIM_FRAGMENT_HEADER(hexStream& hs);
};

struct MBIM_OPEN_MSG : public Serializable {
    MBIM_MESSAGE_HEADER MESSAGE_HEADER;
    Field<uint32_t> MAX_CONTROL_TRANSFER        { "MAX_CONTROL_TRANSFER", "Maximum size of a control transfer"};

    MBIM_OPEN_MSG(hexStream& hs);
};

struct MBIM_CLOSE_MSG : public Serializable {
    MBIM_MESSAGE_HEADER MESSAGE_HEADER;
    MBIM_CLOSE_MSG(hexStream& hs);
};

struct MBIM_COMMAND_MSG : public Serializable {
    MBIM_MESSAGE_HEADER MESSAGE_HEADER;
    MBIM_FRAGMENT_HEADER FRAGMENT_HEADER;

    Field<std::string> DEVICE_SERVICE_ID              { "DEVICE_SERVICE_ID", "Identifies the device service the following CID applies to."};
    Field<uint32_t> CID                               { "CID", "Command ID"};
    Field<MESSAGE_QUERY_OR_SET_ENUM> COMMAND_TYPE     { "COMMAND_TYPE", "Whether to query or set"};
    Field<uint32_t> INFORMATION_BUFFER_LENGTH         { "INFORMATION_BUFFER_LENGTH", "Length in bytes of the following information buffer"};
    Field<std::string> INFORMATION_BUFFER             { "INFORMATION_BUFFER", "Contains command related data"};

    MBIM_COMMAND_MSG(hexStream& hs);
};

struct MBIM_HOST_ERROR_MSG : public Serializable {
    MBIM_MESSAGE_HEADER MESSAGE_HEADER;
    Field<MBIM_PROTOCOL_ERROR_CODES_ENUM> ERROR_STATUS_CODE      { "ERROR_STATUS_CODE", "Status code of the error"};

    MBIM_HOST_ERROR_MSG(hexStream& hs);
};

struct MBIM_OPEN_DONE : public Serializable {
    MBIM_MESSAGE_HEADER MESSAGE_HEADER;
    Field<MBIM_STATUS_TO_HOST_ENUM> STATUS      { "STATUS", "Status of the open procedure"};

    MBIM_OPEN_DONE(hexStream& hs);
};

struct MBIM_CLOSE_DONE : public Serializable {
    MBIM_MESSAGE_HEADER MESSAGE_HEADER;
    Field<MBIM_STATUS_TO_HOST_ENUM> STATUS      { "STATUS", "Status of the open procedure"};

    MBIM_CLOSE_DONE(hexStream& hs);
};

struct MBIM_COMMAND_DONE : public Serializable {
    MBIM_MESSAGE_HEADER MESSAGE_HEADER;
    MBIM_FRAGMENT_HEADER FRAGMENT_HEADER;

    Field<std::string> DEVICE_SERVICE_ID              { "DEVICE_SERVICE_ID", "Identifies the device service the following CID applies to."};
    Field<uint32_t> CID                               { "CID", "Command ID"};
    Field<MBIM_STATUS_TO_HOST_ENUM> STATUS            { "STATUS", "Status of the command"};
    Field<uint32_t> INFORMATION_BUFFER_LENGTH         { "INFORMATION_BUFFER_LENGTH", "Length in bytes of the following information buffer"};
    Field<std::string> INFORMATION_BUFFER             { "INFORMATION_BUFFER", "Contains command related data"};

    MBIM_COMMAND_DONE(hexStream& hs);
};

struct MBIM_INDICATE_STATUS_MSG : public Serializable {
    MBIM_MESSAGE_HEADER MESSAGE_HEADER;
    MBIM_FRAGMENT_HEADER FRAGMENT_HEADER;

    Field<std::string> DEVICE_SERVICE_ID              { "DEVICE_SERVICE_ID", "Identifies the device service the following CID applies to."};
    Field<uint32_t> CID                               { "CID", "Command ID"};
    Field<uint32_t> INFORMATION_BUFFER_LENGTH         { "INFORMATION_BUFFER_LENGTH", "Length in bytes of the following information buffer"};
    Field<std::string> INFORMATION_BUFFER             { "INFORMATION_BUFFER", "Contains command related data"};

    MBIM_INDICATE_STATUS_MSG(hexStream& hs);
};