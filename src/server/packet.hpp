#ifndef PACKET_H_
#define PACKET_H_

#include <string>

class Packet {
public:
    Packet();
    Packet(const std::string& data);

    void SetData(const std::string& data);
    std::string GetData() const;

    void SetHeader(const std::string& header);
    std::string GetHeader() const;

    std::string Serialize() const;
    bool Deserialize(const std::string& serializedData);

private:
    std::string header;
    std::string data;
};

#endif /* PACKET_H_ */
