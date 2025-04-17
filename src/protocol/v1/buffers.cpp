#include "buffers.h"

#include <iostream>

void MBIM_DEVICE_CAPS_INFO::parse(hexStream& hs, MESSAGE_QUERY_OR_SET_ENUM command_type) {
    if (command_type == MESSAGE_QUERY_OR_SET_ENUM::QUERY) {

    } else {
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


        auto* data_class = new VariableField<>("DATA_CLASS", "A custom data class in case data class bitmask contains 80000000h, ignored otherwise");
        data_class->bind(this);
        // Must be declared outside the function's arguments, since argument don't get evaluated in a fixed order
        uint32_t off_1 = hs.readUint32LE();
        uint32_t len_1 = hs.readUint32LE();
        data_class->setOffsetLength(off_1, len_1, hs, base_offset);

        auto* device_id = new VariableField<>("DEVICE_ID", "IMEI for GSM-based deices, ESN or MEID for cdma-based");
        device_id->bind(this);
        uint32_t off_2 = hs.readUint32LE();
        uint32_t len_2 = hs.readUint32LE();
        device_id->setOffsetLength(off_2, len_2, hs, base_offset);

        auto* firmware_info = new VariableField<>("FIRMWARE_INFO", "Firmware specific information");
        firmware_info->bind(this);
        uint32_t off_3 = hs.readUint32LE();
        uint32_t len_3 = hs.readUint32LE();
        firmware_info->setOffsetLength(off_3, len_3, hs, base_offset);

        auto* hardware_info = new VariableField<>("HARDWRE_INFO", "Hardware specific information");
        hardware_info->bind(this);
        uint32_t off_4 = hs.readUint32LE();
        uint32_t len_4 = hs.readUint32LE();
        hardware_info->setOffsetLength(off_4, len_4, hs, base_offset);

        data_class->resolve();
        device_id->resolve();
        firmware_info->resolve();
        hardware_info->resolve();
    }
        
}

void register_all_buffers() {
    register_buffer<MBIM_DEVICE_CAPS_INFO>("a289cc33bcbb8b4fb6b0133ec2aae6df", 1); // BASIC_CONNECT + DEVICE_CAPS
}
