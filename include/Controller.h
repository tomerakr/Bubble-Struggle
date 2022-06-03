#pragma once

#include "MenuScreen.h"
#include "GameScreen.h"
#include "LevelCreator.h"
#include "SFML/Graphics.hpp"

constexpr int maxFPS = 300;

class Controller
{
public:
	Controller();
	void play();

	sf::RenderWindow& getWindow() { return m_window; }

private:
	sf::RenderWindow m_window;
	MenuScreen m_menu;
	GameScreen m_game;
	LevelCreator m_levelCreator;
};