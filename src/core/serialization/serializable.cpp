#include <sstream>
#include <iomanip>
#include <algorithm>

#include "serializable.h"
#include "../exception/mbim_base_exception.h"
#include "../exception/mbim_warnings.h"


void Serializable::registerField(FieldBase* field) {
    fields.push_back(field);
}

std::string Serializable::to_string(bool printWarnings) const {
    std::ostringstream oss;

    if (printWarnings && MBIMBaseWarning::getWarnings().size() > 0) {
        oss << "---------------WARNINGS----------------\n";
        for (const auto& warning : MBIMBaseWarning::getWarnings()) {
            oss << *warning << "\n";
        }
    }

    if (embedded_header) {
        oss << "-----------------HEADER-----------------\n";
        oss << embedded_header->to_string(false);
        if (!embedded_fragment_header) {
            oss << "\n------------COMMAND METADATA-------------\n";
        }
    }

    if (embedded_fragment_header) {
        oss << "\n------------FRAGMENT HEADER-------------\n";
        oss << embedded_fragment_header->to_string(false);
        oss << "\n------------COMMAND METADATA-------------\n";
    }

    bool data_buffer_marker_printed = false;

    size_t max_width = 0;
    for (const auto* f : fields) {
        std::ostringstream tmp;
        tmp << std::left << f->getName() << ": " << f->getValueAsString();
        max_width = std::max(max_width, tmp.str().size());

        if (f->isBitmask()) {
            for (const auto& [flag, _] : f->getBitmaskDescriptions()) {
                std::ostringstream flag_tmp;
                flag_tmp << "  -> " << flag;
                max_width = std::max(max_width, flag_tmp.str().size());
            }
        }
    }
    max_width += 2;

    for (const auto* f : fields) {
        if (!data_buffer_marker_printed && f->isDataField()) {
            oss << "\n---------------DATA BUFFER---------------\n";
            data_buffer_marker_printed = true;
        }

        std::ostringstream line;
        line << std::left << f->getName() << ": " << f->getValueAsString();

        oss << std::left << std::setw(max_width) << line.str();
        if (!f->getDescription().empty()) {
            oss << "// " << f->getDescription();
        }
        oss << "\n";

        if (f->isBitmask()) {
            for (const auto& [flag, description] : f->getBitmaskDescriptions()) {
                std::ostringstream flag_line;
                flag_line << "  -> " << flag;
                oss << std::left << std::setw(max_width) << flag_line.str();
                oss << "// " << description << "\n";
            }
        }
    }

    if (embedded_buffer) {
        oss << "\n----------INFORMATION_BUFFER-----------\n";
        oss << embedded_buffer->to_string(false);
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

Serializable* Serializable::getEmbeddedBuffer() {
    return embedded_buffer.get();
}

const Serializable* Serializable::getEmbeddedBuffer() const {
    return embedded_buffer.get();
}