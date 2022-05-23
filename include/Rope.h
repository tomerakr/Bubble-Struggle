#pragma once

#include "MovingObject.h"
#include "SFML/Graphics.hpp"

class Rope : public MovingObject
{
public:
	Rope(sf::Vector2f pos, sf::Vector2f size);
	//using MovingObject::MovingObject;
	void checkHit();
	void setFreeze();

	void followBear(const sf::Vector2f bearPos);	// move rope to position of bear upon shooting

	void update();


private:
	bool m_freeze = false;

	bool m_isShot = false;

	void resetSize();
};

