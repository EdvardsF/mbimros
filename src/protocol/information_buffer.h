#pragma once

#include <unordered_map>
#include <memory>
#include <string>
#include <functional>
#include <utility>

#include "../core/serializable.h"
#include "../core/hex_stream.h"
#include "../core/field.h"

#include "maps.h"
#include "enums.h"

struct informationBuffer : public Serializable {
    virtual void parse(hexStream& hs) = 0;
    virtual ~informationBuffer() = default;
};

struct pair_hash {
    size_t operator()(const std::pair<std::string, uint32_t>& p) const {
        return std::hash<std::string>()(p.first) ^ std::hash<uint32_t>()(p.second);
    }
};

using BufferFactory = std::function<std::unique_ptr<informationBuffer>()>;

inline std::unordered_map<std::pair<std::string, uint32_t>, BufferFactory, pair_hash> buffer_registry;

template<typename T>
void register_buffer(const std::string& uuid, uint32_t cid) {
    buffer_registry[{uuid, cid}] = []() { return std::make_unique<T>(); };
}
