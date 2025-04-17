#include "hex_stream.h"
#include <stdexcept>
#include <string>

hexStream::hexStream(std::string& hex_data) {
    buffer = hex_data;
    bufferSize = hex_data.size() / 2;
    offset = 0;
}

uint8_t hexStream::readByte() {
    if (!m_isEnoughSize(1))
        throw std::invalid_argument("Hex buffer too short.");

    std::string byte_str = buffer.substr(offset * 2, 2);
    offset++;
    bufferSize--;
    return static_cast<uint8_t>(std::stoul(byte_str, nullptr, 16));
}

std::string hexStream::readByteText() {
    if (!m_isEnoughSize(1))
        throw std::invalid_argument("Hex buffer too short.");

    std::string byte_str = buffer.substr(offset * 2, 2);
    offset++;
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
    for (size_t i = 0; i < 4; ++i) {
        result += readByteText();
    }
    return result;
}

std::u16string hexStream::read_utf16le(size_t num_code_units) {
    std::u16string result;
    for (size_t i = 0; i < num_code_units; ++i) {
        if (!m_isEnoughSize(2))
            throw std::invalid_argument("Hex buffer too short for UTF-16LE");

        uint8_t lo = readByte();
        uint8_t hi = readByte();
        char16_t ch = static_cast<char16_t>((hi << 8) | lo);
        result += ch;
    }
    return result;
}


std::string hexStream::read_n_text_be(size_t n) {
    std::string result;
    for (size_t i = 0; i < n; i++) {
        result += readByteText();
    }
    return result;
}

std::string hexStream::readAll() {
    std::string remaining = buffer.substr(offset * 2);
    bufferSize = 0;
    offset = buffer.size() / 2;
    return remaining;
}

size_t hexStream::currentOffset() const {
    return offset;
}

void hexStream::seek(size_t newOffset) {
    if (newOffset > buffer.size() / 2)
        throw std::out_of_range("hexStream::seek out of bounds");
    offset = newOffset;
}

size_t hexStream::m_getBufferSize() const {
    return (buffer.size() / 2) - offset;
}

bool hexStream::m_isEnoughSize(size_t size) const {
    return size <= m_getBufferSize();
}