#pragma once

#include <SFML/Graphics.hpp>

class Timer
{
public:
	Timer(float time);
	void update();
	std::pair<int, int> timeToInt();
	const int getTimeLeft(); //in seconds



private:
	sf::Clock m_clock;
	sf::Time m_time;

	sf::Text m_timeText;
	float m_levelTime;
};

