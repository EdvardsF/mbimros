#pragma once

#include <memory>
#include <string>
#include "../serialization/serializable.h"
#include "../hex/hex_stream.h"

class Decoder {
public:
    explicit Decoder(std::string hex_data, std::ostream& errorOutput = std::cerr);

    void decodeRaw();

    std::string to_string() const;

private:
    hexStream hs;
    std::ostream& errorStream;
    std::unique_ptr<Serializable> decodedMessage;
};
