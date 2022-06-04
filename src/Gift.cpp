#include "Gift.h"
#include "Board.h"
#include "Bear.h"

Gift::Gift(const sf::Vector2f position, Board* board, const int giftFilter)
	:MovingObject(position, sf::Vector2f(50, 50), Objects::Gifts), m_board(board)
{
    auto textureSize = m_icon.getTexture()->getSize();
    //texture index range: 0 - 4
    m_icon.setTextureRect(sf::IntRect((textureSize.x / static_cast<int>(giftTypes::MAX)) * giftFilter, 0, textureSize.x / static_cast<int>(giftTypes::MAX), textureSize.y));

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(position.x + m_icon.getPosition().x / 2, position.y + m_icon.getPosition().y / 2);

    m_body = m_board->getWorld()->CreateBody(&bodyDef);

    m_rect2D.SetAsBox(m_icon.getSize().x / 2, m_icon.getSize().y / 2);

    b2FixtureDef fixtureDef;
    fixtureDef.density = 1;
    fixtureDef.shape = &m_rect2D;
    fixtureDef.filter.groupIndex = giftFilter;

    m_body->CreateFixture(&fixtureDef);
}

void Gift::update()
{
    //m_timer.update();

    //if (m_timer.timeEnd())
    //{
    //    m_isDone = true;
    //}

    if (m_body->GetFixtureList()->GetFilterData().groupIndex == TOUCH_BEAR)
    {
        m_body->SetTransform(b2Vec2(-500, -500), 0);
    }

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