#include "../external/catch.h"

#include <sstream>
#include <memory>

#include "../src/core/exception/mbim_base_exception.h"

TEST_CASE("MBIMException basic behavior", "[exception]") {
    MBIMBaseException ex("Test exception");

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
    MBIMBaseWarning::clearWarnings();

    auto warn = std::make_unique<MBIMBaseWarning>("Something might be wrong");
    MBIMBaseWarning::registerWarning(std::move(warn));

    const auto& warnings = MBIMBaseWarning::getWarnings();
    REQUIRE(warnings.size() == 1);
    REQUIRE(warnings[0]->getMessage() == "Something might be wrong");
    REQUIRE(warnings[0]->type() == "MBIMWarning");

    std::ostringstream oss;
    oss << *warnings[0];
    std::string output = oss.str();
    REQUIRE(output.find("[ WARNING ]") != std::string::npos);
}

#include "../src/core/exception/mbim_warnings.h"

TEST_CASE("Specific MBIMWarning derived classes register properly", "[warning]") {
    MBIMBaseWarning::clearWarnings();

    auto warn1 = std::make_unique<VariableFieldTooLongWarning>("expected 8, got 16");
    auto warn2 = std::make_unique<UnknownFieldWarning>("Unknown tag 0xAA");

    MBIMBaseWarning::registerWarning(std::move(warn1));
    MBIMBaseWarning::registerWarning(std::move(warn2));

    const auto& warnings = MBIMBaseWarning::getWarnings();
    REQUIRE(warnings.size() == 2);

    REQUIRE(warnings[0]->type() == "VariableFieldTooLongWarning");
    REQUIRE(warnings[0]->getMessage().find("Variable field too long") != std::string::npos);

    REQUIRE(warnings[1]->type() == "UnknownFieldWarning");
    REQUIRE(warnings[1]->getMessage().find("Unknown field encountered") != std::string::npos);
}
