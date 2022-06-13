#include "MenuScreen.h"
#include "Controller.h"

constexpr int maxButtonInMenu = 6;

MenuScreen::MenuScreen(Controller* ctrl, int numOfLevels)
	:m_controller(ctrl)
{
	createLevels(numOfLevels);
	createButton();
	m_background.setSize(sf::Vector2f(windowWidth, windowHeight));
	m_background.setTexture(Resources::instance().getObjectTexture(Objects::Backgrounds));
	auto textureSize = m_background.getTexture()->getSize();
	//texture index range: 0 - 3
	m_background.setTextureRect(sf::IntRect(0, 0, textureSize.x / static_cast<int>(bearTypes::MAX), textureSize.y));
	m_info._skinIndex = 0;
	m_info._host = false;
}

void MenuScreen::createButton()
{
	auto ySize = (windowHeight * (2.f / 3)) / (maxButtonInMenu + 1);
	auto xSize = 300;
	auto xPos = windowWidth / 2.f;
	auto yPos = windowHeight * (4.f / 13);

	for (int i = 0; i < m_buttonNames.size(); ++i)
	{
		auto line = std::vector<Button>();
		for (int j = 0; j < m_buttonNames[i].size(); ++j)
		{
			line.emplace_back(Button{ sf::Vector2f(xPos, yPos + (ySize + 10) * j), sf::Vector2f(xSize, ySize), Objects::Button, m_buttonNames[i][j] });
		}
		m_buttons.push_back(line);
	}
}

//============ O R D E R  FOR  M E N U ============
// Normal		->	chooseLevel	->	(Solo || Duo)	->	(Online -> Host || Connect) || Same PC
// Survival
// Create Level
// Help
// Settings		->	sound || music || size
// Exit

gameInfo MenuScreen::menu()
{
	m_info._screen = Screen::menu;
	auto& window = m_controller->getWindow();
	draw();
	if (sf::Event event; window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;

		case sf::Event::MouseButtonReleased:
			handlePress(window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }));
			break;

		case sf::Event::MouseMoved:
			handleHover(window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y }));
			break;

		case sf::Event::KeyPressed:
			handleKeyboard();
			break;

		default:
			break;
		}
	}
	return m_info;
}

gameInfo MenuScreen::handlePress(const sf::Vector2f& mousePos)
{
	m_info._screen = Screen::menu;
	switch (m_wantedMenu)
	{
		using enum menuNames;
	case static_cast<int>(mainMenu):
		mainMenuPress(mousePos);
		break;

	case static_cast<int>(levels):
		chooseLevel(mousePos);
		break;

	case static_cast<int>(numOfPlayers):
		numOfPlayersPress(mousePos);
		break;

	case static_cast<int>(connection):
		connectionPress(mousePos);
		break;
	default:
		break;
	}
	
	return m_info;
}

void MenuScreen::mainMenuPress(const sf::Vector2f& mousePos)
{
	auto clickSound = false;
	auto mainMenu = static_cast<int>(menuNames::mainMenu);
	if (m_buttons[mainMenu][int(buttonNames::Exit)].isPressed(mousePos) && m_wantedMenu == mainMenu)
	{
		m_controller->getWindow().close();
	}

	if (m_buttons[m_wantedMenu][static_cast<int>(buttonNames::Normal)].isPressed(mousePos))
	{
		m_info._mode = gameMode::Normal;
		m_wantedMenu = static_cast<int>(menuNames::levels);
		m_chooseLevel = true;
		clickSound = true;
	}
	else if(m_buttons[m_wantedMenu][static_cast<int>(buttonNames::Survival)].isPressed(mousePos))
	{
		m_info._mode = gameMode::Survival;
		m_info._numOfPlayers = 1;
		m_info._receive = receiveInfo::Solo;
		m_info._screen = Screen::game;
		clickSound = true;
	}
	else if (m_buttons[m_wantedMenu][static_cast<int>(buttonNames::CreateLevel)].isPressed(mousePos))
	{
		m_info._screen = Screen::levelCreator;
		clickSound = true;
	}
	else if (m_buttons[m_wantedMenu][static_cast<int>(buttonNames::Help)].isPressed(mousePos))
	{
		m_info._host = true;
	}
	if (clickSound)
	{
		Resources::instance().playSound(Sound::click);
	}
}

void MenuScreen::chooseLevel(const sf::Vector2f& mousePos)
{
	for (int i = 0; i < m_levels.size(); ++i)
	{
		if (m_levels[i].isPressed(mousePos))
		{
			m_info._level = i;
			m_chooseLevel = false;
			m_wantedMenu = static_cast<int>(menuNames::numOfPlayers);
			break;
		}
	}
}

void MenuScreen::numOfPlayersPress(const sf::Vector2f& mousePos)
{
	auto clickSound = false;
	if (m_buttons[m_wantedMenu][static_cast<int>(buttonNames::Solo)].isPressed(mousePos))
	{
		m_info._numOfPlayers = 1;
		m_info._receive = receiveInfo::Solo;
		m_info._screen = Screen::game;
		m_info._newGame = true;
		m_wantedMenu = static_cast<int>(menuNames::mainMenu);
		clickSound = true;
	}
	else if (m_buttons[m_wantedMenu][static_cast<int>(buttonNames::Duo)].isPressed(mousePos))
	{
		m_info._numOfPlayers = 2;
		m_info._newGame = true;
		m_wantedMenu = static_cast<int>(menuNames::connection);
		clickSound = true;
	}
	if (clickSound)
	{
		Resources::instance().playSound(Sound::click);
	}
}

void MenuScreen::connectionPress(const sf::Vector2f& mousePos)
{
	auto clickSound = false;
	if (m_buttons[m_wantedMenu][int(buttonNames::SamePC)].isPressed(mousePos))
	{
		m_info._receive = receiveInfo::SamePc;
		m_info._screen = Screen::game;
		m_info._newGame = true;
		m_wantedMenu = static_cast<int>(menuNames::mainMenu);
		clickSound = true;
	}
	else if (m_buttons[m_wantedMenu][int(buttonNames::Online)].isPressed(mousePos))
	{
		m_info._receive = receiveInfo::Online;
		m_info._screen = Screen::game;
		m_info._newGame = true;
		//m_wantedMenu = static_cast<int>(menuNames::connectionType);
		clickSound = true;
	}
	if (clickSound)
	{
		Resources::instance().playSound(Sound::click);
	}
}

void MenuScreen::handleHover(const sf::Vector2f& mousePos)
{
	m_buttons[m_wantedMenu][m_lastHovered].resetTilt(); //reset in last wanted menu and not in current
	for (int i = 0; i < m_buttons[m_wantedMenu].size(); ++i)
	{
		if (m_buttons[m_wantedMenu][i].hover(mousePos))
		{
			m_lastHovered = i;
			break;
		}
	}
}

void MenuScreen::handleKeyboard()
{
	auto right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		m_wantedMenu = static_cast<int>(menuNames::mainMenu);
	}
	else if (right || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_info._skinIndex = (m_info._skinIndex + (right ? 1 : -1)) % static_cast<int>(bearTypes::MAX);
		if (m_info._skinIndex == -1)
		{
			m_info._skinIndex = static_cast<int>(bearTypes::MAX) - 1;
		}

		auto textureSize = m_background.getTexture()->getSize();
		//texture index range: 0 - 3
		m_background.setTextureRect(sf::IntRect((textureSize.x / static_cast<int>(bearTypes::MAX)) * m_info._skinIndex, 0, textureSize.x / static_cast<int>(bearTypes::MAX), textureSize.y));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		m_wantedMenu = static_cast<int>(menuNames::mainMenu);
		m_chooseLevel = false;
	}
}

void MenuScreen::draw()
{
	auto& window = m_controller->getWindow();
	window.draw(m_background);

	if (m_chooseLevel)
	{
		for (auto& levelButton : m_levels)
		{
			levelButton.draw(window);
		}
	}
	else
	{
		for (auto& button : m_buttons[m_wantedMenu])
		{
			button.draw(window);
		}
	}
	
	window.display();
}

constexpr int NUM_OF_LEVELS_IN_ROW = 5;
constexpr int buttonLevelSize = 100;

void MenuScreen::createLevels(int numOfLevels)
{
	auto row = 0;
	auto col = 1;
	m_levels.reserve(numOfLevels);
	for (int i = 0; i < numOfLevels; ++i, ++col)
	{
		const auto& pos = sf::Vector2f((windowWidth / ((13 / 8.f) * NUM_OF_LEVELS_IN_ROW)) * col,
			windowHeight / 3 + row * (5 / 4.f) * buttonLevelSize);
		m_levels.emplace_back(pos, sf::Vector2f(buttonLevelSize, buttonLevelSize), Objects::Button, std::to_string(i + 1));
		if (i % NUM_OF_LEVELS_IN_ROW == 0 && i > 0)
		{
			++row;
			col = 0;
		}
	}
}