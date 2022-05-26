#include "Timer.h"
#include "Resources.h"
#include <utility>
#include <SFML/Graphics.hpp>

Timer::Timer(float time)
	:m_levelTime(time)
{
	m_timeText.setFont(*Resources::instance().getFont());
	m_timeText.setCharacterSize(30);
	m_timeText.setPosition(100, 140);
}

void Timer::update()
{
	m_levelTime -= m_clock.getElapsedTime().asSeconds();
}

std::pair<int, int> Timer::timeToInt()
{
	int leftMinutes = ((int)m_levelTime) / 60;
	int leftSeconds = ((int)m_levelTime) % 60;



	return std::make_pair(leftMinutes, leftSeconds);
}

const int Timer::getTimeLeft()
{
	return m_levelTime;
}

