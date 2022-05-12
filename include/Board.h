#pragma once

#include <vector>

class Ball;
class Tile;

class Board
{
public:
	Board();
	void draw(sf::RenderWindow& window);
	void reset();
	void createBoard();


private:
	std::vector<std::unique_ptr<Ball>> m_balls;
	std::vector<std::unique_ptr<Tile>> m_tiles;
};