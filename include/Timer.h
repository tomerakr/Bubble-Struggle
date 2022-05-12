#pragma once

#include <SFML/Graphics.hpp>

class Timer
{
	Timer();
	const int getTimeLeft(); //in seconds

private:
	sf::Time m_time;
	sf::Clock m_clock;
};

