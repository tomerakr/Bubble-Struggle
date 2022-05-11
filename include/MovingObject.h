#pragma once

#include "GameObject.h"

class MovingObject : public GameObject
{
public:
	using GameObject::GameObject;
	void move(float deltaTime);

private:
	sf::Vector2f m_direction;
};