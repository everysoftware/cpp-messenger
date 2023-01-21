#include <iostream>

#include "client.hpp"

Client client;

int main() {
	sf::IpAddress ip = sf::IpAddress::getLocalAddress();
	constexpr unsigned short port = 2000;

	client.init(ip, port);

	std::cout << "Enter your name:" << std::endl;
	std::cin >> client.username;

	client.msg_api.update_msg();
	std::string message = "";

	while (true) {
		std::cout << client.username << ": ";
		std::getline(std::cin >> std::ws, message);

		if (message == "exit") {
			break;
		}
		else if (message == "up") {
			client.msg_api.update_msg();
		}
		else {
			client.msg_api.update_msg();
			client.msg_api.send_msg(message);
		}
	}

	client.deinit();

	return 0;
}
