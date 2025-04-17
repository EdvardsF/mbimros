#pragma once

#include <string>
#include <cstdint>
#include <stdexcept>

struct hexStream {
    std::string buffer;
    size_t bufferSize;
    size_t offset;

    hexStream(std::string& hex_data);

    uint8_t readByte();
    std::string readByteAsHex();
    uint32_t readUint32LE();
    uint32_t readUint32BE();
    std::string readUint32HexLE();
    std::string readUint32HexBE();
    std::string readHexBytes(size_t n);
    std::u16string readUtf16LE(size_t num_code_units);
    std::string readRemaining();

    size_t currentOffset() const;
    void seek(size_t newOffset);

private:
    size_t availableBytes() const;
    void checkAvailable(size_t count) const;
};
