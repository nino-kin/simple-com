#include "packet.hpp"

Packet::Packet() {}

Packet::Packet(const std::string& data) : data(data) {}

void Packet::SetData(const std::string& data) {
    this->data = data;
}

std::string Packet::GetData() const {
    return data;
}

void Packet::SetHeader(const std::string& header) {
    this->header = header;
}

std::string Packet::GetHeader() const {
    return header;
}

std::string Packet::Serialize() const {
    return header + data;
}

bool Packet::Deserialize(const std::string& serializedData) {
    if (serializedData.length() < header.length()) {
        return false; // Invalid data if header is not long enough
    }

    header = serializedData.substr(0, header.length());
    data = serializedData.substr(header.length());
    return true;
}
