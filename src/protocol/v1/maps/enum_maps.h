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

inline std::string map_subscriber_ready_state(SUBSCRIBER_READY_STATE_ENUM state) {
    switch (state) {
        case SUBSCRIBER_READY_STATE_ENUM::MBIM_SUBSCRIBER_READY_STATE_NOT_INITIALIZED:
            return "The SIM has not yet completed its initialization";
        case SUBSCRIBER_READY_STATE_ENUM::MBIM_SUBSCRIBER_READY_STATE_INITIALIZED:
            return "The SIM is initialized";
        case SUBSCRIBER_READY_STATE_ENUM::MBIM_SUBSCRIBER_READY_STATE_SIM_NOT_INSERTED:
            return "The SIM card is not inserted into the device";
        case SUBSCRIBER_READY_STATE_ENUM::MBIM_SUBSCRIBER_READY_STATE_BAD_SIM:
            return "The SIM card inserted into the device is invalid";
        case SUBSCRIBER_READY_STATE_ENUM::MBIM_SUBSCRIBER_READY_STATE_FAILURE:
            return "A general SIM failure has occurred";
        case SUBSCRIBER_READY_STATE_ENUM::MBIM_SUBSCRIBER_READY_STATE_NOT_ACTIVATED:
            return "The subscription is not activated";
        case SUBSCRIBER_READY_STATE_ENUM::MBIM_SUBSCRIBER_READY_STATE_DEVICE_LOCKED:
            return "The SIM is locked and requires PIN1 or PUK1 to unlock";
        default:
            return "Unknown Subscriber Ready State";
    }
}

inline std::string map_ready_info_flags(MBIM_READY_INFO_FLAGS_ENUM flag) {
    switch (flag) {
        case MBIM_READY_INFO_FLAGS_ENUM::MBIM_READY_INFO_FLAGS_NONE:
            return "The device is in normal mode";
        case MBIM_READY_INFO_FLAGS_ENUM::MBIM_READY_INFO_FLAGS_PROTECT_UNIQUE_ID:
            return "whether the host will display the SubscriberId in this CID";
        default:
            return "Unknown Ready Info Flag";
    }
}



inline std::string map_radio_switch_state(MBIM_RADIO_SWITCH_STATE_ENUM flag) {
    switch (flag) {
        case MBIM_RADIO_SWITCH_STATE_ENUM::MBIM_RADIO_OFF:
            return "Switch off device's radio";
        case MBIM_RADIO_SWITCH_STATE_ENUM::MBIM_RADIO_ON:
            return "Switch on device's radio";
        default:
            return "Unknown Radio Switch State";
    }
}

inline std::string map_pin_type(PIN_TYPE_ENUM type) {
    switch (type) {
        case PIN_TYPE_ENUM::MBIM_PIN_TYPE_NONE:
            return "None (no PIN type specified)";
        case PIN_TYPE_ENUM::MBIM_PIN_TYPE_CUSTOM:
            return "Custom PIN type (non-standard)";
        case PIN_TYPE_ENUM::MBIM_PIN_TYPE_PIN1:
            return "PIN1 (SIM PIN)";
        case PIN_TYPE_ENUM::MBIM_PIN_TYPE_PIN2:
            return "PIN2 (secondary SIM PIN)";
        case PIN_TYPE_ENUM::MBIM_PIN_TYPE_DEVICE_SIM_PIN:
            return "Device-to-SIM PIN (device lock PIN)";
        case PIN_TYPE_ENUM::MBIM_PIN_TYPE_DEVICE_FIRST_SIM_PIN:
            return "Device first SIM PIN";
        case PIN_TYPE_ENUM::MBIM_PIN_TYPE_NETWORK_PIN:
            return "Network unlock PIN";
        case PIN_TYPE_ENUM::MBIM_PIN_TYPE_NETWORK_SUBSET_PIN:
            return "Network subset unlock PIN";
        case PIN_TYPE_ENUM::MBIM_PIN_TYPE_SERVICE_PROVIDER_PIN:
            return "Service provider unlock PIN";
        case PIN_TYPE_ENUM::MBIM_PIN_TYPE_CORPORATE_PIN:
            return "Corporate unlock PIN";
        case PIN_TYPE_ENUM::MBIM_PIN_TYPE_SUBSIDY_LOCK:
            return "Subsidy unlock PIN";
        case PIN_TYPE_ENUM::MBIM_PIN_TYPE_PUK1:
            return "PUK1 (PIN1 unblock code)";
        case PIN_TYPE_ENUM::MBIM_PIN_TYPE_PUK2:
            return "PUK2 (PIN2 unblock code)";
        case PIN_TYPE_ENUM::MBIM_PIN_TYPE_DEVICE_FIRST_SIM_PUK:
            return "Device first SIM PUK";
        case PIN_TYPE_ENUM::MBIM_PIN_TYPE_NETWORK_PUK:
            return "Network unlock PUK";
        case PIN_TYPE_ENUM::MBIM_PIN_TYPE_NETWORK_SUBSET_PUK:
            return "Network subset unlock PUK";
        case PIN_TYPE_ENUM::MBIM_PIN_TYPE_SERVICE_PROVIDER_PUK:
            return "Service provider unlock PUK";
        case PIN_TYPE_ENUM::MBIM_PIN_TYPE_CORPORATE_PUK:
            return "Corporate unlock PUK";
        default:
            return "Unknown PIN type";
    }
}

inline std::string map_pin_state(PIN_STATE_ENUM state) {
    switch (state) {
        case PIN_STATE_ENUM::MBIM_PIN_STATE_UNLOCKED:
            return "PIN unlocked (not required)";
        case PIN_STATE_ENUM::MBIM_PIN_STATE_LOCKED:
            return "PIN locked (entry required)";
        default:
            return "Unknown PIN state";
    }
}

inline std::string map_pin_operation(PIN_OPERATION_ENUM op) {
    switch (op) {
        case PIN_OPERATION_ENUM::MBIM_PIN_OPERATION_ENTER:
            return "Enter PIN";
        case PIN_OPERATION_ENUM::MBIM_PIN_OPERATION_ENABLE:
            return "Enable PIN lock";
        case PIN_OPERATION_ENUM::MBIM_PIN_OPERATION_DISABLE:
            return "Disable PIN lock";
        case PIN_OPERATION_ENUM::MBIM_PIN_OPERATION_CHANGE:
            return "Change PIN";
        default:
            return "Unknown PIN operation";
    }
}

inline std::string map_pin_mode(PIN_MODE_ENUM mode) {
    switch (mode) {
        case PIN_MODE_ENUM::MBIM_PIN_MODE_NOT_SUPPORTED:
            return "PIN lock not supported";
        case PIN_MODE_ENUM::MBIM_PIN_MODE_ENABLED:
            return "PIN lock enabled";
        case PIN_MODE_ENUM::MBIM_PIN_MODE_DISABLED:
            return "PIN lock disabled";
        default:
            return "Unknown PIN mode";
    }
}

inline std::string map_pin_format(PIN_FORMAT_ENUM format) {
    switch (format) {
        case PIN_FORMAT_ENUM::MBIM_PIN_FORMAT_UNKNOWN:
            return "PIN format unknown";
        case PIN_FORMAT_ENUM::MBIM_PIN_FORMAT_NUMERIC:
            return "Numeric PIN format";
        case PIN_FORMAT_ENUM::MBIM_PIN_FORMAT_ALPHANUMERIC:
            return "Alphanumeric PIN format";
        default:
            return "Unknown PIN format";
    }
}

inline std::string map_visible_providers_action(VISIBLE_PROVIDERS_ACTION_ENUM action) {
    switch (action) {
        case VISIBLE_PROVIDERS_ACTION_ENUM::MBIM_VISIBLE_PROVIDERS_ACTION_FULL_SCAN:
            return "Full scan (all providers)";
        case VISIBLE_PROVIDERS_ACTION_ENUM::MBIM_VISIBLE_PROVIDERS_ACTION_RESTRICTED_SCAN:
            return "Restricted scan (preferred providers only)";
        default:
            return "Unknown providers scan action";
    }
}

inline std::string map_register_action(REGISTER_ACTION_ENUM action) {
    switch (action) {
        case REGISTER_ACTION_ENUM::MBIM_REGISTER_ACTION_AUTOMATIC:
            return "Automatic registration";
        case REGISTER_ACTION_ENUM::MBIM_REGISTER_ACTION_MANUAL:
            return "Manual registration";
        default:
            return "Unknown registration action";
    }
}

inline std::string map_register_state(REGISTER_STATE_ENUM state) {
    switch (state) {
        case REGISTER_STATE_ENUM::MBIM_REGISTER_STATE_UNKNOWN:
            return "Registration state unknown";
        case REGISTER_STATE_ENUM::MBIM_REGISTER_STATE_DEREGISTERED:
            return "Not registered";
        case REGISTER_STATE_ENUM::MBIM_REGISTER_STATE_SEARCHING:
            return "Searching for network";
        case REGISTER_STATE_ENUM::MBIM_REGISTER_STATE_HOME:
            return "Registered (home network)";
        case REGISTER_STATE_ENUM::MBIM_REGISTER_STATE_ROAMING:
            return "Registered (roaming)";
        case REGISTER_STATE_ENUM::MBIM_REGISTER_STATE_PARTNER:
            return "Registered (partner network)";
        case REGISTER_STATE_ENUM::MBIM_REGISTER_STATE_DENIED:
            return "Registration denied";
        default:
            return "Unknown registration state";
    }
}

inline std::string map_register_mode(REGISTER_MODE_ENUM mode) {
    switch (mode) {
        case REGISTER_MODE_ENUM::MBIM_REGISTER_MODE_UNKNOWN:
            return "Unknown registration mode";
        case REGISTER_MODE_ENUM::MBIM_REGISTER_MODE_AUTOMATIC:
            return "Automatic registration mode";
        case REGISTER_MODE_ENUM::MBIM_REGISTER_MODE_MANUAL:
            return "Manual registration mode";
        default:
            return "Unknown registration mode";
    }
}

inline std::string map_packet_service_action(PACKET_SERVICE_ACTION_ENUM action) {
    switch (action) {
        case PACKET_SERVICE_ACTION_ENUM::MBIM_PACKET_SERVICE_ACTION_ATTACH:
            return "Attach packet service";
        case PACKET_SERVICE_ACTION_ENUM::MBIM_PACKET_SERVICE_ACTION_DETACH:
            return "Detach packet service";
        default:
            return "Unknown packet service action";
    }
}

inline std::string map_packet_service_state(PACKET_SERVICE_STATE_ENUM state) {
    switch (state) {
        case PACKET_SERVICE_STATE_ENUM::MBIM_PACKET_SERVICE_STATE_UNKNOWN:
            return "Packet service state unknown";
        case PACKET_SERVICE_STATE_ENUM::MBIM_PACKET_SERVICE_STATE_ATTACHING:
            return "Attaching to packet service";
        case PACKET_SERVICE_STATE_ENUM::MBIM_PACKET_SERVICE_STATE_ATTACHED:
            return "Attached to packet service";
        case PACKET_SERVICE_STATE_ENUM::MBIM_PACKET_SERVICE_STATE_DETACHING:
            return "Detaching from packet service";
        case PACKET_SERVICE_STATE_ENUM::MBIM_PACKET_SERVICE_STATE_DETACHED:
            return "Detached from packet service";
        default:
            return "Unknown packet service state";
    }
}

inline std::string map_activation_command(ACTIVATION_COMMAND_ENUM cmd) {
    switch (cmd) {
        case ACTIVATION_COMMAND_ENUM::MBIM_ACTIVATION_COMMAND_DEACTIVATE:
            return "Deactivate connection";
        case ACTIVATION_COMMAND_ENUM::MBIM_ACTIVATION_COMMAND_ACTIVATE:
            return "Activate connection";
        default:
            return "Unknown activation command";
    }
}

inline std::string map_compression(COMPRESSION_ENUM comp) {
    switch (comp) {
        case COMPRESSION_ENUM::MBIM_COMPRESSION_NONE:
            return "No compression";
        case COMPRESSION_ENUM::MBIM_COMPRESSION_ENABLE:
            return "Compression enabled";
        default:
            return "Unknown compression setting";
    }
}

inline std::string map_auth_protocol(AUTH_PROTOCOL_ENUM proto) {
    switch (proto) {
        case AUTH_PROTOCOL_ENUM::MBIM_AUTH_PROTOCOL_NONE:
            return "No authentication";
        case AUTH_PROTOCOL_ENUM::MBIM_AUTH_PROTOCOL_PAP:
            return "PAP (Password Authentication Protocol)";
        case AUTH_PROTOCOL_ENUM::MBIM_AUTH_PROTOCOL_CHAP:
            return "CHAP (Challenge-Handshake Auth Protocol)";
        case AUTH_PROTOCOL_ENUM::MBIM_AUTH_PROTOCOL_MSCHAPV2:
            return "MS-CHAPv2 (Microsoft CHAP v2)";
        default:
            return "Unknown auth protocol";
    }
}

inline std::string map_context_ip_type(CONTEXT_IP_TYPE_ENUM type) {
    switch (type) {
        case CONTEXT_IP_TYPE_ENUM::MBIM_CONTEXT_IP_TYPE_DEFAULT:
            return "Default IP type (no preference)";
        case CONTEXT_IP_TYPE_ENUM::MBIM_CONTEXT_IP_TYPE_IPV4:
            return "IPv4 only";
        case CONTEXT_IP_TYPE_ENUM::MBIM_CONTEXT_IP_TYPE_IPV6:
            return "IPv6 only";
        case CONTEXT_IP_TYPE_ENUM::MBIM_CONTEXT_IP_TYPE_IPV4V6:
            return "IPv4v6 dual-stack";
        case CONTEXT_IP_TYPE_ENUM::MBIM_CONTEXT_IP_TYPE_IPV4_AND_IPV6:
            return "IPv4 and IPv6 (two separate contexts)";
        default:
            return "Unknown context IP type";
    }
}

inline std::string map_activation_state(ACTIVATION_STATE_ENUM state) {
    switch (state) {
        case ACTIVATION_STATE_ENUM::MBIM_ACTIVATION_STATE_UNKNOWN:
            return "Connection state unknown";
        case ACTIVATION_STATE_ENUM::MBIM_ACTIVATION_STATE_ACTIVATED:
            return "Activated (connected)";
        case ACTIVATION_STATE_ENUM::MBIM_ACTIVATION_STATE_ACTIVATING:
            return "Activating (connecting)";
        case ACTIVATION_STATE_ENUM::MBIM_ACTIVATION_STATE_DEACTIVATED:
            return "Deactivated (disconnected)";
        case ACTIVATION_STATE_ENUM::MBIM_ACTIVATION_STATE_DEACTIVATING:
            return "Deactivating (disconnecting)";
        default:
            return "Unknown activation state";
    }
}

inline std::string map_voice_call_state(VOICE_CALL_STATE_ENUM state) {
    switch (state) {
        case VOICE_CALL_STATE_ENUM::MBIM_VOICE_CALL_STATE_NONE:
            return "No voice call";
        case VOICE_CALL_STATE_ENUM::MBIM_VOICE_CALL_STATE_IN_PROGRESS:
            return "Voice call in progress";
        case VOICE_CALL_STATE_ENUM::MBIM_VOICE_CALL_STATE_HANG_UP:
            return "Voice call hang-up";
        default:
            return "Unknown voice call state";
    }
}

inline std::string map_sms_storage_state(SMS_STORAGE_STATE_ENUM state) {
    switch (state) {
        case SMS_STORAGE_STATE_ENUM::MBIM_SMS_STORAGE_NOT_INITIALIZED:
            return "SMS storage not initialized";
        case SMS_STORAGE_STATE_ENUM::MBIM_SMS_STORAGE_INITIALIZED:
            return "SMS storage initialized";
        default:
            return "Unknown SMS storage state";
    }
}

inline std::string map_sms_format(SMS_FORMAT_ENUM fmt) {
    switch (fmt) {
        case SMS_FORMAT_ENUM::MBIM_SMS_FORMAT_PDU:
            return "PDU format SMS";
        case SMS_FORMAT_ENUM::MBIM_SMS_FORMAT_CDMA:
            return "CDMA format SMS";
        default:
            return "Unknown SMS format";
    }
}

inline std::string map_network_idle_hint(NETWORK_IDLE_HINT_ENUM hint) {
    switch (hint) {
        case NETWORK_IDLE_HINT_ENUM::MBIM_NETWORK_IDLE_HINT_DISABLED:
            return "Network idle hint disabled";
        case NETWORK_IDLE_HINT_ENUM::MBIM_NETWORK_IDLE_HINT_ENABLED:
            return "Network idle hint enabled";
        default:
            return "Unknown network idle hint state";
    }
}

inline std::string map_emergency_mode(EMERGENCY_MODE_ENUM mode) {
    switch (mode) {
        case EMERGENCY_MODE_ENUM::MBIM_EMERGENCY_MODE_OFF:
            return "Emergency mode off";
        case EMERGENCY_MODE_ENUM::MBIM_EMERGENCY_MODE_ON:
            return "Emergency mode on";
        default:
            return "Unknown emergency mode state";
    }
}

inline std::string map_3gpp_nw_error(MBIM_3GPP_NW_ERROR_ENUM code) {
    switch (code) {
        case MBIM_3GPP_NW_ERROR_ENUM::IMSI_UNKNOWN_IN_HLR:
            return "Either the SIM or the device is not activated, or the subscription has expired, which caused a network deactivation";
        case MBIM_3GPP_NW_ERROR_ENUM::IMSI_UNKNOWN_IN_VLR:
            return "Roaming feature is not subscribed to";
        case MBIM_3GPP_NW_ERROR_ENUM::ILLEGAL_ME:
            return "MS blocked by network due to stolen report";
        case MBIM_3GPP_NW_ERROR_ENUM::GPRS_SERVICES_NOT_ALLOWED:
            return "User does not have a GPRS subscription Only voice connection subscription is allowed";
        case MBIM_3GPP_NW_ERROR_ENUM::GPRS_AND_NON_GPRS_SERVICES_NOT_ALLOWED:
            return "GPRS and non-GPRS services are not allowed";
        case MBIM_3GPP_NW_ERROR_ENUM::PLMN_NOT_ALLOWED:
            return "Service is blocked by the network due to an expired subscription or another cause";
        case MBIM_3GPP_NW_ERROR_ENUM::LOCATION_AREA_NOT_ALLOWED:
            return "User subscription does not allow access in the present location area";
        case MBIM_3GPP_NW_ERROR_ENUM::ROAMING_NOT_ALLOWED_IN_LOCATION_AREA:
            return "Subscription permits roaming but roaming is not allowed in the present location area";
        case MBIM_3GPP_NW_ERROR_ENUM::GPRS_SERVICES_NOT_ALLOWED_IN_PLMN:
            return "Selected network provider does not provide GPRS service to the MS";
        case MBIM_3GPP_NW_ERROR_ENUM::NO_SUITABLE_CELLS_IN_LOCATION_AREA:
            return "No subscription for the service";
        case MBIM_3GPP_NW_ERROR_ENUM::NETWORK_FAILURE:
            return "Registration failed";
        case MBIM_3GPP_NW_ERROR_ENUM::CONGESTION:
            return "Registration failed due to network congestion";
        default:
            return "Unknown 3GPP TS 24.008 network error";
    }
}
