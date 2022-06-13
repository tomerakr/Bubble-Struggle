#pragma once

#include "Macros.h"
#include "Resources.h"
#include "SFML/Graphics.hpp"

class GameObject
{
public:
	virtual void draw(sf::RenderWindow& window) = 0;
};