#include "Board.h"

Board::Board()
{
	m_balls.emplace_back(Ball{ this/*, pos = sf::Vector2f(200, 100)*/ });
}

void Board::draw(sf::RenderWindow& window)
{
	for (auto ball : m_balls)
	{
		ball.draw(window);
	}
}

void Board::addBalls(float radius, sf::Color color, sf::Vector2f pos)
{
	auto posFirst = sf::Vector2f(pos.x - radius, pos.y);
	auto posSecond = sf::Vector2f(pos.x + radius, pos.y);

	m_balls.emplace_back(Ball{ this, radius, color, posFirst });
	m_balls.emplace_back(Ball{ this, radius, color, posSecond });
}