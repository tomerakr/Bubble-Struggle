#include "Rope.h"

constexpr float ropeHeightChange = 1.5;
constexpr float maxRopeHeight = -650;

void Rope::followBear(const sf::Vector2f bearPos)
{
	m_icon.setPosition(bearPos);

	resetSize();

	m_isShot = true;
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