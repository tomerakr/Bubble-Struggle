#pragma once

#include <SFML/Graphics.hpp>

class Window
{
public:
	Window();
	sf::RenderWindow& getWindow();

private:
	sf::RenderWindow m_window;
};

