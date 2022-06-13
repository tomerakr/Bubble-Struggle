#pragma once

#include "RectangleObjects.h"

class MovingObject : public RectangleObjects
{
public:
	using RectangleObjects::RectangleObjects;
	void move(float deltaTime, const sf::Vector2f& direction);

private:
	float m_speedPerSecond = 200.f;
};