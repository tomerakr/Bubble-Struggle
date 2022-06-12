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
	Ball(Board* board, const sf::Vector2f& pos, const b2Vec2& initialForce, int index = 0, bool special = false);
	Ball(const sf::Vector2f& pos, int index = 0, int direction = 1, int indentaion = 0);
	//Ball(const Ball&) = delete;
	//void operator=(const Ball&) = delete;
	//Ball(Ball&& other) noexcept : m_ball(std::move(other.m_ball)), m_board(std::move(other.m_board)),
	//	m_ball2D(std::move(other.m_ball2D)), m_body(std::exchange(other.m_body, nullptr)),
	//	m_popped(other.m_popped), m_index(other.m_index), m_direction(other.m_direction)
	//{	
	//	;
	//}
	//
	//Ball& operator=(Ball&& other) noexcept
	//{
	//	swap(*this, other);
	//	return *this;
	//}
	//
	//void swap(Ball& that, Ball& other)
	//{
	//	std::ranges::swap(that.m_ball, other.m_ball);
	//	std::ranges::swap(that.m_popped, other.m_popped);
	//	std::ranges::swap(that.m_direction, other.m_direction);
	//	std::ranges::swap(that.m_index, other.m_index);
	//	std::ranges::swap(that.m_board, other.m_board);
	//	std::ranges::swap(that.m_ball2D, other.m_ball2D);
	//	std::ranges::swap(that.m_body, other.m_body);
	//}
	//
	//~Ball();
	void destroyBody();
	void update();
	void split();
	bool popped() const					{ return m_popped; }
	void draw(sf::RenderWindow& window) { window.draw(m_ball); }
	const sf::Vector2f& getPos() const	{ return m_ball.getPosition(); }
	int getIndex() const				{ return m_index; }
	int getRaidus() const				{ return m_ball.getRadius(); }
	int getDirection() const			{ return m_direction; }
	bool contains(const sf::Vector2f& mousePos) const { return m_ball.getGlobalBounds().contains(mousePos); }
	//========================= ?  ?  ?  ?  ?  ?  =========================
	int getCurrDirection() const			{ return (m_body->GetLinearVelocity().x > 0 ? 1 : -1); }
	b2Vec2 getForce() const	{ return m_body->GetLinearVelocity(); }
	void destroy();
	bool destroied() const	{ return m_destroy; }
	void creatingNewBall()		{ m_hadChild = true; }
	bool hadChild()	const	{ return m_hadChild; }

private:
	void setBall2D(const b2Vec2& initialForce);
	sf::CircleShape m_ball;
	bool m_popped = false;
	bool m_destroy = false;
	bool m_hadChild = false;
	bool m_splittable = true;			// if the ball currently splittable
	bool m_special = false;				// if the ball can be unsplittable
	int m_index;
	int m_direction;
	Board* m_board;

	b2CircleShape m_ball2D;
	b2Body* m_body;

	void resetFilter();
};

