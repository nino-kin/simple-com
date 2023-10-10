#include <iostream>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <unistd.h>

#include "spdlog/spdlog.h"

#include "socket_options.hpp"

SocketOptions::SocketOptions()
    : timeout_(0), bufferSize_(8192) {}

void SocketOptions::setOption(Option option, int value) {
    switch (option) {
        case Option::Timeout:
            timeout_ = value;
            break;
        case Option::BufferSize:
            bufferSize_ = value;
            break;
    }
}

int SocketOptions::getOption(Option option) {
    switch (option) {
        case Option::Timeout:
            return timeout_;
        case Option::BufferSize:
            return bufferSize_;
    }

    return -1; // Proper error handling is required in case of an error.
}
