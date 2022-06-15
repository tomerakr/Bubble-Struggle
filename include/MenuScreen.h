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
	MenuScreen(Controller* ctrl, int numOfLevels);
	gameInfo menu();

private:
	void createLevels(int numOfLevels);
	void createButton();
	gameInfo handlePress	(const sf::Vector2f& mousePos);
	void mainMenuPress		(const sf::Vector2f& mousePos);
	void numOfPlayersPress	(const sf::Vector2f& mousePos);
	void connectionPress	(const sf::Vector2f& mousePos);
	void connectType(const sf::Vector2f& mousePos);
	void settings(const sf::Vector2f& mousePos);
	void handleHover		(const sf::Vector2f& mousePos);
	void handleKeyboard(sf::Event event);
	void draw();
	void chooseLevel(const sf::Vector2f& mousePos);

	Controller* m_controller;
	bool m_chooseLevel = false;
	bool m_onlineConnection = false;
	bool m_connectPressed = false;
	bool m_settingPressed = false;
	int m_lastHovered = 0;
	int m_wantedMenu = 0;
	std::vector <Button> m_volume;
	sf::RectangleShape m_volumeRectangle;
	sf::Text m_connectionText;
	sf::RectangleShape m_background;
	gameInfo m_info;
	
	sf::RectangleShape m_textRectangle;
	std::string m_input = "";
	sf::Text m_output;

	std::vector<Button> m_levels;
	std::vector<std::vector<Button>> m_buttons;
	std::vector< std::vector<std::string>> m_buttonNames = 
	{ { "Normal", "Survival", "Create Level", "Help", "Settings", "Exit" }, { "Choose Level" },
	  {"Solo", "Duo"}, {"Online", "Same PC"}, { "Host", "Connect" } };

	enum class buttonNames
	{
		Normal = 0,
		Survival,
		CreateLevel,
		Help,
		Settings,
		Exit,
		ChooseLevel = 0,
		Solo = 0,
		Duo,
		Online = 0,
		SamePC,
		Host = 0,
		Connect
	};

	enum class menuNames
	{
		mainMenu,
		levels,
		numOfPlayers,
		connection,
		connectionType
	};
};