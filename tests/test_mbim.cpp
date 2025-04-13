#define CATCH_CONFIG_MAIN
#include "catch.hpp"

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
