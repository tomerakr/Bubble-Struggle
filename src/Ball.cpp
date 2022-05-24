#include "Ball.h"
#include "Board.h"
#include <time.h>

Ball::Ball(Board* board, const sf::Vector2f pos, const b2Vec2 initialForce, const int index)
	:m_index(index), m_board(board)
{
    m_ball.setTexture(Resources::instance().getObjectTexture(Objects::Ball));
	m_ball.setRadius((defRadius - 10 * m_index));
    m_ball.setOrigin(sf::Vector2f(m_ball.getRadius(), m_ball.getRadius()));
    auto indentation = (initialForce.x > 0 ? m_ball.getRadius() : -m_ball.getRadius());
	m_ball.setPosition(sf::Vector2f(pos.x + indentation , pos.y));
	m_ball.setFillColor(Resources::instance().getColor(index));

    setBall2D(initialForce);
}

void Ball::setBall2D(const b2Vec2 initialForce)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(m_ball.getPosition().x, m_ball.getPosition().y);

    bodyDef.linearVelocity = initialForce;
    m_body = m_board->getWorld()->CreateBody(&bodyDef);
    
    //add circle fixture
    m_ball2D.m_p.Set(1.f, 1.f);
    m_ball2D.m_radius = m_ball.getRadius();

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &m_ball2D;
    fixtureDef.density = 1;
    fixtureDef.friction = 0;
    fixtureDef.restitution = 1.f;
    fixtureDef.filter.groupIndex = -1;

    m_body->CreateFixture(&fixtureDef);
}

void Ball::split()
{
    m_board->getWorld()->DestroyBody(m_body); //why here
    if (m_index < numOfBalls)
    {
        m_board->addBalls(m_ball.getPosition(), m_index + 1);
    }
}

void Ball::update()
{
    auto pos = m_body->GetPosition();
    m_ball.setPosition(pos.x, pos.y);

    for (b2ContactEdge* edge = m_body->GetContactList(); edge; edge = edge->next)
    {
        if (edge->contact->GetFixtureA()->GetFilterData().groupIndex == ROPE_FILTER)
        {
            m_popped = true;
            auto ropeData = edge->contact->GetFixtureA()->GetUserData();

        }
    }
}

void Ball::colorBall() //for DEBUG
{
    srand(time(NULL));

    m_ball.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
}

//Ball::~Ball() //does not work for some reason?
//{
//    m_board->getWorld()->DestroyBody(m_body);
//}