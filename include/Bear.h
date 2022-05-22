#pragma once

#include <SFML/Graphics.hpp>
#include "MovingObject.h"
#include "Macros.h"
#include "Gun.h"
#include "Rope.h"

class Board;

class Bear : public MovingObject
{
public:
	Bear(sf::Vector2f pos);
	void shoot(Board* board);
	void jump();
	const sf::Vector2f getPos() const;
	void update(float deltaTime, const sf::Vector2f direction, bool shoot);
	void drawRopes(sf::RenderWindow& window);

private:
	Gun m_gun;

};

