#define CATCH_CONFIG_MAIN
#include "catch.h"

#include "../src/core/exception/mbim_exception.h"


TEST_CASE("MBIMException basic behavior", "[exception]") {
    MBIMException ex("Test exception");

    REQUIRE(std::string(ex.what()) == "Test exception");
    REQUIRE(ex.type() == "MBIMException");

    std::ostringstream oss;
    oss << ex;
    std::string output = oss.str();

    REQUIRE(output.find("[ ERROR ]") != std::string::npos);
    REQUIRE(output.find("Test exception") != std::string::npos);
}


#include "../src/core/exception/mbim_errors.h"

TEST_CASE("Specific exceptions inherit properly", "[exception]") {
    BufferTooShortException ex("Expected 8 bytes, got 4");

    REQUIRE(std::string(ex.what()).find("Expected 8 bytes") != std::string::npos);
    REQUIRE(ex.type() == "BufferTooShortException");

    std::ostringstream oss;
    oss << ex;
    REQUIRE(oss.str().find("BufferTooShortException") != std::string::npos);
}

TEST_CASE("Different MBIMException derived classes produce correct messages", "[exception]") {
    UnknownMessageTypeException ex1("0xFFFF");
    FieldParsingException ex2("DEVICE_CAPS field");

    REQUIRE(ex1.type() == "UnknownMessageTypeException");
    REQUIRE(std::string(ex1.what()).find("Unknown MBIM message type") != std::string::npos);

    REQUIRE(ex2.type() == "FieldParsingException");
    REQUIRE(std::string(ex2.what()).find("Failed to parse field") != std::string::npos);
}


TEST_CASE("MBIMWarning basic behavior", "[warning]") {
    MBIMWarning::clearWarnings();
    MBIMWarning warn("Something might be wrong");
    MBIMWarning::registerWarning(warn);

    REQUIRE(warn.getMessage() == "Something might be wrong");
    REQUIRE(warn.type() == "MBIMWarning");

    const auto& warnings = MBIMWarning::getWarnings();
    REQUIRE(warnings.size() == 1);
    REQUIRE(warnings[0].getMessage() == "Something might be wrong");

    std::ostringstream oss;
    oss << warn;
    std::string output = oss.str();
    REQUIRE(output.find("[ WARNING ]") != std::string::npos);
}


#include "../src/core/exception/mbim_warnings.h"

TEST_CASE("Specific MBIMWarning derived classes register properly", "[warning]") {
    MBIMWarning::clearWarnings();

    VariableFieldTooLongWarning warn1("expected 8, got 16");
    UnknownFieldWarning warn2("Unknown tag 0xAA");
    MBIMWarning::registerWarning(warn1);
    MBIMWarning::registerWarning(warn2);

    REQUIRE(warn1.type() == "VariableFieldTooLongWarning");
    REQUIRE(warn2.type() == "UnknownFieldWarning");


    const auto& warnings = MBIMWarning::getWarnings();
    REQUIRE(warnings.size() == 2);

    REQUIRE(warnings[0].getMessage().find("Variable field too long") != std::string::npos);
    REQUIRE(warnings[1].getMessage().find("Unknown field encountered") != std::string::npos);
}
