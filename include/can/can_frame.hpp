#ifndef CAN_FRAME_HPP_
#define CAN_FRAME_HPP_


#include <cstdint>

#define DLC_MAX_SIZE 64 /* CAN-FD  */

struct CanFrame {
    uint32_t id_;
    uint32_t rtr_;
    uint8_t dlc_;
    uint8_t data_[DLC_MAX_SIZE];
};

#endif /* CAN_FRAME_HPP_ */
