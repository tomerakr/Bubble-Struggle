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
	std::pair<sf::Vector2f, bool> getInput(std::vector<sf::Keyboard::Key> keys);

private:
	//sf::IpAddress m_myAddress = sf::IpAddress::getLocalAddress();
	//sf::IpAddress m_remoteAddress;
	//sf::UdpSocket m_socket;
	//sf::SocketSelector m_socketSelector;
};