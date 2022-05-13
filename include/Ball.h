#pragma once

#include "SFML/Graphics.hpp"
#include "MovingObject.h"

constexpr float defRadius = 60.f;

class Board;

class Ball/* : public MovingObject*/
{
public:
	Ball(Board* board, float radius = defRadius, sf::Color = sf::Color::Red, sf::Vector2f pos = sf::Vector2f(300, 100),
		sf::Vector2i = sf::Vector2i(1, 0));
	void pop();
	void draw(sf::RenderWindow& window) { window.draw(m_ball); }

private:
	sf::CircleShape m_ball;
	b2CircleShape m_ball2D;
	Board* m_board;
};

