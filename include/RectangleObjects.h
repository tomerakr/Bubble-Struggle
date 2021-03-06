#pragma once

#include "GameObject.h"
#include "SFML/Graphics.hpp"
#include "Macros.h"

class RectangleObjects : public GameObject
{
public:
	RectangleObjects(const sf::Vector2f& pos, const sf::Vector2f& size, const Objects texture);
	void draw(sf::RenderWindow& window);

protected:
	sf::RectangleShape m_icon;
};