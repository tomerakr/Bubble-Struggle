#include "Board.h"

Board::Board()
{
	setWorld();
	createBoard();
}

void Board::setWorld()
{
	b2Vec2 gravity(0.0f, 10.0f);
	m_world = std::make_unique<b2World>(gravity);
}

void Board::createBoard()
{
	m_balls.emplace_back(Ball{ this/*, pos = sf::Vector2f(200, 100)*/ });

	m_tiles.push_back(Tile{this, sf::Vector2f(windowWitdh, 5), sf::Vector2f(0.f, windowHieght - 20 - barHeight)});	//floor
	m_tiles.push_back(Tile{this, sf::Vector2f(5, windowHieght), sf::Vector2f(-180, windowHieght)});					//left wall
	m_tiles.push_back(Tile{this, sf::Vector2f(5, windowHieght), sf::Vector2f(windowWitdh, windowHieght)});			//right wall
}

void Board::draw(sf::RenderWindow& window)
{
	for (auto& ball : m_balls)
	{
		ball.draw(window);
	}
	for (auto& tile : m_tiles)
	{
		tile.draw(window);
	}
}

void Board::update()
{
	m_world->Step(m_timeStep, m_velocityIteration, m_positionIteration);



	//for (auto& ball : m_balls)
	//{
		//ball.updatePos();
		//if (ball.isPopped())
		//{
		//	ball.split();
		//}
	//}

	for (int i = 0; i < m_balls.size(); ++i)
	{
		m_balls[i].updatePos();
		if (m_balls[i].isPopped())
		{
			m_balls[i].split();
		}
	}

	std::erase_if(m_balls, [](const auto& ball) { return ball.isPopped(); });
}

void Board::addBalls(float radius, sf::Color color, sf::Vector2f pos)
{

	auto posLeft = sf::Vector2f(pos.x - radius, pos.y);
	auto posRight = sf::Vector2f(pos.x + radius, pos.y);

	m_balls.emplace_back(Ball{ this, radius, color, posLeft });
	m_balls.emplace_back(Ball{ this, radius, color, posRight });
}
