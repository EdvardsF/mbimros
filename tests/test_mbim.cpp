#define CATCH_CONFIG_MAIN
#include "catch.h"

#include "../src/mbim_decoder.h"
#include "../src/hex_stream.h"

TEST_CASE("MBIM_MESSAGE_HEADER parses fields correctly") {
    std::string hex_data = "010000003400000015000000";
    hexStream hs(hex_data);

    MBIM_MESSAGE_HEADER msg(hs);

    REQUIRE(msg.MESSAGE_TYPE.value == MESSAGE_TYPE_ENUM::MBIM_OPEN_MSG);
    REQUIRE(msg.MESSAGE_LENGTH.value == 52);
    REQUIRE(msg.TRANSACTION_ID.value == 21);
}

TEST_CASE("MBIM_FRAGMENT_HEADER parses fields correctly") {
    std::string hex_data = "0100000000000000";
    hexStream hs(hex_data);

    MBIM_FRAGMENT_HEADER msg(hs);

    REQUIRE(msg.TOTAL_FRAGMENTS.value == 1);
    REQUIRE(msg.CURRENT_FRAGMENT.value == 0);
}

TEST_CASE("MBIM_OPEN_MSG parses fields correctly") {
    std::string msg_header = "000000000000000000000000";
    std::string payload = "50000000";
    std::string to_test = msg_header + payload;
    hexStream hs(to_test);

    MBIM_OPEN_MSG msg(hs);

    REQUIRE(msg.MAX_CONTROL_TRANSFER.value == 80);
}

TEST_CASE("MBIM_CLOSE_MSG parses fields correctly") {
    std::string msg_header = "020000000000000000000000";
    hexStream hs(msg_header);

    MBIM_CLOSE_MSG msg(hs);

    REQUIRE(msg.MESSAGE_HEADER.MESSAGE_TYPE.value == MESSAGE_TYPE_ENUM::MBIM_CLOSE_MSG);
}