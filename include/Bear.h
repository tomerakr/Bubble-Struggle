#pragma once

#include <SFML/Graphics.hpp>
#include "MovingObject.h"
#include "Macros.h"
#include "Gun.h"
#include "Rope.h"
#include <vector>

class Board;

class Bear : public MovingObject
{
public:
	Bear(sf::Vector2f pos);
	void jump();
	void setKeys(std::vector<sf::Keyboard::Key>* keys) { m_keys = *keys; }
	sf::Keyboard::Key getKeys(Keys key) { return m_keys[static_cast<int>(key)]; }
	const sf::Vector2f getPos() const;
	void update(float deltaTime, const sf::Vector2f direction, bool shoot);
	void drawRopes(sf::RenderWindow& window);

private:
	Gun m_gun;
	std::vector<sf::Keyboard::Key> m_keys;
};

