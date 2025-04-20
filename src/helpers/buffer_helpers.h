
#pragma once

#include "../core/serialization/information_buffer.h"

using bufferRegistry = std::unordered_map<BufferKey, BufferFactory, buffer_key_hash>;

std::unique_ptr<informationBuffer> findBuffer(const bufferRegistry& registry, const std::string& uuid, size_t cid, BufferDirection direction);
