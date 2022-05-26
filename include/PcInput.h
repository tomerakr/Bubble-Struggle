#pragma once

#include "Input.h"
#include "SFML/Graphics.hpp"
#include "Macros.h"
#include <vector>

class PcInput : public Input
{
public:
	PcInput() = default;
	//~PcInput() = default;
	std::pair<sf::Vector2f, bool> getInput(std::vector<sf::Keyboard::Key> keys) override;

private:
	sf::Vector2f readDirection(std::vector<sf::Keyboard::Key> keys);
	bool readShoot(std::vector<sf::Keyboard::Key> keys);
};