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

	sender = message.getSenderIP();
	header = message.getHeader();
	port = message.getPort();

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
	else {

		size = message.getSize();
		allocateMemory();

	}

	setCopyData(message.getData());

	return *this;

}

NetworkMessage::~NetworkMessage(){

	memset(data, 0, size);
	clearMemory();

}

NetworkMessage NetworkMessage::getMessageFromUDPSocket(sf::UdpSocket & socket){


	NetworkMessage result;
	MessageHead messageHead;

	sf::IpAddress address;
	std::size_t received;
	unsigned short port;

	if (auto res{ socket.receive(reinterpret_cast<void*>( & messageHead), sizeof(messageHead), received, address, port)}; res != sf::Socket::Status::Done) {

		char message[50];
		sprintf_s(message, "Message from UDP socket don't recieved. Error: %d.", res);
		throw std::logic_error(message);

	}
	int t = sizeof(Header);
	result.setHeader(*reinterpret_cast<Header*>(&messageHead));

	result.getSizeFromType();
	result.allocateMemory();
	result.setCopyData(messageHead.getData());

	result.setSenderIp(address);
	result.setPort(port);

	return result;

}

void NetworkMessage::setCopyData(char* data){

	memcpy(this->data, data, size);

}

void NetworkMessage::getCopyData(char*& data){

	memcpy(data, this->data, size);

}

char* NetworkMessage::getData() const {

	return data;

}

void NetworkMessage::getSizeFromType(){

	switch (header.getType()) {

	case Header::Type::LOGIN : {

		size = 0;
		break;

	}
	case Header::Type::TIME: {

		size = 25;

		break;

	}
	default: {

		size = 0;

	}

	}

}

size_t NetworkMessage::getSize() const {

	return size;

}

void NetworkMessage::setSenderIp(sf::IpAddress address){

	sender = address;

}

sf::IpAddress NetworkMessage::getSenderIP() const {

	return sender;

}

void NetworkMessage::setPort(unsigned short port){

	this->port = port;

}

unsigned short NetworkMessage::getPort() const {

	return port;

}

void NetworkMessage::setHeader(Header header)
{
}

Header NetworkMessage::getHeader() const
{
	return Header();
}

void NetworkMessage::allocateMemory(){

	data = new char[size];

}

void NetworkMessage::clearMemory(){

	delete[] data;

}
