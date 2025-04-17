#pragma once

#include "mbim_exception.h"


struct BufferTooShortException : public MBIMException {
    explicit BufferTooShortException(const std::string& details)
        : MBIMException("The hex buffer is too short: " + details) {}
};

struct UnknownMessageTypeException : public MBIMException {
    explicit UnknownMessageTypeException(const std::string& details)
        : MBIMException("Unknown MBIM message type: " + details) {}
};

struct FieldParsingException : public MBIMException {
    explicit FieldParsingException(const std::string& details)
        : MBIMException("Failed to parse field: " + details) {}
};
