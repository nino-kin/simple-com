#ifndef CAN_CAN_FRAME_HPP_
#define CAN_CAN_FRAME_HPP_

#include <string>
#include <cstdint>

#define DLC_MAX_SIZE 64 // CAN-FD

/// @brief CAN frame structure
struct CanFrame {
    using Id = std::uint32_t;

    Id id_;
    uint32_t rtr_;
    uint8_t dlc_;
    uint8_t data_[DLC_MAX_SIZE];
};

#endif /* CAN_CAN_FRAME_HPP_ */
