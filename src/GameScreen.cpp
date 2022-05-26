#include "GameScreen.h"
#include "Window.h"
#include "Bear.h"
#include "board.h"

GameScreen::GameScreen(Window* window, Board* board)
	: m_window(window), m_board(board)
{
	auto keys = std::vector<sf::Keyboard::Key>();
	keys.push_back(sf::Keyboard::A);
	keys.push_back(sf::Keyboard::D);
	keys.push_back(sf::Keyboard::LControl);
	m_keys.push_back(keys);

	keys.clear();
	keys.push_back(sf::Keyboard::Left);
	keys.push_back(sf::Keyboard::Right);
	keys.push_back(sf::Keyboard::Space);
	m_keys.push_back(keys);

	m_objects.push_back(Objects::Bear);
	m_objects.push_back(Objects::Panda);
}

void GameScreen::game(gameInfo& info)
{
	m_bears.clear();
	auto xPos = windowWitdh / (info._numOfPlayers + 1);
	auto yPos = windowHieght - barHeight - bearHieght - thickness;

	for (int i = 0; i < info._numOfPlayers; ++i)
	{
		m_bears.emplace_back(Bear{sf::Vector2f(xPos * (i + 1), yPos), m_board, info._receive, m_objects[i % info._numOfPlayers]});
		m_bears.back().setKeys(&m_keys[(info._numOfPlayers - i) % m_keys.size()]);
	}
}

void GameScreen::playNormal(gameInfo& info)
{

}

void GameScreen::playSurvival(gameInfo& info)
{

}

Screen GameScreen::gamePlay(gameInfo& info)
{
	if (info._newGame)
	{
		game(info);
		info._newGame = false;
	}
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
	update(deltaTime.asSeconds());

	return screen;
}

void GameScreen::update(float deltaTime)
{
	m_board->update();
	for (auto& bear : m_bears)
	{
		bear.update(deltaTime);
	}
}

Screen GameScreen::handleKeyboard(float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		return Screen::menu;
	}
	return Screen::game;
}

void GameScreen::draw()
{
	m_window->clear();

	for (auto& bear : m_bears)
	{
		bear.drawRopes(m_window->getWindow());
		bear.draw(m_window->getWindow());
	}
	m_board->draw(m_window->getWindow());

	m_window->display();
}