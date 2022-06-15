#pragma once

#include "Timer.h"
#include "Macros.h"
#include "Bear.h"

constexpr int textBarSize = 30;

class Bar
{
public:
	Bar();
	void setBar(float time, const gameInfo& info);
	void update(const std::vector<int> scores);
	void draw(sf::RenderWindow &window, const std::vector<int>& bearsLives);
	void setLevel(int level) { m_levelText.setString("LEVEL: " + std::to_string(level + 1)); }
	bool timeEnded() const;

	void addTime();

	void setTime(const int seconds);

private:
	void setBearInfo(const gameInfo& info, const Objects& texture, sf::RectangleShape &elements, const sf::Vector2f& size, int index);
	void setText(sf::Text &text, unsigned size, const sf::Vector2f& pos = sf::Vector2f(0, 0));
	void setBackgroud();
	void drawBackgroundText(sf::RenderWindow& window, const sf::Vector2f& pos, const sf::Vector2f& size);

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

