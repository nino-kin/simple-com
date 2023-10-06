#include "socket_event.hpp"

SocketEvent::SocketEvent(EventType type)
    : event_type(type), event_data(""), error_code(0) {}

SocketEvent::SocketEvent(EventType type, const std::string& data)
    : event_type(type), event_data(data), error_code(0) {}

SocketEvent::SocketEvent(EventType type, const std::string& data, int error_code)
    : event_type(type), event_data(data), error_code(error_code) {}

EventType SocketEvent::GetType() const {
    return event_type;
}

std::string SocketEvent::GetData() const {
    return event_data;
}

int SocketEvent::GetErrorCode() const {
    return error_code;
}
