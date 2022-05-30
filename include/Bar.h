#pragma once
#include "Timer.h"
#include "Macros.h"
#include "bear.h"

constexpr int textBarSize = 3522;

class Bar
{
public:
	Bar();
	void setBar(float time, gameInfo info);
	void update( Bear &bear);
	void draw(sf::RenderWindow &window, Bear& bear);


private:
	Timer m_timer;
	sf::RectangleShape m_lifeIcon;
	int m_level;
	sf::Text m_levelText;
	sf::Text m_scoreText;
};

