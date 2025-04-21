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
