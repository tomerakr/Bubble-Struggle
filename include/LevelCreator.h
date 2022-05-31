#pragma once

#include "Macros.h"
#include <vector>
#include "SFML/Graphics.hpp"
#include <fstream>
#include <deque>

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

	void setText(sf::Vector2f pos, int size, std::string text, sf::Text& mText);
	void updateText(std::string text, sf::Text& mText) { mText.setString(text); }
	void update(sf::Vector2f mousePos);
	void follow(sf::Vector2f size, sf::Color color, Objects texture, bool setOrigin = false);
	void unfollow();
	float setXpos(int xVal);
	float setYpos(int yVal);
	bool inBoard(const sf::Vector2f& mousePos);
	void handleMouse(const sf::Vector2f& mousePos);
	void createBaseTiles();
	void createBar();
	int getLastLevel();
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
		INC,
		DEC,
		ROT,
	};

	std::deque<lastAction> m_lastAction;
	buttonNames m_action;
	sf::Text m_title;
	sf::Text m_ballIndexText;

	std::vector<Tile> m_baseTiles;
	std::vector<std::pair<Tile, bool>> m_tiles;		//tile, should delete
	std::vector<std::pair<Ball, bool>> m_balls;		//ball, should delete
	std::vector<Button> m_buttons;
	sf::RectangleShape m_bar;
	sf::RectangleShape m_background;
	sf::RectangleShape m_followShape;
	bool m_delete = false;

	sf::Vector2f m_floorSize;
	sf::Vector2f m_wallSize;
	sf::Vector2f m_tileSize;
	int m_ballIndex;
};