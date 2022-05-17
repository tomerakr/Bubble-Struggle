#pragma once

#include "Bear.h"
#include "Board.h"
#include "Window.h"
#include "MenuScreen.h"

class Controller
{
public:
	Controller();
	void play();
	void restartLevel();

private:
	void handleKeyboard(const float deltaTime);
	void draw();

	MenuScreen m_menu;
	Bear m_bear;
	Board m_board;
	Window m_window;
};