#include "LevelCreator.h"
#include "Resources.h"
#include "Tile.h"
#include "Ball.h"
#include "Button.h"
#include "Controller.h"
#include <filesystem>
#include <iostream>

constexpr int STRAIGHTy = 10;
constexpr int STRAIGHTx = 5;

LevelCreator::LevelCreator()
{
	m_background.setSize(sf::Vector2f(windowWidth, windowHeight - barHeight - thickness));
	m_background.setFillColor(m_backgroundColor);

	createBaseTiles();
	createBar();
}

void LevelCreator::createBaseTiles()
{
	auto height = windowHeight - thickness - barHeight;
	m_baseTiles.push_back(Tile{ sf::Vector2f(windowWidth, thickness), sf::Vector2f(0.f, height) });				//floor
	m_baseTiles.push_back(Tile{ sf::Vector2f(windowWidth, thickness), sf::Vector2f(0.f, 0.f) });				//ceiling
	m_baseTiles.push_back(Tile{ sf::Vector2f(thickness, height), sf::Vector2f(0.f, 0.f) });						//left wall
	m_baseTiles.push_back(Tile{ sf::Vector2f(thickness, height), sf::Vector2f(windowWidth - thickness, 0.f) });	//right wall
}

void LevelCreator::createBar()
{
	m_bar.setFillColor(sf::Color(217, 239, 255));
	m_bar.setSize(sf::Vector2f(windowWidth, barHeight));
	m_bar.setPosition(sf::Vector2f(0.f, windowHeight - barHeight));

	auto height = windowHeight - barHeight / 2;

	setText(sf::Vector2f(320, height - 25), 22, std::to_string(m_ballIndex), m_ballIndexText);

	m_buttons.emplace_back(Button{sf::Vector2f(950, height), sf::Vector2f(60, 60), Objects::EraseButton });
	m_buttons.emplace_back(Button{sf::Vector2f(1050,height), sf::Vector2f(60, 60), Objects::ClearButton });
	m_buttons.emplace_back(Button{sf::Vector2f(1150,height), sf::Vector2f(60, 60), Objects::SaveButton });
	m_buttons.emplace_back(Button{sf::Vector2f(250, height), sf::Vector2f(60, 60), Objects::Ball });
	m_buttons.back().setColor(Resources::instance().getColor(m_ballIndex));
	m_buttons.emplace_back(Button{sf::Vector2f(50,	height), sf::Vector2f(20, 70), Objects::Wall });
	m_buttons.emplace_back(Button{sf::Vector2f(310, height + 20), sf::Vector2f(30, 30), Objects::Arrow }); //ball dec size
	m_buttons.emplace_back(Button{sf::Vector2f(350, height + 20), sf::Vector2f(30, 30), Objects::Arrow }); //ball inc size
	m_buttons.back().flip();
	m_buttons.emplace_back(Button{sf::Vector2f(120, height), sf::Vector2f(30, 30), Objects::Arrow }); //tile rotation
	m_buttons.back().flip();
	m_buttons.emplace_back(Button{sf::Vector2f(250, height), sf::Vector2f(30, 30), Objects::Arrow }); //ball direction
	m_buttons.back().flip();
	m_buttons.back().setColor(m_semiTransparent);
}

void LevelCreator::setText(const sf::Vector2f& pos, int size, const std::string& text, sf::Text& mText)
{
	mText.setString(text);
	mText.setCharacterSize(size);
	mText.setOrigin(mText.getLocalBounds().width / 2, mText.getLocalBounds().height / 2);
	mText.setPosition(pos);
	mText.setFont(*Resources::instance().getFont());
	mText.setOutlineColor(sf::Color::Black);
	mText.setOutlineThickness(2);
}

Screen LevelCreator::createLevel(Controller* ctrl)
{
	auto& window = ctrl->getWindow();
	auto screen = Screen::levelCreator;
	if (sf::Event event; window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;

		case sf::Event::MouseButtonReleased:
			handleMouse(window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }));
			break;

		case sf::Event::MouseMoved:
			update(window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y }));

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
	draw(ctrl);

	return screen;
}

void LevelCreator::update(const sf::Vector2f& mousePos)
{
	m_followShape.setPosition(mousePos);
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
			break;
		}
	}
	for (auto& tile : m_tiles)
	{
		if (tile.first.contains(mousePos))
		{
			tile.second = true;
			break;
		}
	}
	std::erase_if(m_balls, [](auto& ball) { return ball.second; });
	std::erase_if(m_tiles, [](auto& tile) { return tile.second; });
}

void LevelCreator::save() const
{
	const auto& levelName = "Level " + std::to_string(getLastLevel()) + ".txt";
	auto file = std::ofstream(levelName);

	if (!file.is_open())
	{
		exit(EXIT_FAILURE);
	}
	file << m_balls.size() << '\n';
	for (auto& ball : m_balls)
	{
		auto pos = ball.first.getPos();
		file << pos.x << ' ' << pos.y << ' ' << ball.first.getIndex() << ' ' << ball.first.getDirection() << '\n';
	}

	file << m_tiles.size() << '\n';
	for (auto& tile : m_tiles)
	{
		auto pos = tile.first.getPos();
		auto size = tile.first.getSize();
		file << size.x << ' ' << size.y << ' ' << pos.x << ' ' << pos.y << '\n';
	}
	file.close();
	
	addToProperties(levelName);
}

int LevelCreator::getLastLevel() const
{
	auto lastLevl = 0;
	auto res = std::filesystem::path("../../../resources");
	if (std::filesystem::exists(res))
	{
		auto levelNames = std::ifstream(res / "LevelsNames.txt");
		if (!levelNames.is_open())
		{
			exit(EXIT_FAILURE);
		}
		levelNames.seekg(-1, std::ios_base::end);
		for (int i = levelNames.tellg(); i > 0; --i, levelNames.seekg(i, std::ios_base::beg))
		{
			if (levelNames.peek() == ' ')
			{
				levelNames.get();
				break;
			}
		}
		levelNames >> lastLevl;
	}
	return lastLevl + 1;
}

void LevelCreator::addToProperties(const std::string& level) const //copy deletes content of file and saves it empty
{
	auto dest = std::filesystem::path("../../../resources");
	if (std::filesystem::exists(dest))
	{
		std::filesystem::copy(level, dest);
		auto cmake = std::ofstream(dest / "CMakeLists.txt", std::ios::app);
		cmake << "configure_file (\"" + level + "\" ${CMAKE_BINARY_DIR} COPYONLY)" << '\n';
		auto levelsNames = std::ofstream(dest / "LevelsNames.txt", std::ios::app);
		levelsNames << level << '\n';
	}
}

void LevelCreator::handleMouse(const sf::Vector2f& mousePos)
{
	if (m_buttons[static_cast<int>(buttonNames::ERASE)].isPressed(mousePos))
	{
		unfollow();
		m_action = buttonNames::ERASE;
	}
	else if (m_buttons[static_cast<int>(buttonNames::CLEAR)].isPressed(mousePos))
	{
		unfollow();
		clear();
	}
	else if (m_buttons[static_cast<int>(buttonNames::SAVE)].isPressed(mousePos))
	{
		unfollow();
		try
		{
			save();
		}
		catch (std::filesystem::filesystem_error const& ex) 
		{
			std::cout << ex.what() << std::endl;
		}
	}
	else if (m_buttons[static_cast<int>(buttonNames::DIR)].isPressed(mousePos))
	{
		m_ballDirecetion *= -1;
		m_buttons[static_cast<int>(buttonNames::DIR)].flip();
	}
	else if (m_buttons[static_cast<int>(buttonNames::BALL)].isPressed(mousePos))
	{
		m_action = buttonNames::BALL;
		followBall();
	}
	else if (m_buttons[static_cast<int>(buttonNames::TILE)].isPressed(mousePos))
	{
		m_action = buttonNames::TILE;
		followMouse(m_wallSize, sf::Color(255, 255, 255, 150), Objects::Wall);
	}
	else if (m_buttons[static_cast<int>(buttonNames::INC)].isPressed(mousePos))
	{
		m_ballIndex = ++m_ballIndex % numOfBalls;
		m_buttons[static_cast<int>(buttonNames::BALL)].setColor(Resources::instance().getColor(m_ballIndex));
		updateText(std::to_string(m_ballIndex), m_ballIndexText);

		if (m_action == buttonNames::BALL)
		{
			followBall();
		}
	}
	else if (m_buttons[static_cast<int>(buttonNames::DEC)].isPressed(mousePos))
	{
		m_ballIndex = --m_ballIndex;
		m_ballIndex = (-1 == m_ballIndex ? numOfBalls - 1 : m_ballIndex);
		updateText(std::to_string(m_ballIndex), m_ballIndexText);
		m_buttons[static_cast<int>(buttonNames::BALL)].setColor(Resources::instance().getColor(m_ballIndex));	

		if (m_action == buttonNames::BALL)
		{
			followBall();
		}
	}
	else if (m_buttons[static_cast<int>(buttonNames::ROT)].isPressed(mousePos))
	{
		m_tileSize = (m_tileSize == m_floorSize ? m_wallSize : m_floorSize);
		m_buttons[static_cast<int>(buttonNames::TILE)].tilt();
		m_followShape.setRotation(m_followShape.getRotation() == 90 ? 0 : 90);
		m_followShape.scale(1, -1);

		if (m_action == buttonNames::TILE)
		{
			followMouse(m_wallSize, m_semiTransparent, Objects::Wall);
		}
	}
	
	else if (!inBoard(mousePos))
	{
		unfollow();
		m_action = buttonNames::NONE;
	}

	placeInBoard(mousePos);
}

void LevelCreator::placeInBoard(const sf::Vector2f& mousePos)
{
	if (!inBoard(mousePos))
	{
		return;
	}

	switch (m_action)
	{
	case buttonNames::BALL:
	{
		auto pos = sf::Vector2f(setPos(mousePos.x, STRAIGHTx), setPos(mousePos.y, STRAIGHTy));
		m_balls.push_back(std::make_pair(Ball{ pos, m_ballIndex, m_ballDirecetion }, false));
		m_lastAction.push_back(lastAction::BALL);
		break;
	}

	case buttonNames::TILE:
		m_tiles.push_back(std::make_pair(Tile{ m_tileSize, sf::Vector2f(setPos(mousePos.x, STRAIGHTx),
															setPos(mousePos.y, STRAIGHTy)) }, false));
		m_lastAction.push_back(lastAction::TILE);
		break;

	case buttonNames::ERASE:
		erase(mousePos);
		break;

	default:
		break;
	}
}

void LevelCreator::followBall()
{
	auto size = (defRadius - 10 * m_ballIndex) * 2;
	auto color = Resources::instance().getColor(m_ballIndex);
	color = sf::Color(color.r, color.g, color.b, 100);
	followMouse(sf::Vector2f(size, size), color, Objects::Ball, true);
}

void LevelCreator::followMouse(const sf::Vector2f& size, const sf::Color& color, const Objects texture, bool setOrigin)
{
	m_followShape.setSize(size);
	m_followShape.setOrigin((setOrigin ? sf::Vector2f(size.x / 2, size.y / 2) : sf::Vector2f(0, 0)));
	m_followShape.setFillColor(color);
	m_followShape.setTexture(Resources::instance().getObjectTexture(texture), true);
}

void LevelCreator::unfollow()
{
	m_followShape.setSize(sf::Vector2f(0, 0));
}

float LevelCreator::setPos(int yVal, int straight) const
{
	auto lastDigit = yVal % straight;
	return (lastDigit > (straight / 2) ? ((yVal / straight) + 1) * straight : (yVal / straight) * straight);
}

bool LevelCreator::inBoard(const sf::Vector2f& mousePos) const
{
	return ((mousePos.x > thickness) && (mousePos.x < windowWidth - thickness) &&
		(mousePos.y > thickness) && (mousePos.y < windowHeight - barHeight - thickness));
}

void LevelCreator::draw(Controller* ctrl)
{
	auto& window = ctrl->getWindow();
	window.clear();
	window.draw(m_background);
	window.draw(m_followShape);
	window.draw(m_bar);
	window.draw(m_ballIndexText);

	for (auto& tile : m_baseTiles)
	{
		tile.draw(window);
	}

	for (auto& ball : m_balls)
	{
		ball.first.draw(window);
	}

	for (auto& tile : m_tiles)
	{
		tile.first.draw(window);
	}

	for (auto& button : m_buttons)
	{
		button.draw(window);
	}

	window.display();
}
