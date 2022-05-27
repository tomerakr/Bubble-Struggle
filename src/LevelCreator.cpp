#include "LevelCreator.h"
#include "Window.h"
#include "Resources.h"
#include "Tile.h"
#include "Ball.h"
#include "Button.h"

LevelCreator::LevelCreator()
{
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
	m_buttons.emplace_back(Button{sf::Vector2f(800, windowHieght - barHeight / 2), sf::Vector2f(60, 60), Objects::UndoButton });
	m_buttons.emplace_back(Button{sf::Vector2f(900, windowHieght - barHeight / 2), sf::Vector2f(60, 60), Objects::EraseButton });
	m_buttons.emplace_back(Button{sf::Vector2f(1000, windowHieght - barHeight / 2), sf::Vector2f(60, 60), Objects::ClearButton });
	m_buttons.emplace_back(Button{sf::Vector2f(1100, windowHieght - barHeight / 2), sf::Vector2f(60, 60), Objects::SaveButton });
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
			handleMouse();
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
			return;
		}
	}
	for (auto& tile : m_tiles)
	{
		if (tile.first.contains(mousePos))
		{
			tile.second = true;
			return;
		}
	}
	std::erase_if(m_balls, [](auto& ball) { return ball.second; });
	std::erase_if(m_tiles, [](auto& tile) { return tile.second; });
}

void LevelCreator::undo()
{
	switch (m_lastAction)
	{
	case lastAction::BALL:
		if (m_balls.size() > 0)
		{
			m_balls.erase(--m_balls.end(), m_balls.end());
		}
		break;

	case lastAction::TILE:
		if (m_tiles.size() > 0)
		{
			m_tiles.erase(--m_tiles.end(), m_tiles.end());
		}

		break;

	default:
		break;
	}
}

void LevelCreator::save()
{
}

void LevelCreator::handleMouse()
{
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
