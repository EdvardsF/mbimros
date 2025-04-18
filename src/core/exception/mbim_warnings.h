#pragma once

#include "mbim_exception.h"


struct VariableFieldTooLongWarning : public MBIMWarning {
    explicit VariableFieldTooLongWarning(const std::string& details)
        : MBIMWarning("Variable field too long: " + details) {}

    std::string type() const override {
        return "VariableFieldTooLongWarning";
    }
};

struct UnknownFieldWarning : public MBIMWarning {
    explicit UnknownFieldWarning(const std::string& details)
        : MBIMWarning("Unknown field encountered: " + details) {}

    std::string type() const override {
        return "UnknownFieldWarning";
    }
};

struct DeprecatedFieldWarning : public MBIMWarning {
    explicit DeprecatedFieldWarning(const std::string& details)
        : MBIMWarning("Deprecated field used: " + details) {}

    std::string type() const override {
        return "DeprecatedFieldWarning";
    }
};

struct UnsupportedFeatureWarning : public MBIMWarning {
    explicit UnsupportedFeatureWarning(const std::string& details)
        : MBIMWarning("Unsupported feature: " + details) {}

    std::string type() const override {
        return "UnsupportedFeatureWarning";
    }
};
