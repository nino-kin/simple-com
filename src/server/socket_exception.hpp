#ifndef SOCKET_EXCEPTION_H_
#define SOCKET_EXCEPTION_H_

#include <exception>
#include <string>

class SocketException : public std::exception {
    public:
        SocketException(const std::string& message) : error_message(message) {}
        virtual const char* what() const noexcept override {
            return error_message.c_str();
        }

    private:
        std::string error_message;
};

#endif /* SOCKET_EXCEPTION_H_ */
