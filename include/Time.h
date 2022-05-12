#pragma once

#include <SFML/Graphics.hpp>

class Time
{
	Time();
	int getTimeLeft();

private:
	sf::Time m_time;
	sf::Clock m_clock;
};

