#pragma once

#include <string>
#include <vector>
#include <variant>
#include <sstream>

#include "../../helpers/hex_helpers.h"


enum class FieldType {
    Numeric,
    SingleOLPair,
    ListOfOLPairs
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

struct ConstructionField {
    FieldType type;
    uint32_t numericValue = 0;
    OLPair olPair;
    RefList refList;

    static std::vector<ConstructionField*> allFields;

    ConstructionField();
    explicit ConstructionField(uint32_t value);
    explicit ConstructionField(const std::string& value);
    explicit ConstructionField(const std::vector<std::string>& values);

    static void clear();
};

struct CompiledBuffer {
    std::string infoBufferHex;
    std::string dataBufferHex;
};

CompiledBuffer compileFields();
