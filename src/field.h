#pragma once

#include <vector>
#include <string>
#include <sstream>

template<typename T>
struct Field {
    T value;
    const char* name;
    const char* description;

    Field(const char* name_, const char* desc_)
        : value{}, name(name_), description(desc_) {}

    void set(T val) { value = val; }
};
