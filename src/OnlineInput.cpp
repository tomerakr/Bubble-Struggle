#include "OnlineInput.h"
#include <iostream>

sf::SocketSelector m_socketSelector;

OnlineInput::OnlineInput()
{}

std::pair<sf::Vector2f, bool> OnlineInput::getInput(gameInput input)
{
	sf::Packet info;

	(input._host ? client(input, info) : server(input, info));
	
	auto xDir = 0.f, yDir = 0.f;
	auto shoot = false;
	info >> xDir >> yDir >> shoot;
	std::cout << xDir << ' ' << yDir << ' ' << shoot << '\n';

	return std::make_pair(sf::Vector2f(xDir, yDir), shoot);
}

void OnlineInput::server(gameInput input, sf::Packet& info)
{
	sf::TcpListener listenr;
	listenr.listen(m_remotePort);

	listenr.accept(m_socket);

	m_socket.receive(info);
	auto temp = info;
	info.clear();
	info << input._otherBear.first.x << input._otherBear.first.y << input._otherBear.second;
	m_socket.send(info);
	info = temp;
}

void OnlineInput::client(gameInput input, sf::Packet& info)
{
	m_socket.connect(m_remoteAddress, m_remotePort);
	
	info << input._otherBear.first.x << input._otherBear.first.y << input._otherBear.second;
	m_socket.send(info);
	info.clear();
	m_socket.receive(info);
}