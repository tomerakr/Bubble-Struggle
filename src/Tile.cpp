#include "Tile.h"
#include "Board.h"



Tile::Tile(Board* board, const sf::Vector2f size, const sf::Vector2f pos, int group)
	:StaticObject(pos, size, (group == FLOOR ? Objects::Floor : Objects::Wall))
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(pos.x + size.x / 2, pos.y + size.y / 2);
	m_groundBody = board->getWorld()->CreateBody(&bodyDef);
	
	b2PolygonShape groundBox;
	groundBox.SetAsBox(size.x / 2, size.y / 2);
	
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &groundBox;
	fixtureDef.filter.groupIndex = group;

	m_groundBody->CreateFixture(&fixtureDef);
};
