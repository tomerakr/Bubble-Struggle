#pragma once

constexpr int myPort = 6969;

#include "Macros.h"
#include "Bar.h"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include <utility>
#include <vector>

class Window;
class Bear;
class Board;

class GameScreen
{
	using getInput = std::pair<sf::Vector2f, bool>(*)(Bear* bear);

public:
	GameScreen(Window* window, Board* board);
	void game(gameInfo& info);
	Screen gamePlay(gameInfo& info);

private:
	std::vector<std::vector<sf::Keyboard::Key>> m_keys;

	Screen playNormal();
	Screen playSurvival();

	void update(float deltaTime, gameInfo& info);
	Screen handleKeyboard(const float deltaTime);
	void draw();

	Window* m_window;
	std::vector<Bear> m_bears;
	Board* m_board;
	Bar m_bar;
	
};
