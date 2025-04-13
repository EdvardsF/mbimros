#include "hex_stream.h"
#include <stdexcept>  // for std::invalid_argument
#include <string>     // for std::stoul

hexStream::hexStream(std::string& hex_data) {
    buffer = hex_data;
}

uint8_t hexStream::readByte() {
    if (!m_isEnoughSize(1))
        throw std::invalid_argument("Hex buffer too short.");

    std::string byte_str = buffer.substr(0, 2);
    buffer.erase(0, 2);
    bufferSize--;
    return static_cast<uint8_t>(std::stoul(byte_str, nullptr, 16));
}

uint32_t hexStream::read4_le() {
    uint8_t b0 = readByte();
    uint8_t b1 = readByte();
    uint8_t b2 = readByte();
    uint8_t b3 = readByte();

    return (b3 << 24) | (b2 << 16) | (b1 << 8) | b0;
}

uint32_t hexStream::read4_be() {
    uint32_t result = 0;
    for (int i = 0; i < 4; ++i) {
        result = (result << 8) | readByte();
    }
    return result;
}

size_t hexStream::m_getBufferSize() {
    return buffer.size() / 2;
}

bool hexStream::m_isEnoughSize(size_t size) {
    return size <= m_getBufferSize();
}
