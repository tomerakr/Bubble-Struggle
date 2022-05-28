#pragma once

#include "Macros.h"
#include <vector>
#include "SFML/Graphics.hpp"
#include <queue>

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
	void undo();
	void erase(const sf::Vector2f& mousePos);
	void clear();
	void save();

	bool inBoard(const sf::Vector2f& mousePos);
	void handleMouse(const sf::Vector2f& mousePos);
	void createBaseTiles();
	void createBar();
	void draw(Window* window);

	enum class lastAction
	{
		BALL,
		TILE,
		ERASE,
	};

	enum class buttonNames
	{
		UNDO,
		ERASE,
		CLEAR,
		SAVE,
		BALL,
		TILE,
	};

	std::queue<lastAction> m_lastAction;
	buttonNames m_action;

	std::vector<Tile> m_baseTiles;
	std::vector<std::pair<Tile, bool>> m_tiles;		//tile, should delete
	std::vector<std::pair<Ball, bool>> m_balls;		//ball, should delete
	std::vector<Button> m_buttons;
	sf::RectangleShape m_bar;
	bool m_delete = false;

	sf::Vector2f m_floorSize;
	sf::Vector2f m_wallSize;
	int m_ballIndex;
};