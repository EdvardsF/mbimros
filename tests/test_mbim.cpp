#define CATCH_CONFIG_MAIN
#include "catch.h"

#include "core/hex_stream.h"
#include "protocol/messages.h"


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

TEST_CASE("MBIM_COMMAND_MSG parses fields correctly") {
    std::string msg_header = "010000003400000015000000";
    std::string msg_fragment_header = "0100000000000000";
    std::string payload = "a289cc33bcbb8b4fb6b0133ec2aae6df01000000000000000400000011111111";
    std::string to_test = msg_header + msg_fragment_header + payload;
    hexStream hs(to_test);

    MBIM_COMMAND_MSG msg(hs);

    REQUIRE(msg.DEVICE_SERVICE_ID.value == "a289cc33bcbb8b4fb6b0133ec2aae6df");
    REQUIRE(msg.CID.value == 1);
    REQUIRE(msg.COMMAND_TYPE.value == MESSAGE_QUERY_OR_SET_ENUM::QUERY);
    REQUIRE(msg.INFORMATION_BUFFER_LENGTH.value == 4);
    //REQUIRE(msg.INFORMATION_BUFFER. == "11111111");
}

TEST_CASE("MBIM_HOST_ERROR_MSG parses fields correctly") {
    std::string msg_header = "010000003400000015000000";
    std::string payload = "03000000";
    std::string to_test = msg_header + payload;
    hexStream hs(to_test);

    MBIM_HOST_ERROR_MSG msg(hs);

    REQUIRE(msg.ERROR_STATUS_CODE.value == MBIM_PROTOCOL_ERROR_CODES_ENUM::MBIM_ERROR_LENGTH_MISMATCH);
}

TEST_CASE("MBIM_OPEN_DONE parses fields correctly") {
    std::string msg_header = "010000800000000001000000";
    std::string payload = "05000000";
    std::string to_test = msg_header + payload;
    hexStream hs(to_test);

    MBIM_OPEN_DONE msg(hs);

    REQUIRE(msg.STATUS.value == MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_PIN_REQUIRED);
}

TEST_CASE("MBIM_CLOSE_DONE parses fields correctly") {
    std::string msg_header = "020000800000000001000000";
    std::string payload = "00000000";
    std::string to_test = msg_header + payload;
    hexStream hs(to_test);

    MBIM_CLOSE_DONE msg(hs);

    REQUIRE(msg.STATUS.value == MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_SUCCESS);
}

TEST_CASE("MBIM_COMMAND_DONE parses fields correctly") {
    std::string msg_header = "010000003400000015000000";
    std::string msg_fragment_header = "0100000000000000";
    std::string payload = "a289cc33bcbb8b4fb6b0133ec2aae6df01000000000000000400000011111111";
    std::string to_test = msg_header + msg_fragment_header + payload;
    hexStream hs(to_test);

    MBIM_COMMAND_DONE msg(hs);

    REQUIRE(msg.DEVICE_SERVICE_ID.value == "a289cc33bcbb8b4fb6b0133ec2aae6df");
    REQUIRE(msg.CID.value == 1);
    REQUIRE(msg.STATUS.value == MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_SUCCESS);
    REQUIRE(msg.INFORMATION_BUFFER_LENGTH.value == 4);
    REQUIRE(msg.INFORMATION_BUFFER.value == "11111111");
}


TEST_CASE("MBIM_INDICATE_STATUS_MSG parses fields correctly") {
    std::string msg_header = "010000003400000015000000";
    std::string msg_fragment_header = "0100000000000000";
    std::string payload = "a289cc33bcbb8b4fb6b0133ec2aae6df010000000400000011111111";
    std::string to_test = msg_header + msg_fragment_header + payload;
    hexStream hs(to_test);

    MBIM_INDICATE_STATUS_MSG msg(hs);

    REQUIRE(msg.DEVICE_SERVICE_ID.value == "a289cc33bcbb8b4fb6b0133ec2aae6df");
    REQUIRE(msg.CID.value == 1);
    REQUIRE(msg.INFORMATION_BUFFER_LENGTH.value == 4);
    REQUIRE(msg.INFORMATION_BUFFER.value == "11111111");
}
