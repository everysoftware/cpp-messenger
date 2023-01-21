#include <iostream>

#include <SFML/Network.hpp>

#include "messages.hpp"
#include "enums.hpp"
#include "client.hpp"

std::ostream& operator<<(std::ostream& os, const Message& msg) {
	os << msg.username << ": " << msg.text;
	return os;
}

std::istream& operator>>(std::istream& is, Message& msg) {
	is >> msg.username >> msg.text;
	return is;
}

void MessagingAPI::send_msg(std::string const& msg) {
	sf::Packet packet;

	packet << enums::SEND_MSG_REQUEST << client.username << msg;
	switch ((*client.socket).send(packet)) {
	case sf::Socket::Done:
		++msg_id;
		break;
	case sf::Socket::Disconnected:
		std::cout << "[Error] Disconnected" << std::endl;
		break;
	case sf::Socket::NotReady:
		std::cout << "[Error] Not ready" << std::endl;
		break;
	case sf::Socket::Partial:
		std::cout << "[Error] Partial" << std::endl;
		break;
	default:
		std::cout << "[Error] Undefined error" << std::endl;
		break;
	}
}

void MessagingAPI::update_msg() {
	sf::Uint8 flag = enums::Status::SUCCESS;
	while (flag == enums::Status::SUCCESS) {
		sf::Packet packet;
		packet << enums::Packet::GET_MSG_REQUEST << msg_id;
		switch ((*client.socket).send(packet)) {
		case sf::Socket::Done:
			break;
		default:
			std::cout << "[Error] Request to get a message not sent" << std::endl;
			exit(EXIT_FAILURE);
		}
		packet.clear();
		switch ((*client.socket).receive(packet)) {
		case sf::Socket::Done:
			break;
		default:
			std::cout << "[Error] The server did not send data" << std::endl;
			exit(EXIT_FAILURE);
		}
		packet >> flag;
		if (flag == enums::Status::SUCCESS) {
			Message m;
			packet >> m.username >> m.text;
			std::cout << m << std::endl;
			++msg_id;
		}
		packet.clear();
	}
}
