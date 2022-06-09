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
	unsigned short m_myPort = 8765;
	unsigned short m_remotePort = 8764;
	sf::IpAddress m_myAddress = sf::IpAddress::getLocalAddress();
	sf::IpAddress m_remoteAddress = sf::IpAddress("10.32.6.101");
};