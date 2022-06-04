#include "Board.h"
#include "Controller.h"

Board::Board()
	:m_currLevel(1)
{
	setWorld();
	setLevel();
}

void Board::setWorld()
{
	b2Vec2 gravity(0.0f, 10.0f);
	m_world = std::make_unique<b2World>(gravity);
	m_world->SetContactListener(new ContactListener());	// need to free
}

void Board::createNormal()
{
	m_baseTiles.clear();
	auto height = windowHieght - thickness - barHeight;
	m_baseTiles.push_back(Tile{this, sf::Vector2f(windowWidth, thickness), sf::Vector2f(0.f, height) });				//floor
	m_baseTiles.push_back(Tile{this, sf::Vector2f(windowWidth, thickness), sf::Vector2f(0.f, 0.f) });					//ceiling
	m_baseTiles.push_back(Tile{this, sf::Vector2f(thickness, height), sf::Vector2f(0.f, 0.f) });						//left wall
	m_baseTiles.push_back(Tile{this, sf::Vector2f(thickness, height), sf::Vector2f(windowWidth - thickness, 0.f) });	//right wall
}

void Board::createSurvival()
{
	m_baseTiles.clear();
	auto height = windowHieght - thickness - barHeight;
	m_baseTiles.push_back(Tile{ this, sf::Vector2f(windowWidth * 3, thickness), sf::Vector2f(0.f, height) });	//floors
	m_baseTiles.push_back(Tile{ this, sf::Vector2f(windowWidth * 3, thickness), sf::Vector2f(0.f, 0.f) });		//ceiling
}

void Board::setLevel()
{
	auto file = std::ifstream(Resources::instance().getLevelName(m_currLevel));

	if (!file.is_open())
	{
		exit(EXIT_FAILURE);
	}

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

	for (auto& gift : m_gifts)
	{
		gift.update();
	}

	std::erase_if(m_balls, [](auto& ball) { return ball.popped(); });
	//std::erase_if(m_gifts, [](auto& gift) { return gift.getIsDone(); });
}

void Board::reset()
{
	m_balls.clear();
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
	const auto pos2 = pos;
	m_balls.push_back(Ball( this, pos, b2Vec2(-20, -30), index ));
	m_balls.emplace_back(this, pos2, b2Vec2(20, -30), index);
}

void Board::addGift(const sf::Vector2f position, const Objects giftType)
{
	auto addGift = rand() % 2 == 0;

	auto _giftType = Objects::GiftShield;			// temp for testing

	if (true)
	{
		switch (_giftType)
		{
		case Objects::GiftFreeze:
		{
			m_gifts.emplace_back(Gift(position, this, GIFT_FREEZE_FILTER));
			break;
		}
		case Objects::GiftDoubleShot:
		{
			m_gifts.emplace_back(Gift(position, this, GIFT_DOUBLE_SHOT_FILTER));
			break;
		}
		case Objects::GiftLife:
		{
			m_gifts.emplace_back(Gift(position, this, GIFT_LIFE_FILTER));
			break;
		}
		case Objects::GiftShield:
		{
			m_gifts.emplace_back(Gift(position, this, GIFT_SHIELD_FILTER));
			break;
		}

		default:
			break;
		}
		
	}
}