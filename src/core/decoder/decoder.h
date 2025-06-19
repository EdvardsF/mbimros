#pragma once

#include <memory>
#include <string>
#include "../serialization/serializable.h"
#include "../hex/hex_stream.h"

class Decoder {
public:
    explicit Decoder(std::string hex_data);
    void decodeRaw();

    std::string to_string() const;
    
    std::unique_ptr<Serializable> decodedMessage;

private:
    hexStream hs;
};
