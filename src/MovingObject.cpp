#include "MovingObject.h"

void MovingObject::move(float deltaTime)
{
	m_prevPos = m_icon.getPosition();
	m_icon.move(m_direction * m_speedPerSecond * deltaTime);
}
