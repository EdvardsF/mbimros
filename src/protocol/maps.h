#pragma once

#include <string>
#include <unordered_map>

#include "enums.h"

inline std::string map_type(MESSAGE_TYPE_ENUM type) {
    switch (type) {
        case MESSAGE_TYPE_ENUM::MBIM_OPEN_MSG:       return "Open a connection";
        case MESSAGE_TYPE_ENUM::MBIM_CLOSE_MSG:      return "Close the connection";
        case MESSAGE_TYPE_ENUM::MBIM_COMMAND_MSG:    return "Command from host";
        case MESSAGE_TYPE_ENUM::MBIM_HOST_ERROR_MSG: return "Host error notification";
        default: return "Unknown message type";
    }
}



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


inline std::string map_host_error(MBIM_PROTOCOL_ERROR_CODES_ENUM type) {
    switch (type) {
        case MBIM_PROTOCOL_ERROR_CODES_ENUM::MBIM_ERROR_TIMEOUT_FRAGMENT:
            return "Timeout while waiting for next fragment";
        case MBIM_PROTOCOL_ERROR_CODES_ENUM::MBIM_ERROR_FRAGMENT_OUT_OF_SEQUENCE:
            return "Received fragment out of sequence";
        case MBIM_PROTOCOL_ERROR_CODES_ENUM::MBIM_ERROR_LENGTH_MISMATCH:
            return "Mismatch in expected length";
        case MBIM_PROTOCOL_ERROR_CODES_ENUM::MBIM_ERROR_DUPLICATED_TID:
            return "Duplicated transaction ID";
        case MBIM_PROTOCOL_ERROR_CODES_ENUM::MBIM_ERROR_NOT_OPENED:
            return "Channel is not open";
        case MBIM_PROTOCOL_ERROR_CODES_ENUM::MBIM_ERROR_UNKNOW:
            return "Unknown error";
        case MBIM_PROTOCOL_ERROR_CODES_ENUM::MBIM_ERROR_CANCEL:
            return "Operation was canceled";
        case MBIM_PROTOCOL_ERROR_CODES_ENUM::MBIM_ERROR_MAX_TRANSFER:
            return "Transfer exceeds maximum size";
        default:
            return "Unrecognized host error";
    }
}
