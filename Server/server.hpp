#ifndef SERVER_HPP

#define SERVER_HPP

#include <memory>
#include <list>

#include <SFML/Network.hpp>

#include "client.hpp"
#include "messages.hpp"

struct Server {
	sf::TcpListener listener;
	sf::SocketSelector selector;
	std::list<std::unique_ptr<Client>> clients;
	
	sf::Uint8 max_clients;

	MessagingAPI msg_api;

	bool is_running;

	void handle_packets();
	void handle_connections();

	void run();

	void init(unsigned short server_ip, sf::Uint8 max_clients);
	void deinit();
};

#endif
