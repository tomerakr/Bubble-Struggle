#include "GameScreen.h"
#include "Window.h"
#include "Bear.h"
#include "board.h"

GameScreen::GameScreen(Window* window, Board* board)
	: m_window(window), m_board(board)
{
	auto keys = std::vector<sf::Keyboard::Key>();
	keys.push_back(sf::Keyboard::Left);
	keys.push_back(sf::Keyboard::Right);
	keys.push_back(sf::Keyboard::Space);
	m_keys.push_back(keys);

	keys.clear();
	keys.push_back(sf::Keyboard::A);
	keys.push_back(sf::Keyboard::D);
	keys.push_back(sf::Keyboard::LControl);
	m_keys.push_back(keys);
}

void GameScreen::game(gameInfo& info)
{
	m_bears.clear();
	auto xPos = windowWitdh / (info._numOfPlayers + 1);
	auto yPos = windowHieght - barHeight - bearHieght - thickness;
	auto textureIndex = info._skinIndex;
	for (int i = info._numOfPlayers; i > 0; --i)
	{
		m_bears.emplace_back(Bear{sf::Vector2f(xPos * i, yPos), m_board, info._receive, textureIndex });
		m_bears.back().setKeys(&m_keys[(info._numOfPlayers - i) % m_keys.size()]);
		textureIndex = --textureIndex % numOfSkins;
		textureIndex = (textureIndex == -1 ? numOfSkins - 1 : textureIndex);
	}
}

Screen GameScreen::playNormal()
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
		m_bar.setBar(15, info);  // need to change later 
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
}

Screen GameScreen::playSurvival()
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
	switch (info._mode)
	{
	case gameMode::Normal:
		screen = playNormal();
		break;

	case gameMode::Survival:
		screen = playSurvival();
		break;

	default:
		break;
	}

	return screen;
}

void GameScreen::update(float deltaTime, gameInfo& info)
{
	m_board->update();
	auto otherBear = std::make_pair(sf::Vector2f(), false);
	for (auto& bear : m_bears)
	{
		otherBear = bear.update(deltaTime, otherBear);
	}
	m_bar.update(m_bears[0]); // change to iterator
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
	m_bar.draw(m_window->getWindow(), m_bears[0]);  // change to iterator

	m_window->display();
}