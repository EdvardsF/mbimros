#include "serializable.h"
#include <sstream>

void Serializable::registerField(FieldBase* field) {
    fields.push_back(field);
}

std::string Serializable::to_string() const {
    std::ostringstream oss;
    for (const auto* f : fields) {
        oss << f->getName() << ": " << f->getValueAsString();
        if (!f->getDescription().empty()) {
            oss << " (" << f->getDescription() << ")";
        }
        oss << "\n";
    }
    return oss.str();
}
