#include <string>
#include <cstdint>
#include <unordered_map>

inline std::string map_basic_connect_cid(uint32_t cid) {
    static const std::unordered_map<uint32_t, std::string> cid_map = {
        { 1,  "MBIM_CID_DEVICE_CAPS - Device capability information" },
        { 2,  "MBIM_CID_SUBSCRIBER_READY_STATUS - SIM and device readiness" },
        { 3,  "MBIM_CID_RADIO_STATE - Radio on/off state" },
        { 4,  "MBIM_CID_PIN - PIN operations" },
        { 5,  "MBIM_CID_PIN_LIST - Supported PIN types" },
        { 6,  "MBIM_CID_HOME_PROVIDER - Home network info" },
        { 7,  "MBIM_CID_PREFERRED_PROVIDERS - Preferred network list" },
        { 8,  "MBIM_CID_VISIBLE_PROVIDERS - Scan visible networks" },
        { 9,  "MBIM_CID_REGISTER_STATE - Network registration status" },
        { 10, "MBIM_CID_PACKET_SERVICE - Packet data service state" },
        { 11, "MBIM_CID_SIGNAL_STATE - Signal strength and quality" },
        { 12, "MBIM_CID_CONNECT - PDP context connect/disconnect" },
        { 13, "MBIM_CID_PROVISIONED_CONTEXTS - List of defined contexts" },
        { 14, "MBIM_CID_SERVICE_ACTIVATION - Subscription activation" },
        { 15, "MBIM_CID_IP_CONFIGURATION - IP settings (IPv4/6)" },
        { 16, "MBIM_CID_DEVICE_SERVICES - Supported device services" },
        { 19, "MBIM_CID_DEVICE_SERVICE_SUBSCRIBE_LIST - Event subscriptions" },
        { 20, "MBIM_CID_PACKET_STATISTICS - Data usage stats" },
        { 21, "MBIM_CID_NETWORK_IDLE_HINT - Power save hint" },
        { 22, "MBIM_CID_EMERGENCY_MODE - Emergency mode status" },
        { 23, "MBIM_CID_IP_PACKET_FILTERS - Packet filter rules" },
        { 24, "MBIM_CID_MULTICARRIER_PROVIDERS - Available carrier list" }
    };

    auto it = cid_map.find(cid);
    if (it != cid_map.end())
        return it->second;
    return "Unknown BASIC_CONNECT CID";
}

inline std::string map_sms_cid(uint32_t cid) {
    static const std::unordered_map<uint32_t, std::string> cid_map = {
        { 1, "MBIM_CID_SMS_CONFIGURATION - SMS format/settings" },
        { 2, "MBIM_CID_SMS_READ - Read SMS messages" },
        { 3, "MBIM_CID_SMS_SEND - Send SMS message" },
        { 4, "MBIM_CID_SMS_DELETE - Delete SMS message" },
        { 5, "MBIM_CID_SMS_MESSAGE_STORE_STATUS - Storage usage info" }
    };

    auto it = cid_map.find(cid);
    if (it != cid_map.end())
        return it->second;
    return "Unknown SMS CID";
}

inline std::string map_ussd_cid(uint32_t cid) {
    static const std::unordered_map<uint32_t, std::string> cid_map = {
        { 1, "MBIM_CID_USSD - USSD session handling" }
    };

    auto it = cid_map.find(cid);
    if (it != cid_map.end())
        return it->second;
    return "Unknown USSD CID";
}

inline std::string map_phonebook_cid(uint32_t cid) {
    static const std::unordered_map<uint32_t, std::string> cid_map = {
        { 1, "MBIM_CID_PHONEBOOK_CONFIGURATION - Phonebook storage info" },
        { 2, "MBIM_CID_PHONEBOOK_READ - Read phonebook entries" },
        { 3, "MBIM_CID_PHONEBOOK_DELETE - Delete phonebook entries" },
        { 4, "MBIM_CID_PHONEBOOK_WRITE - Write phonebook entries" }
    };

    auto it = cid_map.find(cid);
    if (it != cid_map.end())
        return it->second;
    return "Unknown PHONEBOOK CID";
}

inline std::string map_stk_cid(uint32_t cid) {
    static const std::unordered_map<uint32_t, std::string> cid_map = {
        { 1, "MBIM_CID_STK_PAC - Proactive command from SIM" },
        { 2, "MBIM_CID_STK_TERMINAL_RESPONSE - Terminal response to SIM" },
        { 3, "MBIM_CID_STK_ENVELOPE - Event report to SIM" }
    };

    auto it = cid_map.find(cid);
    if (it != cid_map.end())
        return it->second;
    return "Unknown STK CID";
}

inline std::string map_auth_cid(uint32_t cid) {
    static const std::unordered_map<uint32_t, std::string> cid_map = {
        { 1, "MBIM_CID_AKA_AUTH - 3G AKA authentication" },
        { 2, "MBIM_CID_AKAP_AUTH - 3G AKA' authentication" },
        { 3, "MBIM_CID_SIM_AUTH - SIM-based authentication" }
    };

    auto it = cid_map.find(cid);
    if (it != cid_map.end())
        return it->second;
    return "Unknown AUTH CID";
}

inline std::string map_dss_cid(uint32_t cid) {
    static const std::unordered_map<uint32_t, std::string> cid_map = {
        { 1, "MBIM_CID_DSS_CONNECT - Enable/disable out-of-band data" }
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