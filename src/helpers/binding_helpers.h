#pragma once

#include <functional>

#include "../core/exception/mbim_base_exception.h"
#include "../core/serializable.h"
#include "../core/hex_stream.h"
#include "../core/variable_field.h"


template<typename FieldType, typename FormatterFunc>
void bindFormatSet(FieldType& field, Serializable* owner, FormatterFunc formatter, hexStream& hs) {
    field.bind(owner);
    field.setEnumFormatter(std::move(formatter));
    field.set(static_cast<typename FieldType::value_type>(hs.readUint32LE()));
}

template<typename FieldType>
void bindBitmaskSet(FieldType& field, Serializable* owner, std::function<std::string(uint32_t)> formatter, hexStream& hs) {
    field.bind(owner);
    field.setBitmaskFormatter(std::move(formatter));
    field.set(static_cast<typename FieldType::value_type>(hs.readUint32LE()));
}

template<typename FieldType>
void bindSimpleSet(FieldType& field, Serializable* owner, hexStream& hs) {
    field.bind(owner);
    field.set(hs.readUint32LE());
}

template<typename FieldType>
void bindStringSet(FieldType& field, Serializable* owner, const std::string& (*formatter)(const std::string&), hexStream& hs) {
    field.bind(owner);
    field.setStringFormatter(formatter);
    field.set(hs.readHexBytes(16));
}

template<typename T>
VariableField<T>* readOLPair(const std::string& name, const std::string& description, hexStream& hs, size_t baseOffset, size_t maxFieldLength) {
    VariableField<T>* field = new VariableField<T>(name, description, maxFieldLength);
    uint32_t off = hs.readUint32LE();
    uint32_t len = hs.readUint32LE();
    field->setOffsetLength(off, len, hs, baseOffset);
    field->resolve();
    return field;
}

template<typename T>
VariableField<T>* readOLPairAndBind(const std::string& name, const std::string& description, hexStream& hs, Serializable* owner, size_t baseOffset, size_t maxFieldLength) {
    VariableField<T>* field = readOLPair<T>(name, description, hs, baseOffset, maxFieldLength);
    field->bind(owner);
    field->resolve();
    return field;
}

template<typename T>
std::vector<VariableField<T>*> bindReadElementList(const std::string& base_name, const std::string& description, size_t count, hexStream& hs, Serializable* owner, size_t baseOffset, size_t maxFieldLength) {
    std::vector<VariableField<T>*> fields;
    for (size_t i = 0; i < count; i++) {
        VariableField<T>* field = readOLPairAndBind<std::string>(base_name + "_" + std::to_string(i), description, hs, owner, baseOffset, maxFieldLength);
        fields.push_back(field);
    }
    return fields;
}
