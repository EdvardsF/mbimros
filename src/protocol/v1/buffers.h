#pragma once

#include "../../core/serialization/information_buffer.h"
#include "../../core/serialization/variable_field.h"
#include "../../core/exception/mbim_base_exception.h"
#include "../../core/exception/mbim_warnings.h"
#include "../../core/hex/guards.h"

#include "../../helpers/binding_helpers.h"
#include "../../helpers/registration_helpers.h"



#include "enums.h"
#include "maps/maps.h"

void register_all_buffers();

struct EMPTY_BUFFER : public informationBuffer {
    void parse(hexStream& hs) override;
};

struct NOT_APPLICABLE_BUFFER : public informationBuffer {
    void parse(hexStream& hs) override;
};

struct MBIM_DEVICE_CAPS_INFO : public informationBuffer {
    Field<DEVICE_TYPE_ENUM> DEVICE_TYPE   { "DEVICE_TYPE", "Type of the device" };
    Field<uint32_t> CELLULAR_CLASS        { "CELLULAR_CLASS", "Bitmap of relevant cellular technologies" };
    Field<VOICE_CLASS_ENUM> VOICE_CLASS   { "VOICE_CLASS", "Modem voice class" };
    Field<SIM_CLASS_ENUM> SIM_CLASS       { "SIM_CLASS", "Physical SIM or eSIM" };
    Field<uint32_t> DATA_CLASS            { "DATA_CLASS", "Bitmap of radio technologies supported by the modem" };
    Field<uint32_t> SMS_CAPS              { "SMS_CAPS", "Bitmap of SMS types/directions the modem supports" };
    Field<uint32_t> CTRL_CAPS             { "CTRL_CAPS", "Bitmap of the capabilities the modem supports" };
    Field<uint32_t> MAX_SESSIONS          { "MAX_SESSIONS", "Max IP data stream sessions supported" };

    void parse(hexStream& hs) override;
};

struct MBIM_SUBSCRIBER_READY_INFO : public informationBuffer {
    Field<SUBSCRIBER_READY_STATE_ENUM> READY_STATE      { "READY_STATE", "Subscription ready state" };
    Field<MBIM_READY_INFO_FLAGS_ENUM> READY_INFO        { "READY_INFO", "Whether to show ICCID in this command" };
    Field<uint32_t> ELEMENT_COUNT                       { "ELEMENT_COUNT", "Number of telephone numbers following this element" };

    void parse(hexStream& hs) override;
};

struct MBIM_SET_RADIO_STATE : public informationBuffer {
    Field<MBIM_RADIO_SWITCH_STATE_ENUM> RADIO_SWITCH_STATE      { "RADIO_SWITCH_STATE", "Controls whether radio is turned on" };

    void parse(hexStream& hs) override;
};

struct MBIM_RADIO_STATE_INFO : public informationBuffer {
    Field<MBIM_RADIO_SWITCH_STATE_ENUM> HW_RADIO_STATE      { "HW_RADIO_STATE", "Whether radio is turned on at hardware level" };
    Field<MBIM_RADIO_SWITCH_STATE_ENUM> SW_RADIO_STATE      { "SW_RADIO_STATE", "Whether radio is turned on at software level" };

    void parse(hexStream& hs) override;
};

struct MBIM_SET_PIN : public informationBuffer {
    Field<PIN_TYPE_ENUM> MBIM_PIN_TYPE                { "MBIM_PIN_TYPE", "Type of PIN (e.g., PIN1, PIN2, device PIN, etc.)" };
    Field<PIN_OPERATION_ENUM> MBIM_PIN_OPERATION      { "MBIM_PIN_OPERATION", "Type of operation done to the PIN" };

    void parse(hexStream& hs) override;
};

struct MBIM_PIN_INFO : public informationBuffer {
    Field<PIN_TYPE_ENUM> MBIM_PIN_TYPE        { "MBIM_PIN_TYPE", "Type of PIN (e.g., PIN1, PIN2, device PIN, etc.)" };
    Field<PIN_STATE_ENUM> MBIM_PIN_STATE      { "MBIM_PIN_STATE", "Whether the specified PIN is currently locked or unlocked" };
    Field<uint32_t> REMAINING_ATTEMPTS        { "REMAINING_ATTEMPTS", "Number of remaining attempts before the PIN is blocked" };

    void parse(hexStream& hs) override;
};

// TODO: UNFINISHED - REQUIRES NESTING
struct MBIM_PIN_LIST_INFO : public informationBuffer {
    Field<PIN_TYPE_ENUM> MBIM_PIN_TYPE        { "MBIM_PIN_TYPE", "Type of PIN (e.g., PIN1, PIN2, device PIN, etc.)" };
    Field<PIN_STATE_ENUM> MBIM_PIN_STATE      { "MBIM_PIN_STATE", "Whether the specified PIN is currently locked or unlocked" };
    Field<uint32_t> REMAINING_ATTEMPTS        { "REMAINING_ATTEMPTS", "Number of remaining attempts before the PIN is blocked" };

    void parse(hexStream& hs) override;
};

struct MBIM_PROVIDER : public informationBuffer {
    Field<uint32_t> MBIM_PROVIDER_STATE                        { "MBIM_PROVIDER_STATE", "Bitmap of whether the network provider is currently the home provider, a preferred provider, whether it’s visible, etc" };
    Field<uint32_t> MBIM_CELLULAR_CLASS                        { "MBIM_CELLULAR_CLASS", "Bitmap of relevant cellular technologies" };
    Field<uint32_t> RSSI                                       { "RSSI", "Strength of the wireless signal" };
    Field<uint32_t> ERROR_RATE                                 { "ERROR_RATE", "A coded value that represents a percentage range of error rates" };

    void parse(hexStream& hs) override;
};

// TODO: MBIM_CID_PREFERRED_PROVIDERS, MBIM_CID_VISIBLE_PROVIDERS - requires nesting

struct MBIM_SET_REGISTRATION_STATE : public informationBuffer {
    Field<REGISTER_ACTION_ENUM> REGISTER_ACTION       { "REGISTER_ACTION", "Registration action that the device is requested to perform" };
    Field<uint32_t> DATA_CLASS                        { "DATA_CLASS", "Bitmap of radio technologies supported by the modem" };

    void parse(hexStream& hs) override;
};

struct MBIM_REGISTRATION_STATE_INFO : public informationBuffer {
    Field<MBIM_3GPP_NW_ERROR_ENUM> NW_ERROR      { "NW_ERROR", "Detailed 3GPP network error code indicating why registration or service failed" };
    Field<REGISTER_STATE_ENUM> REGISTER_STATE    { "REGISTER_STATE", "Registration state (e.g., home, roaming, denied)" };
    Field<REGISTER_MODE_ENUM> REGISTER_MODE      { "REGISTER_MODE", "Registration mode" };
    Field<uint32_t> AVAILABLE_DATA_CLLASSES      { "AVAILABLE_DATA_CLLASSES", "Bitmask of supported data bearer technologies (e.g., LTE, UMTS, EVDO)" };
    Field<uint32_t> CURRENT_CELLULAR_CLASS       { "CURRENT_CELLULAR_CLASS", "Current radio class" };
    Field<uint32_t> REGISTRATION_FLAG            { "REGISTRATION_FLAG", "Registration flags" };

    void parse(hexStream& hs) override;
};

