#include "MessageReciever.h"

MessageReciever::MessageReciever()
{}


MessageReciever* MessageReciever::instance{};

MessageReciever& MessageReciever::getInstance() {

    static std::once_flag flag;

    if (!instance) {

        std::call_once(flag, []() { instance = new MessageReciever; });

    }

    return *instance;

}

void MessageReciever::receiving(sf::UdpSocket& socket){
    
    std::thread t1([&]() {

        while (true) {

            mutex.lock();
            messageQueue.push(NetworkMessage::getMessageFromUDPSocket(socket));
            Logger::getInstance().info(getMessageForLog());
            mutex.unlock();

        }

    });

    t1.detach();
    
}

NetworkMessage MessageReciever::getMessage(){  

    NetworkMessage temp = messageQueue.front();
    mutex.lock();
    messageQueue.pop();
    mutex.unlock();
    return temp;
}

std::string MessageReciever::getMessageForLog(){

    std::string msg;
    msg.append("Recived messages from ");
    msg.append(messageQueue.front().getSenderIP().toString().c_str());
    return msg;

}
