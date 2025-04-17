#include "messages.h"

#include <iostream>

MBIM_MESSAGE_HEADER::MBIM_MESSAGE_HEADER(hexStream& hs) {
    MESSAGE_TYPE.bind(this);
    MESSAGE_TYPE.setEnumFormatter(map_type);
    MESSAGE_TYPE.set(static_cast<MESSAGE_TYPE_ENUM>(hs.readUint32LE()));

    MESSAGE_LENGTH.bind(this);
    MESSAGE_LENGTH.set(hs.readUint32LE());

    TRANSACTION_ID.bind(this);
    TRANSACTION_ID.set(hs.readUint32LE());
}


MBIM_FRAGMENT_HEADER::MBIM_FRAGMENT_HEADER(hexStream& hs) {
    TOTAL_FRAGMENTS.bind(this);
    TOTAL_FRAGMENTS.set(hs.readUint32LE());

    CURRENT_FRAGMENT.bind(this);
    CURRENT_FRAGMENT.set(hs.readUint32LE());
}


MBIM_OPEN_MSG::MBIM_OPEN_MSG(hexStream& hs) : MESSAGE_HEADER(hs) {
    includeHeader(&MESSAGE_HEADER);
    MAX_CONTROL_TRANSFER.bind(this);
    MAX_CONTROL_TRANSFER.set(hs.readUint32LE());
}

MBIM_CLOSE_MSG::MBIM_CLOSE_MSG(hexStream& hs) : MESSAGE_HEADER(hs) {
    includeHeader(&MESSAGE_HEADER);
}

MBIM_COMMAND_MSG::MBIM_COMMAND_MSG(hexStream& hs) : MESSAGE_HEADER(hs), FRAGMENT_HEADER(hs) {
    includeHeader(&MESSAGE_HEADER);
    includeFragmentHeader(&FRAGMENT_HEADER);

    DEVICE_SERVICE_ID.bind(this);
    DEVICE_SERVICE_ID.setStringFormatter(map_uuid);
    DEVICE_SERVICE_ID.set(hs.readHexBytes(16));

    CID.bind(this);
    CID.setNumberFormatter(get_cid_mapper_for_uuid(DEVICE_SERVICE_ID.value));
    CID.set(hs.readUint32LE());

    COMMAND_TYPE.bind(this);
    COMMAND_TYPE.setEnumFormatter(map_query_or_set);
    COMMAND_TYPE.set(static_cast<MESSAGE_QUERY_OR_SET_ENUM>(hs.readUint32LE()));

    INFORMATION_BUFFER_LENGTH.bind(this);
    INFORMATION_BUFFER_LENGTH.set(hs.readUint32LE());

    // TODO: To avoid duplicating this in each message struct, move it to somewhere later 
    if (auto it = buffer_registry.find({DEVICE_SERVICE_ID.value, CID.value}); it != buffer_registry.end()) {
        auto buffer = it->second();
        buffer->parse(hs, COMMAND_TYPE.value);
        includeInformationBuffer(std::move(buffer));
    } else {
        hs.readHexBytes(INFORMATION_BUFFER_LENGTH.value);
    }
}

MBIM_HOST_ERROR_MSG::MBIM_HOST_ERROR_MSG(hexStream& hs) : MESSAGE_HEADER(hs) {
    includeHeader(&MESSAGE_HEADER);
    ERROR_STATUS_CODE.bind(this);
    ERROR_STATUS_CODE.setEnumFormatter(map_host_error);
    ERROR_STATUS_CODE.set(static_cast<MBIM_PROTOCOL_ERROR_CODES_ENUM>(hs.readUint32LE()));
}

MBIM_OPEN_DONE::MBIM_OPEN_DONE(hexStream& hs) : MESSAGE_HEADER(hs) {
    includeHeader(&MESSAGE_HEADER);
    STATUS.bind(this);
    STATUS.setEnumFormatter(map_host_status);
    STATUS.set(static_cast<MBIM_STATUS_TO_HOST_ENUM>(hs.readUint32LE()));
}

MBIM_CLOSE_DONE::MBIM_CLOSE_DONE(hexStream& hs) : MESSAGE_HEADER(hs) {
    includeHeader(&MESSAGE_HEADER);
    STATUS.bind(this);
    STATUS.setEnumFormatter(map_host_status);
    STATUS.set(static_cast<MBIM_STATUS_TO_HOST_ENUM>(hs.readUint32LE()));
}

MBIM_COMMAND_DONE::MBIM_COMMAND_DONE(hexStream& hs) : MESSAGE_HEADER(hs), FRAGMENT_HEADER(hs) {
    includeHeader(&MESSAGE_HEADER);
    includeFragmentHeader(&FRAGMENT_HEADER);

    DEVICE_SERVICE_ID.bind(this);
    DEVICE_SERVICE_ID.setEnumFormatter(map_uuid);
    DEVICE_SERVICE_ID.set(hs.readHexBytes(16));

    CID.bind(this);
    CID.setNumberFormatter(get_cid_mapper_for_uuid(DEVICE_SERVICE_ID.value));
    CID.set(hs.readUint32LE());

    STATUS.bind(this);
    STATUS.setEnumFormatter(map_host_status);
    STATUS.set(static_cast<MBIM_STATUS_TO_HOST_ENUM>(hs.readUint32LE()));

    INFORMATION_BUFFER_LENGTH.bind(this);
    INFORMATION_BUFFER_LENGTH.set(hs.readUint32LE());

    // TODO: To avoid duplicating this in each message struct, move it to somewhere later 
    if (auto it = buffer_registry.find({DEVICE_SERVICE_ID.value, CID.value}); it != buffer_registry.end()) {
        auto buffer = it->second();
        buffer->parse(hs);
        includeInformationBuffer(std::move(buffer));
    } else {
        hs.readHexBytes(INFORMATION_BUFFER_LENGTH.value);
    }
}

MBIM_INDICATE_STATUS_MSG::MBIM_INDICATE_STATUS_MSG(hexStream& hs) : MESSAGE_HEADER(hs), FRAGMENT_HEADER(hs) {
    includeHeader(&MESSAGE_HEADER);
    includeFragmentHeader(&FRAGMENT_HEADER);

    DEVICE_SERVICE_ID.bind(this);
    DEVICE_SERVICE_ID.setStringFormatter(map_uuid);
    DEVICE_SERVICE_ID.set(hs.readHexBytes(16));

    CID.bind(this);
    CID.setNumberFormatter(get_cid_mapper_for_uuid(DEVICE_SERVICE_ID.value));
    CID.set(hs.readUint32LE());

    INFORMATION_BUFFER_LENGTH.bind(this);
    INFORMATION_BUFFER_LENGTH.set(hs.readUint32LE());

    // TODO: To avoid duplicating this in each message struct, move it to somewhere later 
    if (auto it = buffer_registry.find({DEVICE_SERVICE_ID.value, CID.value}); it != buffer_registry.end()) {
        auto buffer = it->second();
        buffer->parse(hs);
        includeInformationBuffer(std::move(buffer));
    } else {
        hs.readHexBytes(INFORMATION_BUFFER_LENGTH.value);
    }
}