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
	setText(m_levelText, textBarSize, sf::Vector2f(windowWidth / 2.f - 70, windowHeight - barHeight / 2.f));
	setText(m_scoreText, textBarSize - 7);
	setBackgroud();
}

void Bar::setText(sf::Text &text, unsigned size, const sf::Vector2f& pos)
{
	text.setCharacterSize(size);
	text.setFont(*Resources::instance().getFont());
	text.setFillColor(sf::Color::Black);
	text.setOrigin(size / 2.f, size / 2.f);
	text.setPosition(pos);
}

void Bar::setBackgroud()
{
	m_background.setTexture(Resources::instance().getObjectTexture(Objects::BarBackground));
	m_background.setSize(sf::Vector2f(windowWidth, barHeight));
	m_background.setPosition(sf::Vector2f(0, windowHeight - barHeight));
	m_objectsBackground.setTexture(Resources::instance().getObjectTexture(Objects::TextBackground));
}

void Bar::setBar(float time, const gameInfo& info)
{
	if (info._mode == gameMode::Survival)
	{
		m_levelText.setString("Survival");
	}
	else
	{
		m_levelText.setString("level: " + std::to_string(m_level));
		m_timer = Timer{ time };
	}
	m_numOfBears = info._numOfPlayers;
	
	for (int i = 0 ; i < m_numOfBears; ++i)
	{
		m_lifeIcons.emplace_back();
		setBearInfo(info, Objects::BearsHeads, m_lifeIcons[i], sf::Vector2f(45.f, 40.f), i);

		m_ropes.emplace_back();
		setBearInfo(info, Objects::Ropes, m_ropes[i], sf::Vector2f(15.f, 50.f), i);
	}
}

void Bar::setBearInfo(const gameInfo& info, const Objects& texture, sf::RectangleShape &element, const sf::Vector2f& size, int index)
{
	element.setSize(size);
	element.setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
	element.setTexture(Resources::instance().getObjectTexture(texture));
	auto textureSize = element.getTexture()->getSize();
	element.setTextureRect(sf::IntRect((textureSize.x / static_cast<int>(bearTypes::MAX)) * (info._skinIndex + index),
		0, textureSize.x / static_cast<int>(bearTypes::MAX), textureSize.y));
}

void Bar::update(const std::vector<int> scores)
{
	for (int i = 0; i < scores.size(); ++i)
	{
		std::ostringstream ss;
		ss << std::setw(5) << std::setfill('0') << std::to_string(scores[i]);
		std::string s = ss.str();
		m_scoreText.setString(s);
	}
	m_timer.update();
}

bool Bar::timeEnded() const
{
	return m_timer.timeEnd();
}

void Bar::draw(sf::RenderWindow& window, const std::vector<int> &bearsLives)
{
	window.draw(m_background);
	m_timer.draw(window);
	window.draw(m_levelText);

	//time white strip
	drawBackgroundText(window, sf::Vector2f(10, windowHeight - barHeight + 15), sf::Vector2f(windowWidth - 20, 18));

	for (int j = 0; j < m_numOfBears; ++j)
	{
		//drawBackgroundText(window, sf::Vector2f((j * (windowWidth - (40 + 15) * 4 + 5)) + pow(-1, j) * 25,
		//	windowHeight - barHeight / 2 + 10), sf::Vector2f((40 + 15) * 4, 55)); // bears 

		for (int i = 0; i < bearsLives[j]; ++i)
		{
			m_lifeIcons[j].setPosition(
				sf::Vector2f((((j + 1) % m_numOfBears) * windowWidth) + pow(-1, (j + 1) % m_numOfBears) * (50 + i * 55), windowHeight - barHeight / 2 + 10));
			window.draw(m_lifeIcons[j]);
		}

		m_ropes[j].setPosition(
			sf::Vector2f((((j + 1) % m_numOfBears) * windowWidth) + pow(-1, (j + 1) % m_numOfBears) * (420), windowHeight - barHeight / 2 + 10));
		window.draw(m_ropes[j]);

		m_scoreText.setPosition(
			sf::Vector2f((((j + 1) % m_numOfBears) * (windowWidth - 80)) + pow(-1, (j + 1) % m_numOfBears) * 270, windowHeight - barHeight / 2.f + 10));
		window.draw(m_scoreText);
	}
}

void Bar::drawBackgroundText(sf::RenderWindow& window, const sf::Vector2f& pos, const sf::Vector2f& size)
{
	m_objectsBackground.setSize(size);
	m_objectsBackground.setOrigin(0, size.y / 2);
	m_objectsBackground.setPosition(pos);
	window.draw(m_objectsBackground);
}
