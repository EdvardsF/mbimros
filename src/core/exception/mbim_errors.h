#pragma once

#include "mbim_exception.h"

struct BufferTooShortException : public MBIMException {
    explicit BufferTooShortException(const std::string& details)
        : MBIMException("The hex buffer is too short: " + details) {}

    std::string type() const override {
        return "BufferTooShortException";
    }
};

struct UnknownMessageTypeException : public MBIMException {
    explicit UnknownMessageTypeException(const std::string& details)
        : MBIMException("Unknown MBIM message type: " + details) {}

    std::string type() const override {
        return "UnknownMessageTypeException";
    }
};

struct FieldParsingException : public MBIMException {
    explicit FieldParsingException(const std::string& details)
        : MBIMException("Failed to parse field: " + details) {}

    std::string type() const override {
        return "FieldParsingException";
    }
};
