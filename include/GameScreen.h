#pragma once

#include "Macros.h"
#include "SFML/Graphics.hpp"
#include <utility>

class Window;
class Bear;
class Board;

class GameScreen
{
	using getInput = std::pair<sf::Vector2f, bool>(*)();

public:
	GameScreen(Window* window, Board* board);
	static sf::Vector2f readDirection();
	static bool readShoot();
	void game(gameInfo& info);
	Screen gamePlay(gameInfo& info);

private:
	static std::pair<sf::Vector2f, bool> soloInput();
	static std::pair<sf::Vector2f, bool> samePcInput();
	static std::pair<sf::Vector2f, bool> onlineInput();


	void playNormal(gameInfo& info);
	void playSurvival(gameInfo& info);

	void update(float deltaTime);
	Screen handleKeyboard(const float deltaTime);
	void draw();

	getInput m_input;

	Window* m_window;
	std::vector<Bear> m_bears;
	Board* m_board;
};

