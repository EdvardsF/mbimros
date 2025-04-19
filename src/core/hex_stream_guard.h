#pragma once

#include "hex_stream.h"
#include "exception/mbim_base_exception.h"
#include "exception/mbim_errors.h"
#include "exception/mbim_warnings.h"
#include "../helpers/warning_helpers.h"

class HexStreamParseGuard {
public:
    HexStreamParseGuard(hexStream& hs)
        : hs_(hs), start_offset_(hs.currentOffset()) {}

    ~HexStreamParseGuard() {
        size_t unparsedByteCount = hs_.unparsedByteCount();
        if (unparsedByteCount > 0) {
            HexBufferTooLongWarning ex("last " + std::to_string(unparsedByteCount) + " bytes not parsed.");
            registerWarningHelper(ex);
        }
    }

    size_t startOffset() const {
        return start_offset_;
    }

private:
    hexStream& hs_;
    size_t start_offset_;
};
