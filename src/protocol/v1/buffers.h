#pragma once

#include "../../core/information_buffer.h"
#include "../../core/variable_field.h"
#include "../../core/information_buffer.h"
#include "../../core/exception/mbim_base_exception.h"
#include "../../core/exception/mbim_warnings.h"
#include "../../helpers/helpers.h"


#include "enums.h"
#include "maps/maps.h"

void register_all_buffers();

struct MBIM_DEVICE_CAPS_INFO : public informationBuffer {
    Field<DEVICE_TYPE_ENUM> DEVICE_TYPE   { "DEVICE_TYPE", "Type of the device" };
    Field<uint32_t> CELLULAR_CLASS        { "CELLULAR_CLASS", "Bitmap of relevant cellular technologies" };
    Field<VOICE_CLASS_ENUM> VOICE_CLASS   { "VOICE_CLASS", "Modem voice class" };
    Field<SIM_CLASS_ENUM> SIM_CLASS       { "SIM_CLASS", "Physical SIM or eSIM" };
    Field<uint32_t> DATA_CLASS            { "DATA_CLASS", "Bitmap of radio technologies supported by the modem" };
    Field<uint32_t> SMS_CAPS              { "SMS_CAPS", "Bitmap of SMS types/directions the modem supports" };
    Field<uint32_t> CTRL_CAPS             { "CTRL_CAPS", "Bitmap of the capabilities the modem supports" };
    Field<uint32_t> MAX_SESSIONS          { "MAX_SESSIONS", "Max IP data stream sessions supported" };

    void parse(hexStream& hs, MESSAGE_QUERY_OR_SET_ENUM command_type) override;
};

struct MBIM_SUBSCRIBER_READY_INFO : public informationBuffer {
    Field<SUBSCRIBER_READY_STATE_ENUM> READY_STATE      { "READY_STATE", "Subscription ready state" };
    Field<MBIM_READY_INFO_FLAGS_ENUM> READY_INFO        { "READY_INFO", "Whether to show ICCID in this command" };
    Field<uint32_t> ELEMENT_COUNT                       { "ELEMENT_COUNT", "Number of telephone numbers following this element" };

    void parse(hexStream& hs, MESSAGE_QUERY_OR_SET_ENUM command_type) override;
};



