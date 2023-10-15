// DataProcessor.hpp
#ifndef DATA_PROCESSOR_HPP_
#define DATA_PROCESSOR_HPP_

#include "can_frame.hpp"
#include <vector>

class DataProcessor {
public:
    DataProcessor(){};
    ~DataProcessor(){};

    static CanFrame processRequest(const CanFrame& receivedFrame);
};

#endif /* DATA_PROCESSOR_HPP_ */
