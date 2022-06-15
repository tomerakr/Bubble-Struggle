#include "MenuScreen.h"
#include "Controller.h"
#include "SFML/Network.hpp"
#include "OnlineInput.h"

constexpr int maxButtonInMenu = 6;
constexpr int maxVolume = 6;
constexpr int screenSizes = 2;
constexpr int LARGE = 0;
constexpr int NORMAL = 1;

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

	m_help.setSize(sf::Vector2f(windowWidth, windowHeight));
	m_help.setTexture(Resources::instance().getObjectTexture(Objects::General));
	textureSize = m_help.getTexture()->getSize();
	//texture index range: 0 - 3
	m_help.setTextureRect(sf::IntRect(0, 0, textureSize.x / static_cast<int>(backgrounds::MAX), textureSize.y));

	//m_output.setColor(sf::Color(164, 164, 164));
	//m_output.setCharacterSize(30);
	//m_output.setFont(*Resources::instance().getFont());
	//m_output.setPosition(500, 500);
	//m_output.setString("Enter your IP:");
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

	m_textRectangle.setFillColor(sf::Color(255, 255, 255, 150));
	m_textRectangle.setSize(sf::Vector2f(300, 70));
	m_textRectangle.setPosition(windowWidth / 2 - m_textRectangle.getSize().x / 2, yPos + (ySize + 10) * 2);

	m_volumeRectangle.setFillColor(sf::Color::Blue);
	m_volumeRectangle.setSize(sf::Vector2f(10, 15));

	setText(m_screenSizeText, "CHOOSE YOUR SCREEN SIZE", 30, sf::Vector2f(windowWidth / 2 - 350, 300), sf::Color::Black);
	setText(m_volumeText, "SET THE VOLUME", 30, sf::Vector2f(windowWidth / 2 - 250, yPos + (ySize + 10) * 3), sf::Color::Black);
	setText(m_output, "Enter your IP:", 25, sf::Vector2f(windowWidth / 2, yPos + (ySize + 10) * 2.2), sf::Color(164, 164, 164));

	ySize = 50;
	xSize = 20;
	xPos = 450;
	yPos = windowHeight - 200;

	for (int i = 0 ; i < maxVolume; ++i)
	{
		m_volume.emplace_back(Button{sf::Vector2f(xPos + (i * xSize * 2), yPos), sf::Vector2f(xSize, ySize), Objects::Button, std::to_string(i)});
		m_volume.back().textSize(20);
	}

	ySize = 70;
	xSize = 150;
	xPos = 400;
	yPos = 400;
	for (int i = 0; i < screenSizes; ++i)
	{
		m_settingsButtons.emplace_back(Button{ sf::Vector2f(xPos + (i * xSize * 2), yPos), sf::Vector2f(xSize, ySize), Objects::Button, m_settingsButtonsText[i]});
		m_settingsButtons.back().textSize(23);
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
			if (m_connectPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
				{
					auto connectToHost = OnlineInput();
					connectToHost.connect(m_input);
				}
			}
			break;

		case sf::Event::TextEntered:
			if (m_connectPressed)
			{
				if (event.type == sf::Event::TextEntered)
				{
					if (event.text.unicode < 128)
					{
						m_input += static_cast<char>(event.text.unicode);
						m_output.setString(m_input);
					}
				}
			}
			break;

		default:
			break;
		}
	}
	return m_info;
}

gameInfo MenuScreen::handlePress(const sf::Vector2f& mousePos)
{
	if (m_showHelp)
	{
		m_showHelp = false;
		return m_info;
	}
	auto clickSound = false;
	m_info._screen = Screen::menu;
	switch (m_wantedMenu)
	{
		using enum menuNames;
	case static_cast<int>(mainMenu):
		mainMenuPress(mousePos, clickSound);
		break;

	case static_cast<int>(levels):
		chooseLevel(mousePos, clickSound);
		break;

	case static_cast<int>(numOfPlayers):
		numOfPlayersPress(mousePos, clickSound);
		break;

	case static_cast<int>(connection):
		connectionPress(mousePos, clickSound);
		break;

	case static_cast<int>(connectionType):
		connectType(mousePos, clickSound);
		break;

	case static_cast<int>(settings):
		settingsPress(mousePos, clickSound);
		break;


	default:
		break;
	}

	if (clickSound)
	{
		Resources::instance().playSound(Sound::click);
	}
	
	return m_info;
}

void MenuScreen::mainMenuPress(const sf::Vector2f& mousePos, bool& clickSound)
{
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
	else if (m_buttons[m_wantedMenu][static_cast<int>(buttonNames::Settings)].isPressed(mousePos))
	{
		m_wantedMenu = static_cast<int>(menuNames::settings);
		m_settingPressed = true;
		clickSound = true;
	}
	else if (m_buttons[m_wantedMenu][static_cast<int>(buttonNames::Help)].isPressed(mousePos))
	{
		m_showHelp = true;
	}
}

void MenuScreen::chooseLevel(const sf::Vector2f& mousePos, bool& clickSound)
{
	for (int i = 0; i < m_levels.size(); ++i)
	{
		if (m_levels[i].isPressed(mousePos))
		{
			m_info._level = i;
			m_chooseLevel = false;
			m_wantedMenu = static_cast<int>(menuNames::numOfPlayers);
			clickSound = true;
			break;
		}
	}
}

void MenuScreen::numOfPlayersPress(const sf::Vector2f& mousePos, bool& clickSound)
{
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
}

void MenuScreen::connectionPress(const sf::Vector2f& mousePos, bool& clickSound)
{
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
		//m_info._screen = Screen::game;
		//m_info._newGame = true;
		m_wantedMenu = static_cast<int>(menuNames::connectionType);
		m_onlineConnection = true;
		clickSound = true;
	}
	
}

void MenuScreen::connectType(const sf::Vector2f& mousePos, bool& clickSound)
{
	if (m_buttons[m_wantedMenu][int(buttonNames::Host)].isPressed(mousePos))
	{
		m_output.setString(sf::IpAddress::getLocalAddress().toString());
		draw();
		auto host = OnlineInput();
		Resources::instance().playSound(Sound::click);
		host.host();
		m_info._host = true;
	}
	else if (m_buttons[m_wantedMenu][int(buttonNames::Connect)].isPressed(mousePos))
	{
		m_connectPressed = true;
		clickSound = true;
	}
}

void MenuScreen::settingsPress(const sf::Vector2f& mousePos, bool& clickSound)
{
	// music volume choosing
	for (int i = 0; i < m_volume.size(); ++i)
	{
		if (m_volume[i].isPressed(mousePos))
		{
			Resources::instance().setVolume(i);
		}
	}
	
	auto& window = m_controller->getWindow();
	if (m_settingsButtons[LARGE].isPressed(mousePos))
	{
		;
	}
	else if (m_settingsButtons[NORMAL].isPressed(mousePos))
	{
		;
	}
}

void MenuScreen::handleHover(const sf::Vector2f& mousePos)
{
	m_buttons[m_lastWantedMenu][m_lastHovered].resetTilt(); //reset in last wanted menu and not in current
	for (int i = 0; i < m_buttons[m_wantedMenu].size(); ++i)
	{
		if (m_buttons[m_wantedMenu][i].hover(mousePos))
		{
			m_lastHovered = i;
			m_lastWantedMenu = m_wantedMenu;
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
		m_chooseLevel = m_onlineConnection = m_connectPressed = m_settingPressed = m_showHelp = false;
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
}

void MenuScreen::setText(sf::Text &text, std::string str, int size, sf::Vector2f pos, sf::Color color)
{
	text.setColor(color);
	text.setCharacterSize(size);
	text.setFont(*Resources::instance().getFont());
	text.setPosition(pos);
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
	text.setString(str);
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
	else if (m_showHelp)
	{
		window.draw(m_help);
	}
	else if (m_settingPressed)
	{
		for (auto& vol : m_volume)
		{
			vol.draw(window);
		}

		for (auto& button : m_settingsButtons)
		{
			button.draw(window);
			window.draw(m_volumeText);
			window.draw(m_screenSizeText);
		}
	}
	else
	{
		for (auto& button : m_buttons[m_wantedMenu])
		{
			button.draw(window);
		}
		if (m_onlineConnection)
		{
			window.draw(m_textRectangle);
			window.draw(m_output);
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