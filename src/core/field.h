#pragma once

#include <string>
#include <sstream>
#include <type_traits>
#include <functional>
#include <unordered_map>

#include "field_base.h"
#include "serializable.h"

struct Serializable;

template<typename T>
struct Field : public FieldBase {
    T value;
    std::string name;
    std::string description;
    Serializable* owner = nullptr;

    std::function<std::string(T)> enumToString;
    std::function<std::string(T)> bitmaskToString;
    std::function<std::string(const std::string&)> strToString;
    std::function<std::string(uint32_t)> numberToString;

    std::unordered_map<uint32_t, std::string> bitDescriptions;

    Field(const std::string& _name, const std::string& _desc)
        : value{}, name(_name), description(_desc) {}

    void bind(Serializable* s) {
        owner = s;
        if (owner) {
            owner->registerField(this);
        }
    }

    void set(T val) {
        value = val;
    }

    template<typename F>
    void setEnumFormatter(F&& func) {
        enumToString = std::forward<F>(func);
    }

    template<typename F>
    void setBitmaskFormatter(F&& func) {
        bitmaskToString = std::forward<F>(func);
    }

    template<typename F>
    void setStringFormatter(F&& func) {
        strToString = std::forward<F>(func);
    }

    template<typename F>
    void setNumberFormatter(F&& func) {
        if constexpr (std::is_same_v<T, uint32_t>) {
            numberToString = std::forward<F>(func);
        }
    }

    bool isBitmask() const override {
        return static_cast<bool>(bitmaskToString) || !bitDescriptions.empty();
    }

    uint32_t getRawValue() const override {
        if constexpr (std::is_integral_v<T>) {
            return static_cast<uint32_t>(value);
        } else {
            return 0;
        }
    }

    std::string getName() const override { return name; }

    std::string getDescription() const override { return description; }

    std::string getValueAsString() const override {
        if constexpr (std::is_same_v<T, std::string>) {
            if (strToString) {
                return value + " [" + strToString(value) + "]";
            }
            return value;
        } else if constexpr (std::is_enum_v<T>) {
            if (enumToString) {
                std::ostringstream oss;
                oss << static_cast<std::underlying_type_t<T>>(value)
                    << " [" << enumToString(value) << "]";
                return oss.str();
            } else {
                return std::to_string(static_cast<std::underlying_type_t<T>>(value));
            }
        } else if constexpr (std::is_same_v<T, uint32_t>) { // bitmask (quick and dirty fix)
            return std::to_string(value);
        } else if constexpr (std::is_integral_v<T>) {
            if (enumToString) {
                return std::to_string(value) + " [" + enumToString(value) + "]";
            } else {
                return std::to_string(value);
            }
        } else {
            return "[unsupported type]";
        }
    }

    // Quick and dirty fix to improve formatting without chaging data types across whole code base
    std::vector<std::pair<std::string,std::string>> getBitmaskDescriptions() const override {
        std::vector<std::pair<std::string, std::string>> descriptions;

        std::istringstream stream(bitmaskToString(value));
        std::string line;
        while (std::getline(stream, line)) {
            std::vector<std::string> result;
            std::stringstream ss(line);
            std::string token;

            while (std::getline(ss, token, '-')) {
                result.push_back(token);
            }

            descriptions.push_back({result[0], result[1]});

        }
        return descriptions;
    }

private:
    std::string bitFlagName(uint32_t bit) const {
        std::ostringstream oss;
        oss << "0x" << std::hex << bit;
        return oss.str();
    }
};
