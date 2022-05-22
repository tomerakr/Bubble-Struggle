#include "Bear.h"
#include "Board.h"


Bear::Bear(sf::Vector2f pos)
	:MovingObject(pos, sf::Vector2f(bearWitdh, bearHieght), Objects::Bear)
{
	m_icon.setFillColor(sf::Color::White);
	m_icon.setTexture(Resources::instance().getObjectTexture(Objects::Bear));
}

void Bear::update(float deltaTime, const sf::Vector2f direction, bool shoot)
{
	move(deltaTime, direction);
	if (shoot)
	{
		m_gun.shoot(m_icon.getPosition());
	}
	m_gun.update();
}

void Bear::drawRopes(sf::RenderWindow& window)
{
	m_gun.drawRopes(window);
}

void Bear::shoot(Board* board)
{
	//m_gun.shoot(m_icon.getPosition());

	//auto balls = board->getBalls();

	//for (int i = 0; i < balls->size(); ++i)
	//{
	//	if (m_icon.getGlobalBounds().contains(sf::Vector2f((*balls)[i].getPos().x, m_icon.getPosition().y)))
	//	{
	//		(*balls)[i].pop();
	//	}
	//}
	/*add ball iterator in board so can pop it  !!!!!! */
}

void Bear::jump()
{
}

const sf::Vector2f Bear::getPos() const
{
	return m_icon.getPosition();
}
