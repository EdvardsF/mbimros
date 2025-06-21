#pragma once

#include <string>
#include <unordered_map>

using namespace MBIM_CMD;

inline const std::string& map_uuid(const std::string& input) {
    static const std::unordered_map<std::string, std::string> uuid_to_name = {
        { UUID_BASIC_CONNECT::UUID, "UUID_BASIC_CONNECT" },
        { UUID_SMS::UUID,           "UUID_SMS" },
        { UUID_USSD::UUID,          "UUID_USSD" },
        { UUID_PHONEBOOK::UUID,     "UUID_PHONEBOOK" },
        { UUID_STK::UUID,           "UUID_STK" },
        { UUID_AUTH::UUID,          "UUID_AUTH" },
        { UUID_DSS::UUID,           "UUID_DSS" }
    };

    static const std::unordered_map<std::string, std::string> name_to_uuid = {
        { "UUID_BASIC_CONNECT", UUID_BASIC_CONNECT::UUID },
        { "UUID_SMS",           UUID_SMS::UUID },
        { "UUID_USSD",          UUID_USSD::UUID },
        { "UUID_PHONEBOOK",     UUID_PHONEBOOK::UUID },
        { "UUID_STK",           UUID_STK::UUID },
        { "UUID_AUTH",          UUID_AUTH::UUID },
        { "UUID_DSS",           UUID_DSS::UUID }
    };

    auto it1 = uuid_to_name.find(input);
    if (it1 != uuid_to_name.end())
        return it1->second;

    auto it2 = name_to_uuid.find(input);
    if (it2 != name_to_uuid.end())
        return it2->second;

    static const std::string unknown = "Unknown";
    return unknown;
}

inline const std::string& map_context_uuid(const std::string& input) {
    static const std::unordered_map<std::string, std::string> uuid_to_context = {
        { "b43f758ca5604b46b35ec5e89641fb54", "MBIMContextTypeNone - not provisioned" },
        { "7e5e2a7e46ef7272736b656e7e5e2a7e", "MBIMContextTypeInternet - Internet access (mandatory)" },
        { "9b9f7bbe895244b783acca41318df7a0", "MBIMContextTypeVpn - VPN to corporate network" },
        { "889182940ef443968cca8588fbc02b2", "MBIMContextTypeVoice - Voice over IP service" },
        { "05a2a7167c344b4d9a91c5ef0c7aaacc", "MBIMContextTypeVideoShare - video sharing service" },
        { "b3272496ac6c422ba8c0acf687a72717", "MBIMContextTypePurchase - over-the-air activation" },
        { "21610d0130744bce9425b53a07d697d6", "MBIMContextTypeIMS - IP Multimedia Subsystem" },
        { "4672666472696bc69624d1d35389aca9", "MBIMContextTypeMMS - Multimedia Messaging Service" },
        { "a57a9afcb09f45d7bb40033c39f60db9", "MBIMContextTypeLocal - local connection (not over air)" }
    };

    auto it = uuid_to_context.find(input);
    if (it != uuid_to_context.end())
        return it->second;

    static const std::string unknown = "Unknown";
    return unknown;
}
