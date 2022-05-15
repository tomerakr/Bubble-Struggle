#include "Tile.h"
#include "Board.h"

float pixelToMeter(const int pixels)
{
	return pixels * pToMeter;
}

Tile::Tile(Board* board, const sf::Vector2f size, const sf::Vector2f pos)
	:StaticObject(pos, size, Objects::Tile)
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(pos.x, pos.y);
	m_groundBody = board->getWorld()->CreateBody(&bodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(size.x, size.y);
	m_groundBody->CreateFixture(&groundBox, 0.0f);
}