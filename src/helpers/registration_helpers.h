#include "../core/information_buffer.h"
#include <string>

template<typename QueryType, typename SetType, typename HostResponseType, typename IndicationType>
void registerUuidCid(const std::string& uuid, size_t cid) {
    register_buffer<QueryType>(uuid, cid, BufferDirection::HostToModemQuery);
    register_buffer<SetType>(uuid, cid, BufferDirection::HostToModemSet);
    register_buffer<HostResponseType>(uuid, cid, BufferDirection::ModemToHostResponse);
    register_buffer<IndicationType>(uuid, cid, BufferDirection::ModemToHostIndication);
}