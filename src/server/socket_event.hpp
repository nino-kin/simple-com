#ifndef SOCKET_EVENT_H_
#define SOCKET_EVENT_H_

#include <string>

enum class EventType { CONNECTED, DISCONNECTED, DATA_RECEIVED, ERROR };

class SocketEvent {
public:
    SocketEvent(EventType type);
    SocketEvent(EventType type, const std::string& data);
    SocketEvent(EventType type, const std::string& data, int error_code);

    EventType GetType() const;
    std::string GetData() const;
    int GetErrorCode() const;

private:
    EventType event_type;
    std::string event_data;
    int error_code;
};

#endif /* SOCKET_EVENT_H_ */
