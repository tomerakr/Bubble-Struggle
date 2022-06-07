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

	void setViews(sf::View& leftView, sf::View& rightView);
	void update(float deltaTime);
	Screen handleKeyboard();
	void drawNormal();

	void updateSurvival(float deltaTime);
	void drawSurvival();
	void updateBearSurvivalPosition();
	void updateBallSurvivalPosition();
	void draw(sf::RenderWindow& window, sf::View& view);
	std::pair<int, int> m_points; //left point, right point
	std::vector<Bear> m_dummyBears;
	Bear* m_mainBear;

	sf::RectangleShape m_background;
	Controller* m_controller;
	std::vector<Bear> m_bears;
	Board m_board;
	Bar m_bar;
	
};
