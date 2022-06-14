#pragma once

#include "Macros.h"
#include "Board.h"
#include "MovingObject.h"
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

class Rope : public MovingObject
{
public:
	Rope(const sf::Vector2f& bearPos, int ropeTexture, Board* board, bool freezeRope);
	void update();	//true if popped a ball
	bool isDone() { return m_done; }
	void destroy();

	void poppedABall() { m_done = true; }
	void hitAWall() { m_done = true; }

private:
	void setFixture(const b2Vec2& size);
	void growRope();

	bool m_freeze = false;
	bool m_done = false;
	int m_ropeIndex;
	Board* m_board = nullptr;
	b2Body* m_box2DRope = nullptr;
	b2Vec2 m_pos;
};

