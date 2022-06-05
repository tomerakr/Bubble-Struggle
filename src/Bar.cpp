#include "Bar.h"
#include "Resources.h"
#include "cmath"

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

}

void Bar::setBar(float time, const gameInfo& info)
{


	m_timer = Timer{ time };
	m_levelText.setString("level:" + std::to_string(m_level));
	m_numOfBears = info._numOfPlayers;
	//texture index range: 0 - 3

	for (int i = 0; i < m_numOfBears; ++i)
	{
		m_lifeIcons.emplace_back();
		m_lifeIcons[i].setSize(sf::Vector2f(50.f, 50.f));
		m_lifeIcons[i].setOrigin(sf::Vector2f(25.f, 25.f));
		m_lifeIcons[i].setTexture(Resources::instance().getObjectTexture(Objects::BearsHeads));
		auto textureSize = m_lifeIcons[i].getTexture()->getSize();
		m_lifeIcons[i].setTextureRect(sf::IntRect((textureSize.x / static_cast<int>(bearTypes::MAX)) * (info._skinIndex + i), 0, textureSize.x / static_cast<int>(bearTypes::MAX), textureSize.y));

	}
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

	for(int j = 0 ; j < m_numOfBears ; ++j)
	{ 
		for (int i = 0; i < bear.getNumOfLives(); ++i)
		{
			m_lifeIcons[((j+1) % m_numOfBears)].setPosition(sf::Vector2f((j * windowWidth) + pow(-1,j) * (50 + i * 65), windowHeight - barHeight / 2 + 10));
			window.draw(m_lifeIcons[((j + 1) % m_numOfBears)]);
		}
	}
}


//
//void Bar::drawBackgroundText()
//{
//	m_textBackground.setSize(sf::Vector2f(230, 60));
//	m_textBackground.setPosition(10, windowHieght - barHeight / 2);
//	window.draw(m_textBackground);
//}
