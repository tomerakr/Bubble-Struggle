#include "Bar.h"
#include "Resources.h"

Bar::Bar()
	:m_level(1)
{
	m_levelText.setCharacterSize(textBarSize);
	m_levelText.setFont(*Resources::instance().getFont());
	m_levelText.setFillColor(sf::Color::Black);
	m_levelText.setPosition(sf::Vector2f(windowWidth / 2.f, windowHieght - barHeight / 2.f));
	m_levelText.setOrigin(textBarSize / 2.f, textBarSize / 2.f);

	m_scoreText.setCharacterSize(textBarSize);
	m_scoreText.setFont(*Resources::instance().getFont());
	m_scoreText.setFillColor(sf::Color::Black);
	m_scoreText.setPosition(sf::Vector2f(250, windowHieght - barHeight / 2.f));
	m_scoreText.setOrigin(textBarSize / 2.f, textBarSize / 2.f);

	m_background.setTexture(Resources::instance().getBackgroundTexture(Backgrounds::Bar));
	m_background.setSize(sf::Vector2f(windowWitdh, barHeight));
	m_background.setPosition(sf::Vector2f(0, windowHieght - barHeight));

	m_textBackground.setTexture(Resources::instance().getBackgroundTexture(Backgrounds::Text));
}

void Bar::setBar(float time, const gameInfo& info)
{
	m_timer = Timer{ time };
	m_levelText.setString("level: " + std::to_string(m_level));

	for (int i = 0; i < info._numOfPlayers; ++i)
	{
		m_lifeIcons[i].setSize(sf::Vector2f(50.f, 50.f));
		m_lifeIcons[i].setOrigin(sf::Vector2f(25.f, 25.f));
	}

	//m_lifeIcon.setTexture(Resources::instance().getObjectTexture(Resources::instance().getSkin(info._skinIndex)._bear));
}

void Bar::update(Bear &bear)
{
	m_timer.update();
	m_scoreText.setString(std::to_string(bear.getScore()));
}

void Bar::draw(sf::RenderWindow& window, Bear& bear)
{
	window.draw(m_background);
	//drawBackgroundText(window);
	m_timer.draw(window);
	window.draw(m_levelText);
	window.draw(m_scoreText);

	for (int i = 0; i < bear.getNumOfLives(); ++i)
	{
	//	m_lifeIcon.setPosition(sf::Vector2f(20 + i * 65 ,windowHieght - barHeight / 2));
		//window.draw(m_lifeIcon);
	}
}







//
//void Bar::drawBackgroundText()
//{
//	m_textBackground.setSize(sf::Vector2f(230, 60));
//	m_textBackground.setPosition(10, windowHieght - barHeight / 2);
//	window.draw(m_textBackground);
//}
