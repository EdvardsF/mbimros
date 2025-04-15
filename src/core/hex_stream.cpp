#include "hex_stream.h"
#include <stdexcept>  // for std::invalid_argument
#include <string>     // for std::stoul

// TODO: fix naming scheme

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

std::string hexStream::readByteText() {
    if (!m_isEnoughSize(1))
        throw std::invalid_argument("Hex buffer too short.");

    std::string byte_str = buffer.substr(0, 2);
    buffer.erase(0, 2);
    bufferSize--;
    return byte_str;
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

std::string hexStream::read4_text_le() {
    std::string b0 = readByteText();
    std::string b1 = readByteText();
    std::string b2 = readByteText();
    std::string b3 = readByteText();

    return b3 + b2 + b1 + b0;
}

std::string hexStream::read4_text_be() {
    std::string result;
    for (size_t i = 0; i < 3; i++) {
        result += readByteText();
    }
    return result;
}

std::string hexStream::readAll() {
    bufferSize = 0;
    return buffer;
}

std::string hexStream::read_n_text_be(size_t n) {
    std::string result;
    for (int i = 0; i < n; i++) {
        result += readByteText();
    }
    return result;
}

size_t hexStream::m_getBufferSize() {
    return buffer.size() / 2;
}

bool hexStream::m_isEnoughSize(size_t size) {
    return size <= m_getBufferSize();
}
