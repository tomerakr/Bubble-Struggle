#include "..\include\Bear.h"
#include "Bear.h"

constexpr int bearWitdh = 80;
constexpr int bearHieght = 120;

Bear::Bear()
	:MovingObject(sf::Vector2f(windowWitdh / 2, windowHieght - barHeight - bearHieght / 2),
		sf::Vector2f(bearWitdh, bearHieght), Objects::Bear)
{
	m_icon.setOrigin(sf::Vector2f(bearWitdh / 2, bearHieght / 2));
}

void Bear::shoot()
{
}

void Bear::jump()
{
}

sf::Vector2f Bear::getPos()
{
	return m_icon.getPosition();
}
