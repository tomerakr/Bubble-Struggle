#include "Bear.h"
#include "Board.h"
#include "PcInput.h"
#include "OnlineInput.h"

Bear::Bear(sf::Vector2f pos, Board* board, receiveInfo readInput, int textureIndex)
	:MovingObject(pos, sf::Vector2f(bearWitdh, bearHieght), Resources::instance().getSkin(textureIndex)._bear), 
		m_gun(textureIndex, board), m_board(board)
{
	m_icon.setFillColor(sf::Color::White);
	m_icon.setTexture(Resources::instance().getObjectTexture(Resources::instance().getSkin(textureIndex)._bear));

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
	m_box2DBear = m_board->getWorld()->CreateBody(&bodyDef);
	b2PolygonShape bearRectangle;
	bearRectangle.SetAsBox(m_icon.getSize().x + 10, m_icon.getSize().y - 130);
	
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &bearRectangle;
	fixtureDef.filter.groupIndex = BEAR_FILTER;

	m_box2DBear->CreateFixture(&fixtureDef);
}

void Bear::update(float deltaTime)
{
	const auto& [direction, shoot] = m_getInput->getInput(m_keys);
	move(deltaTime, direction);

	if (shoot)
	{
		m_gun.shoot(m_icon.getPosition());
	}

	m_box2DBear->SetTransform(b2Vec2(m_icon.getPosition().x + 30, m_icon.getPosition().y), 0);

	m_gun.update();

	if (m_box2DBear->GetFixtureList()->GetFilterData().groupIndex == POPPED_BALL_FILTER)
	{
//			start level again
		m_board->setLevel(1);

//			reset filter fixture
		b2Filter bearFilter;
		bearFilter.groupIndex = BEAR_FILTER;
		m_box2DBear->GetFixtureList()->SetFilterData(bearFilter);
	}
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
