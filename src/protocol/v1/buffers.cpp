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

void MBIM_PROVIDER::parse(hexStream& hs) {
    HexStreamParseGuard guard(hs);

    VariableField<>* provderId = readOLPair<std::string>("PROVIDER_ID", "MCC+MNC/SID", hs, guard.startOffset(), 12);
    bindBitmaskSet(MBIM_PROVIDER_STATE, this, map_provider_state, hs);
    VariableField<>* provderName = readOLPair<std::string>("PROVIDER_NAME", "Provider's string format name", hs, guard.startOffset(), 40);
    bindBitmaskSet(MBIM_CELLULAR_CLASS, this, map_cellular_class, hs);
    bindSimpleSet(RSSI, this, hs);
    bindSimpleSet(ERROR_RATE, this, hs);

    provderId->bind(this);
    provderName->bind(this);
}

void MBIM_SET_REGISTRATION_STATE::parse(hexStream& hs) {
    HexStreamParseGuard guard(hs);

    VariableField<>* provderId = readOLPair<std::string>("PROVIDER_ID", "MCC+MNC/SID", hs, guard.startOffset(), 12);
    bindFormatSet(REGISTER_ACTION, this, map_register_action, hs);
    bindBitmaskSet(DATA_CLASS, this, map_data_class, hs);

    provderId->bind(this);
}

void MBIM_REGISTRATION_STATE_INFO::parse(hexStream& hs) {
    HexStreamParseGuard guard(hs);

    bindFormatSet(NW_ERROR, this, map_3gpp_nw_error, hs);
    bindFormatSet(REGISTER_STATE, this, map_register_state, hs);
    bindFormatSet(REGISTER_MODE, this, map_register_mode, hs);
    bindBitmaskSet(AVAILABLE_DATA_CLLASSES, this, map_data_class, hs);
    bindBitmaskSet(CURRENT_CELLULAR_CLASS, this, map_cellular_class, hs);
    VariableField<>* provderId = readOLPair<std::string>("PROVIDER_ID", "MCC+MNC/SID", hs, guard.startOffset(), 12);
    VariableField<>* provderName = readOLPair<std::string>("PROVIDER_NAME", "Provider's string format name", hs, guard.startOffset(), 40);
    VariableField<>* roamingText = readOLPair<std::string>("ROAMING_TEXT", "Additional information to the user when the registration state is either MBIMRegisterStatePartner or MBIMRegisterStateRoaming", hs, guard.startOffset(), 126);
    bindBitmaskSet(REGISTRATION_FLAG, this, map_registration_flags, hs);

    provderId->bind(this);
    provderName->bind(this);
    roamingText->bind(this);
}

void MBIM_SET_PACKET_SERVICE::parse(hexStream& hs) {
    HexStreamParseGuard guard(hs);

    bindFormatSet(PACKET_SERVICE_ACTION, this, map_packet_service_action, hs);
}

void MBIM_PACKET_SERVICE_INFO::parse(hexStream& hs) {
    HexStreamParseGuard guard(hs);

    bindFormatSet(NW_ERROR, this, map_3gpp_nw_error, hs);
    bindFormatSet(PACKET_SERVICE_STATE, this, map_packet_service_state, hs);
    bindBitmaskSet(HIGHEST_AVAILABLE_DATA_CLASS, this, map_data_class, hs);
    bindSimpleSet64(UPLINK_SPEED, this, hs);
    bindSimpleSet64(DOWNLINK_SPEED, this, hs);
}

void MBIM_SET_SIGNAL_STATE::parse(hexStream& hs) {
    HexStreamParseGuard guard(hs);

    bindSimpleSet(SIGNAL_STRENGTH_INTERVAL, this, hs);
    bindSimpleSet(RSSI_THRESHOLD, this, hs);
    bindSimpleSet(ERROR_RATE_THRESHOLD, this, hs);
}

void MBIM_SIGNAL_STATE_INFO::parse(hexStream& hs) {
    HexStreamParseGuard guard(hs);

    bindSimpleSet(RSSI, this, hs);
    bindSimpleSet(ERROR_RATE, this, hs);
    bindSimpleSet(SIGNAL_STRENGTH_INTERVAL, this, hs);
    bindSimpleSet(RSSI_THRESHOLD, this, hs);
    bindSimpleSet(ERROR_RATE_THRESHOLD, this, hs);
}

void MBIM_SET_CONNECT::parse(hexStream& hs) {
    HexStreamParseGuard guard(hs);

    bindSimpleSet(SESSION_ID, this, hs);
    bindFormatSet(ACTIVATION_COMMAND, this, map_activation_command, hs);
    VariableField<>* accessString = readOLPair<std::string>("ACCESS_STRING", "", hs, guard.startOffset(), 200);
    VariableField<>* userName = readOLPair<std::string>("USER_NAME", "", hs, guard.startOffset(), 510);
    VariableField<>* password = readOLPair<std::string>("PASSWORD", "", hs, guard.startOffset(), 510);
    bindFormatSet(COMPRESSION, this, map_compression, hs);
    bindFormatSet(AUTH_PROTOCOL, this, map_auth_protocol, hs);
    bindFormatSet(IP_TYPE, this, map_context_ip_type, hs);
    bindStringSet(CONTEXT_TYPE, this, map_context_uuid, hs); 

    accessString->bind(this);
    userName->bind(this);
    password->bind(this);
}

void MBIM_CONNECT_INFO::parse(hexStream& hs) {
    HexStreamParseGuard guard(hs);

    bindSimpleSet(SESSION_ID, this, hs);
    bindFormatSet(ACTIVATION_STATE, this, map_activation_state, hs);
    bindFormatSet(VOICE_CALL_STATE, this, map_voice_call_state, hs);
    bindFormatSet(IP_TYPE, this, map_context_ip_type, hs);
    bindStringSet(CONTEXT_TYPE, this, map_context_uuid, hs);
    bindFormatSet(NW_ERROR, this, map_3gpp_nw_error, hs);
}




void register_all_buffers() {

    using namespace MBIM_CMD;

    // Register Argument order:
    // ------------------------
    // QueryType              |
    // SetType                |
    // HostResponseType       |
    // IndicationType         |
    // ------------------------

    // ---------------------------UUID_BASIC_CONNECT---------------------------

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

    registerUuidCid<
        EMPTY_BUFFER, 
        MBIM_PROVIDER, 
        MBIM_PROVIDER,
        NOT_APPLICABLE_BUFFER
    >(UUID_BASIC_CONNECT::UUID, UUID_BASIC_CONNECT::MBIM_CID_HOME_PROVIDER);

    registerUuidCid<
        EMPTY_BUFFER, 
        MBIM_SET_REGISTRATION_STATE, 
        MBIM_REGISTRATION_STATE_INFO,
        MBIM_REGISTRATION_STATE_INFO
    >(UUID_BASIC_CONNECT::UUID, UUID_BASIC_CONNECT::MBIM_CID_REGISTER_STATE);

    registerUuidCid<
        EMPTY_BUFFER, 
        MBIM_SET_SIGNAL_STATE, 
        MBIM_SIGNAL_STATE_INFO,
        MBIM_SIGNAL_STATE_INFO
    >(UUID_BASIC_CONNECT::UUID, UUID_BASIC_CONNECT::MBIM_CID_SIGNAL_STATE);

    registerUuidCid<
        MBIM_CONNECT_INFO, 
        MBIM_SET_CONNECT, 
        MBIM_CONNECT_INFO,
        MBIM_CONNECT_INFO
    >(UUID_BASIC_CONNECT::UUID, UUID_BASIC_CONNECT::MBIM_CID_CONNECT);

}

