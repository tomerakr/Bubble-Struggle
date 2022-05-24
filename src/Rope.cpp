#include "Rope.h"

constexpr float ropeHeightChange = 1.5;
constexpr float maxRopeHeight = -650;

Rope::Rope(sf::Vector2f pos, sf::Vector2f size, Objects ropeTexture, Board* board)
	:MovingObject(pos, size, ropeTexture, sf::Color::White), m_board(board)
{
	m_icon.setTexture(Resources::instance().getObjectTexture(ropeTexture));

	b2BodyDef bodyDef;	
	m_box2DRope = m_board->getWorld()->CreateBody(&bodyDef);

	b2PolygonShape ropeRectangle;
	ropeRectangle.SetAsBox(m_icon.getSize().x / 2, 400);		
	
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &ropeRectangle;

	m_box2DRope->CreateFixture(&fixtureDef);

	m_box2DRope->SetTransform(b2Vec2(m_box2DRope->GetPosition().x, 1200), 0);	// position is center of rectangle
}

void Rope::followBear(const sf::Vector2f bearPos)
{
	if (!m_isShot)					//	follow bear if not shot already
	{
		m_icon.setPosition(bearPos);

		m_box2DRope->SetTransform(b2Vec2(bearPos.x, m_icon.getPosition().y + 400), 0);

		resetSize();

		m_isShot = true;
	}
}

void Rope::update()
{


	if (m_isShot)
	{
		m_icon.setSize(sf::Vector2f(m_icon.getSize().x, m_icon.getSize().y - ropeHeightChange)); // make rope longer

		m_box2DRope->SetTransform(b2Vec2(m_box2DRope->GetPosition().x,
								m_box2DRope->GetPosition().y - ropeHeightChange), 0);
	}

	if (m_icon.getSize().y < maxRopeHeight)					// if rope height is too long stop increasing height
	{
		m_isShot = false;
		resetSize();
	}
}

void Rope::resetSize()
{
	m_icon.setSize(sf::Vector2f(m_icon.getSize().x, 0));

	m_box2DRope->SetTransform(b2Vec2(m_box2DRope->GetPosition().x, 1200), 0);
}