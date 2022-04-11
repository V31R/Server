#include "RecievingMsgFromSockets.h"

NetworkMessage RecievingMsgFromSockets::getMessageFromUDPSocket(sf::UdpSocket& socket) {


	NetworkMessage result;
	MessageHead messageHead;

	sf::IpAddress address;
	std::size_t received;
	unsigned short port;

	if (auto res{ socket.receive(reinterpret_cast<void*>(&messageHead), sizeof(messageHead), received, address, port) }; res != sf::Socket::Status::Done) {

		char message[50];
		sprintf_s(message, "Message from UDP socket don't recieved. Error: %d.", res);
		throw std::logic_error(message);

	}
	int t = sizeof(Header);
	result.setHeader(messageHead);

	result.setData(messageHead.getData());

	result.setSenderIp(address);
	result.setPort(port);

	return result;

}

NetworkMessage RecievingMsgFromSockets::getMessageFromTCPSocket(sf::TcpSocket& socket) {

	NetworkMessage result;
	MessageHead messageHead;

	std::size_t received;

	if (auto res{ socket.receive(reinterpret_cast<void*>(&messageHead), sizeof(messageHead), received) }; res != sf::Socket::Status::Done) {

		char message[50];
		sprintf_s(message, "Message from TCP socket don't recieved. Error: %d.", res);
		throw std::logic_error(message);

	}

	int t = sizeof(Header);
	result.setHeader(messageHead);

	result.setData(messageHead.getData());

	result.setSenderIp(socket.getRemoteAddress());
	result.setPort(socket.getLocalPort());

	return result;

}
