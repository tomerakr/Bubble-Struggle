#include "OnlineInput.h"
#include <iostream>

constexpr short PORT = 54013;

OnlineInput::OnlineInput()
{}

std::pair<sf::Vector2f, bool> OnlineInput::getInput(gameInput input)
{
	(input._host ? server(input/*, info*/) : client(input/*, info*/));

	auto xDir = 0.f, yDir = 0.f;
	auto shoot = false;
	xDir = m_transferData._dir.x;
	yDir = m_transferData._dir.y;
	shoot = m_transferData._shoot;
	//info >> xDir >> yDir >> shoot;
	//std::cout << xDir << ' ' << yDir << ' ' << shoot << '\n';

	return std::make_pair(sf::Vector2f(xDir, yDir), shoot);
}

void OnlineInput::server(gameInput input/*, sf::Packet& info*/)
{
	auto size = size_t();
	m_transferData._dir = input._otherBear.first;
	m_transferData._shoot = input._otherBear.second;
	m_socket.send(&m_transferData, sizeof(m_transferData));
	m_socket.receive(&m_transferData, sizeof(m_transferData), size);
}

void OnlineInput::client(gameInput input/*, sf::Packet& info*/)
{
	auto size = size_t();
	m_transferData._dir = input._otherBear.first;
	m_transferData._shoot = input._otherBear.second;
	m_socket.send(&m_transferData, sizeof(m_transferData));
	m_socket.receive(&m_transferData, sizeof(m_transferData), size);
}

void OnlineInput::host()
{
	if (!m_connected)
	{
		sf::TcpListener listenr;
		listenr.listen(PORT);
		listenr.accept(m_socket);
		m_connected = true;
	}
}

void OnlineInput::connect(std::string ip)
{
	if (!m_connected)
	{
		m_socket.connect(ip, PORT);
		m_connected = true;
	}
}