#ifndef PACKET_HPP_
#define PACKET_HPP_

#include <cstdint>
#include <vector>

class Packet {
public:
    Packet();
    Packet(uint32_t can_id, uint8_t can_dlc, const std::vector<uint8_t>& data);

    void setCanId(uint32_t can_id);
    uint32_t getCanId() const;

    void setCanDlc(uint8_t can_dlc);
    uint8_t getCanDlc() const;

    void setData(const std::vector<uint8_t>& data);
    std::vector<uint8_t> getData() const;

    std::vector<uint8_t> serialize() const;
    static Packet deserialize(const std::vector<uint8_t>& buffer);

private:
    uint32_t can_id_;
    uint8_t can_dlc_;
    std::vector<uint8_t> data_;
};

#endif /* PACKET_HPP_ */
