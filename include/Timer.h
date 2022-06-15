#pragma once

#include <SFML/Graphics.hpp>

class Timer
{
public:
	Timer() = default;
	Timer(float time);
	void update();
	const int getTimeLeft();
	void draw(sf::RenderWindow& window) { window.draw(m_timeline); }
	bool timeEnd() const;
	void addTime();

	void setTime(const int seconds);

private:
	sf::Clock m_clock;
	sf::Time m_time;

	sf::Text m_timeText;
	float m_levelTime;
	float m_timeLeft ;

	sf::RectangleShape m_timeline;
};

