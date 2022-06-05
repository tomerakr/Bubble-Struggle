#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>


#include "Bar.h"
#include "Resources.h"
#include "cmath"

Bar::Bar()
	:m_level(1)
{
	m_levelText.setCharacterSize(textBarSize);
	m_levelText.setFont(*Resources::instance().getFont());
	m_levelText.setFillColor(sf::Color::Black);
	m_levelText.setOrigin(textBarSize / 2.f, textBarSize / 2.f);
	m_levelText.setPosition(sf::Vector2f(windowWidth / 2.f - 70, windowHeight - barHeight / 2.f));

	m_scoreText.setCharacterSize(textBarSize - 7);
	m_scoreText.setFont(*Resources::instance().getFont());
	m_scoreText.setFillColor(sf::Color::Black);
	m_scoreText.setOrigin(textBarSize / 2.f, textBarSize / 2.f);

	m_background.setTexture(Resources::instance().getObjectTexture(Objects::BarBackground));
	m_background.setSize(sf::Vector2f(windowWidth, barHeight));
	m_background.setPosition(sf::Vector2f(0, windowHeight - barHeight));

	m_objectsBackground.setTexture(Resources::instance().getObjectTexture(Objects::TextBackground));

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
		m_lifeIcons[i].setSize(sf::Vector2f(45.f, 40.f));
		m_lifeIcons[i].setOrigin(sf::Vector2f(20.f, 20.f));
		m_lifeIcons[i].setTexture(Resources::instance().getObjectTexture(Objects::BearsHeads));
		auto textureSize = m_lifeIcons[i].getTexture()->getSize();
		m_lifeIcons[i].setTextureRect(sf::IntRect((textureSize.x / static_cast<int>(bearTypes::MAX)) * (info._skinIndex + i), 0, textureSize.x / static_cast<int>(bearTypes::MAX), textureSize.y));

	}
}

void Bar::update(Bear &bear)
{
	std::ostringstream ss;
	ss << std::setw(5) << std::setfill('0') << std::to_string(bear.getScore());
	std::string s = ss.str();
	m_scoreText.setString(s);

	m_timer.update();

}

void Bar::draw(sf::RenderWindow& window, Bear& bear)
{
	window.draw(m_background);
	m_timer.draw(window);
	window.draw(m_levelText);

	drawBackgroundText(window, sf::Vector2f(10, windowHeight - barHeight + 15), sf::Vector2f(windowWidth - 20, 18));
	//drawBackgroundText(window, m_levelText.getPosition(), sf::Vector2f(m_levelText.getCharacterSize(), 30));
	 

	for(int j = 0 ; j < m_numOfBears ; ++j)
	{ 
		drawBackgroundText(window, sf::Vector2f((j * (windowWidth - (40 + 15) * 4 + 5)) + pow(-1, j) * 25, windowHeight - barHeight / 2 + 10), sf::Vector2f((40 + 15) * 4, 55)); // bears 

		for (int i = 0; i < 4/*bear.getNumOfLives()*/; ++i)
		{
			m_lifeIcons[((j+1) % m_numOfBears)].setPosition(sf::Vector2f((j * windowWidth) + pow(-1,j) * (50 + i * 55), windowHeight - barHeight / 2 + 10));
			window.draw(m_lifeIcons[((j + 1) % m_numOfBears)]);
		}

		m_scoreText.setPosition(sf::Vector2f((j * (windowWidth - 80)) + pow(-1, j) * 270, windowHeight - barHeight / 2.f + 10));
		window.draw(m_scoreText);
	}
}

void Bar::drawBackgroundText(sf::RenderWindow& window, sf::Vector2f pos, sf::Vector2f size)
{
	m_objectsBackground.setSize(size);
	m_objectsBackground.setOrigin(0, size.y / 2);
	m_objectsBackground.setPosition(pos);
	window.draw(m_objectsBackground);
}
