#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "../../protocol/v1/enums.h"
#include "construction_field.h"

class MbimEncoder {
public:
    static std::string encode(
        MESSAGE_TYPE_ENUM type,
        const std::string& deviceServiceIdHex = "",
        uint32_t cid = 0,
        uint32_t commandType = 0,
        const std::vector<ConstructionField>& fields = {}
    );
};
