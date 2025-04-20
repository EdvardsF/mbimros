#include "hex_helpers.h"
#include <sstream>
#include <iomanip>

std::string toHexLE(uint32_t value) {
    std::ostringstream oss;
    oss << std::setfill('0') << std::hex << std::uppercase;
    for (int i = 0; i < 4; ++i) {
        oss << std::setw(2) << ((value >> (i * 8)) & 0xFF);
    }
    return oss.str();
}

std::string stringToUtf16LeAligned(const std::string& input) {
    std::ostringstream oss;
    oss << std::setfill('0') << std::hex << std::uppercase;
    for (char c : input) {
        uint16_t utf16 = static_cast<uint8_t>(c);
        oss << std::setw(2) << (utf16 & 0xFF);
        oss << std::setw(2) << ((utf16 >> 8) & 0xFF);
    }
    size_t totalBytes = input.size() * 2;
    while (totalBytes % 4 != 0) {
        oss << "0000";
        totalBytes += 2;
    }
    return oss.str();
}

size_t getHexStringByteLength(const std::string& hexString) {
    return hexString.length() / 2;
}
