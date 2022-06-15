#include "Timer.h"
#include "Resources.h"
#include <utility>
#include <SFML/Graphics.hpp>

Timer::Timer(float time)
	:m_levelTime(time), m_timeLeft(time)
{
	m_timeline.setSize(sf::Vector2f(windowWidth -30, 10));
	m_timeline.setFillColor(sf::Color::Red);
	m_timeline.setPosition(sf::Vector2f(10,windowHeight - barHeight + 10));
}

void Timer::update()
{
	if (!timeEnd())
	{
		m_timeLeft -= m_clock.getElapsedTime().asSeconds();
		m_timeline.setSize(sf::Vector2f((windowWidth - 30) * (m_timeLeft / m_levelTime), 10));
		m_clock.restart();
	}
}

void Timer::addTime()
{
	m_timeLeft += rand() % BONUS_TIME + BONUS_TIME;
}

void Timer::setTime(const int seconds)
{
	m_timeLeft = seconds;
}

const int Timer::getTimeLeft()
{
	return m_levelTime;
}

bool Timer::timeEnd() const
{
	return m_timeLeft <= 0;
}

