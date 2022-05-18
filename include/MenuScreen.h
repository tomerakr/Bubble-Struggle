#pragma once

#include <vector>
#include "Button.h"
#include "SFML/Graphics.hpp"

class Window;

class MenuScreen
{
public:
	MenuScreen(Window* window);
	void menu();

private:
	void createButton();
	void handlePress(sf::Vector2f mousePos);
	void handleHover(const sf::Vector2f mousePos);
	void draw();

	Window* m_window;
	int m_lastHovered = 0;
	int m_wantedMenu = 0;
	sf::RectangleShape m_background;

	std::vector<std::vector<Button>> m_buttons;
	std::vector< std::vector<std::string>> m_buttonNames = 
	{ { "Normal", "Survival", "Create Level", "Help", "Exit" }, { "Solo", "Duo" }, { "Online", "Same PC" } };

	enum class buttonNames
	{
		Normal = 0,
		Survival,
		CreateLevel,
		Help,
		Exit,
		Solo = 0,
		Duo,
		Online = 0,
		SamePC
	};
};