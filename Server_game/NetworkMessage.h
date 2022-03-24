#pragma once
#include <SFML/Network.hpp>


class NetworkMessage{

public:

    enum class Type { LOGIN };

    NetworkMessage();
    ~NetworkMessage();

    static NetworkMessage getMessageFromUDPSocket(sf::UdpSocket& socket, unsigned short port,NetworkMessage::Type type);

    void setCopyData(char* data);
    void getCopyData(char *& data);

    void getSizeFromType(NetworkMessage::Type type);
    size_t getSize()const;

    void setSenderIp(sf::IpAddress address);
    sf::IpAddress getSenderIP()const;

private:

    void allocateMemory();
    void clearMemory();

    char * data;
    size_t size;
    sf::IpAddress sender;
    

};

