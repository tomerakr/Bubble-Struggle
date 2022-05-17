#pragma once

#include "SFML/Graphics.hpp"
#include "MovingObject.h"
#include "box2d/box2d.h"

constexpr float defRadius = 90.f;

class Board;

class Ball
{
public:
	Ball(Board* board, const b2Vec2 initialForce, const float radius = defRadius,
				sf::Color = sf::Color::Red, const sf::Vector2f pos = sf::Vector2f(300, 100));
	//~Ball();
	void pop()							{ m_popped = true; }
	const bool needToDelete() const		{ return (m_popped || m_ball.getRadius() < 10); }
	void split();
	void draw(sf::RenderWindow& window) { window.draw(m_ball); }
	const sf::Vector2f getPos() const	{ return m_ball.getPosition(); }
	void updatePos();
	void colorBall();			//debug

private:
	void setBall2D(const b2Vec2 initialForce);
	sf::CircleShape m_ball;
	bool m_popped = false;
	Board* m_board;

	b2CircleShape m_ball2D;
	b2Body* m_body;
};

