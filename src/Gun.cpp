#include "Gun.h"

// start game with one default rope
Gun::Gun(int ropeTexture, Board* board)
	: m_board(board), m_ropeTexture(ropeTexture)
{
	m_clock.restart();
}

void Gun::shoot(const sf::Vector2f& bearPos, const bool freezeRope)
{
	m_timeFromLastShot = m_clock.getElapsedTime().asSeconds();

   	if (m_ropes.size() < m_maxRopes && m_timeFromLastShot >= m_coolDown)
	{
		m_ropes.emplace_back(Rope(sf::Vector2f(bearPos.x + bearWitdh / 2 - ropeWitdh / 2, bearPos.y + bearheight),
								m_ropeTexture, m_board, freezeRope));

		m_clock.restart();

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