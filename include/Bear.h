#pragma once

#include "MovingObject.h"

class Bear : public MovingObject
{
public:
	using MovingObject();
	void shoot();
	void jump();
};

