#include "Controller.h"

constexpr int ropeWitdh = 20;
constexpr int ropeHeight = 0;

Controller::Controller()
	: m_window(), m_rope(sf::Vector2f(0,0), sf::Vector2f(ropeWitdh, ropeHeight), Objects::Rope, sf::Color::Red),
		m_bear(&m_rope), m_menu(&m_window)
{}

void Controller::play()
{
	sf::Clock clock;
	m_menu.menu();
	//while (m_window.isOpen())
	//{
	//	draw();
	//	const auto deltaTime = clock.restart();
	//	m_board.update();
	//	m_rope.update();

	//	if (sf::Event event; m_window.getWindow().pollEvent(event))
	//	{
	//		switch (event.type)
	//		{
	//		case sf::Event::Closed:
	//			m_window.close();
	//			break;

	//		case sf::Event::KeyPressed:
	//			handleKeyboard(deltaTime.asSeconds());
	//			break;

	//		default:
	//			break;
	//		}
	//	}
	//}
}

void Controller::handleKeyboard(float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_bear.shoot(&m_board);
	}

	m_bear.setDirection();
	m_bear.move(deltaTime);
}

void Controller::draw()
{
	m_window.clear();

	m_bear.draw(m_window.getWindow());
	m_rope.draw(m_window.getWindow());
	m_board.draw(m_window.getWindow());

	m_window.display();
}