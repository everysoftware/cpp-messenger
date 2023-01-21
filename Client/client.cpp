#include <iostream>

#include <SFML/Network.hpp>

#include "client.hpp"

void Client::init(sf::IpAddress const& ip, unsigned short port)
{
	socket = std::move(std::make_unique<sf::TcpSocket>());
	
	std::cout << "Connecting to server" << std::endl;

	switch ((*socket).connect(ip, port)) {
	case sf::Socket::Done:
		std::cout << "Successfully" << std::endl;
		break;
	default:
		std::cout << "Connection error!" << std::endl;
		exit(EXIT_FAILURE);
	}

}

void Client::deinit()
{
	(*socket).disconnect();
}
