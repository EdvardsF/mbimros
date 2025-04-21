#include "../external/catch.h"
#include "../src/helpers/hex_helpers.h"

TEST_CASE("toHexLE converts uint32_t to little-endian hex string", "[hexHelper]") {
    REQUIRE(toHexLE(0x12345678) == "78563412");
    REQUIRE(toHexLE(0x00000000) == "00000000");
    REQUIRE(toHexLE(0xFFFFFFFF) == "FFFFFFFF");
    REQUIRE(toHexLE(0xAABBCCDD) == "DDCCBBAA");
}

TEST_CASE("stringToUtf16LeAligned converts string to UTF-16 LE hex string and aligns to 4 bytes", "[hexHelper]") {
    SECTION("String of even length that is already 4-byte aligned") {
        REQUIRE(stringToUtf16LeAligned("AB") == "41004200");
    }
    SECTION("String of odd length needs padding") {
        REQUIRE(stringToUtf16LeAligned("A") == "41000000");
        REQUIRE(stringToUtf16LeAligned("ABC") == "4100420043000000");
    }
    SECTION("Empty string returns empty string") {
        REQUIRE(stringToUtf16LeAligned("") == "");
    }
}

TEST_CASE("getHexStringByteLength calculates byte length of hex string", "[hexHelper]") {
    REQUIRE(getHexStringByteLength("AABB") == 2);
    REQUIRE(getHexStringByteLength("AABBCCDD") == 4);
    REQUIRE(getHexStringByteLength("") == 0);
    REQUIRE(getHexStringByteLength("00") == 1);
    REQUIRE(getHexStringByteLength("0011223344556677") == 8);
}
