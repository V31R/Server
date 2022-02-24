#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <cmath>

int main()
{
    sf::RenderWindow window(sf::VideoMode(300, 300), "Server!");
    sf::CircleShape shape(100.f, 4);
    shape.setFillColor(sf::Color::Yellow);

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
    if (socket.receive(data, 100, received, sender, port) != sf::Socket::Done)
    {
        // error...
        shape.setFillColor(sf::Color::Red);
    }
    else {

        shape.setFillColor(sf::Color::Green);

    }
    std::cout << "Received " << received << " bytes from " << sender << " on port " << port << std::endl;
    printf("%s", data);


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

    return 0;
}