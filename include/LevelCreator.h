#pragma once

#include "Macros.h"
#include "SFML/Graphics.hpp"

class Resources;
class Tile;
class Ball;
class Button;
class Window;

class LevelCreator
{
public:
	LevelCreator();
	Screen createLevel(Window* window);

private:
	void clear();
	void erase(const sf::Vector2f& mousePos);
	void undo();
	void save();

	void handleMouse();
	void createBaseTiles();
	void createBar();
	void draw(Window* window);

	enum class lastAction
	{
		BALL,
		TILE
	};

	lastAction m_lastAction;

	std::vector<Tile> m_baseTiles;
	std::vector<std::pair<Tile, bool>> m_tiles;		//tile, should delete
	std::vector<std::pair<Ball, bool>> m_balls;		//ball, should delete
	std::vector<Button> m_buttons;
	sf::RectangleShape m_bar;
};