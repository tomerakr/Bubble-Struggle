#include "Bear.h"
#include "Board.h"
#include "PcInput.h"
#include "OnlineInput.h"
#include <iostream>
#include "GameScreen.h"

constexpr int NUM_OF_BEARS_IN_ROW = 9;
constexpr int maxPoints = 80;
constexpr int minPoints = 30; 

Bear::Bear(const sf::Vector2f& pos, Board* board, const receiveInfo& readInput, int textureIndex)
	:MovingObject(pos, sf::Vector2f(bearWitdh, bearHeight), Objects::Bears),
	m_gun(textureIndex, board), m_board(board), m_lives(START_LIFE), m_score(0), m_animation(sf::Vector2u(NUM_OF_BEARS_IN_ROW, static_cast<int>(bearTypes::MAX)), 0.09)
{
	m_animation.changeTexture(m_icon.getTexture(), textureIndex);
	//texture index range: 0 - 3
	m_icon.setTextureRect(m_animation.getUvRect());

	switch (readInput)
	{
	case receiveInfo::Solo:
	case receiveInfo::SamePc:
		m_getInput = std::make_unique<PcInput>();
		break;

	case receiveInfo::Online:
		m_getInput = std::make_unique<OnlineInput>();
		break;

	default:
		break;
	}

	defineBear2d(pos);
	m_maxPoints.first = 0;
	m_maxPoints.second = windowWidth - bearWitdh;
}

void Bear::resetPowers()
{
	m_shield = false;
	m_freezeRope = false;
	m_gun.resetPowers();
}

void Bear::defineBear2d(const sf::Vector2f& pos)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x + m_icon.getSize().x / 2, pos.y + m_icon.getSize().y / 2);
	m_box2DBear = m_board->getWorld()->CreateBody(&bodyDef);
	b2PolygonShape bearRectangle;
	bearRectangle.SetAsBox(m_icon.getSize().x / 2, m_icon.getSize().y / 2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &bearRectangle;
	fixtureDef.density = 1;
	fixtureDef.filter.groupIndex = BEAR_FILTER;
	m_box2DBear->SetFixedRotation(true);
	m_box2DBear->CreateFixture(&fixtureDef);
}

std::pair<const sf::Vector2f&, bool> Bear::update(float deltaTime, const std::pair<const sf::Vector2f&, bool>& otherBear, 
													GameScreen* gameScreen)
{
	const auto& [direction, shoot] = m_getInput->getInput(gameInput{ m_keys, otherBear, m_host });
	if (m_board->isNormalMode() && (direction.x == RIGHT && m_icon.getPosition().x < m_maxPoints.second) ||
		(direction.x == LEFT && m_icon.getPosition().x > m_maxPoints.first))
	{
		m_icon.move(deltaTime * m_speedPerSecond * direction);
		m_animation.update(deltaTime, direction.x == LEFT, direction.x == 0);
		m_icon.setTextureRect(m_animation.getUvRect());
	}

	if (m_box2DBear->GetFixtureList()->GetFilterData().groupIndex == POPPED_BALL_FILTER)
	{
		if (!m_shield)
		{
			decLives();
		}
		else
		{
			m_shield = false;
		}
		m_board->resetLevel();
	}
	else if (m_box2DBear->GetFixtureList()->GetFilterData().groupIndex == FREEZE_FILTER)
	{
		m_gun.freeze();
	}
	else if (m_box2DBear->GetFixtureList()->GetFilterData().groupIndex == DOUBLE_SHOT_FILTER)
	{
		m_gun.incMaxRopes();
	}
	else if (m_box2DBear->GetFixtureList()->GetFilterData().groupIndex == LIFE_FILTER)
	{
		if (m_lives < MAX_LIFE)
		{
			++m_lives;
		}
	}
	else if (m_box2DBear->GetFixtureList()->GetFilterData().groupIndex == SHIELD_FILTER)
	{
		m_shield = true;
	}
	else if (m_box2DBear->GetFixtureList()->GetFilterData().groupIndex == TIME_FILTER)
	{
		gameScreen->addTime();
	}
	resetFilter();

	if (shoot)
	{
		m_gun.shoot(m_icon.getPosition());
	}

	auto pos = m_icon.getPosition();
	auto size = m_icon.getSize();
	m_box2DBear->SetTransform(b2Vec2(pos.x + size.x / 2, pos.y + size.y / 2), 0);
	if (m_gun.update())
	{
		m_score += rand() % maxPoints + minPoints;
	}

	return std::make_pair(direction, shoot);
}

void Bear::drawRopes(sf::RenderWindow& window)
{
	m_gun.drawRopes(window);
}

const sf::Vector2f& Bear::getPos() const
{
	return m_icon.getPosition();
}

void Bear::resetFilter()
{
	b2Filter bearFilter;
	bearFilter.groupIndex = BEAR_FILTER;
	m_box2DBear->GetFixtureList()->SetFilterData(bearFilter);
}

void Bear::setPos(const sf::Vector2f& pos)
{
	m_icon.setPosition(pos);
	auto size = m_icon.getSize();
	m_box2DBear->SetTransform(b2Vec2(pos.x + size.x / 2, pos.y + size.y / 2), 0);
}

void Bear::destroyBody()
{
	m_board->getWorld()->DestroyBody(m_box2DBear);
}