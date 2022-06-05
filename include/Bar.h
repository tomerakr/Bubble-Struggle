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
	//void drawBackgroundText(sf::RenderWindow& window);


private:
	Timer m_timer;
	std::vector<sf::RectangleShape> m_lifeIcons;
	int m_level;
	int m_numOfBears;
	sf::Text m_levelText;
	sf::Text m_scoreText;
	sf::RectangleShape m_background;
	sf::RectangleShape m_textBackground;

};

