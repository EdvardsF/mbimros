#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "../../protocol/v1/enums.h"
#include "construction_field.h"

std::string constructMessageHeader(MESSAGE_TYPE_ENUM type, size_t length, size_t transaction_id);
std::string constructFragmentHeader(size_t total, size_t current);

namespace Encoder {
    constexpr uint32_t EMPTY_ARG = 0;

    template <typename TOpt, typename TCid, typename TCmd>
    std::string encode(
        MESSAGE_TYPE_ENUM type,
        TOpt optionalValue,
        const std::string& deviceServiceIdHex,
        TCid cid,
        TCmd commandType,
        const std::vector<ConstructionField>& fields
    )
    {
        static_assert(std::is_enum_v<TOpt> || std::is_integral_v<TOpt>, "optionalValue must be integral or enum");
        static_assert(std::is_enum_v<TCid> || std::is_integral_v<TCid>, "cid must be integral or enum");
        static_assert(std::is_enum_v<TCmd> || std::is_integral_v<TCmd>, "commandType must be integral or enum");

        std::string hex;
        bool needsFragment = (
            type == MESSAGE_TYPE_ENUM::MBIM_COMMAND_MSG ||
            type == MESSAGE_TYPE_ENUM::MBIM_COMMAND_DONE ||
            type == MESSAGE_TYPE_ENUM::MBIM_INDICATE_STATUS_MSG
        );

        size_t headerSize = 12;
        size_t fragmentSize = needsFragment ? 8 : 0;
        std::string fieldsHex;

        if (type == MESSAGE_TYPE_ENUM::MBIM_OPEN_MSG) {
            fieldsHex += toHexLE(static_cast<uint32_t>(optionalValue));
        } 
        else if (type == MESSAGE_TYPE_ENUM::MBIM_COMMAND_MSG || 
                type == MESSAGE_TYPE_ENUM::MBIM_COMMAND_DONE ||
                type == MESSAGE_TYPE_ENUM::MBIM_INDICATE_STATUS_MSG) 
        {
            fieldsHex += deviceServiceIdHex;
            fieldsHex += toHexLE(static_cast<uint32_t>(cid));
            if (type == MESSAGE_TYPE_ENUM::MBIM_COMMAND_MSG ||
                type == MESSAGE_TYPE_ENUM::MBIM_COMMAND_DONE)
            {
                fieldsHex += toHexLE(static_cast<uint32_t>(commandType));
            }
            fieldsHex += "00000000"; // placeholder for info buffer length
        }
        else if (type == MESSAGE_TYPE_ENUM::MBIM_HOST_ERROR_MSG) {
            fieldsHex += toHexLE(static_cast<uint32_t>(optionalValue));
        }
        else if (type == MESSAGE_TYPE_ENUM::MBIM_OPEN_DONE ||
                type == MESSAGE_TYPE_ENUM::MBIM_CLOSE_DONE) {
            fieldsHex += toHexLE(static_cast<uint32_t>(optionalValue));
        }

        
        // Clear and re-register fields
        ConstructionField::clear();
        for (const auto& f : fields) {
            ConstructionField::allFields.push_back(const_cast<ConstructionField*>(&f));
        }

        CompiledBuffer compiled = compileFields();
        std::string infoBuffer = compiled.infoBufferHex;
        std::string dataBuffer = compiled.dataBufferHex;

        size_t staticFieldsSize = fieldsHex.length() / 2;
        size_t payloadSize = infoBuffer.length() / 2 + dataBuffer.length() / 2;

        // Patch INFORMATION_BUFFER_LENGTH
        if (type == MESSAGE_TYPE_ENUM::MBIM_COMMAND_MSG ||
            type == MESSAGE_TYPE_ENUM::MBIM_COMMAND_DONE ||
            type == MESSAGE_TYPE_ENUM::MBIM_INDICATE_STATUS_MSG) 
        {
            size_t infoLen = payloadSize;
            std::string patchedLength = toHexLE(static_cast<uint32_t>(infoLen));

            size_t patchOffset = (type == MESSAGE_TYPE_ENUM::MBIM_INDICATE_STATUS_MSG) ? 8 : 16;
            size_t patchPosition = deviceServiceIdHex.length() + patchOffset;
            fieldsHex.replace(patchPosition, 8, patchedLength);
        }

        size_t totalSize = headerSize + fragmentSize + staticFieldsSize + payloadSize;

        if (totalSize % 4 != 0) {
            size_t pad = 4 - (totalSize % 4);
            for (size_t i = 0; i < pad; ++i) {
                dataBuffer += "00";
            }
            totalSize += pad;
        }

        hex += constructMessageHeader(type, totalSize, 0);

        if (needsFragment) {
            hex += constructFragmentHeader(1, 0);
        }

        hex += fieldsHex;
        hex += infoBuffer;
        hex += dataBuffer;

        return hex;
    }

    template <typename TOpt>
    std::string encode(MESSAGE_TYPE_ENUM type, TOpt optionalValue) {
        return encode<TOpt, uint32_t, uint32_t>(
            type,
            optionalValue,
            "",          // UUID (not needed)
            EMPTY_ARG,   // CID (not needed)
            EMPTY_ARG,   // Command type (not needed)
            {}           // No fields
        );
    }
}
