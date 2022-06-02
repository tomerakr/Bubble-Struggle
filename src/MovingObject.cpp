#include "MovingObject.h"

void MovingObject::move(float deltaTime, const sf::Vector2f& direction)
{
	m_icon.move(direction * m_speedPerSecond * deltaTime);
}
