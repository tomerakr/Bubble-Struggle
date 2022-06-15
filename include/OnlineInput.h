#pragma once

#include "Input.h"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "Macros.h"
#include <vector>

struct bilbal
{
	sf::Vector2f _dir;
	bool _shoot;
};

class OnlineInput : public Input
{
public:
	OnlineInput();
	//~OnlineInput() = default;
	std::pair<sf::Vector2f, bool> getInput(gameInput input);
	sf::TcpSocket m_socket;
	void host();
	void connect(std::string ip);


private:
	void server(gameInput input/*, sf::Packet& info*/);
	void client(gameInput input/*, sf::Packet& info*/);
	bool m_connected = false;

	bilbal m_transferData;
};

