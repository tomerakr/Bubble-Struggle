#include "Tile.h"
#include "Board.h"



Tile::Tile(Board* board, const sf::Vector2f size, const sf::Vector2f pos, int group)
	:StaticObject(pos, size, Objects::Tile)
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(pos.x, pos.y);
	m_groundBody = board->getWorld()->CreateBody(&bodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(size.x, size.y);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &groundBox;
	fixtureDef.filter.groupIndex = group;
	m_groundBody->CreateFixture(&fixtureDef);

};
