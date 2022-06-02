#include "Gun.h"

// start game with one default rope
Gun::Gun(int ropeTexture, Board* board)
	: m_board(board), m_ropeTexture(ropeTexture)
{}

void Gun::shoot(const sf::Vector2f& bearPos)
{
	if (m_ropes.size() < m_maxRopes)
	{
		m_ropes.emplace_back(Rope(sf::Vector2f(bearPos.x + bearWitdh / 2 - ropeWitdh / 2, bearPos.y + bearHieght),
								m_ropeTexture, m_board));
	}
}

void Gun::update()
{
	for (auto& rope : m_ropes)
	{
		rope.update();
	}
	std::erase_if(m_ropes, [](auto& rope) { return rope.isDone(); });
}

void Gun::drawRopes(sf::RenderWindow& window)
{
	for (auto& rope : m_ropes)
	{
		rope.draw(window);
	}
}