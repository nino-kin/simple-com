# Design Pattern

## Sample

### Factory Method (ファクトリーメソッド)

どのサブクラスのインスタンスを作成するかをサブクラスにまかせることで、柔軟なインスタンスの生成が可能です。

### Strategy (ストラテジー)

通信プロトコル (UDPやTCP) を柔軟に切り替えることができるようにします。

### Singleton (シングルトン)

通常、Socketクラスはアプリケーション全体で1つだけ存在すべきです。シングルトンパターンを使用することで、複数のSocketインスタンスが作成されることを防ぎます。

### Decorator (デコレータ)

追加の機能や装飾をSocketクラスに付加できるようにします。例えば、暗号化やログの追跡など。

### Observer (オブザーバ)

通信状態の変化を監視し、必要な処理をトリガーする際に使用します。

```cpp
// 1. Factory Method
class SocketFactory {
    public:
        virtual Socket* createSocket() = 0;
};

class UDPSocketFactory : public SocketFactory {
    public:
        Socket* createSocket() override {
            return new UDPSocket();
        }
};

class TCPSocketFactory : public SocketFactory {
public:
    Socket* createSocket() override {
        return new TCPSocket();
    }
};

// 2. Strategy
class CommunicationStrategy {
    public:
        virtual bool send(const CanFrame& can_frame, const std::string& dest_ip, uint16_t dest_port) = 0;
        virtual bool receive(CanFrame& can_frame, std::string& source_ip, uint16_t& source_port) = 0;
};

class UDPSocket : public Socket, public CommunicationStrategy {
    //...
};

class TCPSocket : public Socket, public CommunicationStrategy {
    //...
};

// 3. Singleton
class SocketManager {
    public:
        static SocketManager& getInstance() {
            static SocketManager instance;
            return instance;
        }

        Socket* getSocket() {
            return socketFactory_->createSocket();
        }

    private:
        SocketFactory* socketFactory_;

        SocketManager() : socketFactory_(nullptr) {
            // Initialize the factory based on the application's needs
            // For example, socketFactory_ = new UDPSocketFactory();
        }

        ~SocketManager() {
            delete socketFactory_;
        }
};

// 4. Decorator
class SocketDecorator : public CommunicationStrategy {
    private:
        CommunicationStrategy* wrapped_;

    public:
        SocketDecorator(CommunicationStrategy* wrapped) : wrapped_(wrapped) {}

        bool send(const CanFrame& can_frame, const std::string& dest_ip, uint16_t dest_port) override {
            // Additional functionality
            return wrapped_->send(can_frame, dest_ip, dest_port);
        }

        bool receive(CanFrame& can_frame, std::string& source_ip, uint16_t& source_port) override {
            // Additional functionality
            return wrapped_->receive(can_frame, source_ip, source_port);
        }
};

// 5. Observer
class SocketObserver {
public:
    virtual void update(Socket* socket) = 0;
};

class ErrorLogger : public SocketObserver {
public:
    void update(Socket* socket) override {
        if (socket->hasError()) {
            // Log error
        }
    }
};
```
