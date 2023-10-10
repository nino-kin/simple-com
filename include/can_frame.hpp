#ifndef CAN_FRAME_HPP_
#define CAN_FRAME_HPP_

#include <cstdint>

struct CanFrame {
    uint32_t can_id;
    uint8_t can_dlc;
    uint8_t data[8];
};

#endif /* CAN_FRAME_HPP_ */
