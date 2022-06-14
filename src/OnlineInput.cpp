#include "OnlineInput.h"
#include <iostream>

constexpr short PORT = 54013;

OnlineInput::OnlineInput()
{}

std::pair<sf::Vector2f, bool> OnlineInput::getInput(gameInput input)
{
	//sf::Packet info;

	(input._host ? server(input/*, info*/) : client(input/*, info*/));

	//if (input._host)
	//{
	//	client(input, info);
	//}
	//else 
	//{
	//	static bool first = true;
	//	if (first)
	//	{
	//		listener.listen(44008);
	//		first = false;
	//	}
	//		server(input, info);
	//}

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
	if (!m_connected)
	{
		sf::TcpListener listenr;
		listenr.listen(PORT);
		listenr.accept(m_socket);
		m_connected = true;
	}
	auto size = size_t();
	//info.clear();
	//info << input._otherBear.first.x << input._otherBear.first.y << input._otherBear.second;
	m_transferData._dir = input._otherBear.first;
	m_transferData._shoot = input._otherBear.second;
	m_socket.send(&m_transferData, sizeof(m_transferData));
	m_socket.receive(&m_transferData, sizeof(m_transferData), size);
	//auto temp = info;
	//info = temp;

	//sf::TcpListener listener;
	//
	//// Wait for a connection
	////sf::TcpSocket socket;
	//listener.accept(socket);
	//std::cout << "New client connected: " << socket.getRemoteAddress() << std::endl;
	//// Receive a message from the client
	//char buffer[1024];
	//std::size_t received = 0;
	//socket.receive(buffer, sizeof(buffer), received);
	////std::cout << "The client said: " << buffer << std::endl;
	//// Send an answer
	//std::string message = "Welcome, client";
	//socket.send(message.c_str(), message.size() + 1);
}

void OnlineInput::client(gameInput input/*, sf::Packet& info*/)
{
	if (!m_connected)
	{
		m_socket.connect("10.100.102.4", PORT);
		m_connected = true;
	}

	auto size = size_t();
	//info.clear();
	m_transferData._dir = input._otherBear.first;
	m_transferData._shoot = input._otherBear.second;
	//info << input._otherBear.first.x << input._otherBear.first.y << input._otherBear.second;
	m_socket.send(&m_transferData, sizeof(m_transferData));
	//info.clear();
	m_socket.receive(&m_transferData, sizeof(m_transferData), size);

	////sf::TcpSocket socket;
	//socket.connect(sf::IpAddress::getLocalAddress(), 44008);
	//// Send a message to the connected host
	//std::string message = "Hi, I am a client";
	//socket.send(message.c_str(), message.size() + 1);
	//// Receive an answer from the server
	//char buffer[1024];
	//std::size_t received = 0;
	//socket.receive(buffer, sizeof(buffer), received);
}