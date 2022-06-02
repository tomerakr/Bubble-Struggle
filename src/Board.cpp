#include "Board.h"
#include "Controller.h"

Board::Board()
	:m_currLevel(1)
{
	setWorld();
	createBoard();
	setLevel();
}

void Board::setWorld()
{
	b2Vec2 gravity(0.0f, 10.0f);
	m_world = std::make_unique<b2World>(gravity);
	m_world->SetContactListener(new ContactListener());	// need to free
}

void Board::createBoard()
{
	auto height = windowHieght - thickness - barHeight;
	m_baseTiles.push_back(Tile{this, sf::Vector2f(windowWitdh, thickness), sf::Vector2f(0.f, height) });				//floor
	m_baseTiles.push_back(Tile{this, sf::Vector2f(windowWitdh, thickness), sf::Vector2f(0.f, 0.f) });					//ceiling
	m_baseTiles.push_back(Tile{this, sf::Vector2f(thickness, height), sf::Vector2f(0.f, 0.f) });						//left wall
	m_baseTiles.push_back(Tile{this, sf::Vector2f(thickness, height), sf::Vector2f(windowWitdh - thickness, 0.f) });	//right wall
}

void Board::setLevel()
{
	auto file = std::ifstream(Resources::instance().getLevelName(m_currLevel) + ".txt");
	//namespace fs = std::filesystem;
	//std::filesystem::path p = "LevelsNames.txt";

	//std::cout << "Absolute path for " << p << " is "
	//	<< std::filesystem::absolute(p) << '\n';
	if (!file.is_open())
	{
		exit(EXIT_FAILURE);
	}

	// ---- BALLS ----
	auto ballsNum = 0, index = 0, direction = 0; // direction will get 1 or -1
	auto xPosB = 0.f, yPosB = 0.f;

	file >> ballsNum;
	for (int i = 0; i < ballsNum; ++i)
	{
		file >> xPosB >> yPosB >> index >> direction;
		m_balls.emplace_back(Ball{ this, sf::Vector2f(xPosB, yPosB), b2Vec2(direction * 20,  20), index });
	}

	// ---- TILES ----
	auto tilesNum = 0, group = 0;
	auto xPosT = 0.f, yPosT = 0.f,
		 xSize = 0.f, ySize = 0.f;

	file >> tilesNum;
	for (int j = 0; j < tilesNum; ++j)
	{
		file >> xSize >> ySize >> xPosT >> yPosT >> group;
		m_tiles.emplace_back(Tile{ this, sf::Vector2f(xSize, ySize), sf::Vector2f(xPosT, yPosT) });
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
}

void Board::update()
{
	m_world->Step(m_timeStep, m_velocityIteration, m_positionIteration);

	for (auto& ball : m_balls)
	{
		ball.update();

		if (ball.popped())
		{
			ball.split();
			break;
		}
	}
	std::erase_if(m_balls, [](auto& ball) { return ball.popped(); });
}

void Board::reset()
{
	for (auto& ball : m_balls)
	{
		ball.reset();
	}
	for (auto& tile : m_tiles)
	{
		tile.reset();
	}
	m_balls.clear();
	m_tiles.clear();

	setLevel();
}

void Board::addBalls(const sf::Vector2f& pos, const int index)
{
	m_balls.emplace_back(Ball{ this, pos, b2Vec2(-20, -30), index });
	m_balls.emplace_back(Ball{ this, pos, b2Vec2( 20, -30), index });
}
