#ifndef MESSAGES_HPP

#define MESSAGES_HPP

#include <iostream>

#include <string>

struct Message {
	std::string username = "";
	std::string text = "";
};

std::ostream& operator<<(std::ostream& os, const Message& msg);
std::istream& operator>>(std::istream& is, Message& msg);

class MessagingAPI {
	std::size_t msg_id = 1;
public:
	void send_msg(std::string const& msg);
	void update_msg();
};

#endif
