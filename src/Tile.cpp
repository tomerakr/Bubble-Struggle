#include "Tile.h"
#include "Board.h"

constexpr int FLOOR = -2;
constexpr int WALL = -3;

Tile::Tile(Board* board, const sf::Vector2f size, const sf::Vector2f pos, int group)
	:StaticObject(pos, size, (group == FLOOR ? Objects::Floor : Objects::Wall))
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
