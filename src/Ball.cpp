#include "Ball.h"
#include "Board.h"

Ball::Ball(Board* board, float radius, sf::Color color, sf::Vector2f pos)
	:m_board(board)
{
	m_ball.setPosition(sf::Vector2f(pos));
	m_ball.setRadius(radius);
	m_ball.setFillColor(color);

    //set up dynamic body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.x, pos.y);
    bodyDef.angularVelocity = true; // set with true? can we +a and -a?
    m_body = m_board->getWorld()->CreateBody(&bodyDef);

    //add circle fixture
    m_ball2D.m_p.Set(1.f, 1.f);
    m_ball2D.m_radius = radius * 1.9; //needs convert
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &m_ball2D;
    fixtureDef.density = 1.f;
    fixtureDef.friction = 0.4f;
    fixtureDef.restitution = 0.f;
    m_body->CreateFixture(&fixtureDef);
}

void Ball::foo() //find good name
{
    m_board->addBalls(m_ball.getRadius() / 2, sf::Color::Magenta, m_ball.getPosition());
}

void Ball::updatePos()
{
    auto pos = m_body->GetPosition();
    m_ball.setPosition(pos.x, pos.y);
}

//Ball::~Ball()
//{
//    m_board->getWorld()->DestroyBody(m_body);
//}