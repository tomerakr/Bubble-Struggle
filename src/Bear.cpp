#include "Bear.h"
#include "Board.h"
#include "PcInput.h"
#include "OnlineInput.h"

Bear::Bear(sf::Vector2f pos, Board* board, receiveInfo readInput, int textureIndex)
	:MovingObject(pos, sf::Vector2f(bearWitdh, bearHieght), Resources::instance().getSkin(textureIndex)._bear), 
		m_gun(textureIndex, board), m_board(board)
{
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

std::pair<sf::Vector2f, bool> Bear::update(float deltaTime, std::pair<sf::Vector2f, bool> otherBear)
{
	const auto& [direction, shoot] = m_getInput->getInput(gameInput{ m_keys, otherBear });
	move(deltaTime, direction);

	if (shoot)
	{
		m_gun.shoot(m_icon.getPosition());
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

const sf::Vector2f Bear::getPos() const
{
	return m_icon.getPosition();
}
