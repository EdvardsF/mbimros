#include "messages.h"

#include <iostream>



MBIM_MESSAGE_HEADER::MBIM_MESSAGE_HEADER(hexStream& hs) {
    HexStreamAlignmentGuard _(hs); // Checks for 4 byte alignment

    bindFormatSet(MESSAGE_TYPE, this, map_type, hs.readUint32LE());
    bindSimpleSet(MESSAGE_LENGTH, this, hs.readUint32LE());
    bindSimpleSet(TRANSACTION_ID, this, hs.readUint32LE());
}


MBIM_FRAGMENT_HEADER::MBIM_FRAGMENT_HEADER(hexStream& hs) {
    HexStreamAlignmentGuard _(hs); // Checks for 4 byte alignment

    bindSimpleSet(TOTAL_FRAGMENTS, this, hs.readUint32LE());
    bindSimpleSet(CURRENT_FRAGMENT, this, hs.readUint32LE());
}


MBIM_OPEN_MSG::MBIM_OPEN_MSG(hexStream& hs) : MESSAGE_HEADER(hs) {
    HexStreamAlignmentGuard _(hs); // Checks for 4 byte alignment
    includeHeader(&MESSAGE_HEADER);
    bindSimpleSet(MAX_CONTROL_TRANSFER, this, hs.readUint32LE());
}

MBIM_CLOSE_MSG::MBIM_CLOSE_MSG(hexStream& hs) : MESSAGE_HEADER(hs) {
    HexStreamAlignmentGuard _(hs); // Checks for 4 byte alignment
    includeHeader(&MESSAGE_HEADER);
}

MBIM_COMMAND_MSG::MBIM_COMMAND_MSG(hexStream& hs) : MESSAGE_HEADER(hs), FRAGMENT_HEADER(hs) {
    HexStreamAlignmentGuard _(hs); // Checks for 4 byte alignment
    includeHeader(&MESSAGE_HEADER);
    includeFragmentHeader(&FRAGMENT_HEADER);

    DEVICE_SERVICE_ID.bind(this);
    DEVICE_SERVICE_ID.setStringFormatter(map_uuid);
    DEVICE_SERVICE_ID.set(hs.readHexBytes(16));

    bindFormatSet(CID, this, get_cid_mapper_for_uuid(DEVICE_SERVICE_ID.value), hs.readUint32LE());
    bindFormatSet(COMMAND_TYPE, this, map_query_or_set, hs.readUint32LE());
    bindSimpleSet(INFORMATION_BUFFER_LENGTH, this, hs.readUint32LE());

    BufferDirection direction = COMMAND_TYPE.value == MESSAGE_QUERY_OR_SET_ENUM::QUERY ? BufferDirection::HostToModemQuery : BufferDirection::HostToModemSet;
    std::unique_ptr<informationBuffer> buffer = findBuffer(buffer_registry, DEVICE_SERVICE_ID.value, CID.value, direction);
    buffer->parse(hs);
    includeInformationBuffer(std::move(buffer));
}

MBIM_HOST_ERROR_MSG::MBIM_HOST_ERROR_MSG(hexStream& hs) : MESSAGE_HEADER(hs) {
    HexStreamAlignmentGuard _(hs); // Checks for 4 byte alignment
    includeHeader(&MESSAGE_HEADER);
    bindFormatSet(ERROR_STATUS_CODE, this, map_host_error, hs.readUint32LE());
}

MBIM_OPEN_DONE::MBIM_OPEN_DONE(hexStream& hs) : MESSAGE_HEADER(hs) {
    HexStreamAlignmentGuard _(hs); // Checks for 4 byte alignment
    includeHeader(&MESSAGE_HEADER);
    bindFormatSet(STATUS, this, map_host_status, hs.readUint32LE());
}

MBIM_CLOSE_DONE::MBIM_CLOSE_DONE(hexStream& hs) : MESSAGE_HEADER(hs) {
    HexStreamAlignmentGuard _(hs); // Checks for 4 byte alignment
    includeHeader(&MESSAGE_HEADER);
    bindFormatSet(STATUS, this, map_host_status, hs.readUint32LE());
}

MBIM_COMMAND_DONE::MBIM_COMMAND_DONE(hexStream& hs) : MESSAGE_HEADER(hs), FRAGMENT_HEADER(hs) {
    HexStreamAlignmentGuard _(hs); // Checks for 4 byte alignment
    includeHeader(&MESSAGE_HEADER);
    includeFragmentHeader(&FRAGMENT_HEADER);

    // update bindFormatSet method to handle UUID
    DEVICE_SERVICE_ID.bind(this);
    DEVICE_SERVICE_ID.setEnumFormatter(map_uuid);
    DEVICE_SERVICE_ID.set(hs.readHexBytes(16));

    bindFormatSet(CID, this, get_cid_mapper_for_uuid(DEVICE_SERVICE_ID.value), hs.readUint32LE());
    bindFormatSet(STATUS, this, map_host_status, hs.readUint32LE());
    bindSimpleSet(INFORMATION_BUFFER_LENGTH, this, hs.readUint32LE());

    std::unique_ptr<informationBuffer> buffer = findBuffer(buffer_registry, DEVICE_SERVICE_ID.value, CID.value, BufferDirection::ModemToHostResponse);
    buffer->parse(hs);
    includeInformationBuffer(std::move(buffer));
}

MBIM_INDICATE_STATUS_MSG::MBIM_INDICATE_STATUS_MSG(hexStream& hs) : MESSAGE_HEADER(hs), FRAGMENT_HEADER(hs) {
    HexStreamAlignmentGuard _(hs); // Checks for 4 byte alignment
    includeHeader(&MESSAGE_HEADER);
    includeFragmentHeader(&FRAGMENT_HEADER);

    DEVICE_SERVICE_ID.bind(this);
    DEVICE_SERVICE_ID.setStringFormatter(map_uuid);
    DEVICE_SERVICE_ID.set(hs.readHexBytes(16));

    bindFormatSet(CID, this, get_cid_mapper_for_uuid(DEVICE_SERVICE_ID.value), hs.readUint32LE());
    bindSimpleSet(INFORMATION_BUFFER_LENGTH, this, hs.readUint32LE());

    std::unique_ptr<informationBuffer> buffer = findBuffer(buffer_registry, DEVICE_SERVICE_ID.value, CID.value, BufferDirection::ModemToHostIndication);
    buffer->parse(hs);
    includeInformationBuffer(std::move(buffer));
}