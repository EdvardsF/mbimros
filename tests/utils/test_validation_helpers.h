#pragma once

#include <string>
#include <functional>
#include <memory>
#include <unordered_map>

#include "../src/core/decoder/decoder.h"
#include "../src/core/exception/mbim_base_exception.h"
#include "../src/core/exception/mbim_warnings.h"
#include "../src/core/serialization/serializable.h"
#include "../src/helpers/warning_helpers.h"

template<typename MessageType>
std::string validateDecodedMessage(
    const std::string& encodedHex,
    const std::unordered_map<std::string, std::function<void(MessageType&)>>& fieldChecks,
    const std::vector<std::shared_ptr<MBIMBaseWarning>>& expectedWarnings = {},
    std::shared_ptr<MBIMBaseException> expectedError = nullptr
) {
    std::unique_ptr<Serializable> decoded;
    std::string rawDecodedStr;

    MBIMBaseWarning::clearWarnings();

    try {
        Decoder decoder(encodedHex);
        decoder.decodeRaw();
        rawDecodedStr = decoder.to_string();
        decoded = std::move(decoder.decodedMessage);
    } catch (const MBIMBaseException& ex) {
        if (!expectedError) {
            INFO("Exception: " << ex.what());
            FAIL_CHECK("Unexpected exception thrown: " << typeid(ex).name());
            return {};
        }

        INFO("Expected exception: " << typeid(*expectedError).name()
             << ", actual: " << typeid(ex).name());
        REQUIRE(typeid(ex) == typeid(*expectedError));
        return {};
    } catch (...) {
        FAIL_CHECK("Unexpected non-MBIMBaseException thrown.");
        return {};
    }

    if (expectedError) {
        FAIL_CHECK("Expected exception was not thrown: " << typeid(*expectedError).name());
        return {};
    }

    REQUIRE(decoded != nullptr);
    INFO("Decoded type: " << typeid(*decoded).name());
    REQUIRE(typeid(*decoded) == typeid(MessageType));

    MessageType* msg = dynamic_cast<MessageType*>(decoded.get());
    INFO("Result of dynamic_cast: " << (msg ? "valid" : "nullptr"));
    REQUIRE(msg != nullptr);

    for (const auto& [name, check] : fieldChecks) {
        DYNAMIC_SECTION("Field: " << name) {
            check(*msg);
        }
    }

    const auto& actualWarnings = MBIMBaseWarning::getWarnings();
    for (const auto& expectedWarn : expectedWarnings) {
        INFO("Checking for expected warning type: " << typeid(*expectedWarn).name());
        bool matched = std::any_of(actualWarnings.begin(), actualWarnings.end(),
                                   [&](const auto& actual) {
                                       return typeid(*expectedWarn) == typeid(*actual);
                                   });
        REQUIRE(matched);
    }

    return rawDecodedStr;
}
