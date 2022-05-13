#include "Board.h"


Board::Board()
{
	m_balls.emplace_back(Ball{ this/*, pos = sf::Vector2f(200, 100)*/ });
	m_balls[0].pop();
}

void Board::setWorld()
{
	b2Vec2 gravity(1.0f, 1.0f);
	m_world = std::make_unique<b2World>(gravity);

	m_groundBodyDef.position.Set(0.0f, -10.0f);
	b2Body* groundBody = m_world->CreateBody(&m_groundBodyDef);
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

	m_balls.erase(m_balls.begin()); // change 
	m_balls.emplace_back(Ball{ this, radius, color, posFirst });
	m_balls.emplace_back(Ball{ this, radius, color, posSecond });
}
