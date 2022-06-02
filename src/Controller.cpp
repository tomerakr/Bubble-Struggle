#include "Controller.h"
#include "Resources.h"

Controller::Controller()
	: m_menu(this), m_game(this),
	m_window(sf::VideoMode(windowWitdh, windowHieght), "Bubble Trouble", sf::Style::Close | sf::Style::Titlebar)
{
	m_window.setFramerateLimit(maxFPS);
	auto icon = sf::Image{};
	icon.loadFromFile("icon.png");
	m_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
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
			info._screen = m_levelCreator.createLevel(this);
			break;
		default:
			break;
		}
	}
}