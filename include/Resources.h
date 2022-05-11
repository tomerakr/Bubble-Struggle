#pragma once

#include <vector>
#include "Macros.h"
#include <SFML/Graphics.hpp>

class Resources
{
public:
	const sf::Texture* getTexture(Objects texture);

private:
	std::vector<std::unique_ptr<sf::Texture>> m_texture;
};

