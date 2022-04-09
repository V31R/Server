#include "NetworkMessage.h"

NetworkMessage::NetworkMessage():

	data { nullptr },
	size{ 0 }

{}

NetworkMessage::NetworkMessage(const NetworkMessage& message):

	data{ nullptr },
	size{ message.getSize() },
	sender{ message.getSenderIP() },
	header{ message.getHeader() },
	port{ message .getPort() }

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

void NetworkMessage::setSenderIp(const sf::IpAddress & address){

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

void NetworkMessage::setHeader(const Header & header){

	this->header = header;

}

Header NetworkMessage::getHeader() const{

	return header;

}

void NetworkMessage::setData(char* data){

	getSizeFromType();
	allocateMemory();
	setCopyData(data);

}

void NetworkMessage::allocateMemory(){

	data = new char[size];

}

void NetworkMessage::clearMemory(){

	delete[] data;

}
