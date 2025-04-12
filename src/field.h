#pragma once

#include <string>
#include <sstream>

struct Serializable;  // Forward declaration

template<typename T>
struct Field {
    T value;
    const char* name;
    const char* description;
    Serializable* owner = nullptr;  // Pointer to parent

    Field(const char* name_, const char* desc_)
        : value{}, name(name_), description(desc_) {}

    void bind(Serializable* s) {
        owner = s;
    }

    void set(T val) {
        value = val;
        if (owner) {
            owner->addField(name, std::to_string(value));
        }
    }
};
