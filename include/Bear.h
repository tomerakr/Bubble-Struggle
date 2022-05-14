#pragma once

#include <SFML/Graphics.hpp>
#include "MovingObject.h"
#include "Macros.h"

class Board;

class Bear : public MovingObject
{
public:
	Bear();
	void shoot(Board* board);
	void jump();
	const sf::Vector2f getPos() const;

private:
	int m_numOfShots = 1;
};

