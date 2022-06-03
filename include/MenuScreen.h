#pragma once

#include <vector>
#include "Button.h"
#include "Macros.h"
#include "Resources.h"
#include "SFML/Graphics.hpp"

class Controller;

class MenuScreen
{
public:
	MenuScreen(Controller* ctrl);
	gameInfo menu();

private:
	void createButton();
	gameInfo handlePress	(const sf::Vector2f& mousePos);
	void mainMenuPress		(const sf::Vector2f& mousePos);
	void numOfPlayersPress	(const sf::Vector2f& mousePos);
	void connectionPress	(const sf::Vector2f& mousePos);
	void handleHover		(const sf::Vector2f& mousePos);
	void handleKeyboard();
	void draw();

	Controller* m_controller;
	int m_lastHovered = 0;
	int m_wantedMenu = 0;
	sf::RectangleShape m_background;
	gameInfo m_info;

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

	enum class menuNames
	{
		mainMenu,
		numOfPlayers,
		connection
	};
};