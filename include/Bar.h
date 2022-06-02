#pragma once

#include "Timer.h"
#include "Macros.h"
#include "Bear.h"

constexpr int textBarSize = 40;

class Bar
{
public:
	Bar();
	void setBar(float time, const gameInfo& info);
	void update( Bear &bear);
	void draw(sf::RenderWindow &window, Bear& bear); //why not pointer to bear


private:
	Timer m_timer;
	sf::RectangleShape m_lifeIcon;
	int m_level;
	sf::Text m_levelText;
	sf::Text m_scoreText;
};

