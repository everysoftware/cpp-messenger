#ifndef CLIENT_HPP

#define CLIENT_HPP

#include <memory>

#include <SFML/Network.hpp>

#include "messages.hpp"

struct Client {
	std::unique_ptr<sf::TcpSocket> socket;

	std::string username = "";

	MessagingAPI msg_api;

	void init(sf::IpAddress const& ip, unsigned short port);
	void deinit();
};

extern Client client;

#endif
