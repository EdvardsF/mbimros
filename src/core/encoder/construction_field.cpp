#include "construction_field.h"

#include <iostream>

std::vector<ConstructionField*> ConstructionField::allFields;

OLPair::OLPair() = default;

OLPair::OLPair(const std::string& value)
    : valueUtf16Le(stringToUtf16LeAligned(value))
{
    length = valueUtf16Le.length() / 2;
}

RefList::RefList() = default;

RefList::RefList(const std::vector<std::string>& strings) {
    for (const auto& str : strings) {
        pairs.emplace_back(str);
    }
}

size_t RefList::count() const {
    return pairs.size();
}

StringField::StringField() = default;

StringField::StringField(const std::string& val, const StringType& stringType) {
    value = val;

    if (stringType == StringType::BigEndian) {
        value = stringToUtf16BeAligned(value);
    } else if (stringType == StringType::LittleEndian) {
        value = stringToUtf16LeAligned(value);
    } else if (stringType == StringType::Literal) {
        // no encoding
    } else {
        throw std::runtime_error("Unknown string type for field: " + value);
    }
}

ConstructionField::ConstructionField() = default;

ConstructionField::ConstructionField(uint32_t value)
    : type(FieldType::Numeric), numericValue(value)
{
    allFields.push_back(this);
}

ConstructionField::ConstructionField(const std::string& value)
    : type(FieldType::SingleOLPair), olPair(value)
{
    allFields.push_back(this);
}

ConstructionField::ConstructionField(const std::string& value, const StringType& strType)
    : type(FieldType::String), string(value, strType)
{
    allFields.push_back(this);
}

ConstructionField::ConstructionField(const std::vector<std::string>& values)
    : type(FieldType::ListOfOLPairs), refList(values)
{
    allFields.push_back(this);
}

void ConstructionField::clear() {
    allFields.clear();
}

CompiledBuffer compileFields() {
    std::ostringstream infoStream;
    std::ostringstream dataStream;

    size_t staticInfoSize = 0;
    for (auto* fld : ConstructionField::allFields) {
        if (fld->type == FieldType::Numeric) {
            staticInfoSize += 4;
        } else if (fld->type == FieldType::SingleOLPair) {
            staticInfoSize += 8;
        } else if (fld->type == FieldType::ListOfOLPairs) {
            staticInfoSize += 4;
            staticInfoSize += 8 * fld->refList.count();
        } else if (fld->type == FieldType::String) {
            staticInfoSize += getHexStringByteLength(fld->string.value);
        }
    }

    size_t currentDataOffset = staticInfoSize;
    if (currentDataOffset % 4 != 0) currentDataOffset += (4 - currentDataOffset % 4);

    for (auto* fld : ConstructionField::allFields) {
        if (fld->type == FieldType::SingleOLPair) {
            fld->olPair.offset = currentDataOffset;
            currentDataOffset += fld->olPair.length;
            if (currentDataOffset % 4 != 0) currentDataOffset += (4 - currentDataOffset % 4);
        } else if (fld->type == FieldType::ListOfOLPairs) {
            for (auto& pair : fld->refList.pairs) {
                pair.offset = currentDataOffset;
                currentDataOffset += pair.length;
                if (currentDataOffset % 4 != 0) currentDataOffset += (4 - currentDataOffset % 4);
            }
        }
    }

    for (auto* fld : ConstructionField::allFields) {
        if (fld->type == FieldType::Numeric) {
            infoStream << toHexLE(fld->numericValue);
        } else if (fld->type == FieldType::SingleOLPair) {
            infoStream << toHexLE(static_cast<uint32_t>(fld->olPair.offset));
            infoStream << toHexLE(static_cast<uint32_t>(fld->olPair.length));
        } else if (fld->type == FieldType::ListOfOLPairs) {
            infoStream << toHexLE(static_cast<uint32_t>(fld->refList.count()));
            for (const auto& pair : fld->refList.pairs) {
                infoStream << toHexLE(static_cast<uint32_t>(pair.offset));
                infoStream << toHexLE(static_cast<uint32_t>(pair.length));
            }
        } else if (fld->type == FieldType::String) {
            std::cout << fld->string.value << "\n\n\n";
            infoStream << fld->string.value;
            size_t len = fld->string.value.length() / 2;
            if (len % 4 != 0) {
                size_t pad = 4 - (len % 4);
                for (size_t i = 0; i < pad; ++i) infoStream << "00";
            }
        }
    }

    for (auto* fld : ConstructionField::allFields) {
        if (fld->type == FieldType::SingleOLPair) {
            dataStream << fld->olPair.valueUtf16Le;
            size_t len = fld->olPair.valueUtf16Le.length() / 2;
            if (len % 4 != 0) {
                size_t pad = 4 - (len % 4);
                for (size_t i = 0; i < pad; ++i) dataStream << "00";
            }
        } else if (fld->type == FieldType::ListOfOLPairs) {
            for (const auto& pair : fld->refList.pairs) {
                dataStream << pair.valueUtf16Le;
                size_t len = pair.valueUtf16Le.length() / 2;
                if (len % 4 != 0) {
                    size_t pad = 4 - (len % 4);
                    for (size_t i = 0; i < pad; ++i) dataStream << "00";
                }
            }
        }
    }

    ConstructionField::clear();
    return { infoStream.str(), dataStream.str() };
}
