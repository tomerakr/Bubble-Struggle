#include "Controller.h"

Controller::Controller()
	: m_window(), m_bear(), m_menu(&m_window), m_game(&m_window, &m_bear, &m_board)
{
}

void Controller::play()
{
	auto info = gameInfo{};
	info._screen = Screen::menu;
	while (m_window.isOpen())
	{
		switch (info._screen)
		{
			using enum Screen;
		case menu:
			info = m_menu.menu();
			break;
		case game:
			info._screen= m_game.gamePlay();
			break;
		case levelCreator:

			break;
		default:
			break;
		}
	}
}