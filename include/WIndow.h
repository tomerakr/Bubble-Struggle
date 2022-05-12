#pragma once

#include <SFML/Graphics.hpp>

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

