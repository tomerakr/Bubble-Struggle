#pragma once

#include "box2d/box2d.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <string>
#include "Ball.h"
#include "Tile.h"
#include "ContactListener.h"

class Controller;

class Board
{
public:
	Board();
	void draw(sf::RenderWindow& window);
	void addBalls(const sf::Vector2f pos, const int index);
	void update();
	void reset();
	void createBoard();
	void setLevel(int level);
	b2World* getWorld() { return m_world.get(); }
	std::vector<Ball>* getBalls() { return &m_balls; } // no good we need iterator

	class ballIterator : public std::iterator<std::input_iterator_tag, int>
	{
		ballIterator();
	};

private:
	void setWorld();
	std::vector<Ball> m_balls;
	std::vector<Tile> m_tiles;
	std::vector<Tile> m_baseTiles;
	
	//word definition
	std::unique_ptr<b2World> m_world;

	float m_timeStep = 1.f / 60.f;
	int32 m_velocityIteration = 6;
	int32 m_positionIteration = 2;
	int m_currLevel;
	std::ifstream m_file;
};