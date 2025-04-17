#pragma once

#include <string>
#include <unordered_map>
#include <sstream>

#include "enums.h"

inline std::string map_type(MESSAGE_TYPE_ENUM type) {
    switch (type) {
        case MESSAGE_TYPE_ENUM::MBIM_OPEN_MSG:            return "host -> modem: open a connection";
        case MESSAGE_TYPE_ENUM::MBIM_CLOSE_MSG:           return "host -> modem: close the connection";
        case MESSAGE_TYPE_ENUM::MBIM_COMMAND_MSG:         return "host -> modem: send command";
        case MESSAGE_TYPE_ENUM::MBIM_HOST_ERROR_MSG:      return "host -> modem: host error occured";
        case MESSAGE_TYPE_ENUM::MBIM_OPEN_DONE:           return "modem -> host: response to opening a conncetion";
        case MESSAGE_TYPE_ENUM::MBIM_CLOSE_DONE:          return "modem -> host: modem is closing the connection";
        case MESSAGE_TYPE_ENUM::MBIM_COMMAND_DONE:        return "modem -> host: modem completed a commnad";
        case MESSAGE_TYPE_ENUM::MBIM_FUNCTION_ERROR_MSG:  return "modem -> host: error in modem";
        case MESSAGE_TYPE_ENUM::MBIM_INDICATE_STATUS_MSG: return "modem -> host: status indication";
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

inline std::string map_type_to_host(MESSAGE_TYPE_ENUM type) {
    switch (type) {
        case MESSAGE_TYPE_ENUM::MBIM_OPEN_DONE:
            return "Open complete";
        case MESSAGE_TYPE_ENUM::MBIM_CLOSE_DONE:
            return "Close complete";
        case MESSAGE_TYPE_ENUM::MBIM_COMMAND_DONE:
            return "Command complete";
        case MESSAGE_TYPE_ENUM::MBIM_FUNCTION_ERROR_MSG:
            return "Function-level error";
        case MESSAGE_TYPE_ENUM::MBIM_INDICATE_STATUS_MSG:
            return "Unsolicited indication";
        default:
            return "Unknown message type to host";
    }
}

inline std::string map_host_status(MBIM_STATUS_TO_HOST_ENUM status) {
    switch (status) {
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_SUCCESS:
            return "Operation succeeded";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_BUSY:
            return "Device is busy";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_FAILURE:
            return "Generic failure";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_SIM_NOT_INSERTED:
            return "SIM not inserted";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_BAD_SIM:
            return "SIM is bad and unusable";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_PIN_REQUIRED:
            return "PIN required to proceed";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_PIN_DISABLED:
            return "PIN is disabled";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_NOT_REGISTERED:
            return "Device not registered with network";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_PROVIDERS_NOT_FOUND:
            return "No network providers found";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_NO_DEVICE_SUPPORT:
            return "Device does not support the operation";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_PROVIDER_NOT_VISIBLE:
            return "Service provider not currently visible";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_DATA_CLASS_NOT_AVAILABLE:
            return "Requested data class unavailable";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_PACKET_SERVICE_DETACHED:
            return "Packet service is detached";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_MAX_ACTIVATED_CONTEXTS:
            return "Max activated contexts reached";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_NOT_INITIALIZED:
            return "Device is initializing";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_VOICE_CALL_IN_PROGRESS:
            return "Voice call in progress";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_CONTEXT_NOT_ACTIVATED:
            return "Context not activated";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_SERVICE_NOT_ACTIVATED:
            return "Service not activated";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_INVALID_ACCESS_STRING:
            return "Invalid access string";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_INVALID_USER_NAME_PWD:
            return "Invalid username or password";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_RADIO_POWER_OFF:
            return "Radio is powered off";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_INVALID_PARAMETERS:
            return "Invalid parameters";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_READ_FAILURE:
            return "Read operation failed";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_WRITE_FAILURE:
            return "Write operation failed";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_NO_PHONEBOOK:
            return "No phonebook available";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_PARAMETER_TOO_LONG:
            return "Parameter too long";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_STK_BUSY:
            return "SIM Toolkit is busy";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_OPERATION_NOT_ALLOWED:
            return "Operation not allowed";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_MEMORY_FAILURE:
            return "Device or SIM memory failure";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_INVALID_MEMORY_INDEX:
            return "Invalid memory index";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_MEMORY_FULL:
            return "Memory is full";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_FILTER_NOT_SUPPORTED:
            return "Filter type not supported";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_DSS_INSTANCE_LIMIT:
            return "Exceeded DSS instance limit";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_INVALID_DEVICE_SERVICE_OPERATION:
            return "Invalid device service operation";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_AUTH_INCORRECT_AUTN:
            return "Authentication failed: incorrect AUTN";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_AUTH_SYNC_FAILURE:
            return "Authentication sync failure";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_AUTH_AMF_NOT_SET:
            return "Authentication failed: AMF not set";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_SMS_UNKNOWN_SMSC_ADDRESS:
            return "Unknown SMSC address";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_SMS_NETWORK_TIMEOUT:
            return "SMS network timeout";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_SMS_LANG_NOT_SUPPORTED:
            return "SMS language not supported (CDMA)";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_SMS_ENCODING_NOT_SUPPORTED:
            return "SMS encoding not supported (CDMA)";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_SMS_FORMAT_NOT_SUPPORTED:
            return "SMS format not supported";
        default:
            return "Unrecognized status code";
    }
}


inline std::string map_device_type(DEVICE_TYPE_ENUM type) {
    switch (type) {
        case DEVICE_TYPE_ENUM::MBIM_DEVICE_TYPE_UNKNOWN:         return "Device type is unknown";
        case DEVICE_TYPE_ENUM::MBIM_DEVICE_TYPE_EMBEDDED:        return "Modem is embedded in the system";
        case DEVICE_TYPE_ENUM::MBIM_DEVICE_TYPE_REMOVABLE:       return "Modem is probably on a USB stick";
        case DEVICE_TYPE_ENUM::MBIM_DEVICE_TYPE_REMOTE:          return "Probably tethered cellular phone modem";
        default: return "Unknown";
    }
}

inline std::string map_cellular_class(uint32_t value) {
    std::vector<std::string> flags;

    if (value & static_cast<uint32_t>(CELLULAR_CLASS_ENUM::MBIM_CELLULAR_CLASS_GSM))
        flags.push_back("[MBIM_CELLULAR_CLASS_GSM] - GSM capable device");
    if (value & static_cast<uint32_t>(CELLULAR_CLASS_ENUM::MBIM_CELLULAR_CLASS_CDMA))
        flags.push_back("[MBIM_CELLULAR_CLASS_CDMA] - CDMA capable device");
  
    if (flags.empty())
        return "NONE";

    std::ostringstream oss;
    for (size_t i = 0; i < flags.size(); ++i) {
        oss << "\t -> ";
        oss << flags[i] << "\n";
    }
    return oss.str();
}

inline std::string map_voice_class(VOICE_CLASS_ENUM type) {
    switch (type) {
        case VOICE_CLASS_ENUM::MBIM_VOICE_CLASS_UNKNOWN:                   return "The device uses an unknown method to support voice connections";
        case VOICE_CLASS_ENUM::MBIM_VOICE_CLASS_NO_VOICE:                  return "The device does not support voice connections";
        case VOICE_CLASS_ENUM::MBIM_VOICE_CLASS_SEPARATE_VOICE_DATA:       return "The device supports separate voice and data connections";
        case VOICE_CLASS_ENUM::MBIM_VOICE_CLASS_SIMULTANEOUS_VOICE_DATA:   return "The device supports simultaneous voice and data connections";
        default: return "Unknown";
    }
}

inline std::string map_sim_class(SIM_CLASS_ENUM type) {
    switch (type) {
        case SIM_CLASS_ENUM::MBIM_SIM_CLASS_SIM_LOGICAL:                   return "eSIM";
        case SIM_CLASS_ENUM::MBIM_SIM_CLASS_SIM_REMOVABLE:                  return "Physical SIM";
        default: return "Unknown";
    }
}
inline std::string map_data_class(uint32_t value) {
    std::vector<std::string> flags;

    if (value & static_cast<uint32_t>(DATA_CLASS_ENUM::MBIM_DATA_CLASS_NONE))
        flags.push_back("[MBIM_DATA_CLASS_NONE] - No data class supported");
    if (value & static_cast<uint32_t>(DATA_CLASS_ENUM::MBIM_DATA_CLASS_GPRS))
        flags.push_back("[MBIM_DATA_CLASS_GPRS] - GPRS supported");
    if (value & static_cast<uint32_t>(DATA_CLASS_ENUM::MBIM_DATA_CLASS_EDGE))
        flags.push_back("[MBIM_DATA_CLASS_EDGE] - EDGE supported");
    if (value & static_cast<uint32_t>(DATA_CLASS_ENUM::MBIM_DATA_CLASS_UMTS))
        flags.push_back("[MBIM_DATA_CLASS_UMTS] - UMTS supported");
    if (value & static_cast<uint32_t>(DATA_CLASS_ENUM::MBIM_DATA_CLASS_HSDPA))
        flags.push_back("[MBIM_DATA_CLASS_HSDPA] - HSDPA supported");
    if (value & static_cast<uint32_t>(DATA_CLASS_ENUM::MBIM_DATA_CLASS_HSUPA))
        flags.push_back("[MBIM_DATA_CLASS_HSUPA] - HSUPA supported");
    if (value & static_cast<uint32_t>(DATA_CLASS_ENUM::MBIM_DATA_CLASS_LTE))
        flags.push_back("[MBIM_DATA_CLASS_LTE] - LTE supported");
    if (value & static_cast<uint32_t>(DATA_CLASS_ENUM::MBIM_DATA_CLASS_1XRTT))
        flags.push_back("[MBIM_DATA_CLASS_1XRTT] - 1xRTT supported");
    if (value & static_cast<uint32_t>(DATA_CLASS_ENUM::MBIM_DATA_CLASS_1XEVDO))
        flags.push_back("[MBIM_DATA_CLASS_1XEVDO] - 1xEVDO supported");
    if (value & static_cast<uint32_t>(DATA_CLASS_ENUM::MBIM_DATA_CLASS_1XEVDO_REVA))
        flags.push_back("[MBIM_DATA_CLASS_1XEVDO_REVA] - 1xEVDO Rev-A supported");
    if (value & static_cast<uint32_t>(DATA_CLASS_ENUM::MBIM_DATA_CLASS_1XEVDO_REVB))
        flags.push_back("[MBIM_DATA_CLASS_1XEVDO_REVB] - 1xEVDO Rev-B supported");
    if (value & static_cast<uint32_t>(DATA_CLASS_ENUM::MBIM_DATA_CLASS_UMB))
        flags.push_back("[MBIM_DATA_CLASS_UMB] - UMB supported");
    if (value & static_cast<uint32_t>(DATA_CLASS_ENUM::MBIM_DATA_CLASS_CUSTOM))
        flags.push_back("[MBIM_DATA_CLASS_CUSTOM] - Custom data class");

    if (flags.empty())
        return "NONE";

    std::ostringstream oss;
    for (const auto& flag : flags) {
        oss << "\t -> " << flag << "\n";
    }
    return oss.str();
}

inline std::string map_sms_caps(uint32_t value) {
    std::vector<std::string> flags;

    if (value & static_cast<uint32_t>(SMS_CAPS_ENUM::MBIM_SMS_CAPS_PDU_RECEIVE))
        flags.push_back("[MBIM_SMS_CAPS_PDU_RECEIVE] - Can receive SMS in PDU format");
    if (value & static_cast<uint32_t>(SMS_CAPS_ENUM::MBIM_SMS_CAPS_PDU_SEND))
        flags.push_back("[MBIM_SMS_CAPS_PDU_SEND] - Can send SMS in PDU format");
    if (value & static_cast<uint32_t>(SMS_CAPS_ENUM::MBIM_SMS_CAPS_TEXT_RECEIVE))
        flags.push_back("[MBIM_SMS_CAPS_TEXT_RECEIVE] - Can receive SMS in text format");
    if (value & static_cast<uint32_t>(SMS_CAPS_ENUM::MBIM_SMS_CAPS_TEXT_SEND))
        flags.push_back("[MBIM_SMS_CAPS_TEXT_SEND] - Can send SMS in text format");

    if (flags.empty())
        return "NONE";

    std::ostringstream oss;
    for (const auto& flag : flags) {
        oss << "\t -> " << flag << "\n";
    }
    return oss.str();
}

inline std::string map_ctrl_caps(uint32_t value) {
    std::vector<std::string> flags;

    if (value & static_cast<uint32_t>(CTRL_CAPS_ENUM::MBIM_CTRL_CAPS_REG_MANUAL))
        flags.push_back("[MBIM_CTRL_CAPS_REG_MANUAL] - Supports manual registration");
    if (value & static_cast<uint32_t>(CTRL_CAPS_ENUM::MBIM_CTRL_CAPS_HW_RADIO_SWITCH))
        flags.push_back("[MBIM_CTRL_CAPS_HW_RADIO_SWITCH] - Hardware radio switch is supported");
    if (value & static_cast<uint32_t>(CTRL_CAPS_ENUM::MBIM_CTRL_CAPS_CDMA_MOBILE_IP))
        flags.push_back("[MBIM_CTRL_CAPS_CDMA_MOBILE_IP] - Supports CDMA Mobile IP");
    if (value & static_cast<uint32_t>(CTRL_CAPS_ENUM::MBIM_CTRL_CAPS_CDMA_SIMPLE_IP))
        flags.push_back("[MBIM_CTRL_CAPS_CDMA_SIMPLE_IP] - Supports CDMA Simple IP");
    if (value & static_cast<uint32_t>(CTRL_CAPS_ENUM::MBIM_CTRL_CAPS_MULTI_CARRIER))
        flags.push_back("[MBIM_CTRL_CAPS_MULTI_CARRIER] - Multi-carrier support available");

    if (flags.empty())
        return "NONE";

    std::ostringstream oss;
    for (const auto& flag : flags) {
        oss << "\t -> " << flag << "\n";
    }
    return oss.str();
}
