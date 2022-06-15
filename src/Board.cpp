#include "Board.h"
#include "Controller.h"
#include <filesystem>
#include <iostream>
#include <time.h>

Board::Board(GameScreen* gameScreen)
	:m_gameScreen(gameScreen)
{
	setWorld();
	srand(time(NULL));
}

void Board::setWorld()
{
	b2Vec2 gravity(0.0f, 10.0f);
	m_world = std::make_unique<b2World>(gravity);
	m_world->SetContactListener(new ContactListener());	// need to free
}

void Board::createNormal()
{
	m_normal = true;
	m_baseTiles.clear();
	auto height = windowHeight - thickness - barHeight;
	m_baseTiles.push_back(Tile{this, sf::Vector2f(windowWidth, thickness), sf::Vector2f(0.f, height) });				//floor
	m_baseTiles.push_back(Tile{this, sf::Vector2f(windowWidth, thickness), sf::Vector2f(0.f, 0.f) });					//ceiling
	m_baseTiles.push_back(Tile{this, sf::Vector2f(thickness, height), sf::Vector2f(0.f, 0.f) });						//left wall
	m_baseTiles.push_back(Tile{this, sf::Vector2f(thickness, height), sf::Vector2f(windowWidth - thickness, 0.f) });	//right wall
}

void Board::createSurvival()
{
	m_normal = false;
	m_baseTiles.clear();
	auto height = windowHeight - thickness - barHeight;
	m_baseTiles.push_back(Tile{ this, sf::Vector2f(SurvivalWidth * 3, thickness), sf::Vector2f(-SurvivalWidth, height) });	//floors
	m_baseTiles.push_back(Tile{ this, sf::Vector2f(SurvivalWidth * 3, thickness), sf::Vector2f(-SurvivalWidth, 0.f) });		//ceiling
}

void Board::setLevel()
{

	m_gameScreen->setTime(LEVEL_TIME);

	auto file = std::ifstream(Resources::instance().getLevelName(m_currLevel));

	// ---- BALLS ----
	auto ballsNum = 0, index = 0, direction = 0; // direction will get 1 or -1
	auto xPosB = 0.f, yPosB = 0.f;

	file >> ballsNum;
	m_balls.reserve(ballsNum);
	for (int i = 0; i < ballsNum; ++i)
	{
		file >> xPosB >> yPosB >> index >> direction;
		m_balls.emplace_back(this, sf::Vector2f(xPosB, yPosB), b2Vec2(direction * 20,  20), index);
	}

	// ---- TILES ----
	auto tilesNum = 0;
	auto xPosT = 0.f, yPosT = 0.f,
		 xSize = 0.f, ySize = 0.f;

	file >> tilesNum;
	for (int j = 0; j < tilesNum; ++j)
	{
		file >> xSize >> ySize >> xPosT >> yPosT;
		m_tiles.emplace_back(this, sf::Vector2f(xSize, ySize), sf::Vector2f(xPosT, yPosT));
	}
}

void Board::draw(sf::RenderWindow& window)
{
	for (auto& ball : m_balls)
	{
		ball.draw(window);
	}
	for (auto& tile : m_baseTiles)
	{
		tile.draw(window);
	}
	for (auto& tile : m_tiles)
	{
		tile.draw(window);
	}
	for (auto& gift : m_gifts)
	{
		gift.draw(window);
	}

	//------- BOX2D VIEWER -------
	//DebugDraw d(window);
	//uint32 flags = b2Draw::e_shapeBit;
	//d.SetFlags(flags);
	//m_world->SetDebugDraw(&d);
	//m_world->DebugDraw();
}

void Board::update()
{
	m_world->Step(m_timeStep, m_velocityIteration, m_positionIteration);

	for (auto& ball : m_balls)
	{
		ball.update();

		if (ball.popped())
		{
			ball.destroy();
			ball.split();
			break;
		}
	}

	for (auto& gift : m_gifts)
	{
		gift.update();
		if (gift.getIsDone())
		{
			gift.destroyBody();
		}
	}

	std::erase_if(m_balls, [](auto& ball) { return ball.popped() || ball.destroied(); });
	std::erase_if(m_gifts, [](auto& gift) { return gift.getIsDone(); });
}

void Board::clear()
{
	for (auto& tile : m_baseTiles)
	{
		tile.destroyBody();
	}
	m_baseTiles.clear();
	reset();
}

void Board::reset()
{
	for (auto& tile : m_tiles)
	{
		tile.destroyBody();
	}
	for (auto& ball : m_balls)
	{
		ball.destroy();
	}
	for (auto& gift : m_gifts)
	{
		gift.destroyBody();
	}

	m_gifts.clear();
	m_balls.clear();
	m_tiles.clear();
}

void Board::resetLevel()
{
	reset();
	try
	{
		if (m_normal)
		{
			setLevel();
		}
	}
	catch (std::filesystem::filesystem_error const& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	
}

void Board::addBalls(const sf::Vector2f& pos, const int index)
{
	const auto pos2 = pos;
	m_balls.push_back(Ball( this, pos, b2Vec2(-20, -30), index ));
	m_balls.emplace_back(this, pos2, b2Vec2(20, -30), index);
}

void Board::addGift(const sf::Vector2f& position)
{
	auto addGift = rand() % 1;//CHANCE_OF_GIFT; //chances to get gift is 1 to 14

	auto giftType = rand() % static_cast<int>(giftTypes::MAX);
	if (!addGift)
	{
		m_gifts.emplace_back(Gift(position, this, giftType));
	}
}

void Board::addBall(const sf::Vector2f& pos, const b2Vec2& force, int index)
{
	m_balls.emplace_back(this, pos, force, index);
}

void Board::addBall(Ball& ball, int distance)
{
	auto pos = ball.getPos();
	m_balls.emplace_back(this, sf::Vector2f(pos.x + distance - ball.getCurrDirection() * ball.getRaidus(), pos.y),
		ball.getForce(), ball.getIndex());
}

void Board::nextLevel()
{
	++m_currLevel;
	resetLevel();
	setLevel();
}