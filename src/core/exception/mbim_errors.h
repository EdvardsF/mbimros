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

struct InvalidOffsetException : public MBIMBaseException {
    explicit InvalidOffsetException(const std::string& details)
        : MBIMBaseException("Given variable offset is out of bounds: " + details) {}

    std::string type() const override {
        return "InvalidOffsetException";
    }
};

struct InvalidByteAlignment : public MBIMBaseException {
    explicit InvalidByteAlignment(const std::string& details)
        : MBIMBaseException("Invalid hex buffer length: " + details) {}

    std::string type() const override {
        return "InvalidByteAlignment";
    }
};

struct CidNotFoundException : public MBIMBaseException {
    explicit CidNotFoundException(const std::string& details)
        : MBIMBaseException("No CID found for this UUID: " + details) {}

    std::string type() const override {
        return "CidNotFoundException";
    }
};

struct OpeationNotApplicableException : public MBIMBaseException {
    explicit OpeationNotApplicableException(const std::string& details)
        : MBIMBaseException("Given set/query/notification operation is not supported for this CID. " + details) {}

    std::string type() const override {
        return "OpeationNotApplicableException";
    }
};
