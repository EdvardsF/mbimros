#pragma once

#include <string>
#include <vector>
#include <variant>
#include <sstream>

#include "../../helpers/hex_helpers.h"

enum class StringType {
    BigEndian,
    LittleEndian,
    Literal
};

enum class FieldType {
    Numeric,
    SingleOLPair,
    ListOfOLPairs,
    String
};

struct OLPair {
    size_t offset = 0;
    size_t length = 0;
    std::string valueUtf16Le;

    OLPair();
    explicit OLPair(const std::string& value);
};

struct RefList {
    std::vector<OLPair> pairs;

    RefList();
    explicit RefList(const std::vector<std::string>& strings);
    size_t count() const;
};

struct StringField {
    std::string value;

    StringField();
    explicit StringField(const std::string& val, const StringType& stringType);
};

struct ConstructionField {
    FieldType type;
    uint32_t numericValue = 0;
    OLPair olPair;
    RefList refList;
    StringField string;

    static std::vector<ConstructionField*> allFields;

    ConstructionField();
    explicit ConstructionField(uint32_t value);
    explicit ConstructionField(const std::string& value);
    explicit ConstructionField(const std::vector<std::string>& values);
    explicit ConstructionField(const std::string& value, const StringType& strType);

    template <typename EnumType, typename = std::enable_if_t<std::is_enum_v<EnumType>>>
    explicit ConstructionField(EnumType enumValue)
        : type(FieldType::Numeric), numericValue(static_cast<uint32_t>(enumValue))
    {
        allFields.push_back(this);
    }

    static void clear();
};

struct CompiledBuffer {
    std::string infoBufferHex;
    std::string dataBufferHex;
};

CompiledBuffer compileFields();
