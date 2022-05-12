#include "Controller.h"

Controller::Controller()
	: m_window()
{

}

void Controller::run()
{
	while (m_window.isOpen())
	{
		draw();

		if (sf::Event event; m_window.getWindow().pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.getWindow().close();
				break;

			default:
				break;
			}
		}
	}
}

void Controller::draw()
{
	m_window.clear();
	m_window.display();
}