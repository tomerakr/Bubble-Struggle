#include "Rope.h"

constexpr float ropeHeightChange = 1.8;
constexpr float maxRopeHeight = -(windowHeight - barHeight - thickness);

Rope::Rope(const sf::Vector2f& bearPos, int ropeTexture, Board* board, bool freezeRope)
	:MovingObject(bearPos, sf::Vector2f(ropeWitdh, ropeHeight), Objects::Ropes), m_board(board),
			m_freeze(freezeRope), m_ropeIndex(ropeTexture)
{
	auto textureSize = m_icon.getTexture()->getSize();
	//texture index range: 0 - 3
	m_icon.setTextureRect(sf::IntRect((textureSize.x / static_cast<int>(bearTypes::MAX)) * m_ropeIndex, 0, 
		textureSize.x / static_cast<int>(bearTypes::MAX), 0));

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	m_body = m_board->getWorld()->CreateBody(&bodyDef);

	setFixture(b2Vec2(m_icon.getSize().x / 2, ropeHeight));
	m_pos = b2Vec2(bearPos.x + m_icon.getSize().x / 2, bearPos.y - 1);
	m_body->SetTransform(m_pos, 0);
	m_body->SetFixedRotation(true);
	m_body->SetUserData(this);
}

void Rope::setFixture(const b2Vec2& size)
{
	b2PolygonShape ropeRectangle;
	ropeRectangle.SetAsBox(size.x, size.y);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &ropeRectangle;
	fixtureDef.density = 1;
	fixtureDef.friction = 0;
	fixtureDef.filter.groupIndex = ROPE_FILTER; 

	m_body->CreateFixture(&fixtureDef);
}

void Rope::update()
{
//		if rope collided with ball destroy rope 
	//if (m_box2DRope->GetFixtureList()->GetFilterData().groupIndex == POPPED_BALL_FILTER)		
	//{
	//	m_board->addGift(sf::Vector2f(m_pos.x, m_pos.y + m_icon.getSize().y));
	//	destroy();
	//	return true;
	//}
	//else if (m_box2DRope->GetFixtureList()->GetFilterData().groupIndex == ROPE_TOUCH_WALL)
	//{
	//	(!m_freeze ? destroy() : m_box2DRope->SetTransform(b2Vec2(m_pos.x, m_pos.y + m_icon.getSize().y / 2), 0));
	//
	//	//if (!m_freeze)
	//	//{
	//	//	//destroy();
	//	//}
	//	//else 
	//	//{
	//	//	m_box2DRope->SetTransform(b2Vec2(m_pos.x, m_pos.y + m_icon.getSize().y / 2), 0);
	//	//}
	//}
	//else
	//{
	//	growRope();
	//}
	growRope();
	//return false;
}

void Rope::growRope()
{
	m_icon.setSize(sf::Vector2f(m_icon.getSize().x, m_icon.getSize().y - ropeHeightChange)); // make rope longer
	m_body->DestroyFixture(m_body->GetFixtureList());
	m_body->SetTransform(b2Vec2(m_pos.x, m_pos.y + m_icon.getSize().y / 2), 0);
	setFixture(b2Vec2(m_icon.getSize().x / 2, -m_icon.getSize().y / 2));

	auto textureSize = m_icon.getTexture()->getSize();
	auto reletiveSize = (m_icon.getSize().y / maxRopeHeight) * textureSize.y;
	//texture index range: 0 - 3
	m_icon.setTextureRect(sf::IntRect((textureSize.x / static_cast<int>(bearTypes::MAX)) * m_ropeIndex, 0,
		textureSize.x / static_cast<int>(bearTypes::MAX), reletiveSize));
}

void Rope::destroy()
{
	//m_done = true;
	m_board->getWorld()->DestroyBody(m_body);
}