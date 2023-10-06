#ifndef SOCKET_LISTENER_H_
#define SOCKET_LISTENER_H_

#include <string>
#include <functional>
#include <thread>
#include <atomic>

class SocketListener {
public:
    using ConnectionCallback = std::function<void(int)>;

    SocketListener(const std::string& host, const uint16_t port);
    ~SocketListener();

    bool Start();
    void Stop();

    void SetConnectionCallback(ConnectionCallback callback);

private:
    std::string host;
    uint16_t port;
    int listener_fd;
    std::thread listener_thread;
    std::atomic<bool> running;
    ConnectionCallback connection_callback;

    void Listen();
};

#endif /* SOCKET_LISTENER_H_ */
