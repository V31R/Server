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
    unsigned short port{ 9993U };
    sf::Thread thread([&]() {
        Logger::getInstance().debug("debug");
        while (true){

            NetworkMessage message{};

            try {

                message = NetworkMessage::getMessageFromUDPSocket(&socket, NetworkMessage::Type::TIME);
                shape.setFillColor(sf::Color::Green);

            }
            catch (std::exception& exception) {

                Logger::getInstance().error(exception.what());
                shape.setFillColor(sf::Color::Red);

            }

            shape.setFillColor(sf::Color::Green);


        std::cout << "Received " << message.getSize() << " bytes from " << message.getSenderIP() << " on port " << message.getPort() << std::endl;

        time_t clientTime;
        if (message.getData()) {
            sscanf_s(message.getData(), "%lld", &clientTime);

            time_t serverTIme;
            time(&serverTIme);
            printf("Send: %lld Recieve: %lld Time: %lld\n", clientTime, serverTIme, serverTIme - clientTime);
        }

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