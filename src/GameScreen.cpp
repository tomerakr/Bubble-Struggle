#include "GameScreen.h"
#include "Window.h"
#include "Bear.h"
#include "board.h"

GameScreen::GameScreen(Window* window, Bear* bear, Board* board)
	: m_window(window), m_bear(bear), m_board(board)
{}

void GameScreen::game()
{
	sf::Clock clock;
	while (m_window->isOpen())
	{
		draw();
		const auto deltaTime = clock.restart();

		if (sf::Event event; m_window->getWindow().pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window->close();
				break;

			case sf::Event::KeyPressed:
				handleKeyboard(deltaTime.asSeconds());
				break;

			default:
				break;
			}
		}
		update(deltaTime.asSeconds());
	}
}

void GameScreen::update(float deltaTime)
{
	m_board->update();
	m_bear->move(deltaTime);
}

void GameScreen::handleKeyboard(float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_bear->shoot(m_board);
	}

	m_bear->setDirection();
}

void GameScreen::draw()
{
	m_window->clear();

	m_bear->draw(m_window->getWindow());
	m_board->draw(m_window->getWindow());

	m_window->display();
}