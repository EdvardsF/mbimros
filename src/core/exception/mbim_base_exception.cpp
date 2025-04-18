#include "mbim_base_exception.h"

MBIMBaseException::MBIMBaseException(const std::string& msg)
    : message(msg) {}

const char* MBIMBaseException::what() const noexcept {
    return message.c_str();
}

std::ostream& operator<<(std::ostream& os, const MBIMBaseException& ex) {
    os << "[ ERROR ] (" << ex.type() << ")\n"
       << "  - " << ex.getMessage() << "\n";
    return os;
}

std::string MBIMBaseException::type() const {
    return "MBIMException";
}

const std::string& MBIMBaseException::getMessage() const {
    return message;
}

// ------------------------- Warnings -------------------------

MBIMBaseWarning::MBIMBaseWarning(const std::string& msg)
    : message(msg) {}

MBIMBaseWarning::~MBIMBaseWarning() = default;

void MBIMBaseWarning::registerWarning(std::unique_ptr<MBIMBaseWarning> warning) {
    warnings().push_back(std::move(warning));
}

const std::string& MBIMBaseWarning::getMessage() const {
    return message;
}

const std::vector<std::unique_ptr<MBIMBaseWarning>>& MBIMBaseWarning::getWarnings() {
    return warnings();
}

std::string MBIMBaseWarning::type() const {
    return "MBIMWarning";
}

void MBIMBaseWarning::clearWarnings() {
    warnings().clear();
}

std::ostream& operator<<(std::ostream& os, const MBIMBaseWarning& ex) {
    os << "[ WARNING ] (" << ex.type() << ")\n"
       << "  - " << ex.getMessage() << "\n";
    return os;
}

std::vector<std::unique_ptr<MBIMBaseWarning>>& MBIMBaseWarning::warnings() {
    static std::vector<std::unique_ptr<MBIMBaseWarning>> warnings_instance;
    return warnings_instance;
}
