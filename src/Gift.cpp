#include "Gift.h"
#include "Board.h"
#include "Bear.h"

constexpr int giftSideSize = 50;

Gift::Gift(const sf::Vector2f position, Board* board, int giftFilter)
	:StaticObject(position, sf::Vector2f(giftSideSize, giftSideSize), Objects::Gifts), m_board(board)
{
    auto textureSize = m_icon.getTexture()->getSize();
    //texture index range: 0 - 4
    m_icon.setTextureRect(sf::IntRect((textureSize.x / static_cast<int>(giftTypes::MAX)) * giftFilter, 0,
        textureSize.x / static_cast<int>(giftTypes::MAX), textureSize.y));

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(position.x + m_icon.getSize().x / 2, position.y + m_icon.getSize().y / 2);

    m_body = m_board->getWorld()->CreateBody(&bodyDef);
    m_body->SetUserData(this);

    m_rect2D.SetAsBox(m_icon.getSize().x / 2, m_icon.getSize().y / 2);

    b2FixtureDef fixtureDef;
    fixtureDef.density = 1;
    fixtureDef.shape = &m_rect2D;
    fixtureDef.filter.groupIndex = m_filters[giftFilter];

    m_body->CreateFixture(&fixtureDef);
}

void Gift::update()
{
    //m_timer.update();
    //
    //if (m_timer.timeEnd())
    //{
    //    m_isDone = true;
    //}

    //if (m_body->GetFixtureList()->GetFilterData().groupIndex == TOUCH_BEAR)
    //{
    //    m_board->getWorld()->DestroyBody(m_body);   //temp solution
    //    m_done = true;
    //}
    //else
    m_icon.setPosition(sf::Vector2f(m_body->GetPosition().x - m_icon.getSize().x / 2,
        m_body->GetPosition().y - m_icon.getSize().y / 2));
}

bool Gift::getIsDone() const
{
    return m_done;
}

void Gift::destroyBody()
{
    m_board->getWorld()->DestroyBody(m_body);
}

void Gift::taken()
{
    m_done = true;
    destroyBody();
}