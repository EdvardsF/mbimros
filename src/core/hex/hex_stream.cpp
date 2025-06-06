#include "hex_stream.h"
#include <stdexcept>
#include <string>

hexStream::hexStream(std::string& hex_data)
    : buffer(hex_data), offset(0) {
        visited.resize(buffer.size() / 2, false);
    }

uint8_t hexStream::readByte() {
    checkAvailable(1);

    std::string byte_str = buffer.substr(offset * 2, 2);
    visited[offset] = true;
    offset++;

    return static_cast<uint8_t>(std::stoul(byte_str, nullptr, 16));
}

std::string hexStream::readByteAsHex() {
    checkAvailable(1);

    std::string byte_str = buffer.substr(offset * 2, 2);
    offset++;
    return byte_str;
}

uint32_t hexStream::readUint32LE() {
    uint8_t b0 = readByte();
    uint8_t b1 = readByte();
    uint8_t b2 = readByte();
    uint8_t b3 = readByte();

    return (static_cast<uint32_t>(b3) << 24) |
           (static_cast<uint32_t>(b2) << 16) |
           (static_cast<uint32_t>(b1) << 8)  |
           (static_cast<uint32_t>(b0));
}

uint32_t hexStream::readUint32BE() {
    uint32_t result = 0;
    for (int i = 0; i < 4; ++i) {
        result = (result << 8) | readByte();
    }
    return result;
}

std::string hexStream::readUint32HexLE() {
    std::string b0 = readByteAsHex();
    std::string b1 = readByteAsHex();
    std::string b2 = readByteAsHex();
    std::string b3 = readByteAsHex();

    return b3 + b2 + b1 + b0;
}

std::string hexStream::readUint32HexBE() {
    std::string result;
    for (int i = 0; i < 4; ++i) {
        result += readByteAsHex();
    }
    return result;
}

std::u16string hexStream::readUtf16LE(size_t numCodeUnits) {
    std::u16string result;
    result.reserve(numCodeUnits);

    for (size_t i = 0; i < numCodeUnits; ++i) {
        checkAvailable(2);

        uint8_t low = readByte();
        uint8_t high = readByte();
        result.push_back(static_cast<char16_t>((high << 8) | low));
    }
    return result;
}

std::string hexStream::readHexBytes(size_t count) {
    std::string result;
    result.reserve(count * 2);

    for (size_t i = 0; i < count; ++i) {
        result += readByteAsHex();
        visited[offset - 1] = true;
    }
    return result;
}

std::string hexStream::readRemaining() {
    std::string remaining = buffer.substr(offset * 2);

    while (offset < buffer.size() / 2) {
        visited[offset] = true;
        ++offset;
    }

    return remaining;
}

size_t hexStream::currentOffset() const {
    return offset;
}

void hexStream::seek(size_t newOffset) {
    size_t maxOffset = buffer.size() / 2;
    if (newOffset > maxOffset) {
        throw InvalidOffsetException(
            "Tried to seek to offset " + std::to_string(newOffset) +
            ", but maximum allowed offset is " + std::to_string(maxOffset) + "."
        );
    }
    offset = newOffset;
}

size_t hexStream::totalBufferSize() {
    return buffer.size() / 2;
}

bool hexStream::isAlignedAt4Bytes() {
    if (buffer.size() % 2 != 0) {
        throw InvalidByteAlignment("hex buffer must have an even number of characters (full bytes required), got: " + std::to_string(buffer.size()) + " characters.");
    }
    return buffer.size() % 8 == 0;
}


size_t hexStream::availableBytes() const {
    return (buffer.size() / 2) - offset;
}

void hexStream::checkAvailable(size_t count) const {
    if (count > availableBytes()) {
        throw BufferTooShortException(
            "Requested " + std::to_string(count) + 
            " bytes, but only " + std::to_string(availableBytes()) + " available."
        );
    }
}

size_t hexStream::unparsedByteCount() const {
    size_t count = 0;
    for (bool v : visited) {
        if (!v) {
            count++;
        }
    }
    return count;
}

