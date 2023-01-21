#ifndef ENUMS_HPP

#define ENUMS_HPP

#include <SFML/Network.hpp>

namespace enums {
	enum Packet : sf::Uint8 {
		INVALID = 0U,
		SEND_MSG_REQUEST,
		GET_MSG_REQUEST
	};
	enum Status : sf::Uint8 {
		SUCCESS = 0U,
		NOT_FOUND
	};
}

#endif
