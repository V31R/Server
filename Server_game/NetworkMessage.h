#pragma once
#include <SFML/Network.hpp>
#include "Logger.h"
#include <string>

class NetworkMessage{

public:

    enum class Type { LOGIN, TIME };

    NetworkMessage();
    NetworkMessage(const NetworkMessage & message);
    NetworkMessage& operator=(const NetworkMessage& message);

    ~NetworkMessage();

    static NetworkMessage getMessageFromUDPSocket(sf::UdpSocket * socket, NetworkMessage::Type type);

    void setCopyData(char* data);
    void getCopyData(char *& data);
    char* getData()const;

    void getSizeFromType(NetworkMessage::Type type);
    size_t getSize()const;

    void setSenderIp(sf::IpAddress address);
    sf::IpAddress getSenderIP()const;

    void setPort(unsigned short port);
    unsigned short getPort()const;

private:

    void allocateMemory();
    void clearMemory();

    char * data;
    size_t size;
    sf::IpAddress sender;
    unsigned short port;

};

