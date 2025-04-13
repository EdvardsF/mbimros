#include "../parser/parser.h"
#include "messages.h"

#include <iostream>

MBIM_MESSAGE_HEADER::MBIM_MESSAGE_HEADER(hexStream& hs) {
    MESSAGE_TYPE.bind(this);
    MESSAGE_TYPE.setFormatter(map_type);
    MESSAGE_TYPE.set(static_cast<MESSAGE_TYPE_ENUM>(hs.read4_le()));

    MESSAGE_LENGTH.bind(this);
    MESSAGE_LENGTH.set(hs.read4_le());

    TRANSACTION_ID.bind(this);
    TRANSACTION_ID.set(hs.read4_le());
}


MBIM_FRAGMENT_HEADER::MBIM_FRAGMENT_HEADER(hexStream& hs) {
    TOTAL_FRAGMENTS.bind(this);
    TOTAL_FRAGMENTS.set(hs.read4_le());

    CURRENT_FRAGMENT.bind(this);
    CURRENT_FRAGMENT.set(hs.read4_le());
}


MBIM_OPEN_MSG::MBIM_OPEN_MSG(hexStream& hs) : MESSAGE_HEADER(hs) {
    includeHeader(&MESSAGE_HEADER);
    MAX_CONTROL_TRANSFER.bind(this);
    MAX_CONTROL_TRANSFER.set(hs.read4_le());
}

MBIM_CLOSE_MSG::MBIM_CLOSE_MSG(hexStream& hs) : MESSAGE_HEADER(hs) {
    includeHeader(&MESSAGE_HEADER);
}

MBIM_COMMAND_MSG::MBIM_COMMAND_MSG(hexStream& hs) : MESSAGE_HEADER(hs), FRAGMENT_HEADER(hs) {
    includeHeader(&MESSAGE_HEADER);
    includeFragmentHeader(&FRAGMENT_HEADER);

    DEVICE_SERVICE_ID.bind(this);
    DEVICE_SERVICE_ID.setFormatter(map_uuid);
    DEVICE_SERVICE_ID.set(hs.read_n_text_be(16));

    CID.bind(this);
    CID.setFormatter(get_cid_mapper_for_uuid(DEVICE_SERVICE_ID.value));
    CID.set(hs.read4_le());

    COMMAND_TYPE.bind(this);
    COMMAND_TYPE.setFormatter(map_query_or_set);
    COMMAND_TYPE.set(static_cast<MESSAGE_QUERY_OR_SET_ENUM>(hs.read4_le()));

    INFORMATION_BUFFER_LENGTH.bind(this);
    INFORMATION_BUFFER.bind(this);
    INFORMATION_BUFFER_LENGTH.set(hs.read4_le());
    INFORMATION_BUFFER.set(hs.read_n_text_be(INFORMATION_BUFFER_LENGTH.value));
}

MBIM_HOST_ERROR_MSG::MBIM_HOST_ERROR_MSG(hexStream& hs) : MESSAGE_HEADER(hs) {
    includeHeader(&MESSAGE_HEADER);
    ERROR_STATUS_CODE.bind(this);
    ERROR_STATUS_CODE.setFormatter(map_host_error);
    ERROR_STATUS_CODE.set(static_cast<MBIM_PROTOCOL_ERROR_CODES_ENUM>(hs.read4_le()));
}

MBIM_OPEN_DONE::MBIM_OPEN_DONE(hexStream& hs) : MESSAGE_HEADER(hs) {
    includeHeader(&MESSAGE_HEADER);
    STATUS.bind(this);
    STATUS.setFormatter(map_host_status);
    STATUS.set(static_cast<MBIM_STATUS_TO_HOST_ENUM>(hs.read4_le()));
}

MBIM_CLOSE_DONE::MBIM_CLOSE_DONE(hexStream& hs) : MESSAGE_HEADER(hs) {
    includeHeader(&MESSAGE_HEADER);
    STATUS.bind(this);
    STATUS.setFormatter(map_host_status);
    STATUS.set(static_cast<MBIM_STATUS_TO_HOST_ENUM>(hs.read4_le()));
}

MBIM_COMMAND_DONE::MBIM_COMMAND_DONE(hexStream& hs) : MESSAGE_HEADER(hs), FRAGMENT_HEADER(hs) {
    includeHeader(&MESSAGE_HEADER);
    includeFragmentHeader(&FRAGMENT_HEADER);

    DEVICE_SERVICE_ID.bind(this);
    DEVICE_SERVICE_ID.setFormatter(map_uuid);
    DEVICE_SERVICE_ID.set(hs.read_n_text_be(16));

    CID.bind(this);
    CID.setFormatter(get_cid_mapper_for_uuid(DEVICE_SERVICE_ID.value));
    CID.set(hs.read4_le());

    STATUS.bind(this);
    STATUS.setFormatter(map_host_status);
    STATUS.set(static_cast<MBIM_STATUS_TO_HOST_ENUM>(hs.read4_le()));

    INFORMATION_BUFFER_LENGTH.bind(this);
    INFORMATION_BUFFER.bind(this);
    INFORMATION_BUFFER_LENGTH.set(hs.read4_le());
    INFORMATION_BUFFER.set(hs.read_n_text_be(INFORMATION_BUFFER_LENGTH.value));
}