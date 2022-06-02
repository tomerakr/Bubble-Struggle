#include "Rope.h"

constexpr float ropeHeightChange = 2;
constexpr float maxRopeHeight = -(windowHieght - barHeight - thickness);

Rope::Rope(sf::Vector2f bearPos, int ropeTexture, Board* board)
	:MovingObject(bearPos, sf::Vector2f(ropeWitdh, ropeHeight), 
		Resources::instance().getSkin(ropeTexture)._rope, sf::Color::White), 
		m_board(board)
{
	b2BodyDef bodyDef;
	m_box2DRope = m_board->getWorld()->CreateBody(&bodyDef);
	setFixture(b2Vec2(m_icon.getSize().x / 2, 0));
	m_box2DRope->SetTransform(b2Vec2(bearPos.x + m_icon.getSize().x / 2, bearPos.y), 0);
}

void Rope::setFixture(b2Vec2 size)
{
	b2PolygonShape ropeRectangle;
	ropeRectangle.SetAsBox(size.x, size.y);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &ropeRectangle;
	fixtureDef.filter.groupIndex = ROPE_FILTER;
	fixtureDef.density = 1;

	m_box2DRope->CreateFixture(&fixtureDef);
}

void Rope::update()
{
// if rope height is too long or touched ball destroy rope
	if (m_box2DRope->GetFixtureList()->GetFilterData().groupIndex == POPPED_BALL_FILTER)		
	{
		destroy();
	}

	else if (m_box2DRope->GetFixtureList()->GetFilterData().groupIndex == TOUCH_WALL)
	{
		if (!m_freeze)
		{
			destroy();
		}
	}

	else
	{
		m_icon.setSize(sf::Vector2f(m_icon.getSize().x, m_icon.getSize().y - ropeHeightChange)); // make rope longer
		m_box2DRope->DestroyFixture(m_box2DRope->GetFixtureList());
		setFixture(b2Vec2(m_icon.getSize().x / 2, -m_icon.getSize().y));
	}

	
	//for (b2ContactEdge* edge = m_box2DRope->GetContactList(); edge; edge = edge->next)
	//{
	//	if (edge->contact->GetFixtureB()->GetFilterData().groupIndex == BALL_FILTER)
	//	{
	//		b2Filter filter;
	//		filter.groupIndex = POPPED_BALL_FILTER;
	//		edge->contact->GetFixtureB()->SetFilterData(filter);
	//		m_done = true;
	//		m_board->getWorld()->DestroyBody(m_box2DRope); //why we cant in destructor
	//		break;
	//	}
	//	else if (edge->contact->GetFixtureB()->GetFilterData().groupIndex == FLOOR)
	//	{
	//		m_done = true;
	//		m_board->getWorld()->DestroyBody(m_box2DRope);
	//		break;
	//	}
	//}
}

void Rope::destroy()
{
	m_done = true;
	m_board->getWorld()->DestroyBody(m_box2DRope);
}