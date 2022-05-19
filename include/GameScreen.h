#pragma once

class Window;
class Bear;
class Board;

class GameScreen
{
public:
	GameScreen(Window* window, Bear* bear, Board* board);
	void game();

private:
	void update(float deltaTime);
	void handleKeyboard(const float deltaTime);
	void draw();

	Window* m_window;
	Bear* m_bear;
	Board* m_board;
};