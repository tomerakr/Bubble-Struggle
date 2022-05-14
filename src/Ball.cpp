#include "Ball.h"
#include "Board.h"

Ball::Ball(Board* board, float radius, sf::Color color, sf::Vector2f pos, sf::Vector2i direction)
	:m_board(board)
{
	m_ball.setPosition(sf::Vector2f(pos));
	m_ball.setRadius(radius);
	m_ball.setFillColor(color);

    //set up dynamic body
    m_bodyDef.type = b2_dynamicBody;
    m_bodyDef.position.Set(pos.x, 5.f);
    m_body = m_board->getWorld()->CreateBody(&m_bodyDef);

    //add circle fixture
    m_ball2D.m_p.Set(1.f, 1.f);
    m_ball2D.m_radius = radius;
    
    m_fixtureDef.shape = &m_ball2D;
    m_fixtureDef.density = 1.0f;
    m_body->CreateFixture(&m_fixtureDef);
}

void Ball::pop()
{
	m_board->addBalls(m_ball.getRadius() / 2, sf::Color::Magenta, m_ball.getPosition()); 
}

void Ball::updatePos()
{
    auto pos = m_body->GetPosition();
    pos *= 100.f;
    m_ball.setPosition(pos.x, pos.y);
    m_ball.setFillColor(sf::Color::Blue);
}
