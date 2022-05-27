#include "Bear.h"
#include "Board.h"
#include "PcInput.h"
#include "OnlineInput.h"

Bear::Bear(sf::Vector2f pos, Board* board, receiveInfo readInput, int textureIndex)
	:MovingObject(pos, sf::Vector2f(bearWitdh, bearHieght), Resources::instance().getSkin(textureIndex)._bear), m_gun(textureIndex, board)
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
}

void Bear::update(float deltaTime)
{
	const auto& [direction, shoot] = m_getInput->getInput(m_keys);
	move(deltaTime, direction);
	if (shoot)
	{
		m_gun.shoot(m_icon.getPosition());
	}
	m_gun.update();
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
