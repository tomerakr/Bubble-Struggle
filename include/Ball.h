#pragma once

#include "SFML/Graphics.hpp"
#include "MovingObject.h"
#include "box2d/box2d.h"

constexpr float defRadius = 60.f;

class Board;

class Ball
{
public:
	Ball(Board* board, float radius = defRadius, sf::Color = sf::Color::Red, sf::Vector2f pos = sf::Vector2f(300, 100),
		sf::Vector2i direction = sf::Vector2i(1, 0));
	void pop();
	void draw(sf::RenderWindow& window) { window.draw(m_ball); }
	sf::Vector2f getPos() { return m_ball.getPosition(); }
	void updatePos();

private:
	sf::CircleShape m_ball;
	Board* m_board;

	b2CircleShape m_ball2D;
	b2Body* m_body;
};

