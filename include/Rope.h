#pragma once

#include "Macros.h"
#include "Board.h"
#include "MovingObject.h"
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"


class Rope : public MovingObject
{
public:
	Rope(sf::Vector2f bearPos, int ropeTexture, Board* board);
	void setFreeze();
	void update();
	bool isDone() { return m_done; }

private:
	void setFixture(b2Vec2 size);

	bool m_freeze = false;
	bool m_done = false;

	Board* m_board = nullptr;
	b2Body* m_box2DRope = nullptr;
};

