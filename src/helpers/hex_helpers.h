#pragma once

#include <string>
#include <cstdint>

std::string toHexLE(uint32_t value);
std::string stringToUtf16LeAligned(const std::string& input);
std::string stringToUtf16BeAligned(const std::string& input);
size_t getHexStringByteLength(const std::string& hexString);
