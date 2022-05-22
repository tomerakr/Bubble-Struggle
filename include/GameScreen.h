#pragma once

#include "Macros.h"
#include "SFML/Graphics.hpp"
#include <utility>

class Window;
class Bear;
class Board;
typedef std::pair<sf::Vector2f, bool>(*getInput)();
//using getInfo = std::pair<sf::Vector2f, bool>(*getInput)();

class GameScreen
{
public:
	GameScreen(Window* window, Bear* bear, Board* board);
	void game(gameInfo& info);
	Screen gamePlay();

private:
	void playNormal(gameInfo& info);
	void playSurvival(gameInfo& info);

	std::pair<sf::Vector2f, bool> soloInput();
	sf::Vector2f readDirection();
	bool readShoot();

	std::pair<sf::Vector2f, bool> samePcInput();
	std::pair<sf::Vector2f, bool> onlineInput();

	//using getInfo = std::pair<sf::Vector2f, bool>(*foo)();	
	//using getInfo = int(*foo())(int);

	void update(float deltaTime);
	Screen handleKeyboard(const float deltaTime);
	void draw();

	Window* m_window;
	Bear* m_bear;
	Board* m_board;
};

