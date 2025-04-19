#pragma once

#include <unordered_map>
#include <memory>
#include <string>
#include <functional>
#include <utility>
#include <tuple>

#include "serializable.h"
#include "hex_stream.h"
#include "field.h"
#include "../protocol/v1/maps/maps.h"

enum class BufferDirection {
    HostToModemSet,
    HostToModemQuery,
    ModemToHostResponse,
    ModemToHostIndication
};

struct informationBuffer : public Serializable {
    virtual void parse(hexStream&) {
        throw std::runtime_error("This InformationBuffer does not support basic parse()");
    }

    virtual ~informationBuffer() = default;

private:
    std::vector<std::unique_ptr<Field<std::string>>> dynamic_fields;
};

using BufferKey = std::tuple<std::string, uint32_t, BufferDirection>;

struct buffer_key_hash {
    size_t operator()(const BufferKey& key) const {
        auto& [uuid, cid, direction] = key;
        size_t h1 = std::hash<std::string>()(uuid);
        size_t h2 = std::hash<uint32_t>()(cid);
        size_t h3 = std::hash<int>()(static_cast<int>(direction));
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

using BufferFactory = std::function<std::unique_ptr<informationBuffer>()>;

extern std::unordered_map<BufferKey, BufferFactory, buffer_key_hash> buffer_registry;

template<typename T>
void register_buffer(const std::string& uuid, uint32_t cid, BufferDirection direction) {
    buffer_registry[{uuid, cid, direction}] = []() { return std::make_unique<T>(); };
}

void register_all_buffers();
