#pragma once

#include "box2d/box2d.h"
#include "StaticObject.h"

class Board;

class Tile : public StaticObject
{
public:
	Tile(Board* board, const sf::Vector2f size, const sf::Vector2f pos);

private:
	b2BodyDef m_groundBodyDef;
	b2Body* m_groundBody;
	//bool m_vertical;
};

