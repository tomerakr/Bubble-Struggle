#pragma once

#include "Macros.h"
#include "SFML/Graphics.hpp"

class GameObject
{
public:
	GameObject(const sf::Vector2f pos, const sf::Vector2f size, const Objects texture);
	void draw(sf::RenderWindow& window);

protected:
	sf::RectangleShape m_icon;
};
