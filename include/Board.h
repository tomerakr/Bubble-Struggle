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
	void draw(sf::RenderWindow& window);
	void addBalls(float radius, sf::Color color, sf::Vector2f pos);
	void update();
	void reset();
	void createBoard();
	b2World* getWorld() { return m_world.get(); }

private:
	void setWorld();
	std::vector<Ball> m_balls;
	//std::vector<Tile> m_tiles;
	
	//word definition
	std::unique_ptr<b2World, std::default_delete<b2World>> m_world;
	b2BodyDef m_groundBodyDef;
	b2Body* m_groundBody;

	float m_timeStep = 1.f / 60.f;
	int32 m_velocityIteration = 6;
	int32 m_positionIteration = 2;
};