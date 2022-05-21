#include "GameScreen.h"
#include "Window.h"
#include "Bear.h"
#include "board.h"

GameScreen::GameScreen(Window* window, Bear* bear, Board* board)
	: m_window(window), m_bear(bear), m_board(board)
{}

Screen GameScreen::gamePlay()
{
	auto screen = Screen::game;
	sf::Clock clock;

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
			screen = handleKeyboard(deltaTime.asSeconds());
			break;

		default:
			break;
		}
	}
	m_bear->setDirection();
	update(deltaTime.asSeconds());

	return screen;
}

void GameScreen::update(float deltaTime)
{
	m_board->update();
	m_bear->update();
	m_bear->move(deltaTime);
}

Screen GameScreen::handleKeyboard(float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_bear->shoot(m_board);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		return Screen::menu;
	}
	return Screen::game;
}

void GameScreen::draw()
{
	m_window->clear();

	m_bear->draw(m_window->getWindow());
	m_bear->drawRopes(m_window->getWindow());
	m_board->draw(m_window->getWindow());

	m_window->display();
}