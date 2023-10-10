#include "spdlog/spdlog.h"

#include "data_processor.hpp"

CanFrame DataProcessor::processRequest(const CanFrame& receivedFrame) {
    CanFrame replyFrame = {}; // Initialized reply CanFrame

    // Add logic to process receivedFrame here
    // Example: Processing for specific requests, data conversion, executing database queries, etc.

    // Generate response data and set it in replyFrame
    // Example: Setting response data
    replyFrame.can_id = 1234; // Set a custom Can ID
    replyFrame.can_dlc = 8;   // Set data length
    replyFrame.data[0] = 0x08;
    replyFrame.data[1] = 0x07;
    replyFrame.data[2] = 0x06;
    replyFrame.data[3] = 0x05;
    replyFrame.data[4] = 0x04;
    replyFrame.data[5] = 0x03;
    replyFrame.data[6] = 0x02;
    replyFrame.data[7] = 0x01;

    return replyFrame;
}
