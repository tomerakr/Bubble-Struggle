#include "Controller.h"

Controller::Controller()
	: m_window(), m_menu(&m_window), m_game(&m_window, &m_board)
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
			info._screen = m_game.gamePlay(info);
			break;
		case levelCreator:
			info._screen = m_levelCreator.createLevel(&m_window);
			break;
		default:
			break;
		}
	}
}