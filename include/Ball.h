#pragma once

#include "SFML/Graphics.hpp"
#include "MovingObject.h"
#include "box2d/box2d.h"

constexpr float defRadius = 90.f;

class Board;

class Ball
{
public:
	Ball(Board* board, int direction = 1, float radius = defRadius, sf::Color = sf::Color::Red, sf::Vector2f pos = sf::Vector2f(300, 100));
	//~Ball();
	void pop()							{ m_popped = true; }
	void collision(Board* board);	//--
	void pushBallUP();			//--
	const bool needToDelete() const		{ return (m_popped || m_ball.getRadius() < 10); }
	void split();
	void draw(sf::RenderWindow& window) { window.draw(m_ball); }
	sf::Vector2f getPos()				{ return m_ball.getPosition(); }
	void updatePos();
	void colorBall();			//debug

private:

	sf::CircleShape m_ball;
	bool m_popped = false;
	Board* m_board;

	b2CircleShape m_ball2D;
	b2Body* m_body;
};

