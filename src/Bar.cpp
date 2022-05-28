#include "Bar.h"

Bar::Bar(float levelTime)
	:m_timer(levelTime)
{
	
}

void Bar::update()
{
	m_timer.update();
}

void Bar::draw(sf::RenderWindow window)
{
	m_timer.draw(window);

	for (int i = 0; i < m_lives; ++i)
	{

	}
}
