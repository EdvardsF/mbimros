#include "buffers.h"

#include <iostream>

void EMPTY_BUFFER::parse(hexStream& hs) {
    if (hs.availableBytes() != 0) {
        HexBufferTooLongWarning ex("last " + std::to_string(hs.availableBytes()) + " bytes not parsed.");
        registerWarningHelper(ex);
    }
}

void MBIM_DEVICE_CAPS_INFO::parse(hexStream& hs) {
    size_t base_offset = hs.currentOffset();

    DEVICE_TYPE.bind(this);
    DEVICE_TYPE.setEnumFormatter(map_device_type);
    DEVICE_TYPE.set(static_cast<DEVICE_TYPE_ENUM>(hs.readUint32LE()));

    CELLULAR_CLASS.bind(this);
    CELLULAR_CLASS.setBitmaskFormatter(map_cellular_class);
    CELLULAR_CLASS.set(hs.readUint32LE());

    VOICE_CLASS.bind(this);
    VOICE_CLASS.setEnumFormatter(map_voice_class);
    VOICE_CLASS.set(static_cast<VOICE_CLASS_ENUM>(hs.readUint32LE()));

    SIM_CLASS.bind(this);
    SIM_CLASS.setEnumFormatter(map_sim_class);
    SIM_CLASS.set(static_cast<SIM_CLASS_ENUM>(hs.readUint32LE()));

    DATA_CLASS.bind(this);
    DATA_CLASS.setBitmaskFormatter(map_data_class);
    DATA_CLASS.set(hs.readUint32LE());

    SMS_CAPS.bind(this);
    SMS_CAPS.setBitmaskFormatter(map_sms_caps);
    SMS_CAPS.set(hs.readUint32LE());

    CTRL_CAPS.bind(this);
    CTRL_CAPS.setBitmaskFormatter(map_ctrl_caps);
    CTRL_CAPS.set(hs.readUint32LE());

    MAX_SESSIONS.bind(this);
    MAX_SESSIONS.set(hs.readUint32LE());


    auto* data_class = new VariableField<>("DATA_CLASS", "A custom data class in case data class bitmask contains 80000000h, ignored otherwise", 22);
    data_class->bind(this);
    // Must be declared outside the function's arguments, since argument don't get evaluated in a fixed order
    uint32_t off_1 = hs.readUint32LE();
    uint32_t len_1 = hs.readUint32LE();
    data_class->setOffsetLength(off_1, len_1, hs, base_offset);

    auto* device_id = new VariableField<>("DEVICE_ID", "IMEI for GSM-based deices, ESN or MEID for cdma-based", 36);
    device_id->bind(this);
    uint32_t off_2 = hs.readUint32LE();
    uint32_t len_2 = hs.readUint32LE();
    device_id->setOffsetLength(off_2, len_2, hs, base_offset);

    auto* firmware_info = new VariableField<>("FIRMWARE_INFO", "Firmware specific information", 60);
    firmware_info->bind(this);
    uint32_t off_3 = hs.readUint32LE();
    uint32_t len_3 = hs.readUint32LE();
    firmware_info->setOffsetLength(off_3, len_3, hs, base_offset);

    auto* hardware_info = new VariableField<>("HARDWRE_INFO", "Hardware specific information", 60);
    hardware_info->bind(this);
    uint32_t off_4 = hs.readUint32LE();
    uint32_t len_4 = hs.readUint32LE();
    hardware_info->setOffsetLength(off_4, len_4, hs, base_offset);

    data_class->resolve();
    device_id->resolve();
    firmware_info->resolve();
    hardware_info->resolve();

    if (hs.availableBytes() != 0) {
        HexBufferTooLongWarning ex("last " + std::to_string(hs.availableBytes()) + " bytes not parsed.");
        registerWarningHelper(ex);
    }
        
}

void MBIM_SUBSCRIBER_READY_INFO::parse(hexStream& hs) {
    size_t base_offset = hs.currentOffset();

    READY_STATE.bind(this);
    READY_STATE.setEnumFormatter(map_subscriber_ready_state);
    READY_STATE.set(static_cast<SUBSCRIBER_READY_STATE_ENUM>(hs.readUint32LE()));

    auto* subscriber_id = new VariableField<>("SUBSCRIBER_ID", "IMSI for GSM-based deices, MIN or IRM for cdma-based", 30);
    
    uint32_t off_1 = hs.readUint32LE();
    uint32_t len_1 = hs.readUint32LE();
    subscriber_id->setOffsetLength(off_1, len_1, hs, base_offset);

    auto* sim_iccid = new VariableField<>("SIM_ICCID", "International Circuit Card ID", 40);
    uint32_t off_2 = hs.readUint32LE();
    uint32_t len_2 = hs.readUint32LE();
    sim_iccid->setOffsetLength(off_2, len_2, hs, base_offset);

    READY_INFO.bind(this);
    READY_INFO.setEnumFormatter(map_ready_info_flags);
    READY_INFO.set(static_cast<MBIM_READY_INFO_FLAGS_ENUM>(hs.readUint32LE()));

    ELEMENT_COUNT.bind(this);
    ELEMENT_COUNT.set(hs.readUint32LE());

    subscriber_id->bind(this);
    sim_iccid->bind(this);

    std::vector<VariableField<>*> listItems;
    for (size_t i = 0; i < ELEMENT_COUNT.value; i++) {
        auto* item_n = new VariableField<>("TELEPHONE_NUMBER_" + std::to_string(i), "Stored telephone number", 15);
        item_n->bind(this);
        uint32_t offset = hs.readUint32LE();
        uint32_t length = hs.readUint32LE();
        listItems.push_back(item_n);
        item_n->setOffsetLength(offset, length, hs, base_offset);
    }

    subscriber_id->resolve();
    sim_iccid->resolve();

    for (auto* item: listItems) {
        item->resolve();
    }

    if (hs.availableBytes() != 0) {
        HexBufferTooLongWarning ex("last " + std::to_string(hs.availableBytes()) + " bytes not parsed.");
        registerWarningHelper(ex);
    }
}
void MBIM_SET_RADIO_STATE::parse(hexStream& hs) {
    RADIO_SWITCH_STATE.bind(this);
    RADIO_SWITCH_STATE.setEnumFormatter(map_radio_switch_state);
    RADIO_SWITCH_STATE.set(static_cast<MBIM_RADIO_SWITCH_STATE_ENUM>(hs.readUint32LE()));

    if (hs.availableBytes() != 0) {
        HexBufferTooLongWarning ex("last " + std::to_string(hs.availableBytes()) + " bytes not parsed.");
        registerWarningHelper(ex);
    }
}

void MBIM_RADIO_STATE_INFO::parse(hexStream& hs) {
    HW_RADIO_STATE.bind(this);
    HW_RADIO_STATE.setEnumFormatter(map_radio_switch_state);
    HW_RADIO_STATE.set(static_cast<MBIM_RADIO_SWITCH_STATE_ENUM>(hs.readUint32LE()));

    SW_RADIO_STATE.bind(this);
    SW_RADIO_STATE.setEnumFormatter(map_radio_switch_state);
    SW_RADIO_STATE.set(static_cast<MBIM_RADIO_SWITCH_STATE_ENUM>(hs.readUint32LE()));

    if (hs.availableBytes() != 0) {
        HexBufferTooLongWarning ex("last " + std::to_string(hs.availableBytes()) + " bytes not parsed.");
        registerWarningHelper(ex);
    }
}


void register_all_buffers() {
    register_buffer<EMPTY_BUFFER>("a289cc33bcbb8b4fb6b0133ec2aae6df", 1, BufferDirection::HostToModemQuery); // BASIC_CONNECT + DEVICE_CAPS
    register_buffer<MBIM_DEVICE_CAPS_INFO>("a289cc33bcbb8b4fb6b0133ec2aae6df", 1, BufferDirection::ModemToHostResponse); // BASIC_CONNECT + DEVICE_CAPS

    register_buffer<EMPTY_BUFFER>("a289cc33bcbb8b4fb6b0133ec2aae6df", 2, BufferDirection::HostToModemQuery); // BASIC_CONNECT + MBIM_SUBSCRIBER_READY_STATUS
    register_buffer<MBIM_SUBSCRIBER_READY_INFO>("a289cc33bcbb8b4fb6b0133ec2aae6df", 2, BufferDirection::ModemToHostResponse); // BASIC_CONNECT + MBIM_SUBSCRIBER_READY_STATUS
    register_buffer<MBIM_SUBSCRIBER_READY_INFO>("a289cc33bcbb8b4fb6b0133ec2aae6df", 2, BufferDirection::ModemToHostIndication); // BASIC_CONNECT + MBIM_SUBSCRIBER_READY_STATUS

    register_buffer<EMPTY_BUFFER>("a289cc33bcbb8b4fb6b0133ec2aae6df", 3, BufferDirection::HostToModemQuery); // BASIC_CONNECT + MBIM_CID_RADIO_STATE
    register_buffer<MBIM_SET_RADIO_STATE>("a289cc33bcbb8b4fb6b0133ec2aae6df", 3, BufferDirection::HostToModemSet); // BASIC_CONNECT + MBIM_CID_RADIO_STATE

    register_buffer<MBIM_SET_RADIO_STATE>("a289cc33bcbb8b4fb6b0133ec2aae6df", 3, BufferDirection::HostToModemSet); // BASIC_CONNECT + MBIM_CID_RADIO_STATE
    register_buffer<EMPTY_BUFFER>("a289cc33bcbb8b4fb6b0133ec2aae6df", 3, BufferDirection::HostToModemQuery); // BASIC_CONNECT + MBIM_CID_RADIO_STATE
    register_buffer<MBIM_RADIO_STATE_INFO>("a289cc33bcbb8b4fb6b0133ec2aae6df", 3, BufferDirection::ModemToHostResponse); // BASIC_CONNECT + MBIM_CID_RADIO_STATE
    register_buffer<MBIM_RADIO_STATE_INFO>("a289cc33bcbb8b4fb6b0133ec2aae6df", 3, BufferDirection::ModemToHostIndication); // BASIC_CONNECT + MBIM_CID_RADIO_STATE

}
