#pragma once

#include "Bear.h"
#include "Board.h"
#include "Window.h"
#include "MenuScreen.h"
#include "GameScreen.h"

class Controller
{
public:
	Controller();
	void play();

private:
	int currentLevel = 1;

	Board m_board;
	Window m_window;
	MenuScreen m_menu;
	GameScreen m_game;
};