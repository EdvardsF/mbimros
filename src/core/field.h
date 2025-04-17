#pragma once

#include <string>
#include <sstream>
#include <type_traits>
#include <functional>

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
        return static_cast<bool>(bitmaskToString);
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
        } else if constexpr (std::is_same_v<T, uint32_t>) {
            if (bitmaskToString) {
                return std::to_string(value) + "\n" + bitmaskToString(value);
            } else if (numberToString) {
                return std::to_string(value) + " [" + numberToString(value) + "]";
            } else {
                return std::to_string(value);
            }
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


};
