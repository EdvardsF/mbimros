#include "information_buffer.h"

std::unordered_map<std::tuple<std::string, uint32_t, BufferDirection>, BufferFactory, buffer_key_hash> buffer_registry;
