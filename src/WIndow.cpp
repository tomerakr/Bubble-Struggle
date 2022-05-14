#include "Window.h"

Window::Window()
	: m_window(sf::VideoMode(windowWitdh, windowHieght), "Bubble Struggle", sf::Style::Close | sf::Style::Titlebar)
{
	m_window.setFramerateLimit(maxFPS);
}