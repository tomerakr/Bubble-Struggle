#include "Ball.h"
#include "Board.h"
#include <time.h>
#include <math.h>

float pixelToMeter(const int pixels) { return pixels * UNRATIO; }

Ball::Ball(Board* board, const b2Vec2 initialForce, const float radius, sf::Color color, const sf::Vector2f pos)
	:m_board(board)
{
	m_ball.setPosition(sf::Vector2f(pos));
	m_ball.setRadius(radius);
	m_ball.setFillColor(color);

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
    m_ball2D.m_radius = pixelToMeter(m_ball.getRadius()); //needs convert

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
    m_board->addBalls(m_ball.getRadius() / 2, sf::Color::Magenta, m_ball.getPosition());
}

void Ball::updatePos()
{
    auto pos = m_body->GetPosition();
    m_ball.setPosition(pos.x, pos.y);
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