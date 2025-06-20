#pragma once

#include <string>
#include <sstream>
#include <vector>

// For now there is a quick and dirty fix to format bitmap fields correctly, but
// this requires to have this exact format for these functions:
//     1. Flag string separated by "-" with no spcaes
//     2. Returns these values as a string separated with /n with no additional formatting

inline std::string map_cellular_class(uint32_t value) {
    std::vector<std::string> flags;

    if (value & static_cast<uint32_t>(CELLULAR_CLASS_ENUM::MBIM_CELLULAR_CLASS_GSM))
        flags.push_back("[MBIM_CELLULAR_CLASS_GSM]-GSM capable device");
    if (value & static_cast<uint32_t>(CELLULAR_CLASS_ENUM::MBIM_CELLULAR_CLASS_CDMA))
        flags.push_back("[MBIM_CELLULAR_CLASS_CDMA]-CDMA capable device");

    if (flags.empty())
        return "NONE";

    std::ostringstream oss;
    for (const auto& flag : flags) {
        oss << flag << "\n";
    }
    return oss.str();
}

inline std::string map_data_class(uint32_t value) {
    std::vector<std::string> flags;

    if (value & static_cast<uint32_t>(DATA_CLASS_ENUM::MBIM_DATA_CLASS_NONE))
        flags.push_back("[MBIM_DATA_CLASS_NONE]-No data class supported");
    if (value & static_cast<uint32_t>(DATA_CLASS_ENUM::MBIM_DATA_CLASS_GPRS))
        flags.push_back("[MBIM_DATA_CLASS_GPRS]-GPRS supported");
    if (value & static_cast<uint32_t>(DATA_CLASS_ENUM::MBIM_DATA_CLASS_EDGE))
        flags.push_back("[MBIM_DATA_CLASS_EDGE]-EDGE supported");
    if (value & static_cast<uint32_t>(DATA_CLASS_ENUM::MBIM_DATA_CLASS_UMTS))
        flags.push_back("[MBIM_DATA_CLASS_UMTS]-UMTS supported");
    if (value & static_cast<uint32_t>(DATA_CLASS_ENUM::MBIM_DATA_CLASS_HSDPA))
        flags.push_back("[MBIM_DATA_CLASS_HSDPA]-HSDPA supported");
    if (value & static_cast<uint32_t>(DATA_CLASS_ENUM::MBIM_DATA_CLASS_HSUPA))
        flags.push_back("[MBIM_DATA_CLASS_HSUPA]-HSUPA supported");
    if (value & static_cast<uint32_t>(DATA_CLASS_ENUM::MBIM_DATA_CLASS_LTE))
        flags.push_back("[MBIM_DATA_CLASS_LTE]-LTE supported");
    if (value & static_cast<uint32_t>(DATA_CLASS_ENUM::MBIM_DATA_CLASS_1XRTT))
        flags.push_back("[MBIM_DATA_CLASS_1XRTT]-1xRTT supported");
    if (value & static_cast<uint32_t>(DATA_CLASS_ENUM::MBIM_DATA_CLASS_1XEVDO))
        flags.push_back("[MBIM_DATA_CLASS_1XEVDO]-1xEVDO supported");
    if (value & static_cast<uint32_t>(DATA_CLASS_ENUM::MBIM_DATA_CLASS_1XEVDO_REVA))
        flags.push_back("[MBIM_DATA_CLASS_1XEVDO_REVA]-1xEVDO Rev-A supported");
    if (value & static_cast<uint32_t>(DATA_CLASS_ENUM::MBIM_DATA_CLASS_1XEVDO_REVB))
        flags.push_back("[MBIM_DATA_CLASS_1XEVDO_REVB]-1xEVDO Rev-B supported");
    if (value & static_cast<uint32_t>(DATA_CLASS_ENUM::MBIM_DATA_CLASS_UMB))
        flags.push_back("[MBIM_DATA_CLASS_UMB]-UMB supported");
    if (value & static_cast<uint32_t>(DATA_CLASS_ENUM::MBIM_DATA_CLASS_CUSTOM))
        flags.push_back("[MBIM_DATA_CLASS_CUSTOM]-Custom data class");

    if (flags.empty())
        return "NONE";

    std::ostringstream oss;
    for (const auto& flag : flags) {
        oss << flag << "\n";
    }
    return oss.str();
}

inline std::string map_sms_caps(uint32_t value) {
    std::vector<std::string> flags;

    if (value & static_cast<uint32_t>(SMS_CAPS_ENUM::MBIM_SMS_CAPS_PDU_RECEIVE))
        flags.push_back("[MBIM_SMS_CAPS_PDU_RECEIVE]-Can receive SMS in PDU format");
    if (value & static_cast<uint32_t>(SMS_CAPS_ENUM::MBIM_SMS_CAPS_PDU_SEND))
        flags.push_back("[MBIM_SMS_CAPS_PDU_SEND]-Can send SMS in PDU format");
    if (value & static_cast<uint32_t>(SMS_CAPS_ENUM::MBIM_SMS_CAPS_TEXT_RECEIVE))
        flags.push_back("[MBIM_SMS_CAPS_TEXT_RECEIVE]-Can receive SMS in text format");
    if (value & static_cast<uint32_t>(SMS_CAPS_ENUM::MBIM_SMS_CAPS_TEXT_SEND))
        flags.push_back("[MBIM_SMS_CAPS_TEXT_SEND]-Can send SMS in text format");

    if (flags.empty())
        return "NONE";

    std::ostringstream oss;
    for (const auto& flag : flags) {
        oss << flag << "\n";
    }
    return oss.str();
}

inline std::string map_ctrl_caps(uint32_t value) {
    std::vector<std::string> flags;

    if (value & static_cast<uint32_t>(CTRL_CAPS_ENUM::MBIM_CTRL_CAPS_REG_MANUAL))
        flags.push_back("[MBIM_CTRL_CAPS_REG_MANUAL]-Supports manual registration");
    if (value & static_cast<uint32_t>(CTRL_CAPS_ENUM::MBIM_CTRL_CAPS_HW_RADIO_SWITCH))
        flags.push_back("[MBIM_CTRL_CAPS_HW_RADIO_SWITCH]-Hardware radio switch supported");
    if (value & static_cast<uint32_t>(CTRL_CAPS_ENUM::MBIM_CTRL_CAPS_CDMA_MOBILE_IP))
        flags.push_back("[MBIM_CTRL_CAPS_CDMA_MOBILE_IP]-Supports CDMA Mobile IP");
    if (value & static_cast<uint32_t>(CTRL_CAPS_ENUM::MBIM_CTRL_CAPS_CDMA_SIMPLE_IP))
        flags.push_back("[MBIM_CTRL_CAPS_CDMA_SIMPLE_IP]-Supports CDMA Simple IP");
    if (value & static_cast<uint32_t>(CTRL_CAPS_ENUM::MBIM_CTRL_CAPS_MULTI_CARRIER))
        flags.push_back("[MBIM_CTRL_CAPS_MULTI_CARRIER]-Multi-carrier support");

    if (flags.empty())
        return "NONE";

    std::ostringstream oss;
    for (const auto& flag : flags) {
        oss << flag << "\n";
    }
    return oss.str();
}


inline std::string map_provider_state(uint32_t value) {
    std::vector<std::string> flags;

    if (value & static_cast<uint32_t>(MBIM_PROVIDER_STATE_ENUM::MBIM_PROVIDER_STATE_UNKNOWN))
        flags.push_back("[MBIM_PROVIDER_STATE_UNKNOWN]-Network provider state is unknown");
    if (value & static_cast<uint32_t>(MBIM_PROVIDER_STATE_ENUM::MBIM_PROVIDER_STATE_HOME))
        flags.push_back("[MBIM_PROVIDER_STATE_HOME]-Network provider is a home operator");
    if (value & static_cast<uint32_t>(MBIM_PROVIDER_STATE_ENUM::MBIM_PROVIDER_STATE_FORBIDDEN))
        flags.push_back("[MBIM_PROVIDER_STATE_FORBIDDEN]-Network provider is on the blocked list");
    if (value & static_cast<uint32_t>(MBIM_PROVIDER_STATE_ENUM::MBIM_PROVIDER_STATE_PREFERRED))
        flags.push_back("[MBIM_PROVIDER_STATE_PREFERRED]-Network provider is on the preferred list");
    if (value & static_cast<uint32_t>(MBIM_PROVIDER_STATE_ENUM::MBIM_PROVIDER_STATE_VISIBLE))
        flags.push_back("[MBIM_PROVIDER_STATE_VISIBLE]-Network provider is visible");
    if (value & static_cast<uint32_t>(MBIM_PROVIDER_STATE_ENUM::MBIM_PROVIDER_STATE_REGISTERED))
        flags.push_back("[MBIM_PROVIDER_STATE_REGISTERED]-Network provider is currently registered");
    if (value & static_cast<uint32_t>(MBIM_PROVIDER_STATE_ENUM::MBIM_PROVIDER_STATE_PREFERRED_MULTICARRIER))
        flags.push_back("[MBIM_PROVIDER_STATE_PREFERRED_MULTICARRIER]-Preferred multicarrier network provider");

    if (flags.empty())
        return "NONE";

    std::ostringstream oss;
    for (const auto& flag : flags) {
        oss << flag << "\n";
    }
    return oss.str();
}

inline std::string map_registration_flags(uint32_t value) {
    std::vector<std::string> flags;

    if (value & static_cast<uint32_t>(MBIM_REGISTRATION_FLAGS_ENUM::MBIM_REGISTRATION_MANUAL_SELECTION_NOT_AVAILABLE)) {
        flags.push_back("[MBIM_REGISTRATION_MANUAL_SELECTION_NOT_AVAILABLE]-Manual network selection not supported (may vary per cell)");
    }
    if (value & static_cast<uint32_t>(MBIM_REGISTRATION_FLAGS_ENUM::MBIM_REGISTRATION_PACKET_SERVICE_AUTOMATIC_ATTACH)) {
        flags.push_back("[MBIM_REGISTRATION_PACKET_SERVICE_AUTOMATIC_ATTACH]-Will auto-attach to network post registration without host involvement");
    }
    if (value == static_cast<uint32_t>(MBIM_REGISTRATION_FLAGS_ENUM::MBIM_REGISTRATION_NONE)) {
        flags.push_back("[MBIM_REGISTRATION_NONE]-No bits are set");
    }
    if (flags.empty())
        return "UNKNOWN or unsupported registration flags";

    std::ostringstream oss;
    for (const auto& flag : flags)
        oss << flag << "\n";

    return oss.str();
}

