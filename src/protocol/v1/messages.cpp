#include "messages.h"

#include <iostream>



MBIM_MESSAGE_HEADER::MBIM_MESSAGE_HEADER(hexStream& hs) {
    HexStreamAlignmentGuard _(hs);

    bindFormatSet(MESSAGE_TYPE, this, map_type, hs);
    bindSimpleSet(MESSAGE_LENGTH, this, hs);
    bindSimpleSet(TRANSACTION_ID, this, hs);
}


MBIM_FRAGMENT_HEADER::MBIM_FRAGMENT_HEADER(hexStream& hs) {
    HexStreamAlignmentGuard _(hs);

    bindSimpleSet(TOTAL_FRAGMENTS, this, hs);
    bindSimpleSet(CURRENT_FRAGMENT, this, hs);
}


MBIM_OPEN_MSG::MBIM_OPEN_MSG(hexStream& hs) : MESSAGE_HEADER(hs) {
    HexStreamAlignmentGuard _(hs);
    includeHeader(&MESSAGE_HEADER);
    bindSimpleSet(MAX_CONTROL_TRANSFER, this, hs);
}

MBIM_CLOSE_MSG::MBIM_CLOSE_MSG(hexStream& hs) : MESSAGE_HEADER(hs) {
    HexStreamAlignmentGuard _(hs);
    includeHeader(&MESSAGE_HEADER);
}

MBIM_COMMAND_MSG::MBIM_COMMAND_MSG(hexStream& hs) : MESSAGE_HEADER(hs), FRAGMENT_HEADER(hs) {
    HexStreamAlignmentGuard _(hs);
    includeHeader(&MESSAGE_HEADER);
    includeFragmentHeader(&FRAGMENT_HEADER);

    bindStringSet(DEVICE_SERVICE_ID, this, map_uuid, hs);  
    bindFormatSet(CID, this, get_cid_mapper_for_uuid(DEVICE_SERVICE_ID.value), hs);
    bindFormatSet(COMMAND_TYPE, this, map_query_or_set, hs);
    bindSimpleSet(INFORMATION_BUFFER_LENGTH, this, hs);

    BufferDirection direction = COMMAND_TYPE.value == MESSAGE_QUERY_OR_SET_ENUM::QUERY ? BufferDirection::HostToModemQuery : BufferDirection::HostToModemSet;
    std::unique_ptr<informationBuffer> buffer = findBuffer(buffer_registry, DEVICE_SERVICE_ID.value, CID.value, direction);
    buffer->parse(hs);
    includeInformationBuffer(std::move(buffer));
}

MBIM_HOST_ERROR_MSG::MBIM_HOST_ERROR_MSG(hexStream& hs) : MESSAGE_HEADER(hs) {
    HexStreamAlignmentGuard _(hs);
    includeHeader(&MESSAGE_HEADER);
    bindFormatSet(ERROR_STATUS_CODE, this, map_host_error, hs);
}

MBIM_OPEN_DONE::MBIM_OPEN_DONE(hexStream& hs) : MESSAGE_HEADER(hs) {
    HexStreamAlignmentGuard _(hs);
    includeHeader(&MESSAGE_HEADER);
    bindFormatSet(STATUS, this, map_host_status, hs);
}

MBIM_CLOSE_DONE::MBIM_CLOSE_DONE(hexStream& hs) : MESSAGE_HEADER(hs) {
    HexStreamAlignmentGuard _(hs);
    includeHeader(&MESSAGE_HEADER);
    bindFormatSet(STATUS, this, map_host_status, hs);
}

MBIM_COMMAND_DONE::MBIM_COMMAND_DONE(hexStream& hs) : MESSAGE_HEADER(hs), FRAGMENT_HEADER(hs) {
    HexStreamAlignmentGuard _(hs);
    includeHeader(&MESSAGE_HEADER);
    includeFragmentHeader(&FRAGMENT_HEADER);

    bindStringSet(DEVICE_SERVICE_ID, this, map_uuid, hs);    
    bindFormatSet(CID, this, get_cid_mapper_for_uuid(DEVICE_SERVICE_ID.value), hs);
    bindFormatSet(STATUS, this, map_host_status, hs);
    bindSimpleSet(INFORMATION_BUFFER_LENGTH, this, hs);

    std::unique_ptr<informationBuffer> buffer = findBuffer(buffer_registry, DEVICE_SERVICE_ID.value, CID.value, BufferDirection::ModemToHostResponse);
    buffer->parse(hs);
    includeInformationBuffer(std::move(buffer));
}

MBIM_INDICATE_STATUS_MSG::MBIM_INDICATE_STATUS_MSG(hexStream& hs) : MESSAGE_HEADER(hs), FRAGMENT_HEADER(hs) {
    HexStreamAlignmentGuard _(hs);
    includeHeader(&MESSAGE_HEADER);
    includeFragmentHeader(&FRAGMENT_HEADER);

    bindStringSet(DEVICE_SERVICE_ID, this, map_uuid, hs);  
    bindFormatSet(CID, this, get_cid_mapper_for_uuid(DEVICE_SERVICE_ID.value), hs);
    bindSimpleSet(INFORMATION_BUFFER_LENGTH, this, hs);

    std::unique_ptr<informationBuffer> buffer = findBuffer(buffer_registry, DEVICE_SERVICE_ID.value, CID.value, BufferDirection::ModemToHostIndication);
    buffer->parse(hs);
    includeInformationBuffer(std::move(buffer));
}