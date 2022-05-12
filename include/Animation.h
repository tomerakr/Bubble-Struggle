   #pragma once

#include "SFML/Graphics/hpp"

class Animation
{
public:
	Animation();
	void update();

private:
	sf::UVrect m_UVrect;
};

