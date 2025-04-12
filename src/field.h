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

struct Serializable {
    std::vector<std::pair<std::string, std::string>> printableFields;

    void addField(const std::string& name, const std::string& value) {
        printableFields.emplace_back(name, value);
    }

    template<typename T>
    void addField(const Field<T>& f) {
        printableFields.emplace_back(f.name, std::to_string(f.value));
    }

    std::string to_string() const {
        std::ostringstream oss;
        for (const auto& [name, value] : printableFields) {
            oss << name << ": " << value << "\n";
        }
        return oss.str();
    }
};