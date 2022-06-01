#pragma once

constexpr int myPort = 6969;

#include "Macros.h"
#include "Bar.h"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include <utility>
#include <vector>
#include "board.h"

class Controller;
class Bear;

class GameScreen
{
	using getInput = std::pair<sf::Vector2f, bool>(*)(Bear* bear);

public:
	GameScreen(Controller* ctrl);
	void game(gameInfo& info);
	Screen gamePlay(gameInfo& info);

private:
	std::vector<std::vector<sf::Keyboard::Key>> m_keys;

	Screen playNormal();
	Screen playSurvival();

	void update(float deltaTime/*, gameInfo& info*/);
	Screen handleKeyboard(const float deltaTime);
	void draw();
	void drawSurvival() { ; }

	Controller* m_controller;
	std::vector<Bear> m_bears;
	Board m_board;
	Bar m_bar;
	
};
