#include "Ball.h"
#include "Board.h"

Ball::Ball(Board* board, float radius, sf::Color color, sf::Vector2f pos, sf::Vector2i direction)
	:m_board(board)
{
	m_ball.setPosition(sf::Vector2f(pos));
	m_ball.setRadius(radius);
	m_ball.setFillColor(color);
}

void Ball::pop()
{
	m_board->addBalls(m_ball.getRadius() / 2, sf::Color::Magenta, m_ball.getPosition());
}