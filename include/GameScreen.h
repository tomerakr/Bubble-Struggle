#pragma once

#include "Macros.h"
#include "SFML/Graphics.hpp"
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
	static sf::Vector2f readDirection(Bear* bear);
	static bool readShoot(Bear* bear);
	void game(gameInfo& info);
	Screen gamePlay(gameInfo& info);

private:
	static std::pair<sf::Vector2f, bool> soloInput(Bear* bear);
	static std::pair<sf::Vector2f, bool> samePcInput(Bear* bear);
	static std::pair<sf::Vector2f, bool> onlineInput(Bear* bear);

	std::vector<std::vector<sf::Keyboard::Key>> m_keys;
	std::vector<Objects> m_objects;

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

