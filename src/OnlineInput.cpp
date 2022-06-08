#include "OnlineInput.h"

//sf::IpAddress m_myAddress = sf::IpAddress::getLocalAddress();
//sf::IpAddress m_remoteAddress;
//sf::SocketSelector m_socketSelector;

constexpr int PORT = 696942;

OnlineInput::OnlineInput()
{
	//sf::UdpSocket m_socket;
	//m_socket.bind(PORT);
}

std::pair<sf::Vector2f, bool> OnlineInput::getInput(gameInput input)
{
	//sf::Packet info;
	//info << input._otherBear.first.x << input._otherBear.first.y << input._otherBear.second;
	//m_socket.send(info, otherAdress, otherPort);
	//m_socket.receive(info, otherOdress, otherPort);

	//auto xDir = 0.f, yDir = 0.f;
	//auto shoot = false;

	//info >> xDir >> yDir >> shoot;

	//return std::make_pair(sf::Vector2f(xDir, yDir), shoot);
	return std::make_pair(sf::Vector2f(0, 0), true);
}