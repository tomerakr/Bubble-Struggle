#pragma once

#include "StaticObject.h"
#include "Macros.h"
#include "box2d/box2d.h"
#include "Timer.h"

class Board;
class Bear;

class Gift : public StaticObject
{
public:
	Gift(const sf::Vector2f position, Board* board, int giftFilter);

	void update();
	void destroyBody();
	bool getIsDone() const;

	void taken();

protected:
	Board* m_board;
	b2Body* m_body;
	b2PolygonShape m_rect2D;
	Timer m_timer = Timer(giftTimer);

	bool m_done = false;
	int m_filters[static_cast<int>(giftTypes::MAX)] = { FREEZE_FILTER, SHIELD_FILTER, TIME_FILTER, LIFE_FILTER, DOUBLE_SHOT_FILTER };
};