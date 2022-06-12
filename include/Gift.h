#pragma once

#include "MovingObject.h"
#include "Macros.h"
#include "box2d/box2d.h"
#include "Timer.h"

class Board;
class Bear;

class Gift : public MovingObject
{
public:
	Gift(const sf::Vector2f position, Board* board, int giftFilter);

	//~Gift();

	void update();

	bool getIsDone() const;

protected:
	Board* m_board;
	b2Body* m_body;
	b2PolygonShape m_rect2D;
	Timer m_timer = Timer(giftTimer);

	bool m_isDone = false;
	int m_filters[static_cast<int>(giftTypes::MAX)] = { FREEZE_FILTER, DOUBLE_SHOT_FILTER, LIFE_FILTER, SHIELD_FILTER, TIME_FILTER };
};