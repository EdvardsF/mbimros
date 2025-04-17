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
    std::string readByteText();
    uint32_t read4_le();
    uint32_t read4_be();
    std::string read4_text_le();
    std::string read4_text_be();
    std::string read_n_text_be(size_t n);
    std::u16string read_utf16le(size_t num_code_units);
    std::string readAll();

    size_t currentOffset() const;
    void seek(size_t newOffset);

private:
    size_t m_getBufferSize() const;
    bool m_isEnoughSize(size_t size) const;
};
