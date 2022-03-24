#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <ctime>
#include "Logger.h"

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

    char data[100];
    std::size_t received;
    sf::IpAddress sender;
    unsigned short port;
    sf::Thread thread([&]() {
        Logger::getInstance().debug("debug");
        while (true){

            if (socket.receive(data, 100, received, sender, port) != sf::Socket::Done)
            {
                // error...
                shape.setFillColor(sf::Color::Red);
            }
            else {

                shape.setFillColor(sf::Color::Green);

            }
        
        std::cout << "Received " << received << " bytes from " << sender << " on port " << port << std::endl;

        time_t clientTime;
        sscanf_s(data, "%lld", &clientTime);

        time_t serverTIme;
        time(&serverTIme);
        printf("Send: %lld Recieve: %lld Time: %lld\n",clientTime,serverTIme,serverTIme-clientTime);

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