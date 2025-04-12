#pragma once
#include <string>

struct FieldBase {
    virtual std::string getName() const = 0;
    virtual std::string getValueAsString() const = 0;
    virtual std::string getDescription() const = 0;
    virtual ~FieldBase() = default;
};
