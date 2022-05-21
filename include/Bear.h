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
	Bear();
	void shoot(Board* board);
	void jump();
	const sf::Vector2f getPos() const;
	void update();
	void drawRopes(sf::RenderWindow& window);

private:
	Gun m_gun;

};

