#pragma once

#include <codecvt>
#include <locale>

#include "variable_field.h"

#include <iostream>


template<typename T>
VariableField<T>::VariableField(const std::string& name, const std::string& desc)
    : Field<T>(name, desc) {}

template<typename T>
void VariableField<T>::setOffsetLength(uint32_t ofs, uint32_t len, hexStream& hs, size_t bs) {
    offset = ofs + bs;
    length = len;
    hs_ref = &hs;
}

template<typename T>
void VariableField<T>::resolve() {
    if (length == 0 || hs_ref == nullptr) return;

    size_t saved = hs_ref->currentOffset();

    const_cast<hexStream*>(hs_ref)->seek(offset);
    auto data = hs_ref->readUtf16LE(length / 2);
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> conv;

    const_cast<hexStream*>(hs_ref)->seek(saved);

    this->set(conv.to_bytes(data));
}
