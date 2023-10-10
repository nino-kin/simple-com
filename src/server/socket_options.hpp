#ifndef SOCKET_OPTIONS_HPP_
#define SOCKET_OPTIONS_HPP_

class SocketOptions {
public:
    enum class Option {
        Timeout,
        BufferSize
    };

    SocketOptions();

    void setOption(Option option, int value);
    int getOption(Option option);

private:
    int timeout_;
    int bufferSize_;
};

#endif /* SOCKET_OPTIONS_HPP_ */
