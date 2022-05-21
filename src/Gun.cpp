#include "Gun.h"

constexpr int ropeWitdh = 20;
constexpr int ropeHeight = 0;

// start game with one default rope
Gun::Gun()
{
	m_ropes.emplace_back(Rope(sf::Vector2f(0, 0), sf::Vector2f(ropeWitdh, ropeHeight), 
							Objects::Rope, sf::Color::Red));
}

void Gun::shoot(const sf::Vector2f bearPos)
{
	m_ropes[m_ropes.size() - 1].followBear(bearPos);
}

void Gun::update()
{
	for (auto& rope : m_ropes)
	{
		rope.update();
	}
}

void Gun::drawRopes(sf::RenderWindow& window)
{
	for (auto& rope : m_ropes)
	{
		rope.draw(window);
	}
}