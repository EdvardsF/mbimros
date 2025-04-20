#include "buffer_helpers.h"

std::unique_ptr<informationBuffer> findBuffer(const bufferRegistry& registry, const std::string& uuid, size_t cid, BufferDirection direction) {
    if (auto it = registry.find({uuid, cid, direction}); it != registry.end()) {
        return it->second();
    } else {
        throw CidNotFoundException("UUID " + uuid + " , CID " + std::to_string(cid) + ".");
    }
}