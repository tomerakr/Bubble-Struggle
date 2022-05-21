#include "Controller.h"

Controller::Controller()
	: m_window(), m_bear(), m_menu(&m_window), m_game(&m_window, &m_bear, &m_board)
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
			screen = m_menu.menu();
			break;
		case game:
			screen = m_game.gamePlay();
			break;
		case levelCreator:

			break;
		default:
			break;
		}
	}
}