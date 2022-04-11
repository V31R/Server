#pragma once
#include "NetworkMessage.h"

class RecievingMsgFromSockets{

public:
	static NetworkMessage getMessageFromUDPSocket(sf::UdpSocket& socket);
	static NetworkMessage getMessageFromTCPSocket(sf::TcpSocket& socket);

};

