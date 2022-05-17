#pragma once

#include "MovingObject.h"

class Rope : public MovingObject
{
public:

	using MovingObject::MovingObject;
	void checkHit();
	void setFreeze();

	void followBear(const sf::Vector2f bearPos);	// move rope to position of bear upon shooting

	void update();


private:
	bool m_freeze = false;

	bool m_isShot = false;

	void resetSize();
};

