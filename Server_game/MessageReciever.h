#pragma once
#include <mutex>

class MessageReciever{
public:

	static MessageReciever& getInstance();

	void getMessages();

private:

	MessageReciever();
	MessageReciever(const MessageReciever&) = delete;
	MessageReciever& operator=(const MessageReciever&) = delete;

	static MessageReciever * instance;

};

