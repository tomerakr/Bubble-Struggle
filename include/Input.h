#pragma once

#include "SFML/Graphics.hpp"
#include <utility>

class Input
{
public:
	//virtual ~Input() = 0;
	~Input() = default;
	virtual std::pair<sf::Vector2f, bool> getInput(std::vector<sf::Keyboard::Key> keys) = 0;
};