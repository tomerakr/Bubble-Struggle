#include "Bear.h"
#include "Board.h"

constexpr int bearWitdh = 80;
constexpr int bearHieght = 120;

Bear::Bear()
	:MovingObject(sf::Vector2f(windowWitdh / 2, windowHieght - barHeight - bearHieght / 2),
		sf::Vector2f(bearWitdh, bearHieght), Objects::Bear)
{
	m_icon.setOrigin(sf::Vector2f(bearWitdh / 2, bearHieght / 2));
}

void Bear::shoot(Board* board)
{
	auto balls = board->getBalls();

	for (int i = 0; i < balls->size(); ++i)
	{
		if (m_icon.getGlobalBounds().contains(sf::Vector2f((*balls)[i].getPos().x, m_icon.getPosition().y)))
		{
			(*balls)[i].pop();
		}
	}
	/*add ball iterator in board so can pop it*/
}

void Bear::jump()
{
}

const sf::Vector2f Bear::getPos() const
{
	return m_icon.getPosition();
}
