#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Ball.h"

//class Tile;

class Board
{
public:
	Board();
	void draw(sf::RenderWindow& window);
	void addBalls(float radius, sf::Color color, sf::Vector2f pos);
	void reset();
	void createBoard();


private:
	std::vector<Ball> m_balls;
	//std::vector<Tile> m_tiles;
};