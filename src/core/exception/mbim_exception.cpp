#include "mbim_exception.h"


MBIMException::MBIMException(const std::string& msg)
    : message(msg) {}

const char* MBIMException::what() const noexcept {
    return message.c_str();
}

std::ostream& operator<<(std::ostream& os, const MBIMException& ex) {
    os << "[ ERROR ] (" << ex.type() << ")\n"
       << "  - " << ex.getMessage() << "\n";
    return os;
}

std::string MBIMException::type() const {
    return "MBIMException";
}

const std::string& MBIMException::getMessage() const {
    return message;
}


MBIMWarning::MBIMWarning(const std::string& msg)
    : message(msg) {}

MBIMWarning::~MBIMWarning() = default;

void MBIMWarning::registerWarning(const MBIMWarning& warning) {
    warnings().push_back(warning);
}


const std::string& MBIMWarning::getMessage() const {
    return message;
}

const std::vector<MBIMWarning>& MBIMWarning::getWarnings() {
    return warnings();
}

std::string MBIMWarning::type() const {
    return "MBIMWarning";
}

void MBIMWarning::clearWarnings() {
    warnings().clear();
}

std::ostream& operator<<(std::ostream& os, const MBIMWarning& ex) {
    os << "[ WARNING ] (" << ex.type() << ")\n"
       << "  - " << ex.getMessage() << "\n";
    return os;
}

std::vector<MBIMWarning>& MBIMWarning::warnings() {
    static std::vector<MBIMWarning> warnings_instance;
    return warnings_instance;
}
