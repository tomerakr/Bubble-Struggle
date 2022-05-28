#pragma once
#include "Timer.h"

class Bar
{
public:
	Bar(float levelTime);
	void update();
	void draw(sf::RenderWindow window);


private:
	Timer m_timer;
	sf::RectangleShape m_lifeIcon;

	int m_lives;
	int m_level;
	int m_score;
	
};

