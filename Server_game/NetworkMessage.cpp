#include "NetworkMessage.h"

NetworkMessage::NetworkMessage():

	data { nullptr },
	size{ 0 }

{}

NetworkMessage::NetworkMessage(const NetworkMessage& message):

	data{ nullptr },
	size{ message.getSize() },
	sender{ message.getSenderIP() }

{

	allocateMemory();
	setCopyData(message.getData());

}

NetworkMessage& NetworkMessage::operator=(const NetworkMessage& message){


	if (data) {

		if (size != message.getSize()) {

			clearMemory();
			size = message.getSize();
			allocateMemory();

		}
		else {

			memset(data, 0, size);

		}

	}

	setCopyData(message.getData());

}

NetworkMessage::~NetworkMessage()
{
}

NetworkMessage NetworkMessage::getMessageFromUDPSocket(sf::UdpSocket& socket, unsigned short port, NetworkMessage::Type type)
{
	return NetworkMessage();
}

void NetworkMessage::setCopyData(char* data)
{
}

void NetworkMessage::getCopyData(char*& data)
{
}

char* NetworkMessage::getData() const
{
	return nullptr;
}

void NetworkMessage::getSizeFromType(NetworkMessage::Type type)
{
}

size_t NetworkMessage::getSize() const
{
	return size_t();
}

void NetworkMessage::setSenderIp(sf::IpAddress address)
{
}

sf::IpAddress NetworkMessage::getSenderIP() const
{
	return sf::IpAddress();
}

void NetworkMessage::allocateMemory()
{
}

void NetworkMessage::clearMemory()
{
}
