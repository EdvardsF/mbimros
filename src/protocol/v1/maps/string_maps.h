#pragma once

#include <string>
#include <unordered_map>

inline const std::string& map_uuid(const std::string& input) {
    static const std::unordered_map<std::string, std::string> uuid_to_name = {
        { "a289cc33bcbb8b4fb6b0133ec2aae6df", "UUID_BASIC_CONNECT" },
        { "533fbeeb14fe44679f9033a223e56c3f", "UUID_SMS" },
        { "e550a0c85e82479e82f710abf4c3351f", "UUID_USSD" },
        { "4bf384761e6a41dbb1d8bed289c25bdb", "UUID_PHONEBOOK" },
        { "d8f20131fcb54e178602d6ed3816164c", "UUID_STK" },
        { "1d2b5ff70aa148b2aa5250f15767174e", "UUID_AUTH" },
        { "c08a26dd7718438284826e0d583c4d0e", "UUID_DSS" }
    };

    static const std::unordered_map<std::string, std::string> name_to_uuid = {
        { "UUID_BASIC_CONNECT", "a289cc33bcbb8b4fb6b0133ec2aae6df" },
        { "UUID_SMS",            "533fbeeb14fe44679f9033a223e56c3f" },
        { "UUID_USSD",           "e550a0c85e82479e82f710abf4c3351f" },
        { "UUID_PHONEBOOK",      "4bf384761e6a41dbb1d8bed289c25bdb" },
        { "UUID_STK",            "d8f20131fcb54e178602d6ed3816164c" },
        { "UUID_AUTH",           "1d2b5ff70aa148b2aa5250f15767174e" },
        { "UUID_DSS",            "c08a26dd7718438284826e0d583c4d0e" }
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

