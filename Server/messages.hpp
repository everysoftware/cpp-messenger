#ifndef MESSAGES_HPP
#define MESSAGES_HPP

#include <string>
#include <list>

#include "client.hpp"

struct Message {
	std::string username = "";
	std::string text = "";
};

struct MessagingAPI {
private:
	std::list<Message> msg_list;
public:
	void send_msg(Client& client, sf::Packet& packet);
	void get_msg(Client& client, sf::Packet& packet);
};

#endif

