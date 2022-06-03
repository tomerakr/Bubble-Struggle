#pragma once

#include "GameObject.h"

class MovingObject : public GameObject
{
public:
	using GameObject::GameObject;
	void move(float deltaTime, const sf::Vector2f& direction);

private:
	float m_speedPerSecond = 200.f;
};