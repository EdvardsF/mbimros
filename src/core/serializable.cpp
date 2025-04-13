#include "serializable.h"
#include <sstream>


void Serializable::registerField(FieldBase* field) {
    fields.push_back(field);
}

std::string Serializable::to_string() const {
    std::ostringstream oss;

    if (embedded_header) {
        oss << embedded_header->to_string();
    }

    for (const auto* f : fields) {
        oss << f->getName() << ": " << f->getValueAsString();
        if (!f->getDescription().empty()) {
            oss << " ..." << f->getDescription();
        }
        oss << "\n";
    }

    if (embedded_buffer) {
        oss << "\n|-----------INFORMATION_BUFFER-----------|\n";
        oss << embedded_buffer->to_string();
    }

    return oss.str();
}

void Serializable::includeHeader(const Serializable* header) {
    embedded_header = header;
}

void Serializable::includeFragmentHeader(const Serializable* header) {
    embedded_fragment_header = header;
}

void Serializable::includeInformationBuffer(std::unique_ptr<Serializable> buffer) {
    embedded_buffer = std::move(buffer);
}