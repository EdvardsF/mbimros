#include <iostream>
#include <string>
#include <variant>

#include "core/decoder/decoder.h"
#include "core/encoder/encoder.h"
#include "protocol/v1/enums.h"
#include "core/encoder/construction_field.h"



int main() {
    //std::string hex = "0700008034000000000000000100000000000000a289cc33bcbb8b4fb6b0133ec2aae6df03000000080000000100000000000000";
    // std::vector<ConstructionField> bufferFields = {
    //     ConstructionField(0),                           // Numeric
    //     ConstructionField("3101501234567898"),
    //     ConstructionField("90141032111181510720"),
    //     ConstructionField(1), 
    //     ConstructionField(std::vector<std::string>{"123", "456", "789"}) // List of OLs
    // };

    // std::string hexMessage = Encoder::encode(
    //     MESSAGE_TYPE_ENUM::MBIM_COMMAND_DONE,
    //     Encoder::EMPTY_ARG,
    //     "a289cc33bcbb8b4fb6b0133ec2aae6df",  // UUID
    //     2,                                   // CID
    //     0,                                   // succeeded
    //     bufferFields
    // );

    // std::cout << "\n\nHEX: " << hexMessage << " END\n";

    std::vector<ConstructionField> bufferFields = {
        ConstructionField(1),
        ConstructionField(2),
        ConstructionField(3),
        ConstructionField(4),
        ConstructionField(5),
        ConstructionField("id"),
        ConstructionField("name"),
        ConstructionField("roaming"),
        ConstructionField(6),
    };

    std::string hexMessage = Encoder::encode(
        MESSAGE_TYPE_ENUM::MBIM_COMMAND_DONE,
        Encoder::EMPTY_ARG,
        "a289cc33bcbb8b4fb6b0133ec2aae6df",  // UUID
        MBIM_CMD::UUID_BASIC_CONNECT::MBIM_CID_REGISTER_STATE,
        0,                                   // quey/set/status
        bufferFields
    );

    std::cout << "\n\nHEX: " << hexMessage << " END\n";
    
    Decoder decoder(hexMessage);
    decoder.decodeRaw();
    std::cout << decoder.to_string() << "\n";
}
