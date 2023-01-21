#ifndef CLIENT_HPP

#define CLIENT_HPP

#include <iostream>
#include <memory>

#include <SFML/Network.hpp>

struct Client {
	std::unique_ptr<sf::TcpSocket> socket;
	const sf::Uint64 uid;

	Client() : socket(std::move(std::make_unique<sf::TcpSocket>())),
		uid((sf::Uint64)socket.get()) {}
};


#endif