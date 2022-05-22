#include "GameScreen.h"
#include "Window.h"
#include "Bear.h"
#include "board.h"

GameScreen::GameScreen(Window* window, Bear* bear, Board* board)
	: m_window(window), m_bear(bear), m_board(board)
{}

void GameScreen::game(gameInfo& info)
{
	std::pair<sf::Vector2f, bool>(*getInput)() = nullptr;

	switch (info._receive)
	{
	case receiveInfo::Solo:
		getInput = &soloInput();
		break;

	case receiveInfo::SamePc:
		getInput = samePcInput;
		break;

	case receiveInfo::Online:
		getInput = onlineInput;
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
	//gample(test,etste)
}

void GameScreen::playNormal(gameInfo& info)
{

}

void GameScreen::playSurvival(gameInfo& info)
{

}

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
	update(deltaTime.asSeconds());

	return screen;
}

void GameScreen::update(float deltaTime)
{
	m_board->update();
	m_bear->update();
	//m_bear->move(deltaTime);
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

	m_bear->drawRopes(m_window->getWindow());
	m_board->draw(m_window->getWindow());
	m_bear->draw(m_window->getWindow());

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
