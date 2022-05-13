#pragma once

#include "box2d/box2d.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Ball.h"

//class Tile;

class Board
{
public:
	Board();
	void setWorld();
	void draw(sf::RenderWindow& window);
	void addBalls(float radius, sf::Color color, sf::Vector2f pos);
	void reset();
	void createBoard();


private:
	std::vector<Ball> m_balls;
	//std::vector<Tile> m_tiles;
	
	std::unique_ptr<b2World, std::default_delete<b2World>> m_world;
	b2BodyDef m_groundBodyDef;

};