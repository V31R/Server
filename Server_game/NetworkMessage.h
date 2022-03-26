#pragma once
#include <SFML/Network.hpp>
#include "MessageHead.h"
#include "Logger.h"
#include <string>

class NetworkMessage{

public:


    NetworkMessage();
    NetworkMessage(const NetworkMessage & message);
    NetworkMessage& operator=(const NetworkMessage& message);

    ~NetworkMessage();

    static NetworkMessage getMessageFromUDPSocket(sf::UdpSocket & socket);

    void setCopyData(char* data);
    void getCopyData(char *& data);
    char* getData()const;

    void getSizeFromType();
    size_t getSize()const;

    void setSenderIp(const sf::IpAddress & address);
    sf::IpAddress getSenderIP()const;

    void setPort(unsigned short port);
    unsigned short getPort()const;

    void setHeader(const Header & header);
    Header getHeader() const;

private:

    void allocateMemory();
    void clearMemory();
    Header header;
    char * data;
    size_t size;
    sf::IpAddress sender;
    unsigned short port;
    

};

