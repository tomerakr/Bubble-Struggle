#include "LevelCreator.h"
#include "Window.h"
#include "Resources.h"
#include "Tile.h"
#include "Ball.h"
#include "Button.h"

LevelCreator::LevelCreator()
{
	m_floorSize = sf::Vector2f(200, thickness);
	m_wallSize = sf::Vector2f(thickness, 200);
	m_ballIndex = 8;

	createBaseTiles();
	createBar();
}

void LevelCreator::createBaseTiles()
{
	auto height = windowHieght - thickness - barHeight;
	m_baseTiles.push_back(Tile{ sf::Vector2f(windowWitdh, thickness), sf::Vector2f(0.f, height) });				//floor
	m_baseTiles.push_back(Tile{ sf::Vector2f(windowWitdh, thickness), sf::Vector2f(0.f, 0.f) });				//ceiling
	m_baseTiles.push_back(Tile{ sf::Vector2f(thickness, height), sf::Vector2f(0.f, 0.f) });						//left wall
	m_baseTiles.push_back(Tile{ sf::Vector2f(thickness, height), sf::Vector2f(windowWitdh - thickness, 0.f) });	//right wall
}

void LevelCreator::createBar()
{
	m_bar.setFillColor(sf::Color(217, 239, 255));
	m_bar.setSize(sf::Vector2f(windowWitdh, barHeight));
	m_bar.setPosition(sf::Vector2f(0.f, windowHieght - barHeight));

	auto height = windowHieght - barHeight / 2;

	m_buttons.emplace_back(Button{sf::Vector2f(800, height), sf::Vector2f(60, 60), Objects::UndoButton });
	m_buttons.emplace_back(Button{sf::Vector2f(900, height), sf::Vector2f(60, 60), Objects::EraseButton });
	m_buttons.emplace_back(Button{sf::Vector2f(1000, height), sf::Vector2f(60, 60), Objects::ClearButton });
	m_buttons.emplace_back(Button{sf::Vector2f(1100, height), sf::Vector2f(60, 60), Objects::SaveButton });
	m_buttons.emplace_back(Button{sf::Vector2f(440, height), sf::Vector2f(60, 60), Objects::Ball});
	m_buttons.emplace_back(Button{sf::Vector2f(50, height), sf::Vector2f(20, 70), Objects::Wall });
	m_buttons.emplace_back(Button{sf::Vector2f(240, height), sf::Vector2f(100, 20), Objects::Floor });
}

Screen LevelCreator::createLevel(Window* window)
{
	auto screen = Screen::levelCreator;
	if (sf::Event event; window->getWindow().pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window->close();
			break;

		case sf::Event::MouseButtonReleased:
			handleMouse(window->getWindow().mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }));
			break;

		case sf::Event::KeyPressed:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				screen = Screen::menu;
			}
			break;
		default:
			break;
		}
	}
	draw(window);

	return screen;
}

void LevelCreator::clear()
{
	m_balls.clear();
	m_tiles.clear();
}

void LevelCreator::erase(const sf::Vector2f& mousePos)
{
	for (auto& ball : m_balls)
	{
		if (ball.first.contains(mousePos))
		{
			ball.second = true;
		}
	}
	for (auto& tile : m_tiles)
	{
		if (tile.first.contains(mousePos))
		{
			tile.second = true;
		}
	}
	std::erase_if(m_balls, [](auto& ball) { return ball.second; });
	std::erase_if(m_tiles, [](auto& tile) { return tile.second; });
}

void LevelCreator::undo()
{
	if (m_lastAction.empty())
	{
		return;
	}
	switch (m_lastAction.front())
	{
	case lastAction::BALL:
		if (m_balls.size() > 0)
		{
			m_balls.erase(--m_balls.end(), m_balls.end());
			m_lastAction.pop();
		}
		break;

	case lastAction::TILE:
		if (m_tiles.size() > 0)
		{
			m_tiles.erase(--m_tiles.end(), m_tiles.end());
			m_lastAction.pop();
		}
		break;

	default:
		break;
	}
}

void LevelCreator::save()
{
}

void LevelCreator::handleMouse(const sf::Vector2f& mousePos)
{
	if (m_buttons[static_cast<int>(buttonNames::UNDO)].isPressed(mousePos))
	{
		undo();
	}
	else if (m_buttons[static_cast<int>(buttonNames::ERASE)].isPressed(mousePos))
	{
		m_action = buttonNames::ERASE;
	}
	else if (m_buttons[static_cast<int>(buttonNames::CLEAR)].isPressed(mousePos))
	{
		clear();
	}
	else if (m_buttons[static_cast<int>(buttonNames::SAVE)].isPressed(mousePos))
	{
		save();
	}
	else if (m_buttons[static_cast<int>(buttonNames::BALL)].isPressed(mousePos))
	{
		m_action = buttonNames::BALL;
	}
	else if (m_buttons[static_cast<int>(buttonNames::TILE)].isPressed(mousePos))
	{
		m_action = buttonNames::TILE;
	}

	if (inBoard(mousePos))
	{
		switch (m_action)
		{
		case buttonNames::BALL:
			m_balls.push_back(std::make_pair(Ball{ sf::Vector2f(mousePos.x, mousePos.y), m_ballIndex }, false));
			m_lastAction.push(lastAction::BALL);
			break;

		case buttonNames::TILE:
			m_tiles.push_back(std::make_pair(Tile{ m_floorSize, sf::Vector2f(mousePos.x, mousePos.y) }, false));
			m_lastAction.push(lastAction::TILE);
			break;

		case buttonNames::ERASE:
			erase(mousePos);
			break;

		default:
			break;
		}
	}
}

bool LevelCreator::inBoard(const sf::Vector2f& mousePos)
{
	return ((mousePos.x > thickness) && (mousePos.x < windowWitdh - thickness) &&
		(mousePos.y > thickness) && (mousePos.y < windowHieght - barHeight - thickness));
}

void LevelCreator::draw(Window* window)
{
	window->clear();
	window->getWindow().draw(m_bar);

	for (auto& tile : m_baseTiles)
	{
		tile.draw(window->getWindow());
	}

	for (auto& ball : m_balls)
	{
		ball.first.draw(window->getWindow());
	}

	for (auto& tile : m_tiles)
	{
		tile.first.draw(window->getWindow());
	}

	for (auto& button : m_buttons)
	{
		button.draw(window->getWindow());
	}

	window->display();
}
