#pragma once

#include <string>
#include <sstream>
#include <type_traits>
#include <functional>
#include "field_base.h"

struct Serializable;

template<typename T>
struct Field : public FieldBase {
    T value;
    const char* name;
    const char* description;
    Serializable* owner = nullptr;
    std::function<std::string(T)> enumToString = nullptr;  // <-- add this

    Field(const char* name_, const char* desc_)
        : value{}, name(name_), description(desc_) {}

    void bind(Serializable* s) {
        owner = s;
        if (owner) {
            owner->registerField(this);
        }
    }

    void set(T val) {
        value = val;
    }

    void setFormatter(std::function<std::string(T)> mapper) {
        enumToString = mapper;
    }

    std::string getName() const override { return name; }

    std::string getDescription() const override { return description; }

    std::string getValueAsString() const override {
        if constexpr (std::is_enum_v<T>) {
            if (enumToString) {
                std::ostringstream oss;
                oss << static_cast<std::underlying_type_t<T>>(value)
                    << " [" << enumToString(value) << "]";
                return oss.str();
            } else {
                return std::to_string(static_cast<std::underlying_type_t<T>>(value));
            }
        } else {
            return std::to_string(value);
        }
    }


};
