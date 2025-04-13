#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <memory>

#include "field_base.h"

template<typename T>
struct Field;  // forward declare

class Serializable {
public:
    void registerField(FieldBase* field);
    virtual std::string to_string() const;
    virtual ~Serializable() = default;

    template<typename T>
    void addField(const Field<T>& f);

    template<typename T, typename F>
    void addField(const Field<T>& f, F&& enumToString);

    const Serializable* embedded_header = nullptr;
    const Serializable* embedded_fragment_header = nullptr;

    void includeHeader(const Serializable* header);
    void includeFragmentHeader(const Serializable* header);

    void includeInformationBuffer(std::unique_ptr<Serializable> buffer);

protected:
    std::vector<FieldBase*> fields;
    std::vector<std::pair<std::string, std::string>> printableFields;
    std::unique_ptr<Serializable> embedded_buffer = nullptr;
};

template<typename T>
void Serializable::addField(const Field<T>& f) {
    printableFields.emplace_back(f.name, std::to_string(f.value));
}

template<typename T, typename F>
void Serializable::addField(const Field<T>& f, F&& enumToString) {
    printableFields.emplace_back(f.name, enumToString(f.value));
}