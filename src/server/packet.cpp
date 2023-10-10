#include "packet.hpp"

Packet::Packet() : can_id_(0), can_dlc_(0) {}

Packet::Packet(uint32_t can_id, uint8_t can_dlc, const std::vector<uint8_t>& data)
    : can_id_(can_id), can_dlc_(can_dlc), data_(data) {}

void Packet::setCanId(uint32_t can_id) {
    this->can_id_ = can_id;
}

uint32_t Packet::getCanId() const {
    return can_id_;
}

void Packet::setCanDlc(uint8_t can_dlc) {
    this->can_dlc_ = can_dlc;
}

uint8_t Packet::getCanDlc() const {
    return can_dlc_;
}

void Packet::setData(const std::vector<uint8_t>& data) {
    this->data_ = data;
}

std::vector<uint8_t> Packet::getData() const {
    return data_;
}

std::vector<uint8_t> Packet::serialize() const {
    std::vector<uint8_t> buffer;
    buffer.reserve(13); // Reserve space for can_id, can_dlc, and data

    // Serialize can_id (4 bytes)
    buffer.push_back((can_id_ >> 24) & 0xFF);
    buffer.push_back((can_id_ >> 16) & 0xFF);
    buffer.push_back((can_id_ >> 8) & 0xFF);
    buffer.push_back(can_id_ & 0xFF);

    // Serialize can_dlc (1 byte)
    buffer.push_back(can_dlc_);

    // Append data
    buffer.insert(buffer.end(), data_.begin(), data_.end());

    return buffer;
}

Packet Packet::deserialize(const std::vector<uint8_t>& buffer) {
    if (buffer.size() < 5) {
        throw std::runtime_error("Invalid buffer size for deserialization");
    }

    // Deserialize can_id (4 bytes)
    uint32_t can_id = (buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | buffer[3];

    // Deserialize can_dlc (1 byte)
    uint8_t can_dlc = buffer[4];

    // Extract data
    std::vector<uint8_t> data(buffer.begin() + 5, buffer.end());

    return Packet(can_id, can_dlc, data);
}
