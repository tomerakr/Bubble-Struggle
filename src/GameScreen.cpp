#include "GameScreen.h"
#include "Window.h"
#include "Bear.h"
#include "board.h"

GameScreen::GameScreen(Window* window, Board* board)
	: m_window(window), m_board(board)
{}

void GameScreen::game(gameInfo& info)
{
	m_bears.clear();
	auto xPos = windowWitdh / (info._numOfPlayers + 1);
	auto yPos = windowHieght - barHeight - bearHieght - thickness;

	for (int i = 0; i < info._numOfPlayers; ++i)
	{
		m_bears.emplace_back(Bear{sf::Vector2f(xPos * (i + 1), yPos)});
	}
	
	switch (info._receive)
	{
	case receiveInfo::Solo:
		m_input = soloInput;
		break;

	case receiveInfo::SamePc:
		m_input = samePcInput;
		break;

	case receiveInfo::Online:
		m_input = onlineInput;
		break;

	default:
		break;
	}

	//switch (info._mode)
	//{
	//case gameMode::Normal:
	//	playNormal(info);
	//	break;
	//case gameMode::Survival:
	//	playSurvival(info);
	//	break;
	//default:
	//	break;
	//}
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
		const auto& [direction, shoot] = *m_input;
		bear.update(deltaTime, direction, shoot);
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

	//m_bear->drawRopes(m_window->getWindow());
	m_board->draw(m_window->getWindow());
	//m_bear->draw(m_window->getWindow());

	m_window->display();
}

std::pair<sf::Vector2f, bool> GameScreen::soloInput()
{
	auto direction = readDirection();
	auto shoot = readShoot();
	return std::make_pair(direction, shoot);
}

std::pair<sf::Vector2f, bool> GameScreen::samePcInput()
{
	return std::make_pair(sf::Vector2f(0.f, 0.f), true);
}

std::pair<sf::Vector2f, bool> GameScreen::onlineInput()
{
	return std::make_pair(sf::Vector2f(0.f, 0.f), true);
}

sf::Vector2f GameScreen::readDirection()
{
	auto direction = sf::Vector2f();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		direction = sf::Vector2f(-1, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
			 sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		direction = sf::Vector2f(1, 0);
	}
	else
	{
		direction = sf::Vector2f(0, 0);
	}

	return direction;
}

bool GameScreen::readShoot()
{
	auto shoot = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		shoot = true;
	}

	return shoot;
}
