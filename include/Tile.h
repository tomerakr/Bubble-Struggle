#pragma once

#include "box2d/box2d.h"
#include "StaticObject.h"

class Board;

class Tile : public StaticObject
{
public:
	Tile(Board* board, const sf::Vector2f& size, const sf::Vector2f& pos);
	Tile(const sf::Vector2f& size, const sf::Vector2f& pos);
	void destroyBody();
	bool contains(const sf::Vector2f& mousePos) { return m_icon.getGlobalBounds().contains(mousePos); }
	const sf::Vector2f& getPos() const  { return m_icon.getPosition(); }
	const sf::Vector2f& getSize() const { return m_icon.getSize(); }

private:
	Board* m_board;
	b2BodyDef m_tileBodyDef;
	b2Body* m_tileBody;
};

