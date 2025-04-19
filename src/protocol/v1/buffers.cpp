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
    readOLPairAndBind<std::string>("DATA_CLASS", "A custom data class in case data class bitmask contains 80000000h, ignored otherwise", hs, this, guard.startOffset(), 36);
    readOLPairAndBind<std::string>("DEVICE_ID", "IMEI for GSM-based deices, ESN or MEID for cdma-based", hs, this, guard.startOffset(), 36);
    readOLPairAndBind<std::string>("FIRMWARE_INFO", "Firmware specific information", hs, this, guard.startOffset(), 60);
    readOLPairAndBind<std::string>("HARDWRE_INFO", "Hardware specific information", hs, this, guard.startOffset(), 60);
        
}

void MBIM_SUBSCRIBER_READY_INFO::parse(hexStream& hs) {
    HexStreamParseGuard guard(hs);

    bindFormatSet(READY_STATE, this, map_subscriber_ready_state, hs.readUint32LE());
    VariableField<>* subscriber_id = readOLPair<std::string>("SUBSCRIBER_ID", "IMSI for GSM-based deices, MIN or IRM for cdma-based", hs, guard.startOffset(), 30);
    VariableField<>* sim_iccid = readOLPair<std::string>("SIM_ICCID", "International Circuit Card ID", hs, guard.startOffset(), 40);
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
