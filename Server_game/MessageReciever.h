#pragma once
#include <mutex>
#include <queue>
#include <thread>
#include <string>
#include "NetworkMessage.h"
#include "Logger.h"

class MessageReciever{
public:

	static MessageReciever& getInstance();

	void receiving(sf::UdpSocket& socket);

	NetworkMessage getMessage();

	std::string getMessageForLog();

private:

	MessageReciever();
	MessageReciever(const MessageReciever&) = delete;
	MessageReciever& operator=(const MessageReciever&) = delete;

	static MessageReciever * instance;

	std::queue <NetworkMessage> messageQueue;

	std::mutex mutex;
};

