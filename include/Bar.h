#pragma once

#include "Timer.h"
#include "Macros.h"
#include "Bear.h"

constexpr int textBarSize = 30;

class Bar
{
public:
	Bar();
	void setText(sf::Text &text, unsigned size, sf::Vector2f pos = sf::Vector2f(0, 0));
	void setBackgroud();
	void setBar(float time, const gameInfo& info);
	void setBearInfo(const gameInfo& info, Objects texture, sf::RectangleShape &elements, sf::Vector2f size, int index);
	void update(std::vector<Bear> &bear);
	void draw(sf::RenderWindow &window, std::vector<Bear> &bears);
	void setLevel(int level) { m_levelText.setString("LEVEL: " + std::to_string(level)); }

private:
	void drawBackgroundText(sf::RenderWindow& window, sf::Vector2f pos, sf::Vector2f size);

	Timer m_timer;
	std::vector<sf::RectangleShape> m_lifeIcons;
	std::vector<sf::RectangleShape> m_ropes;
	int m_level;
	int m_numOfBears;
	sf::Text m_levelText;
	sf::Text m_scoreText;
	sf::RectangleShape m_background;
	sf::RectangleShape m_objectsBackground;

};

