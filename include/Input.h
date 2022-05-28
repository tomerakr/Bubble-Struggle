#pragma once

#include "SFML/Graphics.hpp"
#include <utility>
#include "Macros.h"

class Input
{
public:
	//virtual ~Input() = 0;
	~Input() = default;
	virtual std::pair<sf::Vector2f, bool> getInput(gameInput input) = 0;
};