#pragma once

#include <string>
#include "GameObject.h"

class Button : public GameObject
{
public:
	using GameObject::GameObject;
	void setText(std::string text);
	bool isPressed(sf::Vector2f mousePos);
};
