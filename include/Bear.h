#pragma once
#include <SFML/Graphics.hpp>
#include "MovingObject.h"

class Bear : public MovingObject
{
public:
	using MovingObject::GameObject;
	void shoot();
	void jump();

private:


};

