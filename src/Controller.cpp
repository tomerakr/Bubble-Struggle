#include "Controller.h"

Controller::Controller()
	: m_window(), m_bear()
{
}

void Controller::play()
{
	sf::Clock clock;
	while (m_window.isOpen())
	{
		draw();
		const auto deltaTime = clock.restart();
		m_board.update();

		if (sf::Event event; m_window.getWindow().pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.getWindow().close();
				break;

			case sf::Event::KeyPressed:
				handleKeyboard(deltaTime.asSeconds());
				break;

			default:
				break;
			}
		}
	}
}

void Controller::handleKeyboard(float deltaTime)
{
	m_bear.setDirection();
	m_bear.move(deltaTime);
}

void Controller::draw()
{
	m_window.clear();

	m_bear.draw(m_window.getWindow());
	m_board.draw(m_window.getWindow());

	m_window.display();
}