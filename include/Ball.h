#pragma once

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"
#include "GameObject.h"
#include "Macros.h"

#include <concepts>

constexpr float defRadius = 90.f;

class Board;

class Ball : public GameObject
{
public:
	Ball(Board* board, const sf::Vector2f& pos, const b2Vec2& initialForce, int index = 0, bool special = false);
	Ball(const sf::Vector2f& pos, int index = 0, int direction = 1, int indentaion = 0);

	void pop() { m_popped = true; }

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

