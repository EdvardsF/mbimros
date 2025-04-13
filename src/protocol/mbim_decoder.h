#pragma once

#include <cstdint>
#include <unordered_map>
#include "../core/hex_stream.h"
#include "../core/field.h"
#include "../core/serializable.h"


// ENUMS AND THEIR MAPS

// ----------------------------------------------------------------------------------------------
enum class MESSAGE_TYPE_ENUM : uint32_t {
    MBIM_OPEN_MSG = 1,
    MBIM_CLOSE_MSG,
    MBIM_COMMAND_MSG,
    MBIM_HOST_ERROR_MSG
};

inline std::string map_type(MESSAGE_TYPE_ENUM type) {
    switch (type) {
        case MESSAGE_TYPE_ENUM::MBIM_OPEN_MSG:       return "Open a connection";
        case MESSAGE_TYPE_ENUM::MBIM_CLOSE_MSG:      return "Close the connection";
        case MESSAGE_TYPE_ENUM::MBIM_COMMAND_MSG:    return "Command from host";
        case MESSAGE_TYPE_ENUM::MBIM_HOST_ERROR_MSG: return "Host error notification";
        default: return "Unknown message type";
    }
}

enum class MESSAGE_QUERY_OR_SET_ENUM : uint32_t {
    QUERY,
    SET 
};

inline std::string map_query_or_set(MESSAGE_QUERY_OR_SET_ENUM query_or_set) {
    switch (query_or_set) {
        case MESSAGE_QUERY_OR_SET_ENUM::QUERY:       return "Ouery";
        case MESSAGE_QUERY_OR_SET_ENUM::SET:         return "Set";
        default: return "Unknown";
    }
}

inline std::string map_uuid(const std::string& uuid) {
    static const std::unordered_map<std::string, std::string> uuid_map = {
        { "a289cc33bcbb8b4fb6b0133ec2aae6df", "UUID_BASIC_CONNECT" },
        { "533fbeeb14fe44679f9033a223e56c3f", "UUID_SMS" },
        { "e550a0c85e82479e82f710abf4c3351f", "UUID_USSD" },
        { "4bf384761e6a41dbb1d8bed289c25bdb", "UUID_PHONEBOOK" },
        { "d8f20131fcb54e178602d6ed3816164c", "UUID_STK" },
        { "1d2b5ff70aa148b2aa5250f15767174e", "UUID_AUTH" },
        { "c08a26dd7718438284826e0d583c4d0e", "UUID_DSS" }
    };

    auto it = uuid_map.find(uuid);
    if (it != uuid_map.end())
        return it->second;
    return "Unknown UUID";
}

inline std::string map_basic_connect_cid(uint32_t cid) {
    static const std::unordered_map<uint32_t, std::string> cid_map = {
        { 1,  "MBIM_CID_DEVICE_CAPS" },
        { 2,  "MBIM_CID_SUBSCRIBER_READY_STATUS" },
        { 3,  "MBIM_CID_RADIO_STATE" },
        { 4,  "MBIM_CID_PIN" },
        { 5,  "MBIM_CID_PIN_LIST" },
        { 6,  "MBIM_CID_HOME_PROVIDER" },
        { 7,  "MBIM_CID_PREFERRED_PROVIDERS" },
        { 8,  "MBIM_CID_VISIBLE_PROVIDERS" },
        { 9,  "MBIM_CID_REGISTER_STATE" },
        { 10, "MBIM_CID_PACKET_SERVICE" },
        { 11, "MBIM_CID_SIGNAL_STATE" },
        { 12, "MBIM_CID_CONNECT" },
        { 13, "MBIM_CID_PROVISIONED_CONTEXTS" },
        { 14, "MBIM_CID_SERVICE_ACTIVATION" },
        { 15, "MBIM_CID_IP_CONFIGURATION" },
        { 16, "MBIM_CID_DEVICE_SERVICES" },
        { 19, "MBIM_CID_DEVICE_SERVICE_SUBSCRIBE_LIST" },
        { 20, "MBIM_CID_PACKET_STATISTICS" },
        { 21, "MBIM_CID_NETWORK_IDLE_HINT" },
        { 22, "MBIM_CID_EMERGENCY_MODE" },
        { 23, "MBIM_CID_IP_PACKET_FILTERS" },
        { 24, "MBIM_CID_MULTICARRIER_PROVIDERS" }
    };

    auto it = cid_map.find(cid);
    if (it != cid_map.end())
        return it->second;
    return "Unknown BASIC_CONNECT CID";
}

inline std::string map_sms_cid(uint32_t cid) {
    static const std::unordered_map<uint32_t, std::string> cid_map = {
        { 1, "MBIM_CID_SMS_CONFIGURATION" },
        { 2, "MBIM_CID_SMS_READ" },
        { 3, "MBIM_CID_SMS_SEND" },
        { 4, "MBIM_CID_SMS_DELETE" },
        { 5, "MBIM_CID_SMS_MESSAGE_STORE_STATUS" }
    };

    auto it = cid_map.find(cid);
    if (it != cid_map.end())
        return it->second;
    return "Unknown SMS CID";
}

inline std::string map_ussd_cid(uint32_t cid) {
    static const std::unordered_map<uint32_t, std::string> cid_map = {
        { 1, "MBIM_CID_USSD" }
    };

    auto it = cid_map.find(cid);
    if (it != cid_map.end())
        return it->second;
    return "Unknown USSD CID";
}

inline std::string map_phonebook_cid(uint32_t cid) {
    static const std::unordered_map<uint32_t, std::string> cid_map = {
        { 1, "MBIM_CID_PHONEBOOK_CONFIGURATION" },
        { 2, "MBIM_CID_PHONEBOOK_READ" },
        { 3, "MBIM_CID_PHONEBOOK_DELETE" },
        { 4, "MBIM_CID_PHONEBOOK_WRITE" }
    };

    auto it = cid_map.find(cid);
    if (it != cid_map.end())
        return it->second;
    return "Unknown PHONEBOOK CID";
}

inline std::string map_stk_cid(uint32_t cid) {
    static const std::unordered_map<uint32_t, std::string> cid_map = {
        { 1, "MBIM_CID_STK_PAC" },
        { 2, "MBIM_CID_STK_TERMINAL_RESPONSE" },
        { 3, "MBIM_CID_STK_ENVELOPE" }
    };

    auto it = cid_map.find(cid);
    if (it != cid_map.end())
        return it->second;
    return "Unknown STK CID";
}

inline std::string map_auth_cid(uint32_t cid) {
    static const std::unordered_map<uint32_t, std::string> cid_map = {
        { 1, "MBIM_CID_AKA_AUTH" },
        { 2, "MBIM_CID_AKAP_AUTH" },
        { 3, "MBIM_CID_SIM_AUTH" }
    };

    auto it = cid_map.find(cid);
    if (it != cid_map.end())
        return it->second;
    return "Unknown AUTH CID";
}

inline std::string map_dss_cid(uint32_t cid) {
    static const std::unordered_map<uint32_t, std::string> cid_map = {
        { 1, "MBIM_CID_DSS_CONNECT" }
    };

    auto it = cid_map.find(cid);
    if (it != cid_map.end())
        return it->second;
    return "Unknown DSS CID";
}

inline std::string (*get_cid_mapper_for_uuid(const std::string& uuid))(uint32_t) {
    static const std::unordered_map<std::string, std::string(*)(uint32_t)> mapper_map = {
        { "a289cc33bcbb8b4fb6b0133ec2aae6df", map_basic_connect_cid },
        { "533fbeeb14fe44679f9033a223e56c3f", map_sms_cid },
        { "e550a0c85e82479e82f710abf4c3351f", map_ussd_cid },
        { "4bf384761e6a41dbb1d8bed289c25bdb", map_phonebook_cid },
        { "d8f20131fcb54e178602d6ed3816164c", map_stk_cid },
        { "1d2b5ff70aa148b2aa5250f15767174e", map_auth_cid },
        { "c08a26dd7718438284826e0d583c4d0e", map_dss_cid }
    };

    auto it = mapper_map.find(uuid);
    if (it != mapper_map.end())
        return it->second;

    return nullptr;
}





// ----------------------------------------------------------------------------------------------


// HEADERS

// ----------------------------------------------------------------------------------------------

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

// ----------------------------------------------------------------------------------------------

// MESSAGES

// ----------------------------------------------------------------------------------------------

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
