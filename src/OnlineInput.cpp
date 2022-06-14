#include "OnlineInput.h"
#include <iostream>

constexpr short PORT = 54013;

OnlineInput::OnlineInput()
{}

std::pair<sf::Vector2f, bool> OnlineInput::getInput(gameInput input)
{
	sf::Packet info;

	(input._host ? server(input, info) : client(input, info));

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
	info >> xDir >> yDir >> shoot;
	//std::cout << xDir << ' ' << yDir << ' ' << shoot << '\n';

	return std::make_pair(sf::Vector2f(xDir, yDir), shoot);
}

void OnlineInput::server(gameInput input, sf::Packet& info)
{
	if (!m_connected)
	{
		sf::TcpListener listenr;
		listenr.listen(PORT);
		listenr.accept(m_socket);
		m_connected = true;
	}
	
	info << input._otherBear.first.x << input._otherBear.first.y << input._otherBear.second;
	m_socket.send(info);
	 info.clear();
	m_socket.receive(info);
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

void OnlineInput::client(gameInput input, sf::Packet& info)
{
	if (!m_connected)
	{
		m_socket.connect("10.100.102.4", PORT);
		m_connected = true;
	}
	info << input._otherBear.first.x << input._otherBear.first.y << input._otherBear.second;
	m_socket.send(info);
	info.clear();
	m_socket.receive(info);

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