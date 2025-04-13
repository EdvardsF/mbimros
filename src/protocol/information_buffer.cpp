#include "information_buffer.h"

struct MBIM_DEVICE_CAPS_INFO : public informationBuffer {
    Field<DEVICE_TYPE_ENUM> DEVICE_TYPE            { "DEVICE_TYPE", "Type of the device" };

    void parse(hexStream& hs) override {
        DEVICE_TYPE.bind(this);
        DEVICE_TYPE.setFormatter(map_device_type);
        DEVICE_TYPE.set(static_cast<DEVICE_TYPE_ENUM>(hs.read4_le()));
    }
};

// Don't forget to call this function to initialize
void register_all_buffers() {
    register_buffer<MBIM_DEVICE_CAPS_INFO>("a289cc33bcbb8b4fb6b0133ec2aae6df", 1); // BASIC_CONNECT + DEVICE_CAPS
}
