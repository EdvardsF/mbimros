#include "decoder.h"
#include "../protocol/v1/messages.h"

Decoder::Decoder(std::string hex_data, std::ostream& errorOutput)
    : hs(hex_data), errorStream(errorOutput) {}

void Decoder::decodeRaw() {
    try {
        register_all_buffers();
        size_t saved_offset = hs.currentOffset();
        auto message_type = static_cast<MESSAGE_TYPE_ENUM>(hs.readUint32LE());
        hs.seek(saved_offset);

        static const std::unordered_map<MESSAGE_TYPE_ENUM, std::function<std::unique_ptr<Serializable>(hexStream&)>> message_factory = {
            { MESSAGE_TYPE_ENUM::MBIM_OPEN_MSG,           [](hexStream& hs) { return std::make_unique<MBIM_OPEN_MSG>(hs); }},
            { MESSAGE_TYPE_ENUM::MBIM_CLOSE_MSG,          [](hexStream& hs) { return std::make_unique<MBIM_CLOSE_MSG>(hs); }},
            { MESSAGE_TYPE_ENUM::MBIM_COMMAND_MSG,        [](hexStream& hs) { return std::make_unique<MBIM_COMMAND_MSG>(hs); }},
            { MESSAGE_TYPE_ENUM::MBIM_HOST_ERROR_MSG,     [](hexStream& hs) { return std::make_unique<MBIM_HOST_ERROR_MSG>(hs); }},
            { MESSAGE_TYPE_ENUM::MBIM_OPEN_DONE,          [](hexStream& hs) { return std::make_unique<MBIM_OPEN_DONE>(hs); }},
            { MESSAGE_TYPE_ENUM::MBIM_CLOSE_DONE,         [](hexStream& hs) { return std::make_unique<MBIM_CLOSE_DONE>(hs); }},
            { MESSAGE_TYPE_ENUM::MBIM_COMMAND_DONE,       [](hexStream& hs) { return std::make_unique<MBIM_COMMAND_DONE>(hs); }},
            { MESSAGE_TYPE_ENUM::MBIM_INDICATE_STATUS_MSG,[](hexStream& hs) { return std::make_unique<MBIM_INDICATE_STATUS_MSG>(hs); }}
        };

        auto it = message_factory.find(message_type);
        if (it != message_factory.end()) {
            decodedMessage = it->second(hs);
        } else {
            throw UnsupportedMessageTypeException("MessageType: " + std::to_string(static_cast<uint32_t>(message_type)));
        }

    } catch (const MBIMBaseException& ex) {
        decodedMessage = nullptr;
        errorStream << ex << std::endl;
    } catch (const std::exception& ex) {
        decodedMessage = nullptr;
        errorStream << "General Error: " << ex.what() << std::endl;
    } catch (...) {
        decodedMessage = nullptr;
        errorStream << "Unknown decoding error occurred!" << std::endl;
    }
}

std::string Decoder::to_string() const {
    if (decodedMessage) {
        return decodedMessage->to_string();
    } else {
        return "";
    }
}
