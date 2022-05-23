#include "Gun.h"

// start game with one default rope
Gun::Gun()
{
	m_ropes.emplace_back(Rope(sf::Vector2f(0, 0), sf::Vector2f(ropeWitdh, ropeHeight)));
}

void Gun::shoot(const sf::Vector2f bearPos)
{
	m_ropes[m_ropes.size() - 1].followBear(sf::Vector2f(bearPos.x + bearWitdh / 2 - ropeWitdh / 2, bearPos.y + bearHieght));
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