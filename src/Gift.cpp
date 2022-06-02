#include "Gift.h"
#include "Board.h"

Gift::Gift(const sf::Vector2f position, Board* board, const Objects giftType)
	:MovingObject(position, sf::Vector2f(50, 50), Objects::Bear), m_giftType(giftType),
		m_board(board)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(position.x + m_icon.getPosition().x / 2, position.y + m_icon.getPosition().y / 2);

    m_body = m_board->getWorld()->CreateBody(&bodyDef);

    m_rect2D.SetAsBox(m_icon.getSize().x / 2, m_icon.getSize().y / 2);

    b2FixtureDef fixtureDef;
    fixtureDef.density = 1;
    fixtureDef.shape = &m_rect2D;
    fixtureDef.filter.groupIndex = GIFT_FREEZE_FILTER;

    m_body->CreateFixture(&fixtureDef);
}

void Gift::update()
{
    //m_timer.update();

    //if (m_timer.timeEnd())
    //{
    //    m_isDone = true;
    //}

    m_icon.setPosition(sf::Vector2f(m_body->GetPosition().x, m_body->GetPosition().y));
}

bool Gift::getIsDone() const
{
    return m_isDone;
}

//Gift::~Gift()
//{
//    if (m_body != nullptr)
//    {
//        m_board->getWorld()->DestroyBody(m_body);
//    }
//}