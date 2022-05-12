#pragma once

#include "SFML/Graphics.hpp"
#include "MovingObject.h"

constexpr float defRadius = 30.f;

class Ball : public MovingObject
{
public:
	Ball(float radius = defRadius, sf::Color = sf::Color::Red, sf::Vector2i = sf::Vector2i(1, 0));
	void pop();
};

