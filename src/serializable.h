#pragma once

#include <vector>
#include <string>
#include <sstream>
#include "field_base.h"

template<typename T>
struct Field;  // forward declare

class Serializable {
public:
    void registerField(FieldBase* field);
    std::string to_string() const;

    template<typename T>
    void addField(const Field<T>& f);

    template<typename T, typename F>
    void addField(const Field<T>& f, F&& enumToString);

protected:
    std::vector<FieldBase*> fields;
    std::vector<std::pair<std::string, std::string>> printableFields;
};

template<typename T>
void Serializable::addField(const Field<T>& f) {
    printableFields.emplace_back(f.name, std::to_string(f.value));
}

template<typename T, typename F>
void Serializable::addField(const Field<T>& f, F&& enumToString) {
    printableFields.emplace_back(f.name, enumToString(f.value));
}
