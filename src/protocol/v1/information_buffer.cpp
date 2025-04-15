#include "information_buffer.h"

struct MBIM_DEVICE_CAPS_INFO : public informationBuffer {
    Field<DEVICE_TYPE_ENUM> DEVICE_TYPE             { "DEVICE_TYPE", "Type of the device" };
    Field<uint32_t> CELLULAR_CLASS                  { "CELLULAR_CLASS", "Bitmap of relevant cellular technologies" };
    Field<VOICE_CLASS_ENUM> VOICE_CLASS             { "VOICE_CLASS", "Modem voice class" };
    Field<SIM_CLASS_ENUM> SIM_CLASS                 { "SIM_CLASS", "Physical SIM or eSIM" };
    Field<DATA_CLASS_ENUM> DATA_CLASS               { "DATA_CLASS", "Bitmap of radio technologies supported by the modem" };
    Field<SMS_CAPS_ENUM> SMS_CAPS                   { "SMS_CAPS", "Bitmap of SMS types/directions the modem supports" };
    Field<CTRL_CAPS_ENUM> CTRL_CAPS                 { "CTRL_CAPS", "Bitmap of the capabilities the modem supports" };
    Field<uint32_t> MAX_SESSIONS                    { "MAX_SESSIONS", "Max IP data stream sessions supported"};
    // TODO MORE


    void parse(hexStream& hs) override {
        DEVICE_TYPE.bind(this);
        DEVICE_TYPE.setFormatter(map_device_type);
        DEVICE_TYPE.set(static_cast<DEVICE_TYPE_ENUM>(hs.read4_le()));

        CELLULAR_CLASS.bind(this);
        CELLULAR_CLASS.setFormatter(map_cellular_class);
        CELLULAR_CLASS.set(hs.read4_le());

        VOICE_CLASS.bind(this);
        VOICE_CLASS.setFormatter(map_voice_class);
        VOICE_CLASS.set(static_cast<VOICE_CLASS_ENUM>(hs.read4_le()));
        
        SIM_CLASS.bind(this);
        SIM_CLASS.setFormatter(map_sim_class);
        SIM_CLASS.set(static_cast<SIM_CLASS_ENUM>(hs.read4_le()));

        DATA_CLASS.bind(this);
        DATA_CLASS.set(static_cast<DATA_CLASS_ENUM>(hs.read4_le()));

        SMS_CAPS.bind(this);
        SMS_CAPS.set(static_cast<SMS_CAPS_ENUM>(hs.read4_le()));

        CTRL_CAPS.bind(this);
        CTRL_CAPS.set(static_cast<CTRL_CAPS_ENUM>(hs.read4_le()));

        MAX_SESSIONS.bind(this);
        MAX_SESSIONS.set(hs.read4_le());
    }
};



// Don't forget to call this function to initialize
void register_all_buffers() {
    register_buffer<MBIM_DEVICE_CAPS_INFO>("a289cc33bcbb8b4fb6b0133ec2aae6df", 1); // BASIC_CONNECT + DEVICE_CAPS
}
