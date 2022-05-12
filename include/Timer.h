#pragma once

#include <SFML/Graphics.hpp>

class Timer
{
public:
	Timer();
	const int getTimeLeft(); //in seconds

private:
	sf::Time m_time;
	sf::Clock m_clock;
};

