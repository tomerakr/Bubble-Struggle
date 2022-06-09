#include "Bear.h"
#include "Board.h"
#include "PcInput.h"
#include "OnlineInput.h"

constexpr int NUM_OF_BEARS_IN_ROW = 6;

Bear::Bear(const sf::Vector2f& pos, Board* board, const receiveInfo& readInput, int textureIndex)
	:MovingObject(pos, sf::Vector2f(0, 0), Objects::Bears),
	m_gun(textureIndex, board), m_board(board), m_lives(3), m_score(0), m_animation(sf::Vector2u(NUM_OF_BEARS_IN_ROW, 1/*num of bears*/), 0.09)
{
	m_animation.changeTexture(m_icon.getTexture(), 0);
	//texture index range: 0 - 3
	m_icon.setTextureRect(m_animation.getUvRect());
	//m_icon.setTextureRect(sf::IntRect((textureSize.x / static_cast<int>(bearTypes::MAX)) * textureIndex, 0, textureSize.x / static_cast<int>(bearTypes::MAX), textureSize.y));

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
}

void Bear::defineBear2d(const sf::Vector2f& pos)
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(pos.x + m_icon.getSize().x / 2, pos.y + m_icon.getSize().y / 2);
	m_box2DBear = m_board->getWorld()->CreateBody(&bodyDef);

	b2PolygonShape bearRectangle;
	bearRectangle.SetAsBox(m_icon.getSize().x / 2, m_icon.getSize().y / 2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &bearRectangle;
	fixtureDef.filter.groupIndex = BEAR_FILTER;

	m_box2DBear->CreateFixture(&fixtureDef);
}

std::pair<const sf::Vector2f&, bool> Bear::update(float deltaTime, std::pair<sf::Vector2f, bool> otherBear)
{
	const auto& [direction, shoot] = m_getInput->getInput(gameInput{ m_keys, otherBear });
	move(deltaTime, direction);
	m_animation.update(deltaTime, direction.x == LEFT, direction.x == 0 && direction.y == 0);
	m_icon.setTextureRect(m_animation.getUvRect());

	if (m_box2DBear->GetFixtureList()->GetFilterData().groupIndex == POPPED_BALL_FILTER)
	{
		if (!m_hasShield)
		{
	//			start level again
			m_board->reset();
			if (m_lives > 0)
			{
				--m_lives;
			}
		}
		else
		{
			m_hasShield = false;
		}

//			reset filter fixture
		resetFilter();
	}

	if (m_box2DBear->GetFixtureList()->GetFilterData().groupIndex == GIFT_FREEZE_FILTER)
	{
		m_freezeRope = true;

		resetFilter();
	}

	if (m_box2DBear->GetFixtureList()->GetFilterData().groupIndex == GIFT_DOUBLE_SHOT_FILTER)
	{
		m_gun.incMaxRopes();

		resetFilter();
	}

	if (m_box2DBear->GetFixtureList()->GetFilterData().groupIndex == GIFT_LIFE_FILTER)
	{
		if (m_lives + 1 <= m_Maxlives)
		{
			++m_lives;
		}

		resetFilter();
	}

	if (m_box2DBear->GetFixtureList()->GetFilterData().groupIndex == GIFT_SHIELD_FILTER)
	{
		m_hasShield = true;

		resetFilter();
	}

	if (shoot)
	{
		m_gun.shoot(m_icon.getPosition(), m_freezeRope);

		m_freezeRope = false;
	}

	auto pos = m_icon.getPosition();
	m_box2DBear->SetTransform(b2Vec2(pos.x + m_icon.getSize().x / 2, pos.y + m_icon.getSize().y / 2), 0);

	m_gun.update();


	return std::make_pair(direction, shoot);
}

void Bear::drawRopes(sf::RenderWindow& window)
{
	m_gun.drawRopes(window);
}

void Bear::jump()
{
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