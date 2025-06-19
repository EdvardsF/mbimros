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