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