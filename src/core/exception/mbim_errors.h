#pragma once

#include "mbim_base_exception.h"

struct BufferTooShortException : public MBIMBaseException {
    explicit BufferTooShortException(const std::string& details)
        : MBIMBaseException("The hex buffer is too short: " + details) {}

    std::string type() const override {
        return "BufferTooShortException";
    }
};

struct UnknownMessageTypeException : public MBIMBaseException {
    explicit UnknownMessageTypeException(const std::string& details)
        : MBIMBaseException("Unknown MBIM message type: " + details) {}

    std::string type() const override {
        return "UnknownMessageTypeException";
    }
};

struct FieldParsingException : public MBIMBaseException {
    explicit FieldParsingException(const std::string& details)
        : MBIMBaseException("Failed to parse field: " + details) {}

    std::string type() const override {
        return "FieldParsingException";
    }
};
