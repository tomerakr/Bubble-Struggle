#include "MenuScreen.h"
#include "Window.h"

constexpr int maxButtonInMenu = 5; //change to function

MenuScreen::MenuScreen(Window* window)
	:m_window(window)
{
	createButton();
	m_background.setSize(sf::Vector2f(windowWitdh, windowHieght));
	m_background.setTexture(Resources::instance().getBackgroundTexture(Backgrounds::Menu));
}

void MenuScreen::createButton()
{
	auto ySize = (windowHieght * (2.f / 3)) / (maxButtonInMenu + 1);
	auto xSize = 300;
	auto xPos = windowWitdh / 2.f;
	auto yPos = windowHieght * (2.f / 5);

	for (int i = 0; i < m_buttonNames.size(); ++i)
	{
		auto line = std::vector<Button>();
		for (int j = 0; j < m_buttonNames[i].size(); ++j)
		{
			line.emplace_back(Button{ sf::Vector2f(xPos, yPos + (ySize + 10) * j), sf::Vector2f(xSize, ySize), m_buttonNames[i][j]});
		}
		m_buttons.push_back(line);
	}
}

//============ O R D E R  FOR  M E N U ============
// Normal		->	Solo
// Survival		->	Duo		->	Online || Same PC
// Create Level
// Help
// Exit

Screen MenuScreen::menu()
{
	auto screen = Screen::menu;

	draw();
	if (sf::Event event; m_window->getWindow().pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_window->close();
			break;

		case sf::Event::MouseButtonReleased:
			screen = handlePress(m_window->getWindow().mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }));
			break;

		case sf::Event::MouseMoved:
			handleHover(m_window->getWindow().mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y }));
			break;

		case sf::Event::KeyPressed:
			handleKeyboard();
			break;

		default:
			break;
		}
	}
	return screen;
}

Screen MenuScreen::handlePress(sf::Vector2f mousePos)
{
	if (m_buttons[0][int(buttonNames::Exit)].isPressed(mousePos) && m_wantedMenu == 0)
	{
		m_window->close();
	}

	auto screen = Screen::menu;
	switch (m_wantedMenu)
	{
		using enum menuNames;
	case static_cast<int>(mainMenu):
		mainMenuPress(mousePos);
		break;

	case static_cast<int>(numOfPlayers):
		screen = numOfPlayersPress(mousePos);
		break;

	case static_cast<int>(connection):
		screen = connectionPress(mousePos);
		break;
	default:
		break;
	}
	
	return screen;
}

void MenuScreen::mainMenuPress(sf::Vector2f mousePos)
{
	if (m_buttons[m_wantedMenu][int(buttonNames::Normal)].isPressed(mousePos) ||
		m_buttons[m_wantedMenu][int(buttonNames::Survival)].isPressed(mousePos))
	{
		m_wantedMenu = static_cast<int>(menuNames::numOfPlayers);
	}
}

Screen MenuScreen::numOfPlayersPress(sf::Vector2f mousePos)
{
	if (m_buttons[m_wantedMenu][int(buttonNames::Solo)].isPressed(mousePos))
	{
		m_wantedMenu = static_cast<int>(menuNames::mainMenu);
		return Screen::game;
	}
	else if (m_buttons[m_wantedMenu][int(buttonNames::Duo)].isPressed(mousePos))
	{
		m_wantedMenu = static_cast<int>(menuNames::connection);
	}
	return Screen::menu;
}

Screen MenuScreen::connectionPress(sf::Vector2f mousePos)
{
	if (m_buttons[m_wantedMenu][int(buttonNames::SamePC)].isPressed(mousePos) ||
		m_buttons[m_wantedMenu][int(buttonNames::Online)].isPressed(mousePos))
	{
		m_wantedMenu = static_cast<int>(menuNames::mainMenu);
		return Screen::game;
	}

	return Screen::menu;
}

void MenuScreen::handleHover(sf::Vector2f mousePos)
{
	m_buttons[m_wantedMenu][m_lastHovered].resetColor();
	for (int i = 0; i < m_buttons[m_wantedMenu].size(); ++i)
	{
		if (m_buttons[m_wantedMenu][i].hover(mousePos))
		{
			m_lastHovered = i;
			break;
		}
	}
}

void MenuScreen::handleKeyboard()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		m_wantedMenu = 0;
	}
}

void MenuScreen::draw()
{
	m_window->getWindow().draw(m_background);

	for (auto& button : m_buttons[m_wantedMenu])
	{
		button.draw(m_window->getWindow());
	}
	m_window->display();
}
