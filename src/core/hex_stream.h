#pragma once

#include <string>
#include <cstdint>
#include <stdexcept>

struct hexStream {
    std::string buffer;
    size_t bufferSize;

    hexStream(std::string& hex_data);

    uint8_t readByte();
    std::string readByteText();
    uint32_t read4_le();
    uint32_t read4_be();
    std::string read4_text_le();
    std::string read4_text_be();
    std::string read_n_text_be(size_t n);
    std::string readAll();

private:
    size_t m_getBufferSize();
    bool m_isEnoughSize(size_t size);
};
