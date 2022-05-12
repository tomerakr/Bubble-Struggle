#pragma once

#include "SFML/Graphics.hpp"

class GameObject
{
public:
	GameObject(const sf::Vector2f pos, const sf::Vector2f size, const int texture = 0);
	void draw(sf::RenderWindow& window);

private:
	sf::Sprite m_sprite;
};
