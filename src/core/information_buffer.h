#pragma once

#include <unordered_map>
#include <memory>
#include <string>
#include <functional>
#include <utility>

#include "serializable.h"
#include "hex_stream.h"
#include "field.h"

#include "../protocol/v1/maps/maps.h"

struct informationBuffer : public Serializable {
    virtual void parse(hexStream&) {
        throw std::runtime_error("This InformationBuffer does not support basic parse()");
    }

    virtual void parse(hexStream&, MESSAGE_QUERY_OR_SET_ENUM) {
        throw std::runtime_error("This InformationBuffer does not support command_type parse()");
    }

    virtual ~informationBuffer() = default;
    

private:
    std::vector<std::unique_ptr<Field<std::string>>> dynamic_fields;
};

struct pair_hash {
    size_t operator()(const std::pair<std::string, uint32_t>& p) const {
        return std::hash<std::string>()(p.first) ^ std::hash<uint32_t>()(p.second);
    }
};

using BufferFactory = std::function<std::unique_ptr<informationBuffer>()>;

extern std::unordered_map<std::pair<std::string, uint32_t>, BufferFactory, pair_hash> buffer_registry;

template<typename T>
void register_buffer(const std::string& uuid, uint32_t cid) {
    buffer_registry[{uuid, cid}] = []() { return std::make_unique<T>(); };
}

void register_all_buffers();
