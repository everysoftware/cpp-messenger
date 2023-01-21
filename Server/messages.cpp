#include <iostream>

#include <SFML/Network.hpp>

#include "messages.hpp"
#include "enums.hpp"

void MessagingAPI::send_msg(Client& client, sf::Packet& packet) {
	Message m;
	packet >> m.username >> m.text;

	std::cout << "Recevied a request to send a message from " << m.username << ": " << m.text << std::endl;

	msg_list.push_back(m);
	
	std::cout << "Sent" << std::endl;
}

void MessagingAPI::get_msg(Client& client, sf::Packet& packet) {
	std::size_t id = 0;
	packet >> id;
	sf::Packet p;

	std::cout << "Recevied a request to get a message #" << id << std::endl;

	if (id == 0 || id > msg_list.size()) {
		p << enums::Status::NOT_FOUND;
		std::cout << "Not found" << std::endl;
	}
	else {
		Message m;
		std::size_t i = 1;
		auto it = msg_list.begin();
		while (it != msg_list.end()) {
			if (i == id) {
				m = *it;
				break;
			}
			++it;
			++i;
		}
		p << enums::Status::SUCCESS << m.username << m.text;
		std::cout << "Found (" << m.username << ": " << m.text << ")" << std::endl;
	}

	switch ((*client.socket).send(p)) {
	case sf::Socket::Done:
		std::cout << "Successfully" << std::endl;
		break;
	default:
		std::cout << "Error" << std::endl;
		break;
	}
}
