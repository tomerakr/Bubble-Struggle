#include "Tile.h"
#include "Board.h"

Tile::Tile(Board* board, const sf::Vector2f& size, const sf::Vector2f& pos)
	:StaticObject(pos, size, (size.x > size.y ? Objects::Floor : Objects::Wall)), m_board(board)
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(pos.x + size.x / 2, pos.y + size.y / 2);
	m_tileBody = board->getWorld()->CreateBody(&bodyDef);
	
	b2PolygonShape groundBox;
	groundBox.SetAsBox(size.x / 2, size.y / 2);
	
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &groundBox;
	fixtureDef.density = 3000;
	fixtureDef.filter.groupIndex = TILE;// (pos.y == windowHeight - thickness - barHeight ? TILE : CEILING);
	m_tileBody->CreateFixture(&fixtureDef);
};

Tile::Tile(const sf::Vector2f& size, const sf::Vector2f& pos)
	:StaticObject(pos, size, (size.x > size.y ? Objects::Floor : Objects::Wall))
{}

void Tile::destroyBody()
{
	m_board->getWorld()->DestroyBody(m_tileBody);
}
