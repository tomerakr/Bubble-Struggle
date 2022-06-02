#pragma once

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"
#include "Macros.h"
#include <concepts>

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
		m_popped(other.m_popped), m_index(other.m_index)
	{
		;
	}

	Ball& operator=(Ball&& other) noexcept
	{
		auto temp = std::move(other);
		swap(std::move(*this), std::move(temp));
		return *this;
	}

	void swap(Ball&& that, Ball&& other)
	{
		std::ranges::swap(that.m_ball, other.m_ball);
		std::ranges::swap(that.m_popped, other.m_popped);
		std::ranges::swap(that.m_index, other.m_index);
		std::ranges::swap(that.m_board, other.m_board);
		std::ranges::swap(that.m_ball2D, other.m_ball2D);
		std::ranges::swap(that.m_body, other.m_body);
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

