#pragma once

#include "mbim_base_exception.h"


struct VariableFieldTooLongWarning : public MBIMBaseWarning {
    explicit VariableFieldTooLongWarning(const std::string& details)
        : MBIMBaseWarning("Variable field too long: " + details) {}

    std::string type() const override {
        return "VariableFieldTooLongWarning";
    }
};

struct UnknownFieldWarning : public MBIMBaseWarning {
    explicit UnknownFieldWarning(const std::string& details)
        : MBIMBaseWarning("Unknown field encountered: " + details) {}

    std::string type() const override {
        return "UnknownFieldWarning";
    }
};

struct DeprecatedFieldWarning : public MBIMBaseWarning {
    explicit DeprecatedFieldWarning(const std::string& details)
        : MBIMBaseWarning("Deprecated field used: " + details) {}

    std::string type() const override {
        return "DeprecatedFieldWarning";
    }
};

struct UnsupportedFeatureWarning : public MBIMBaseWarning {
    explicit UnsupportedFeatureWarning(const std::string& details)
        : MBIMBaseWarning("Unsupported feature: " + details) {}

    std::string type() const override {
        return "UnsupportedFeatureWarning";
    }
};

struct HexBufferTooLongWarning : public MBIMBaseWarning {
    explicit HexBufferTooLongWarning(const std::string& details)
        : MBIMBaseWarning("Hex buffer is longer than expected, some bytes did not get parsed: " + details) {}

    std::string type() const override {
        return "HexBufferTooLongWarning";
    }
};


struct InformationBufferMismatchWarning : public MBIMBaseWarning {
    explicit InformationBufferMismatchWarning(const std::string& details)
        : MBIMBaseWarning("Information buffer length field does not match the actual length: " + details) {}

    std::string type() const override {
        return "InformationBufferMismatchWarning";
    }
};
