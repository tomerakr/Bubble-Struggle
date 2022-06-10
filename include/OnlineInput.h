#pragma once

#include "Input.h"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "Macros.h"
#include <vector>

class OnlineInput : public Input
{
public:
	OnlineInput();
	//~OnlineInput() = default;
	std::pair<sf::Vector2f, bool> getInput(gameInput input);
	sf::UdpSocket m_socket;

private:
	unsigned short m_port = 55001;
	sf::IpAddress m_myAddress = sf::IpAddress::getLocalAddress();
	sf::IpAddress m_remoteAddress = sf::IpAddress("10.100.102.14");
};