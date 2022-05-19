#include "Controller.h"

constexpr int ropeWitdh = 20;
constexpr int ropeHeight = 0;

Controller::Controller()
	: m_window(), m_rope(sf::Vector2f(0,0), sf::Vector2f(ropeWitdh, ropeHeight), Objects::Rope, sf::Color::Red),
		m_bear(&m_rope), m_menu(&m_window), m_game(&m_window, &m_bear, &m_board)
{
}

void Controller::play()
{
	auto screen = Screen::menu;
	while (m_window.isOpen())
	{
		switch (screen)
		{
			using enum Screen;
		case menu:
			/*screen = */m_menu.menu();

		case game:
			/*screen = */m_game.game();

		case levelCreator:


		default:
			break;
		}
	}
}