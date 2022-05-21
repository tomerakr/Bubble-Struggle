#pragma once

#include "Macros.h"

class Window;
class Bear;
class Board;

class GameScreen
{
public:
	GameScreen(Window* window, Bear* bear, Board* board);
	Screen gamePlay();

private:
	void update(float deltaTime);
	Screen handleKeyboard(const float deltaTime);
	void draw();

	Window* m_window;
	Bear* m_bear;
	Board* m_board;
};