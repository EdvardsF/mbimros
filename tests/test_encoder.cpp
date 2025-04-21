#include "../external/catch.h"
#include "../src/core/encoder/encoder.h"


std::string removePadding(const std::string& hex) {
    size_t pos = hex.find_last_not_of('0');
    if (pos != std::string::npos)
        return hex.substr(0, pos + 1);
    return hex;
}

TEST_CASE("ConstructionField creates correct Information and Data Buffers", "[ConstructionField]") {
    ConstructionField::clear();

    ConstructionField f1(0x11223344);                  
    ConstructionField f2("TEST");                      
    ConstructionField f3(std::vector<std::string>{"A", "BB", "CCC"});  

    auto compiled = compileFields();

    SECTION("Info Buffer correctness") {
        
        REQUIRE(compiled.infoBufferHex.length() > 0);
        REQUIRE(compiled.infoBufferHex.find("44332211") != std::string::npos); 

        REQUIRE(compiled.infoBufferHex.find("03000000") != std::string::npos); 
    }

    SECTION("Data Buffer correctness") {
        
        REQUIRE(compiled.dataBufferHex.find("5400450053005400") != std::string::npos); 

        REQUIRE(compiled.dataBufferHex.find("4100") != std::string::npos);  
        REQUIRE(compiled.dataBufferHex.find("42004200") != std::string::npos); 
        REQUIRE(compiled.dataBufferHex.find("430043004300") != std::string::npos); 
    }
}

TEST_CASE("MbimEncoder encodes basic message", "[MbimEncoder]") {
    std::vector<ConstructionField> bufferFields = {
        ConstructionField(0x1234),
        ConstructionField("DATA"),
        ConstructionField(std::vector<std::string>{"ONE", "TWO"})
    };

    std::string uuid = "a289cc33bcbb8b4fb6b0133ec2aae6df";

    std::string hex = MbimEncoder::encode(
        MESSAGE_TYPE_ENUM::MBIM_COMMAND_MSG,
        uuid,
        2,
        0,
        bufferFields
    );

    SECTION("Message header presence") {
        REQUIRE(hex.substr(0, 8) == "03000000"); 
    }

    SECTION("UUID correctly inserted") {
        REQUIRE(hex.find(uuid) != std::string::npos);
    }

    SECTION("INFORMATION_BUFFER_LENGTH correctly patched") {
        size_t infoLenFieldPos = uuid.length() + 16;
        std::string infoLenHex = hex.substr(infoLenFieldPos, 8);
        REQUIRE(infoLenHex != "00000000"); 
    }

    SECTION("Information and Data buffer merged") {
        REQUIRE(hex.find("4400341200") == std::string::npos); 
    }
}

TEST_CASE("Padding works correctly for DataBuffer fields", "[Padding]") {
    ConstructionField::clear();

    ConstructionField shortStr("X");    
    ConstructionField mediumStr("XYZ"); 

    auto compiled = compileFields();

    SECTION("Padding added to align to 4 bytes") {
        REQUIRE(compiled.dataBufferHex.length() % 8 == 0); 
    }
}

TEST_CASE("Offsets are calculated relative to InformationBuffer start", "[Offsets]") {
    ConstructionField::clear();

    ConstructionField num1(1);
    ConstructionField text1("AAAA");
    ConstructionField text2("BBBB");

    auto compiled = compileFields();

    size_t offset1 = static_cast<size_t>(std::stoul(compiled.infoBufferHex.substr(8, 8), nullptr, 16));
    size_t offset2 = static_cast<size_t>(std::stoul(compiled.infoBufferHex.substr(24, 8), nullptr, 16));

    SECTION("Offsets non-overlapping") {
        REQUIRE(offset2 > offset1);
    }
}

TEST_CASE("constructMessageHeader generates correct header", "[Encoder][MessageHeader]") {
    SECTION("Typical values") {
        std::string result = constructMessageHeader(
            MESSAGE_TYPE_ENUM::MBIM_COMMAND_MSG, // Type: 3
            128,                                // Length
            0xAABBCCDD                           // Transaction ID
        );

        // Should be:
        // 03 00 00 00 (type)
        // 80 00 00 00 (length)
        // DD CC BB AA (transaction id)
        REQUIRE(result == "0300000080000000DDCCBBAA");
    }

    SECTION("Zero transaction id") {
        std::string result = constructMessageHeader(
            MESSAGE_TYPE_ENUM::MBIM_OPEN_MSG, // Type: 1
            64,
            0
        );

        REQUIRE(result == "010000004000000000000000");
    }
}

TEST_CASE("constructFragmentHeader generates correct fragment", "[Encoder][FragmentHeader]") {
    SECTION("Single fragment") {
        std::string result = constructFragmentHeader(1, 0);

        // Should be:
        // 01 00 00 00 (total)
        // 00 00 00 00 (current)
        REQUIRE(result == "0100000000000000");
    }

    SECTION("Multi fragment") {
        std::string result = constructFragmentHeader(2, 1);

        // Should be:
        // 02 00 00 00 (total)
        // 01 00 00 00 (current)
        REQUIRE(result == "0200000001000000");
    }
}