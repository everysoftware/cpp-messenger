#include <iostream>

#include "server.hpp"
#include "enums.hpp"

void Server::handle_connections() {
	auto client = std::move(std::make_unique<Client>());

	if (listener.accept(*client->socket) == sf::Socket::Done) {
		if (clients.size() < max_clients) {
			std::cout << client->socket->getRemoteAddress() << ":" << client->socket->getRemotePort() << " connected." << std::endl;

			selector.add(*client->socket);
			clients.push_back(std::move(client));
		}
		else {
			std::cout << "Disconneting client: " << client->socket->getRemoteAddress() << ":" << client->socket->getRemotePort() << std::endl;
			client->socket->disconnect();
		}
	}
}

void Server::handle_packets() {
	auto iter = clients.begin();

	while (iter != clients.end()) {
		Client& ref = **iter;

		if (selector.isReady(*ref.socket)) {
			sf::Packet packet;

			switch (ref.socket->receive(packet)) {
			case sf::TcpSocket::Done: {
				sf::Uint8 flag = enums::Packet::INVALID;
				packet >> flag;

				switch (flag) {
				case enums::Packet::INVALID:
					std::cout << "Received invalid packet" << std::endl;
					break;
				case enums::Packet::SEND_MSG_REQUEST:
					msg_api.send_msg(ref, packet);
					break;
				case enums::Packet::GET_MSG_REQUEST:
					msg_api.get_msg(ref, packet);
					break;
				default:
					std::cout << "Undefined flag " << flag << std::endl;
					break;
				}
				++iter;

				break;
			}

			case sf::TcpSocket::Disconnected: {
				std::cout << ref.socket->getRemoteAddress() << ":" << ref.socket->getRemotePort() << " disconnected." << std::endl;
				selector.remove(*ref.socket);
				iter = clients.erase(iter);

				break;
			}
			}
		}
		else {
			++iter;
		}
	}
}

void Server::run() {
	while (is_running) {
		if (selector.wait(sf::seconds(1.0F))) {
			if (selector.isReady(listener)) {
				handle_connections();
			}
			else {
				handle_packets();
			}
		}
	}
}

void Server::init(unsigned short _port, sf::Uint8 _max) {
	max_clients = _max;

	if (listener.listen(_port) != sf::Socket::Done) {
		throw "Server::run() != sf::Socket::Done";
	}

	selector.add(listener);

	std::cout
		<< "# IP Lan: " << sf::IpAddress::getLocalAddress() << std::endl
		<< "# IP Pub: " << sf::IpAddress::getPublicAddress(sf::seconds(1.0F)) << std::endl
		<< "# Port: " << listener.getLocalPort() << std::endl <<
		std::endl;

	is_running = true;

	run();
}


void Server::deinit() {
	printf("Disconnecting all clients...\n");

	is_running = false;
	for (auto& ptr : clients) {
		ptr->socket->disconnect();
	}
}
