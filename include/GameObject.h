#pragma once

#include "Macros.h"
#include "Resources.h"
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

class GameObject
{
public:
	virtual void draw(sf::RenderWindow& window) = 0;

protected:
	b2Body* m_body = nullptr;
};