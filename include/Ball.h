#pragma once

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"
#include "Macros.h"

constexpr float defRadius = 90.f;

class Board;

class Ball
{
public:
	Ball(Board* board, const sf::Vector2f& pos, const b2Vec2& initialForce, int index = 0);
	Ball(const sf::Vector2f& pos, int index = 0, int indentaion = 0);
	Ball(const Ball&) = delete;
	void operator=(const Ball&) = delete;
	Ball(Ball&& other) : m_ball(std::move(other.m_ball)), m_board(std::move(other.m_board)), 
		m_ball2D(std::move(other.m_ball2D)), m_body(std::exchange(other.m_body, nullptr)),
		m_popped(std::move(other.m_popped)), m_index(std::move(other.m_index))
	{}

	Ball& operator=(Ball&& other)
	{
		m_ball = std::move(other.m_ball);
		m_popped = std::move(other.m_popped);
		m_index = std::move(other.m_index);
		m_board = std::move(other.m_board);
		m_ball2D = std::move(other.m_ball2D);
		m_body = std::move(other.m_body);

		return *this;
	}

	~Ball();
	void reset() { ; }	//until the destructor will work
	void update();
	void split();
	bool popped() const					{ return m_popped; }
	void draw(sf::RenderWindow& window) { window.draw(m_ball); }
	const sf::Vector2f& getPos() const	{ return m_ball.getPosition(); }
	int getIndex() const			{ return m_index; }
	bool contains(const sf::Vector2f& mousePos) const { return m_ball.getGlobalBounds().contains(mousePos); }

private:
	void setBall2D(const b2Vec2& initialForce);
	sf::CircleShape m_ball;
	bool m_popped = false;
	int m_index;
	Board* m_board;

	b2CircleShape m_ball2D;
	b2Body* m_body;
};

