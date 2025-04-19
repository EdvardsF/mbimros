#pragma once

#include <functional>

#include "../core/exception/mbim_base_exception.h"
#include "../core/serializable.h"
#include "../core/hex_stream.h"
#include "../core/variable_field.h"


template<typename FieldType, typename FormatterFunc>
void bindFormatSet(FieldType& field, Serializable* owner, FormatterFunc formatter, uint32_t value) {
    field.bind(owner);
    field.setEnumFormatter(std::move(formatter));
    field.set(static_cast<typename FieldType::value_type>(value));
}

template<typename FieldType>
void bindBitmaskSet(FieldType& field, Serializable* owner, std::function<std::string(uint32_t)> formatter, uint32_t value) {
    field.bind(owner);
    field.setBitmaskFormatter(std::move(formatter));
    field.set(value);
}

template<typename FieldType>
void bindSimpleSet(FieldType& field, Serializable* owner, uint32_t value) {
    field.bind(owner);
    field.set(value);
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
    return field;
}