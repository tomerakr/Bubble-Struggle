#include "Timer.h"
#include "Resources.h"
#include <utility>
#include <SFML/Graphics.hpp>

Timer::Timer(float time)
	:m_levelTime(time), m_timeLeft(time)
{
	m_timeline.setSize(sf::Vector2f(windowWitdh, 10));
	m_timeline.setFillColor(sf::Color::Red);
	m_timeline.setPosition(sf::Vector2f(0,windowHieght - barHeight + 10));
}

void Timer::update()
{
	m_timeLeft -= m_clock.getElapsedTime().asSeconds();
	m_timeline.setSize(sf::Vector2f(windowWitdh * (m_timeLeft / m_levelTime), 10));
	m_clock.restart();
}

const int Timer::getTimeLeft()
{
	return m_levelTime;
}

bool Timer::timeEnd()
{
	return m_timeLeft <= 0;
}

