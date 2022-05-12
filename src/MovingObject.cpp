#include "MovingObject.h"

//constexpr sf::Vector2f left = sf::Vector2f(-1, 0);
//constexpr sf::Vector2f right = sf::Vector2f(1, 0);

void MovingObject::move(float deltaTime)
{
	m_prevPos = m_icon.getPosition();
	m_icon.move(m_direction * m_speedPerSecond * deltaTime);
}

void MovingObject::setDirection()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_direction = sf::Vector2f(-1, 0);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_direction = sf::Vector2f(1, 0);
    }
    else
    {
        m_direction = sf::Vector2f(0, 0);
    }
}
