#pragma once

#include "field_base.h"
#include "field.h"
#include "hex_stream.h"
#include "exception/mbim_base_exception.h"
#include "exception/mbim_warnings.h"
#include "../helpers/warning_helpers.h"


template<typename T = std::string>
class VariableField : public Field<T> {
private:
    uint32_t offset = 0;
    uint32_t length = 0;
    size_t maxLength = 0;
    hexStream* hs_ref = nullptr;

public:
    VariableField(const std::string& name, const std::string& desc, size_t maxLength);

    void setOffsetLength(uint32_t ofs, uint32_t len, hexStream& hs, size_t bs);
    void resolve();

    virtual bool isDataField() const { return true; }
};

// Template implementation
#include "variable_field.tpp"
