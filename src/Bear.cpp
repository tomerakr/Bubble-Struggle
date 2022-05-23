#include "Bear.h"
#include "Board.h"


Bear::Bear(sf::Vector2f pos, Objects texture)
	:MovingObject(pos, sf::Vector2f(bearWitdh, bearHieght), texture), m_ropeTexture((texture == Objects::Bear ? Objects::HoneyRope : Objects::BambooRope)),
	m_gun(m_ropeTexture)
{
	m_icon.setFillColor(sf::Color::White);
	m_icon.setTexture(Resources::instance().getObjectTexture(texture));
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

void Bear::jump()
{
}

const sf::Vector2f Bear::getPos() const
{
	return m_icon.getPosition();
}
