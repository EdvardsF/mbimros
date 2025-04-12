#pragma once

#include <string>
#include <cstdint>
#include <stdexcept>

struct hexStream {
    std::string buffer;
    size_t bufferSize;

    hexStream(std::string& hex_data);

    uint8_t readByte();
    uint32_t read4_le();
    uint32_t read4_be();

private:
    size_t m_getBufferSize();
    bool isEnoughSize(size_t size);
};
