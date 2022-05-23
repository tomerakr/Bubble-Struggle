#include "Rope.h"

constexpr float ropeHeightChange = 1.5;
constexpr float maxRopeHeight = -650;

Rope::Rope(sf::Vector2f pos, sf::Vector2f size, Objects ropeTexture)
	:MovingObject(pos, size, ropeTexture, sf::Color::White)
{
	m_icon.setTexture(Resources::instance().getObjectTexture(ropeTexture));
}

void Rope::followBear(const sf::Vector2f bearPos)
{
	if (!m_isShot)					//	follow bear if not shot already
	{
		m_icon.setPosition(bearPos);

		resetSize();

		m_isShot = true;
	}
}

void Rope::update()
{
	if (m_isShot)
	{
		m_icon.setSize(sf::Vector2f(m_icon.getSize().x, m_icon.getSize().y - ropeHeightChange)); // make rope longer
	}

	if (m_icon.getSize().y < maxRopeHeight)					// if rope height is too long stop increasing height
	{
		m_isShot = false;
		resetSize();
	}
}

void Rope::resetSize()
{
	m_icon.setSize(sf::Vector2f(m_icon.getSize().x, 0));
}