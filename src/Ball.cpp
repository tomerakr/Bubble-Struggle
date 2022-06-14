#include "Ball.h"
#include "Board.h"

Ball::Ball(Board* board, const sf::Vector2f& pos, const b2Vec2& initialForce, int index, bool special)
	:Ball(pos, index, (initialForce.x > 0 ? 1 : -1), (initialForce.x > 0 ? 1 : -1))
{
    m_index = index;
    m_board = board;

    m_special = special;

    setBall2D(initialForce);
}

Ball::Ball(const sf::Vector2f& pos, int index, int direction, int indentaion)
    : m_index(index), m_board(nullptr), m_body(nullptr), m_direction(direction)
{
    m_ball.setTexture(Resources::instance().getObjectTexture(Objects::Ball));
    m_ball.setRadius((defRadius - 10 * index));
    m_ball.setOrigin(sf::Vector2f(m_ball.getRadius(), m_ball.getRadius()));
    m_ball.setPosition(sf::Vector2f(pos.x + indentaion * m_ball.getRadius(), pos.y));
    m_ball.setFillColor(Resources::instance().getColor(index));
}

void Ball::destroy()
{
    m_destroy = true;
    destroyBody();
    m_body = nullptr;
}

void Ball::setBall2D(const b2Vec2& initialForce)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(m_ball.getPosition().x, m_ball.getPosition().y);

    bodyDef.linearVelocity = initialForce/* + b2Vec2(0, -100)*/;
    m_body = m_board->getWorld()->CreateBody(&bodyDef);
    
    //add circle fixture
    m_ball2D.m_p.Set(1.f, 1.f);
    m_ball2D.m_radius = m_ball.getRadius();

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &m_ball2D;
    fixtureDef.density = 1;
    fixtureDef.friction = 0.f;
    fixtureDef.restitution = 1;
    fixtureDef.filter.groupIndex = BALL_FILTER;
    m_body->CreateFixture(&fixtureDef);
    m_body->SetUserData(this);
    //std::cout << typeid(static_cast<GameObject*>(m_body->GetUserData())).name() << '\n';
}

void Ball::split()
{
    if (m_index < numOfBalls && m_splittable)
    {
        m_board->addBalls(m_ball.getPosition(), m_index + 1);
    }
}

void Ball::destroyBody()
{
    if (m_body)
    { 
        m_board->getWorld()->DestroyBody(m_body);
    }
}

void Ball::update()
{
    if (!m_body)
    {
        return;
    }
    auto pos = m_body->GetPosition();
    m_ball.setPosition(pos.x, pos.y);
    if (/*m_popped m_body->GetFixtureList()->GetFilterData().groupIndex == POPPED_BALL_FILTER || */m_ball.getRadius() < 10)
    {
        m_popped = true;
        //if (m_splittable)
        //{
        //    m_popped = true;
        //}
        //
        //resetFilter();
    }

    else if (m_body->GetFixtureList()->GetFilterData().groupIndex == TILE && m_special)
    {
        m_splittable = !m_splittable;
        resetFilter();
    }
}

void Ball::resetFilter()
{
    b2Filter ballFilter;
    ballFilter.groupIndex = BALL_FILTER;
    m_body->GetFixtureList()->SetFilterData(ballFilter);
}

//Ball::~Ball()
//{
//    if (m_body)
//    {
//        m_board->getWorld()->DestroyBody(m_body);
//    }
//}