#include <iostream>

#include <SFML/Network.hpp>

#include "server.hpp"

constexpr sf::Uint8 max_clients = 255;
constexpr unsigned short port = 2000;

int main() {
	Server server;
	
	server.init(port, max_clients);
	server.deinit();

	return 0;
}
