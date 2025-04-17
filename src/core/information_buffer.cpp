#include "information_buffer.h"

std::unordered_map<std::pair<std::string, uint32_t>, BufferFactory, pair_hash> buffer_registry;
