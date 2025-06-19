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
    Field<PIN_TYPE_ENUM> MBIM_PIN_TYPE      { "MBIM_PIN_TYPE", "" };
    Field<PIN_OPERATION_ENUM> MBIM_PIN_OPERATION      { "MBIM_PIN_OPERATION", "" };

    void parse(hexStream& hs) override;
};

struct MBIM_PIN_INFO : public informationBuffer {
    Field<PIN_TYPE_ENUM> MBIM_PIN_TYPE      { "MBIM_PIN_TYPE", "" };
    Field<PIN_STATE_ENUM> MBIM_PIN_STATE      { "MBIM_PIN_STATE", "" };
    Field<uint32_t> REMAINING_ATTEMPTS         { "REMAINING_ATTEMPTS", "Number of telephone numbers following this element" };

    void parse(hexStream& hs) override;
};


