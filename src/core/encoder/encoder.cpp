#include <iomanip>

#include "encoder.h"
#include "../../helpers/hex_helpers.h"


std::string constructMessageHeader(MESSAGE_TYPE_ENUM type, size_t length, size_t transaction_id) {
    std::string result;
    result += toHexLE(static_cast<uint32_t>(type));
    result += toHexLE(static_cast<uint32_t>(length));
    result += toHexLE(static_cast<uint32_t>(transaction_id));
    return result;
}

std::string constructFragmentHeader(size_t total, size_t current) {
    std::string result;
    result += toHexLE(static_cast<uint32_t>(total));
    result += toHexLE(static_cast<uint32_t>(current));
    return result;
}

std::string MbimEncoder::encode(
    MESSAGE_TYPE_ENUM type,
    const std::string& deviceServiceIdHex,
    uint32_t cid,
    uint32_t commandType,
    const std::vector<ConstructionField>& fields
) {
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
        fieldsHex += toHexLE(0);
    } 
    else if (type == MESSAGE_TYPE_ENUM::MBIM_COMMAND_MSG || 
             type == MESSAGE_TYPE_ENUM::MBIM_COMMAND_DONE ||
             type == MESSAGE_TYPE_ENUM::MBIM_INDICATE_STATUS_MSG) 
    {
        fieldsHex += deviceServiceIdHex;
        fieldsHex += toHexLE(cid);
        if (type == MESSAGE_TYPE_ENUM::MBIM_COMMAND_MSG) {
            fieldsHex += toHexLE(commandType);
        } else {
            std:: cout << "\n1. \nAAAAAA\n\n" << fieldsHex << " END";
            fieldsHex += toHexLE(0);
            std:: cout << "\n2. \nAAAAAA\n\n" << fieldsHex << " END";
        }
        fieldsHex += "00000000"; // placeholder for INFORMATION_BUFFER_LENGTH
        std:: cout << "\n3. \nAAAAAA\n\n" << fieldsHex << " END";
    }
    else if (type == MESSAGE_TYPE_ENUM::MBIM_HOST_ERROR_MSG) {
        fieldsHex += toHexLE(0);
    }
    else if (type == MESSAGE_TYPE_ENUM::MBIM_OPEN_DONE ||
             type == MESSAGE_TYPE_ENUM::MBIM_CLOSE_DONE) {
        fieldsHex += toHexLE(0);
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

        size_t patchPosition = deviceServiceIdHex.length() + 16;
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
