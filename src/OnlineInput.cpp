#include "OnlineInput.h"
#include <iostream>

sf::SocketSelector m_socketSelector;

OnlineInput::OnlineInput()
{
	m_socket.bind(sf::Socket::AnyPort);
}

std::pair<sf::Vector2f, bool> OnlineInput::getInput(gameInput input)
{
	sf::Packet info;
	info << input._otherBear.first.x << input._otherBear.first.y << input._otherBear.second;
	m_socket.send(info, sf::IpAddress("10.32.6.101"), m_remotePort);
	m_socket.receive(info, m_remoteAddress, m_remotePort);
	
	auto xDir = 0.f, yDir = 0.f;
	auto shoot = false;
	std::cout << xDir << yDir << shoot << '\n';
	//info >> xDir >> yDir >> shoot;

	//return std::make_pair(sf::Vector2f(xDir, yDir), shoot);
	return std::make_pair(sf::Vector2f(0, 0), true);
}