#pragma once

#include <SFML/Graphics.hpp>
#include "MovingObject.h"
#include "Macros.h"

class Bear : public MovingObject
{
public:
	using MovingObject::MovingObject;
	void shoot();
	void jump();

private:
	int m_numOfShots = 1;

};

