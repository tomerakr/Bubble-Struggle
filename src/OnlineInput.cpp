#include "OnlineInput.h"
#include <iostream>

sf::SocketSelector m_socketSelector;

OnlineInput::OnlineInput()
{
	
}

std::pair<sf::Vector2f, bool> OnlineInput::getInput(gameInput input)
{
	m_socket.bind(m_port);
	sf::Packet info;
	info << input._otherBear.first.x << input._otherBear.first.y << input._otherBear.second;
	m_socket.send(info, m_remoteAddress, m_port);
	m_socket.receive(info, m_remoteAddress, m_port);
	
	auto xDir = 0.f, yDir = 0.f;
	auto shoot = false;
	info >> xDir >> yDir >> shoot;
	std::cout << xDir << yDir << shoot << '\n';

	//return std::make_pair(sf::Vector2f(xDir, yDir), shoot);
	return std::make_pair(sf::Vector2f(0, 0), shoot);
}