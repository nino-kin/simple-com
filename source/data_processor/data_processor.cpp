#include "spdlog/spdlog.h"

#include "data_processor.hpp"

CanFrame DataProcessor::processRequest(const CanFrame& receivedFrame) {
    CanFrame replyFrame = {}; // Initialized reply CanFrame

    // Add logic to process receivedFrame here
    // Example: Processing for specific requests, data conversion, executing database queries, etc.

    // Generate response data and set it in replyFrame
    // Example: Setting response data
    spdlog::info("Generating response data...");
    replyFrame.id_ = 321;
    replyFrame.rtr_ = 0;
    replyFrame.dlc_ = 8;
    replyFrame.data_[0] = 0x08;
    replyFrame.data_[1] = 0x07;
    replyFrame.data_[2] = 0x06;
    replyFrame.data_[3] = 0x05;
    replyFrame.data_[4] = 0x04;
    replyFrame.data_[5] = 0x03;
    replyFrame.data_[6] = 0x02;
    replyFrame.data_[7] = 0x01;

    return replyFrame;
}
