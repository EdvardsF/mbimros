#include "../external/catch.h"

#include "utils/test_validation_helpers.h"

#include "../src/core/decoder/decoder.h"
#include "../src/core/encoder/encoder.h"
#include "../src/helpers/hex_helpers.h"
#include "../src/protocol/v1/messages.h"
#include "../src/protocol/v1/buffers.h"

#include <sstream>


TEST_CASE("Decoder parses MBIM_OPEN_MSG correctly", "[Decoder][MBIM_OPEN_MSG]") {

    std::string hex = Encoder::encode(
        MESSAGE_TYPE_ENUM::MBIM_OPEN_MSG,
        1234
    );

    validateDecodedMessage<MBIM_OPEN_MSG>(
        hex,
        {
            {"MAX_CONTROL_TRANSFER", [](MBIM_OPEN_MSG& msg) {
                REQUIRE(msg.MAX_CONTROL_TRANSFER.value == 1234);
            }}
        }
    );
}


TEST_CASE("Decoder parses MBIM_OPEN_DONE correctly", "[Decoder][MBIM_OPEN_DONE_MSG]") {

    std::string hex = Encoder::encode(
        MESSAGE_TYPE_ENUM::MBIM_OPEN_DONE,
        MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_AUTH_INCORRECT_AUTN
    );

    validateDecodedMessage<MBIM_OPEN_DONE>(
        hex,
        {
            {"STATUS", [](MBIM_OPEN_DONE& msg) {
                REQUIRE(msg.STATUS.value == MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_AUTH_INCORRECT_AUTN);
            }}
        }
    );
}

TEST_CASE("Decoder parses MBIM_CLOSE_MSG correctly", "[Decoder][MBIM_OPEN_MSG]") {

    std::string hex = Encoder::encode(
        MESSAGE_TYPE_ENUM::MBIM_CLOSE_MSG,
        Encoder::EMPTY_ARG
    );

    validateDecodedMessage<MBIM_CLOSE_MSG>(
        hex,
        {
            {"", [](MBIM_CLOSE_MSG&) {
                // No fields to validate
            }}
        }
    );
}


TEST_CASE("Decoder parses MBIM_CLOSE_DONE correctly", "[Decoder][MBIM_CLOSE_DONE_MSG]") {

    std::string hex = Encoder::encode(
        MESSAGE_TYPE_ENUM::MBIM_CLOSE_DONE,
        MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_BAD_SIM
    );

    validateDecodedMessage<MBIM_CLOSE_DONE>(
        hex,
        {
            {"STATUS", [](MBIM_CLOSE_DONE& msg) {
                REQUIRE(msg.STATUS.value == MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_BAD_SIM);
            }}
        }
    );
}

TEST_CASE("Decoder parses MBIM_COMMAND_MSG correctly", "[Decoder][MBIM_COMMAND_MSG]") {

    std::string hex = Encoder::encode(
        MESSAGE_TYPE_ENUM::MBIM_COMMAND_MSG,
        Encoder::EMPTY_ARG,
        MBIM_CMD::UUID_BASIC_CONNECT::UUID,
        MBIM_CMD::UUID_BASIC_CONNECT::MBIM_CID_RADIO_STATE,
        MESSAGE_QUERY_OR_SET_ENUM::SET,
        {
            ConstructionField(MBIM_RADIO_SWITCH_STATE_ENUM::MBIM_RADIO_OFF)
        }
    );

    validateDecodedMessage<MBIM_COMMAND_MSG>(
        hex,
        {
            {"DEVICE_SERVICE_ID", [](MBIM_COMMAND_MSG& msg) {
                REQUIRE(msg.DEVICE_SERVICE_ID.value == MBIM_CMD::UUID_BASIC_CONNECT::UUID);
            }},
            {"CID", [](MBIM_COMMAND_MSG& msg) {
                REQUIRE(msg.CID.value == MBIM_CMD::UUID_BASIC_CONNECT::MBIM_CID_RADIO_STATE);
            }},
            {"COMMAND_TYPE", [](MBIM_COMMAND_MSG& msg) {
                REQUIRE(msg.COMMAND_TYPE.value == MESSAGE_QUERY_OR_SET_ENUM::SET);
            }},
            {"INFORMATION_BUFFER_LENGTH", [](MBIM_COMMAND_MSG& msg) {
                REQUIRE(msg.INFORMATION_BUFFER_LENGTH.value == 4);
            }},
            {"RADIO_SWITCH_STATE", [](MBIM_COMMAND_MSG& msg) {
                auto* buffer = dynamic_cast<MBIM_SET_RADIO_STATE*>(msg.getEmbeddedBuffer());
                REQUIRE(buffer->RADIO_SWITCH_STATE.value == MBIM_RADIO_SWITCH_STATE_ENUM::MBIM_RADIO_OFF);
            }}

        }
    );
}

TEST_CASE("Decoder parses MBIM_COMMAND_DONE correctly", "[Decoder][MBIM_COMMAND_DONE]") {

    std::string hex = Encoder::encode(
        MESSAGE_TYPE_ENUM::MBIM_COMMAND_DONE,
        Encoder::EMPTY_ARG,
        MBIM_CMD::UUID_BASIC_CONNECT::UUID,
        MBIM_CMD::UUID_BASIC_CONNECT::MBIM_CID_RADIO_STATE,
        MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_BAD_SIM,
        {
            ConstructionField(MBIM_RADIO_SWITCH_STATE_ENUM::MBIM_RADIO_ON),
            ConstructionField(MBIM_RADIO_SWITCH_STATE_ENUM::MBIM_RADIO_OFF)
        }
    );

    validateDecodedMessage<MBIM_COMMAND_DONE>(
        hex,
        {
            {"DEVICE_SERVICE_ID", [](MBIM_COMMAND_DONE& msg) {
                REQUIRE(msg.DEVICE_SERVICE_ID.value == MBIM_CMD::UUID_BASIC_CONNECT::UUID);
            }},
            {"CID", [](MBIM_COMMAND_DONE& msg) {
                REQUIRE(msg.CID.value == MBIM_CMD::UUID_BASIC_CONNECT::MBIM_CID_RADIO_STATE);
            }},
            {"STATUS", [](MBIM_COMMAND_DONE& msg) {
                REQUIRE(msg.STATUS.value == MBIM_STATUS_TO_HOST_ENUM::MBIM_STATUS_BAD_SIM);
            }},
            {"INFORMATION_BUFFER_LENGTH", [](MBIM_COMMAND_DONE& msg) {
                REQUIRE(msg.INFORMATION_BUFFER_LENGTH.value == 8);
            }},
            {"HW_RADIO_STATE", [](MBIM_COMMAND_DONE& msg) {
                auto* buffer = dynamic_cast<MBIM_RADIO_STATE_INFO*>(msg.getEmbeddedBuffer());
                REQUIRE(buffer->HW_RADIO_STATE.value == MBIM_RADIO_SWITCH_STATE_ENUM::MBIM_RADIO_ON);
            }},
            {"SW_RADIO_STATE", [](MBIM_COMMAND_DONE& msg) {
                auto* buffer = dynamic_cast<MBIM_RADIO_STATE_INFO*>(msg.getEmbeddedBuffer());
                REQUIRE(buffer->SW_RADIO_STATE.value == MBIM_RADIO_SWITCH_STATE_ENUM::MBIM_RADIO_OFF);
            }}
        }
    );
}

TEST_CASE("Decoder parses MBIM_HOST_ERROR_MSG correctly", "[Decoder][MBIM_HOST_ERROR_MSG]") {

    std::string hex = Encoder::encode(
        MESSAGE_TYPE_ENUM::MBIM_HOST_ERROR_MSG,
        MBIM_PROTOCOL_ERROR_CODES_ENUM::MBIM_ERROR_DUPLICATED_TID
    );

    validateDecodedMessage<MBIM_HOST_ERROR_MSG>(
        hex,
        {
            {"ERROR_STATUS_CODE", [](MBIM_HOST_ERROR_MSG& msg) {
                REQUIRE(msg.ERROR_STATUS_CODE.value == MBIM_PROTOCOL_ERROR_CODES_ENUM::MBIM_ERROR_DUPLICATED_TID);
            }}
        }
    );
}

TEST_CASE("Decoder parses MBIM_INDICATE_STATUS_MSG correctly", "[Decoder][MBIM_INDICATE_STATUS_MSG]") {

    std::string hex = Encoder::encode(
        MESSAGE_TYPE_ENUM::MBIM_INDICATE_STATUS_MSG,
        Encoder::EMPTY_ARG,
        MBIM_CMD::UUID_BASIC_CONNECT::UUID,
        MBIM_CMD::UUID_BASIC_CONNECT::MBIM_CID_RADIO_STATE,
        Encoder::EMPTY_ARG,
        {
            ConstructionField(MBIM_RADIO_SWITCH_STATE_ENUM::MBIM_RADIO_ON),
            ConstructionField(MBIM_RADIO_SWITCH_STATE_ENUM::MBIM_RADIO_OFF)
        }
    );

    validateDecodedMessage<MBIM_INDICATE_STATUS_MSG>(
        hex,
        {
            {"DEVICE_SERVICE_ID", [](MBIM_INDICATE_STATUS_MSG& msg) {
                REQUIRE(msg.DEVICE_SERVICE_ID.value == MBIM_CMD::UUID_BASIC_CONNECT::UUID);
            }},
            {"CID", [](MBIM_INDICATE_STATUS_MSG& msg) {
                REQUIRE(msg.CID.value == MBIM_CMD::UUID_BASIC_CONNECT::MBIM_CID_RADIO_STATE);
            }},
            {"INFORMATION_BUFFER_LENGTH", [](MBIM_INDICATE_STATUS_MSG& msg) {
                REQUIRE(msg.INFORMATION_BUFFER_LENGTH.value == 8);
            }},
            {"HW_RADIO_STATE", [](MBIM_INDICATE_STATUS_MSG& msg) {
                auto* buffer = dynamic_cast<MBIM_RADIO_STATE_INFO*>(msg.getEmbeddedBuffer());
                REQUIRE(buffer->HW_RADIO_STATE.value == MBIM_RADIO_SWITCH_STATE_ENUM::MBIM_RADIO_ON);
            }},
            {"SW_RADIO_STATE", [](MBIM_INDICATE_STATUS_MSG& msg) {
                auto* buffer = dynamic_cast<MBIM_RADIO_STATE_INFO*>(msg.getEmbeddedBuffer());
                REQUIRE(buffer->SW_RADIO_STATE.value == MBIM_RADIO_SWITCH_STATE_ENUM::MBIM_RADIO_OFF);
            }}
        }
    );
}




// --------------- ERRORS AND WARNINGS -----------------
// TODO: ADD MORE

TEST_CASE("Decoder throws CidNotFoundException", "[Decoder][CidNotFoundException]") {

    std::string hex = Encoder::encode(
        MESSAGE_TYPE_ENUM::MBIM_COMMAND_MSG,
        Encoder::EMPTY_ARG,
        "a289cc33bcbb8b4fb6b013ffffffffff",
        99,
        MESSAGE_QUERY_OR_SET_ENUM::SET,
        {
            ConstructionField(0)
        }
    );

    validateDecodedMessage<MBIM_COMMAND_MSG>(
        hex,
        {},
        {},
        std::make_shared<CidNotFoundException>("")
    );
}