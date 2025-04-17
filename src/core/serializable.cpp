#include "serializable.h"
#include <sstream>


void Serializable::registerField(FieldBase* field) {
    fields.push_back(field);
}

std::string Serializable::to_string() const {
    std::ostringstream oss;

    if (embedded_header) {
        oss << "-----------------HEADER-----------------\n";
        oss << embedded_header->to_string();
    }

    if (embedded_fragment_header) {
        oss << "\n------------FRAGMENT HEADER-------------\n";
        oss << embedded_fragment_header->to_string();
        oss << "\n------------COMMAND METADATA-------------\n";

    }


    bool data_buffer_marker_printed = false;

    for (const auto* f : fields) {
        // Check if it's a VariableField and the marker wasn't printed yet
        if (!data_buffer_marker_printed && f->isDataField()) {
            oss << "\n---------------DATA BUFFER---------------\n";
            data_buffer_marker_printed = true;
        }

        if (f->isBitmask()) {
            oss << f->getName() << ": ..." << f->getDescription() << " | RAW=" << f->getValueAsString();
        } else {
            oss << f->getName() << ": " << f->getValueAsString();
            if (!f->getDescription().empty()) {
                oss << " ..." << f->getDescription();
            }
            oss << "\n";
        }
    }

    if (embedded_buffer) {
        oss << "\n----------INFORMATION_BUFFER-----------\n";
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