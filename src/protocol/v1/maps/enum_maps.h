#pragma once

#include <string>
#include <sstream>

inline std::string map_device_type(DEVICE_TYPE_ENUM type) {
    switch (type) {
        case DEVICE_TYPE_ENUM::MBIM_DEVICE_TYPE_UNKNOWN:         return "Device type is unknown";
        case DEVICE_TYPE_ENUM::MBIM_DEVICE_TYPE_EMBEDDED:        return "Modem is embedded in the system";
        case DEVICE_TYPE_ENUM::MBIM_DEVICE_TYPE_REMOVABLE:       return "Modem is probably on a USB stick";
        case DEVICE_TYPE_ENUM::MBIM_DEVICE_TYPE_REMOTE:          return "Probably tethered cellular phone modem";
        default: return "Unknown";
    }
}

inline std::string map_type(MESSAGE_TYPE_ENUM type) {
    switch (type) {
        case MESSAGE_TYPE_ENUM::MBIM_OPEN_MSG:            return "host -> modem: open a connection";
        case MESSAGE_TYPE_ENUM::MBIM_CLOSE_MSG:           return "host -> modem: close the connection";
        case MESSAGE_TYPE_ENUM::MBIM_COMMAND_MSG:         return "host -> modem: send command";
        case MESSAGE_TYPE_ENUM::MBIM_HOST_ERROR_MSG:      return "host -> modem: host error occurred";
        case MESSAGE_TYPE_ENUM::MBIM_OPEN_DONE:           return "modem -> host: response to opening a connection";
        case MESSAGE_TYPE_ENUM::MBIM_CLOSE_DONE:          return "modem -> host: modem is closing the connection";
        case MESSAGE_TYPE_ENUM::MBIM_COMMAND_DONE:        return "modem -> host: modem completed a command";
        case MESSAGE_TYPE_ENUM::MBIM_FUNCTION_ERROR_MSG:  return "modem -> host: error in modem";
        case MESSAGE_TYPE_ENUM::MBIM_INDICATE_STATUS_MSG: return "modem -> host: status indication";
        default: return "Unknown message type";
    }
}

inline std::string map_query_or_set(MESSAGE_QUERY_OR_SET_ENUM query_or_set) {
    switch (query_or_set) {
        case MESSAGE_QUERY_OR_SET_ENUM::QUERY: return "Query";
        case MESSAGE_QUERY_OR_SET_ENUM::SET:   return "Set";
        default: return "Unknown";
    }
}

inline std::string map_voice_class(VOICE_CLASS_ENUM type) {
    switch (type) {
        case VOICE_CLASS_ENUM::MBIM_VOICE_CLASS_UNKNOWN:                  return "Unknown voice class";
        case VOICE_CLASS_ENUM::MBIM_VOICE_CLASS_NO_VOICE:                 return "No voice support";
        case VOICE_CLASS_ENUM::MBIM_VOICE_CLASS_SEPARATE_VOICE_DATA:      return "Separate voice/data supported";
        case VOICE_CLASS_ENUM::MBIM_VOICE_CLASS_SIMULTANEOUS_VOICE_DATA:  return "Simultaneous voice and data supported";
        default: return "Unknown";
    }
}

inline std::string map_sim_class(SIM_CLASS_ENUM type) {
    switch (type) {
        case SIM_CLASS_ENUM::MBIM_SIM_CLASS_SIM_LOGICAL:   return "eSIM";
        case SIM_CLASS_ENUM::MBIM_SIM_CLASS_SIM_REMOVABLE: return "Physical SIM";
        default: return "Unknown";
    }
}

inline std::string map_host_error(MBIM_PROTOCOL_ERROR_CODES_ENUM type) {
    switch (type) {
        case MBIM_PROTOCOL_ERROR_CODES_ENUM::MBIM_ERROR_TIMEOUT_FRAGMENT:        return "Timeout while waiting for next fragment";
        case MBIM_PROTOCOL_ERROR_CODES_ENUM::MBIM_ERROR_FRAGMENT_OUT_OF_SEQUENCE: return "Received fragment out of sequence";
        case MBIM_PROTOCOL_ERROR_CODES_ENUM::MBIM_ERROR_LENGTH_MISMATCH:          return "Mismatch in expected length";
        case MBIM_PROTOCOL_ERROR_CODES_ENUM::MBIM_ERROR_DUPLICATED_TID:           return "Duplicated transaction ID";
        case MBIM_PROTOCOL_ERROR_CODES_ENUM::MBIM_ERROR_NOT_OPENED:               return "Channel not open";
        case MBIM_PROTOCOL_ERROR_CODES_ENUM::MBIM_ERROR_UNKNOW:                   return "Unknown error";
        case MBIM_PROTOCOL_ERROR_CODES_ENUM::MBIM_ERROR_CANCEL:                   return "Operation was canceled";
        case MBIM_PROTOCOL_ERROR_CODES_ENUM::MBIM_ERROR_MAX_TRANSFER:             return "Transfer exceeds maximum size";
        default: return "Unrecognized host error";
    }
}

inline std::string map_type_to_host(MESSAGE_TYPE_ENUM type) {
    switch (type) {
        case MESSAGE_TYPE_ENUM::MBIM_OPEN_DONE:           return "Open complete";
        case MESSAGE_TYPE_ENUM::MBIM_CLOSE_DONE:          return "Close complete";
        case MESSAGE_TYPE_ENUM::MBIM_COMMAND_DONE:        return "Command complete";
        case MESSAGE_TYPE_ENUM::MBIM_FUNCTION_ERROR_MSG:  return "Function-level error";
        case MESSAGE_TYPE_ENUM::MBIM_INDICATE_STATUS_MSG: return "Unsolicited indication";
        default: return "Unknown message type to host";
    }
}

inline std::string map_host_status(MBIM_STATUS_TO_HOST_ENUM status) {
    switch (status) {
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_SUCCESS:                      return "Operation succeeded";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_BUSY:                         return "Device is busy";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_FAILURE:                      return "Generic failure";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_SIM_NOT_INSERTED:             return "SIM not inserted";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_BAD_SIM:                      return "Bad SIM card";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_PIN_REQUIRED:                 return "PIN required";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_PIN_DISABLED:                 return "PIN disabled";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_NOT_REGISTERED:               return "Device not registered";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_PROVIDERS_NOT_FOUND:          return "No providers found";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_NO_DEVICE_SUPPORT:            return "Device does not support the operation";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_PROVIDER_NOT_VISIBLE:         return "Provider not visible";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_DATA_CLASS_NOT_AVAILABLE:     return "Data class unavailable";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_PACKET_SERVICE_DETACHED:      return "Packet service detached";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_MAX_ACTIVATED_CONTEXTS:       return "Max activated contexts reached";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_NOT_INITIALIZED:              return "Device initializing";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_VOICE_CALL_IN_PROGRESS:       return "Voice call in progress";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_CONTEXT_NOT_ACTIVATED:        return "Context not activated";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_SERVICE_NOT_ACTIVATED:        return "Service not activated";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_INVALID_ACCESS_STRING:        return "Invalid access string";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_INVALID_USER_NAME_PWD:        return "Invalid username or password";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_RADIO_POWER_OFF:              return "Radio is off";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_INVALID_PARAMETERS:           return "Invalid parameters";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_READ_FAILURE:                 return "Read failure";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_WRITE_FAILURE:                return "Write failure";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_NO_PHONEBOOK:                 return "No phonebook";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_PARAMETER_TOO_LONG:           return "Parameter too long";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_STK_BUSY:                     return "SIM Toolkit busy";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_OPERATION_NOT_ALLOWED:        return "Operation not allowed";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_MEMORY_FAILURE:               return "Memory failure";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_INVALID_MEMORY_INDEX:         return "Invalid memory index";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_MEMORY_FULL:                  return "Memory full";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_FILTER_NOT_SUPPORTED:         return "Filter not supported";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_DSS_INSTANCE_LIMIT:           return "DSS instance limit exceeded";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_INVALID_DEVICE_SERVICE_OPERATION: return "Invalid device service operation";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_AUTH_INCORRECT_AUTN:          return "Auth failed: incorrect AUTN";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_AUTH_SYNC_FAILURE:            return "Auth sync failure";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_AUTH_AMF_NOT_SET:             return "Auth AMF not set";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_SMS_UNKNOWN_SMSC_ADDRESS:     return "Unknown SMSC address";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_SMS_NETWORK_TIMEOUT:          return "SMS network timeout";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_SMS_LANG_NOT_SUPPORTED:       return "SMS language not supported";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_SMS_ENCODING_NOT_SUPPORTED:   return "SMS encoding not supported";
        case MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_SMS_FORMAT_NOT_SUPPORTED:     return "SMS format not supported";
        default: return "Unrecognized status code";
    }
}
