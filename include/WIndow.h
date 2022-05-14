#pragma once

#include "Macros.h"
#include <SFML/Graphics.hpp>

constexpr int maxFPS = 300;

class Window
{
public:
	Window();

	sf::RenderWindow& getWindow()	{ return m_window; }
	bool isOpen()					{ return m_window.isOpen(); }
	void clear()					{ m_window.clear(sf::Color::White); }
	void display()					{ m_window.display(); }

private:
	sf::RenderWindow m_window;
};

