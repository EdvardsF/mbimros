#include "buffers.h"

#include <iostream>


void EMPTY_BUFFER::parse(hexStream& hs) {
    HexStreamParseGuard _(hs);
}

void NOT_APPLICABLE_BUFFER::parse(hexStream&) {
    throw OpeationNotApplicableException("");
}


void MBIM_DEVICE_CAPS_INFO::parse(hexStream& hs) {
    HexStreamParseGuard guard(hs);

    bindFormatSet(DEVICE_TYPE, this, map_device_type, hs);
    bindFormatSet(CELLULAR_CLASS, this, map_cellular_class, hs);
    bindFormatSet(VOICE_CLASS, this, map_voice_class, hs);
    bindFormatSet(SIM_CLASS, this, map_sim_class, hs);
    bindFormatSet(DATA_CLASS, this, map_data_class, hs);
    bindFormatSet(SMS_CAPS, this, map_sms_caps, hs);
    bindFormatSet(CTRL_CAPS, this, map_ctrl_caps, hs);
    bindSimpleSet(MAX_SESSIONS, this, hs);
    readOLPairAndBind<std::string>("DATA_CLASS", "A custom data class in case data class bitmask contains 80000000h, ignored otherwise", hs, this, guard.startOffset(), 36);
    readOLPairAndBind<std::string>("DEVICE_ID", "IMEI for GSM-based deices, ESN or MEID for cdma-based", hs, this, guard.startOffset(), 36);
    readOLPairAndBind<std::string>("FIRMWARE_INFO", "Firmware specific information", hs, this, guard.startOffset(), 60);
    readOLPairAndBind<std::string>("HARDWRE_INFO", "Hardware specific information", hs, this, guard.startOffset(), 60);   
}

void MBIM_SUBSCRIBER_READY_INFO::parse(hexStream& hs) {
    HexStreamParseGuard guard(hs);

    bindFormatSet(READY_STATE, this, map_subscriber_ready_state, hs);
    VariableField<>* subscriber_id = readOLPair<std::string>("SUBSCRIBER_ID", "IMSI for GSM-based deices, MIN or IRM for cdma-based", hs, guard.startOffset(), 30);
    VariableField<>* sim_iccid = readOLPair<std::string>("SIM_ICCID", "International Circuit Card ID", hs, guard.startOffset(), 40);
    bindFormatSet(READY_INFO, this, map_ready_info_flags, hs);
    bindSimpleSet(ELEMENT_COUNT, this, hs);

    subscriber_id->bind(this);
    sim_iccid->bind(this);

    bindReadElementList<std::string>("TELEPHONE_NUMBER", "Stored telephone number", ELEMENT_COUNT.value, hs, this, guard.startOffset(), 15);
}
void MBIM_SET_RADIO_STATE::parse(hexStream& hs) {
    HexStreamParseGuard guard(hs);
    bindFormatSet(RADIO_SWITCH_STATE, this, map_radio_switch_state, hs);
}

void MBIM_RADIO_STATE_INFO::parse(hexStream& hs) {
    HexStreamParseGuard guard(hs);

    bindFormatSet(HW_RADIO_STATE, this, map_radio_switch_state, hs);
    bindFormatSet(SW_RADIO_STATE, this, map_radio_switch_state, hs);
}

void MBIM_SET_PIN::parse(hexStream& hs) {
    HexStreamParseGuard guard(hs);

    bindFormatSet(MBIM_PIN_TYPE, this, map_pin_type, hs);
    bindFormatSet(MBIM_PIN_OPERATION, this, map_pin_operation, hs);
    readOLPairAndBind<std::string>("MBIM_PIN", "Current PIN", hs, this, guard.startOffset(), 32);
    readOLPairAndBind<std::string>("MBIM_NEW_PIN", "New PIN", hs, this, guard.startOffset(), 32);
}

void MBIM_PIN_INFO::parse(hexStream& hs) {
    HexStreamParseGuard guard(hs);

    bindFormatSet(MBIM_PIN_TYPE, this, map_pin_type, hs);
    bindFormatSet(MBIM_PIN_STATE, this, map_pin_state, hs);
    bindSimpleSet(REMAINING_ATTEMPTS, this, hs);
}




void register_all_buffers() {

    using namespace MBIM_CMD;

    // QueryType
    // SetType
    // HostResponseType
    // IndicationType

    registerUuidCid<
        EMPTY_BUFFER, 
        NOT_APPLICABLE_BUFFER, 
        MBIM_DEVICE_CAPS_INFO, 
        NOT_APPLICABLE_BUFFER
    >(UUID_BASIC_CONNECT::UUID, UUID_BASIC_CONNECT::MBIM_CID_DEVICE_CAPS);

    registerUuidCid<
        EMPTY_BUFFER, 
        NOT_APPLICABLE_BUFFER, 
        MBIM_SUBSCRIBER_READY_INFO, 
        MBIM_SUBSCRIBER_READY_INFO
    >(UUID_BASIC_CONNECT::UUID, UUID_BASIC_CONNECT::MBIM_CID_SUBSCRIBER_READY_STATUS);

    registerUuidCid<
        EMPTY_BUFFER, 
        MBIM_SET_RADIO_STATE, 
        MBIM_RADIO_STATE_INFO,
        MBIM_RADIO_STATE_INFO
    >(UUID_BASIC_CONNECT::UUID, UUID_BASIC_CONNECT::MBIM_CID_RADIO_STATE);

    registerUuidCid<
        EMPTY_BUFFER, 
        MBIM_SET_PIN, 
        MBIM_PIN_INFO,
        NOT_APPLICABLE_BUFFER
    >(UUID_BASIC_CONNECT::UUID, UUID_BASIC_CONNECT::MBIM_CID_PIN);
}

