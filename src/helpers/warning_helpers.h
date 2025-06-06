#pragma once

#include "../core/exception/mbim_base_exception.h"
#include <memory>

template<typename WarningType>
void registerWarningHelper(const WarningType& warning) {
    MBIMBaseWarning::registerWarning(std::make_unique<WarningType>(warning));
}
