#pragma once

#include "Bear.h"
#include "Board.h"
#include "Window.h"

class Controller
{
public:
	Controller();
	void play();
	void restartLevel();

private:
	void handleKeyboard(float deltaTime);
	void draw();

	Rope m_rope;
	Bear m_bear;
	Board m_board;
	Window m_window;

};