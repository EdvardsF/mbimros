#pragma once
#include <string>

struct FieldBase {
    virtual std::string getName() const = 0;
    virtual std::string getValueAsString() const = 0;
    virtual std::string getDescription() const = 0;
    virtual bool isBitmask() const { return false; }
    virtual ~FieldBase() = default;
    virtual bool isDataField() const { return false; }
    virtual uint32_t getRawValue() const { return 0; }
    virtual std::vector<std::pair<std::string,std::string>> getBitmaskDescriptions() const {
        return {};
    }
};
