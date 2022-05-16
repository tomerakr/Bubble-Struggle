#include "MenuScreen.h"
#include "WIndow.h"

MenuScreen::MenuScreen(Window* window)
	:m_window(window)
{
	createButton();
}

void MenuScreen::createButton()
{
	m_buttons.emplace_back(Button{ sf::Vector2f(), sf::Vector2f(), "Normal" });
	m_buttons.emplace_back(Button{ sf::Vector2f(), sf::Vector2f(), "Survival" });
	m_buttons.emplace_back(Button{ sf::Vector2f(), sf::Vector2f(), "Create Level" });
	//m_buttons.emplace_back(Button{ sf::Vector2f(), sf::Vector2f(), "Settings" }); //consider
	m_buttons.emplace_back(Button{ sf::Vector2f(), sf::Vector2f(), "Help" });
	m_buttons.emplace_back(Button{ sf::Vector2f(), sf::Vector2f(), "Exit" });

	m_buttons.emplace_back(Button{ sf::Vector2f(), sf::Vector2f(), "Solo" });
	m_buttons.emplace_back(Button{ sf::Vector2f(), sf::Vector2f(), "Duo" });
	m_buttons.emplace_back(Button{ sf::Vector2f(), sf::Vector2f(), "Online" });
	m_buttons.emplace_back(Button{ sf::Vector2f(), sf::Vector2f(), "Same PC" });
}
//============ O R D E R  FOR  M E N U ============
// Normal		->	Solo
// Survival		->	Duo		->	Online || Same PC
// Create Level
// Help
// Exit

void MenuScreen::Menu()
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
				break;

			case sf::Event::MouseMoved:
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

void MenuScreen::draw()
{
	// not good we don't want to show all buttons at all times
	for (auto& button : m_buttons)
	{
		button.draw(m_window->getWindow());
	}
}
