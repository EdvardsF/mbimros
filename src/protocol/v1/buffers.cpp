#include "buffers.h"

#include <iostream>


void EMPTY_BUFFER::parse(hexStream& hs) {
    HexStreamParseGuard _(hs);
}

void MBIM_DEVICE_CAPS_INFO::parse(hexStream& hs) {
    HexStreamParseGuard guard(hs);

    bindFormatSet(DEVICE_TYPE, this, map_device_type, hs.readUint32LE());
    bindFormatSet(CELLULAR_CLASS, this, map_cellular_class, hs.readUint32LE());
    bindFormatSet(VOICE_CLASS, this, map_voice_class, hs.readUint32LE());
    bindFormatSet(SIM_CLASS, this, map_sim_class, hs.readUint32LE());
    bindFormatSet(DATA_CLASS, this, map_data_class, hs.readUint32LE());
    bindFormatSet(SMS_CAPS, this, map_sms_caps, hs.readUint32LE());
    bindFormatSet(CTRL_CAPS, this, map_ctrl_caps, hs.readUint32LE());
    bindSimpleSet(MAX_SESSIONS, this, hs.readUint32LE());

    auto* data_class = new VariableField<>("DATA_CLASS", "A custom data class in case data class bitmask contains 80000000h, ignored otherwise", 22);
    data_class->bind(this);
    // Must be declared outside the function's arguments, since argument don't get evaluated in a fixed order
    uint32_t off_1 = hs.readUint32LE();
    uint32_t len_1 = hs.readUint32LE();
    data_class->setOffsetLength(off_1, len_1, hs, guard.startOffset());

    auto* device_id = new VariableField<>("DEVICE_ID", "IMEI for GSM-based deices, ESN or MEID for cdma-based", 36);
    device_id->bind(this);
    uint32_t off_2 = hs.readUint32LE();
    uint32_t len_2 = hs.readUint32LE();
    device_id->setOffsetLength(off_2, len_2, hs, guard.startOffset());

    auto* firmware_info = new VariableField<>("FIRMWARE_INFO", "Firmware specific information", 60);
    firmware_info->bind(this);
    uint32_t off_3 = hs.readUint32LE();
    uint32_t len_3 = hs.readUint32LE();
    firmware_info->setOffsetLength(off_3, len_3, hs, guard.startOffset());

    auto* hardware_info = new VariableField<>("HARDWRE_INFO", "Hardware specific information", 60);
    hardware_info->bind(this);
    uint32_t off_4 = hs.readUint32LE();
    uint32_t len_4 = hs.readUint32LE();
    hardware_info->setOffsetLength(off_4, len_4, hs, guard.startOffset());

    data_class->resolve();
    device_id->resolve();
    firmware_info->resolve();
    hardware_info->resolve();
        
}

void MBIM_SUBSCRIBER_READY_INFO::parse(hexStream& hs) {
    HexStreamParseGuard guard(hs);

    bindFormatSet(READY_STATE, this, map_subscriber_ready_state, hs.readUint32LE());

    auto* subscriber_id = new VariableField<>("SUBSCRIBER_ID", "IMSI for GSM-based deices, MIN or IRM for cdma-based", 30);
    
    uint32_t off_1 = hs.readUint32LE();
    uint32_t len_1 = hs.readUint32LE();
    subscriber_id->setOffsetLength(off_1, len_1, hs, guard.startOffset());

    auto* sim_iccid = new VariableField<>("SIM_ICCID", "International Circuit Card ID", 40);
    uint32_t off_2 = hs.readUint32LE();
    uint32_t len_2 = hs.readUint32LE();
    sim_iccid->setOffsetLength(off_2, len_2, hs, guard.startOffset());

    bindFormatSet(READY_INFO, this, map_ready_info_flags, hs.readUint32LE());
    bindSimpleSet(ELEMENT_COUNT, this, hs.readUint32LE());

    subscriber_id->bind(this);
    sim_iccid->bind(this);

    std::vector<VariableField<>*> listItems;
    for (size_t i = 0; i < ELEMENT_COUNT.value; i++) {
        auto* item_n = new VariableField<>("TELEPHONE_NUMBER_" + std::to_string(i), "Stored telephone number", 15);
        item_n->bind(this);
        uint32_t offset = hs.readUint32LE();
        uint32_t length = hs.readUint32LE();
        listItems.push_back(item_n);
        item_n->setOffsetLength(offset, length, hs, guard.startOffset());
    }

    subscriber_id->resolve();
    sim_iccid->resolve();

    for (auto* item: listItems) {
        item->resolve();
    }
}
void MBIM_SET_RADIO_STATE::parse(hexStream& hs) {
    HexStreamParseGuard guard(hs);
    bindFormatSet(RADIO_SWITCH_STATE, this, map_radio_switch_state, hs.readUint32LE());
}

void MBIM_RADIO_STATE_INFO::parse(hexStream& hs) {
    HexStreamParseGuard guard(hs);

    bindFormatSet(HW_RADIO_STATE, this, map_radio_switch_state, hs.readUint32LE());
    bindFormatSet(SW_RADIO_STATE, this, map_radio_switch_state, hs.readUint32LE());
}


void register_all_buffers() {
    // BASIC_CONNECT + DEVICE_CAPS
    register_buffer<EMPTY_BUFFER>("a289cc33bcbb8b4fb6b0133ec2aae6df", 1, BufferDirection::HostToModemQuery);
    register_buffer<MBIM_DEVICE_CAPS_INFO>("a289cc33bcbb8b4fb6b0133ec2aae6df", 1, BufferDirection::ModemToHostResponse);

    // BASIC_CONNECT + MBIM_SUBSCRIBER_READY_STATUS
    register_buffer<EMPTY_BUFFER>("a289cc33bcbb8b4fb6b0133ec2aae6df", 2, BufferDirection::HostToModemQuery);
    register_buffer<MBIM_SUBSCRIBER_READY_INFO>("a289cc33bcbb8b4fb6b0133ec2aae6df", 2, BufferDirection::ModemToHostResponse);
    register_buffer<MBIM_SUBSCRIBER_READY_INFO>("a289cc33bcbb8b4fb6b0133ec2aae6df", 2, BufferDirection::ModemToHostIndication);

    // BASIC_CONNECT + MBIM_CID_RADIO_STATE
    register_buffer<EMPTY_BUFFER>("a289cc33bcbb8b4fb6b0133ec2aae6df", 3, BufferDirection::HostToModemQuery); 
    register_buffer<MBIM_SET_RADIO_STATE>("a289cc33bcbb8b4fb6b0133ec2aae6df", 3, BufferDirection::HostToModemSet); 

    // BASIC_CONNECT + MBIM_CID_RADIO_STATE
    register_buffer<MBIM_SET_RADIO_STATE>("a289cc33bcbb8b4fb6b0133ec2aae6df", 4, BufferDirection::HostToModemSet);
    register_buffer<EMPTY_BUFFER>("a289cc33bcbb8b4fb6b0133ec2aae6df", 4, BufferDirection::HostToModemQuery);
    register_buffer<MBIM_RADIO_STATE_INFO>("a289cc33bcbb8b4fb6b0133ec2aae6df", 4, BufferDirection::ModemToHostResponse);
    register_buffer<MBIM_RADIO_STATE_INFO>("a289cc33bcbb8b4fb6b0133ec2aae6df", 4, BufferDirection::ModemToHostIndication);

}
