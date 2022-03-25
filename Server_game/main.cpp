#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <ctime>
#include "Logger.h"
#include "NetworkMessage.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(300, 300), "Server!");
    sf::CircleShape shape(100.f, 4);
    shape.setFillColor(sf::Color::Yellow);

    Logger::getInstance().logging();

    Logger::getInstance().info("info");

    shape.setPosition(100, 100);
    sf::UdpSocket socket;

    if (socket.bind(9993) != sf::Socket::Done)
    {
        // error...
        shape.setFillColor(sf::Color::Red);
    }
    window.clear();
    window.draw(shape);
    window.display();

    //char data[100];
    //std::size_t received;
    //sf::IpAddress sender;
    //unsigned short port{ 9993U };
    sf::Thread thread([&]() {
        
        while (true){

            NetworkMessage message{};
            char buffer[256];
            try {

                message = NetworkMessage::getMessageFromUDPSocket(socket);
                shape.setFillColor(sf::Color::Green);
                
                sprintf_s(buffer, "Recived messages from %s on port %lld", message.getSenderIP().toString().c_str(), message.getPort());
                Logger::getInstance().debug(buffer);
            }
            catch (std::exception& exception) {

                Logger::getInstance().error(exception.what());
                sprintf_s(buffer, "%s", exception.what());
                shape.setFillColor(sf::Color::Red);

            }


        std::cout << buffer << std::endl;

        time_t clientTime{message.getHeader().getTime()};
        //if (message.getData()) {
            //sscanf_s(message.getData(), "%lld", &clientTime);

        time_t serverTIme;
        time(&serverTIme);
        printf("Send: %lld Recieve: %lld Time: %lld\n", clientTime, serverTIme, serverTIme - clientTime);
        //}

        }
        });
    thread.launch();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
    thread.terminate();

    return 0;
}