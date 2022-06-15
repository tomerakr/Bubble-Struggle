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
#include "DebugDraw.h"

class Controller;
class GameScreen;

class Board
{
	friend class BallIterator;

public:
	Board(GameScreen* gameScreen);
	void draw(sf::RenderWindow& window);
	void addBalls(const sf::Vector2f& pos, const int index);
	void update();
	void clear();
	void createNormal();
	void createSurvival();
	b2World* getWorld()			{ return m_world.get(); }
	int getNumBalls() const		{ return m_balls.size(); }
	void pickLevel(int level)	{ m_currLevel = level; }
	void nextLevel();
	void reset();
	void resetLevel();
	int getLevelIndex() const	{ return m_currLevel; }
	//=======================================
	void SetDebugDraw(DebugDraw* d) { m_world->SetDebugDraw(d); }
	//=======================================
	void addGift(const sf::Vector2f& position);

	class BallIterator
	{
	public:
		BallIterator(std::vector<Ball>& balls) :m_balls(balls) {}
		void next()
		{
			if (!isEnd())
			{
				++ballIndex;
			}
		}
		bool isEnd() const
		{
			return ballIndex == m_balls.size();
		}
		Ball& value() const
		{
			return m_balls[ballIndex];
		}


	private:
		std::vector<Ball>& m_balls;
		int ballIndex = 0;
	};

	BallIterator getBalls() { return BallIterator(getBallsVector()); }

	void addBall(const sf::Vector2f& pos, const b2Vec2& force, int index);
	void addBall(Ball& ball, int distance);
	void setLevel();

private:
	void setWorld();
	std::vector<Gift> m_gifts;
	std::vector<Ball> m_balls;
	std::vector<Tile> m_tiles;
	std::vector<Tile> m_baseTiles;
	
	//world definition
	std::unique_ptr<b2World> m_world;

	bool m_normal = false;
	float m_timeStep = 1.f / 60.f;
	int32 m_velocityIteration = 10;
	int32 m_positionIteration = 2;
	int m_currLevel;

	GameScreen* m_gameScreen = nullptr;

	std::vector<Ball>& getBallsVector() { return m_balls; }

};

