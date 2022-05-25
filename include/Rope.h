#pragma once

#include "Macros.h"
#include "Board.h"
#include "MovingObject.h"
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

class Rope : public MovingObject
{
public:
	Rope(sf::Vector2f size, Objects ropeTexture, Board* board);
	//using MovingObject::MovingObject;
	void checkHit();
	void setFreeze();
	void setFixture(b2Vec2 size);
	void followBear(const sf::Vector2f bearPos);	// move rope to position of bear upon shooting
	void update();


private:
	bool m_freeze = false;
	bool m_shot = false;

	Board* m_board = nullptr;
	b2Body* m_box2DRope = nullptr;

	void resetSize();
};

