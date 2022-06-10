#include "Bear.h"
#include "Board.h"
#include "PcInput.h"
#include "OnlineInput.h"

constexpr int NUM_OF_BEARS_IN_ROW = 6;

Bear::Bear(const sf::Vector2f& pos, Board* board, const receiveInfo& readInput, int textureIndex)
	:MovingObject(pos, sf::Vector2f(bearWitdh, bearHeight), Objects::Bears),
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
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x + m_icon.getSize().x / 2, pos.y + m_icon.getSize().y / 2);

	m_box2DBear = m_board->getWorld()->CreateBody(&bodyDef);
	b2PolygonShape bearRectangle;
	bearRectangle.SetAsBox(m_icon.getSize().x / 2, m_icon.getSize().y / 2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &bearRectangle;
	fixtureDef.density = 1;
	fixtureDef.filter.groupIndex = BEAR_FILTER;
	m_box2DBear->CreateFixture(&fixtureDef);
}

std::pair<const sf::Vector2f&, bool> Bear::update(float deltaTime, std::pair<sf::Vector2f, bool> otherBear)
{
	const auto& [direction, shoot] = m_getInput->getInput(gameInput{ m_keys, otherBear });
	m_box2DBear->SetTransform(m_box2DBear->GetTransform().p + b2Vec2(deltaTime * m_speedPerSecond * direction.x, 0), 0);
	m_animation.update(deltaTime, direction.x == LEFT, direction.x == 0);
	m_icon.setTextureRect(m_animation.getUvRect());
	if (direction.y != 0)
	{
		jump();
	}
	if (m_box2DBear->GetFixtureList()->GetFilterData().groupIndex == POPPED_BALL_FILTER)
	{
		if (!m_shield)
		{
			--m_lives;
			if (0 == m_lives)
			{
				m_lives = START_LIFE;
			}
			m_board->reset();
		}
		else
		{
			m_shield = false;
		}
	}
	else if (m_box2DBear->GetFixtureList()->GetFilterData().groupIndex == GIFT_FREEZE_FILTER)
	{
		m_gun.freeze();
	}
	else if (m_box2DBear->GetFixtureList()->GetFilterData().groupIndex == GIFT_DOUBLE_SHOT_FILTER)
	{
		m_gun.incMaxRopes();
	}
	else if (m_box2DBear->GetFixtureList()->GetFilterData().groupIndex == GIFT_LIFE_FILTER)
	{
		if (m_lives < MAX_LIFE)
		{
			++m_lives;
		}
	}
	else if (m_box2DBear->GetFixtureList()->GetFilterData().groupIndex == GIFT_SHIELD_FILTER)
	{
		m_shield = true;
	}
	resetFilter();

	if (shoot)
	{
		m_gun.shoot(m_icon.getPosition());
	}

	auto pos = m_box2DBear->GetTransform().p;
	m_icon.setPosition(sf::Vector2f(pos.x - m_icon.getSize().x / 2, pos.y - m_icon.getSize().y / 2));

	m_gun.update();

	return std::make_pair(direction, shoot);
}

void Bear::drawRopes(sf::RenderWindow& window)
{
	m_gun.drawRopes(window);
}

void Bear::jump()
{
	auto impulse = m_box2DBear->GetMass() * -1;
	m_box2DBear->ApplyLinearImpulse(b2Vec2(0, impulse), m_box2DBear->GetWorldCenter(), true);
	//m_touchGround = (m_box2DBear->GetLinearVelocity().y == 0 ? true : false);
	//if (m_touchGround)
	//{
	//}
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
	auto size = m_icon.getSize();
	m_box2DBear->SetTransform(b2Vec2(pos.x + size.x / 2, pos.y + size.y / 2), 0);
}

void Bear::destroyBody()
{
	m_board->getWorld()->DestroyBody(m_box2DBear);
}