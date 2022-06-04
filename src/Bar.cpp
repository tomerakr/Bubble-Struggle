#include "Bar.h"
#include "Resources.h"

Bar::Bar()
	:m_level(1)
{
	m_levelText.setCharacterSize(textBarSize);
	m_levelText.setFont(*Resources::instance().getFont());
	m_levelText.setFillColor(sf::Color::Black);
	m_levelText.setPosition(sf::Vector2f(windowWidth / 2.f, windowHeight - barHeight / 2.f));
	m_levelText.setOrigin(textBarSize / 2.f, textBarSize / 2.f);

	m_scoreText.setCharacterSize(textBarSize);
	m_scoreText.setFont(*Resources::instance().getFont());
	m_scoreText.setFillColor(sf::Color::Black);
	m_scoreText.setPosition(sf::Vector2f(250, windowHeight - barHeight / 2.f));
	m_scoreText.setOrigin(textBarSize / 2.f, textBarSize / 2.f);

	m_lifeIcon.setSize(sf::Vector2f(50.f, 50.f));
	m_lifeIcon.setTexture(Resources::instance().getObjectTexture(Objects::BearsHeads));
}

void Bar::setBar(float time, const gameInfo& info)
{
	m_timer = Timer{ time };
	m_levelText.setString("level:" + std::to_string(m_level));
	auto textureSize = m_lifeIcon.getTexture()->getSize();
	//texture index range: 0 - 3
	m_lifeIcon.setTextureRect(sf::IntRect((textureSize.x / static_cast<int>(bearTypes::MAX)) * info._skinIndex, 0, textureSize.x / static_cast<int>(bearTypes::MAX), textureSize.y));
}

void Bar::update(Bear &bear)
{
	m_timer.update();
	m_scoreText.setString(std::to_string(bear.getScore()));
}

void Bar::draw(sf::RenderWindow& window, Bear& bear)
{
	m_timer.draw(window);
	window.draw(m_levelText);
	window.draw(m_scoreText);

	for (int i = 0; i < bear.getNumOfLives(); ++i)
	{
		m_lifeIcon.setPosition(sf::Vector2f(20 + i * 65  ,windowHeight - barHeight + 30));
		window.draw(m_lifeIcon);
	}
}
