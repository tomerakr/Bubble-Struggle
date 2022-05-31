#pragma once

#include "box2d/box2d.h"
#include "StaticObject.h"

class Board;

class Tile : public StaticObject
{
public:
	Tile(Board* board, const sf::Vector2f size, const sf::Vector2f pos, const int group = 0);
	Tile(const sf::Vector2f& size, const sf::Vector2f& pos);
	void reset();
	//void collision(Board* board);
	bool contains(const sf::Vector2f& mousePos) { return m_icon.getGlobalBounds().contains(mousePos); }
	const sf::Vector2f getPos() const { return m_icon.getPosition(); }

private:
	Board* m_board;
	b2BodyDef m_groundBodyDef; //change name to tile
	b2Body* m_groundBody;
};

