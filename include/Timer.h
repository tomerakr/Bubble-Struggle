#pragma once

#include <SFML/Graphics.hpp>

class Time
{
	Time();
	const int getTimeLeft(); //in seconds

private:
	sf::Time m_time;
	sf::Clock m_clock;
};

