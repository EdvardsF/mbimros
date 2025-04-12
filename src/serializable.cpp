#include "serializable.h"
#include <sstream>

void Serializable::addField(const std::string& name, const std::string& value) {
    printableFields.emplace_back(name, value);
}

std::string Serializable::to_string() const {
    std::ostringstream oss;
    for (const auto& [name, value] : printableFields) {
        oss << name << ": " << value << "\n";
    }
    return oss.str();
}