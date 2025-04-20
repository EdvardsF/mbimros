#include "../external/catch.h"

#include "../src/core/exception/mbim_errors.h"
#include "../src/core/hex/hex_stream.h"

TEST_CASE("hexStream basic operations", "[hexStream]") {
    std::string hexData = "01020304AABBCCDD1122";
    hexStream hs(hexData);

    SECTION("readByte reads correctly") {
        REQUIRE(hs.readByte() == 0x01);
        REQUIRE(hs.readByte() == 0x02);
        REQUIRE(hs.readByte() == 0x03);
        REQUIRE(hs.readByte() == 0x04);
    }

    SECTION("readByteAsHex reads correctly") {
        REQUIRE(hs.readByteAsHex() == "01");
        REQUIRE(hs.readByteAsHex() == "02");
        REQUIRE(hs.readByteAsHex() == "03");
        REQUIRE(hs.readByteAsHex() == "04");
    }

    SECTION("readUint32LE reads little-endian correctly") {
        REQUIRE(hs.readUint32LE() == 0x04030201);
    }

    SECTION("readUint32BE reads big-endian correctly") {
        REQUIRE(hs.readUint32BE() == 0x01020304);
    }

    SECTION("readUint32HexLE reads hex little-endian correctly") {
        REQUIRE(hs.readUint32HexLE() == "04030201");
    }

    SECTION("readUint32HexBE reads hex big-endian correctly") {
        REQUIRE(hs.readUint32HexBE() == "01020304");
    }
}

TEST_CASE("hexStream utf16le reading", "[hexStream]") {
    // 'A', 'B', 'C' in UTF-16LE
    std::string hexData = "410042004300";  
    hexStream hs(hexData);

    auto result = hs.readUtf16LE(3);
    REQUIRE(result.size() == 3);
    REQUIRE(result[0] == u'A');
    REQUIRE(result[1] == u'B');
    REQUIRE(result[2] == u'C');
}

TEST_CASE("hexStream seek and offset", "[hexStream]") {
    std::string hexData = "DEADBEEF";
    hexStream hs(hexData);

    REQUIRE(hs.currentOffset() == 0);
    hs.seek(2);
    REQUIRE(hs.currentOffset() == 2);

    REQUIRE_THROWS_AS(hs.seek(10), InvalidOffsetException);
}

TEST_CASE("hexStream availableBytes and reading remaining", "[hexStream]") {
    std::string hexData = "11223344";
    hexStream hs(hexData);

    REQUIRE(hs.availableBytes() == 4);

    hs.readByte();
    REQUIRE(hs.availableBytes() == 3);

    std::string remaining = hs.readRemaining();
    REQUIRE(remaining == "223344");
}

TEST_CASE("hexStream exceptions", "[hexStream]") {
    std::string hexData = "AA";
    hexStream hs(hexData);

    REQUIRE(hs.readByte() == 0xAA);

    REQUIRE_THROWS_AS(hs.readByte(), BufferTooShortException);
    REQUIRE_THROWS_AS(hs.readByteAsHex(), BufferTooShortException);
    REQUIRE_THROWS_AS(hs.readUint32LE(), BufferTooShortException);
    REQUIRE_THROWS_AS(hs.readUtf16LE(1), BufferTooShortException);
}