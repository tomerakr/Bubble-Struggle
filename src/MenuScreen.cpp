#include "MenuScreen.h"
#include "Window.h"

constexpr int maxButtonInMenu = 5; //change to function

MenuScreen::MenuScreen(Window* window)
	:m_window(window)
{
	createButton();
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

void MenuScreen::menu()
{
	while (m_window->isOpen())
	{
		draw();

		if (sf::Event event; m_window->getWindow().pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window->close();
				break;

			case sf::Event::MouseButtonReleased:
				handlePress(m_window->getWindow().mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }));
				break;

			case sf::Event::MouseMoved:
				handleHover(m_window->getWindow().mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y }));
				break;

			//we want this so can control menu using keyboard + mouse
			//case sf::Event::KeyPressed:
			//	handleKeyboard(deltaTime.asSeconds());
			//	break;

			default:
				break;
			}
		}
	}
}

void MenuScreen::handlePress(sf::Vector2f mousePos)
{
	if (m_buttons[0][int(buttonNames::Normal)].isPressed(mousePos) ||
		m_buttons[0][int(buttonNames::Survival)].isPressed(mousePos))
	{
		m_wantedMenu = 1;
	}
	else if (m_buttons[1][int(buttonNames::Duo)].isPressed(mousePos))
	{
		m_wantedMenu = 2;
	}
	else if (m_buttons[2][int(buttonNames::SamePC)].isPressed(mousePos))
	{
		m_wantedMenu = 0;
	}
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

void MenuScreen::draw()
{
	m_window->clear();
	for (auto& button : m_buttons[m_wantedMenu])
	{
		button.draw(m_window->getWindow());
	}
	m_window->display();
}
