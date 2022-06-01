#pragma once

#include "Macros.h"
#include "Bar.h"
#include "SFML/Graphics.hpp"
#include <utility>
#include <vector>
#include "board.h"

class Controller;
class Bear;

class GameScreen
{
public:
	GameScreen(Controller* ctrl);
	void game(const gameInfo& info);
	Screen gamePlay(gameInfo& info);

private:
	std::vector<std::vector<sf::Keyboard::Key>> m_keys;

	Screen playNormal();
	Screen playSurvival();

	void update(float deltaTime);
	Screen handleKeyboard();
	void draw();
	void drawSurvival() { ; }

	Controller* m_controller;
	std::vector<Bear> m_bears;
	Board m_board;
	Bar m_bar;
	
};
