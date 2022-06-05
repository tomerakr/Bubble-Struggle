#pragma once

#include "box2d/box2d.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <string>
#include "Ball.h"
#include "Tile.h"
#include "ContactListener.h"
#include "MovingObject.h"
#include "Gift.h"

class Controller;

class Board
{
public:
	Board();
	void draw(sf::RenderWindow& window);
	void addBalls(const sf::Vector2f& pos, const int index);
	void update();
	void reset();
	void createNormal();
	void createSurvival();
	b2World* getWorld() { return m_world.get(); }
	void addGift(const sf::Vector2f position);

	std::vector<Ball>* getBalls() { return &m_balls; } // add iterator ~~~~~~~~~~~!!!!!!!!!!!!!
	void addBall(Ball& ball, int distance)
	{
		auto pos = ball.getPos();
		m_balls.emplace_back(this, sf::Vector2f(pos.x + distance - ball.getDirection() * ball.getRaidus(), pos.y), 
				ball.getForce(), ball.getIndex());
	}

private:
	void setLevel();
	void setWorld();
	std::vector<Gift> m_gifts;

	std::vector<Ball> m_balls;
	std::vector<Tile> m_tiles;
	std::vector<Tile> m_baseTiles;
	
	//world definition
	std::unique_ptr<b2World> m_world;

	float m_timeStep = 1.f / 60.f;
	int32 m_velocityIteration = 6;
	int32 m_positionIteration = 2;
	int m_currLevel;

};