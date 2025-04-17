#include "mbim_exception.h"


MBIMException::MBIMException(const std::string& msg)
    : message(msg) {}

const char* MBIMException::what() const noexcept {
    return message.c_str();
}

std::ostream& operator<<(std::ostream& os, const MBIMException& ex) {
    os << "[ ERROR ] " << ex.type() << ":\n"
       << "  - " << ex.message << "\n";
    return os;
}

std::string MBIMException::type() const {
    return "MBIMException";
}


MBIMWarning::MBIMWarning(const std::string& msg)
    : message(msg) {
    warnings().push_back(*this);
}

std::ostream& operator<<(std::ostream& os, const MBIMException& ex) {
    os << "[ WARNING ] " << ex.type() << ":\n"
       << "  - " << ex.message << "\n";
    return os;
}

const std::string& MBIMWarning::getMessage() const {
    return message;
}

const std::vector<MBIMWarning>& MBIMWarning::getWarnings() {
    return warnings();
}

void MBIMWarning::clearWarnings() {
    warnings().clear();
}

std::ostream& operator<<(std::ostream& os, const MBIMWarning& warn) {
    os << "MBIM WARNING! " << warn.message << "\n";
    return os;
}

std::vector<MBIMWarning>& MBIMWarning::warnings() {
    static std::vector<MBIMWarning> warnings_instance;
    return warnings_instance;
}
