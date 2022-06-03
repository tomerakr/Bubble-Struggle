#include "GameScreen.h"
#include "Bear.h"
#include "Controller.h"

GameScreen::GameScreen(Controller* ctrl)
	: m_controller(ctrl), m_board()
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

void GameScreen::game(const gameInfo& info)
{
	m_bears.clear();
	auto xPos = windowWitdh / (info._numOfPlayers + 1);
	auto yPos = windowHieght - barHeight - bearHieght - thickness;
	auto textureIndex = info._skinIndex;
	for (int i = info._numOfPlayers; i > 0; --i)
	{
		m_bears.emplace_back(Bear{sf::Vector2f(xPos * i, yPos), &m_board, info._receive, textureIndex });
		m_bears.back().setKeys(&m_keys[(info._numOfPlayers - i) % m_keys.size()]);
		textureIndex = --textureIndex % numOfSkins;
		textureIndex = (textureIndex == -1 ? numOfSkins - 1 : textureIndex);
	}
	switch (info._mode)
	{
	case gameMode::Normal:
		m_board.createNormal();
		break;

	case gameMode::Survival:
		m_board.createSurvival();
		break;

	default:
		break;
	}
}

Screen GameScreen::playNormal()
{
	auto screen = Screen::game;
	sf::Clock clock;
	auto& window = m_controller->getWindow();

	draw();
	const auto deltaTime = clock.restart();

	if (sf::Event event; window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;

		case sf::Event::KeyPressed:
			screen = handleKeyboard();
			break;

		default:
			break;
		}
	}
	update(deltaTime.asSeconds());
	return screen;
}

Screen GameScreen::playSurvival()
{
	auto screen = Screen::game;
	auto& window = m_controller->getWindow();
	sf::Clock clock;

	drawSurvival();
	const auto deltaTime = clock.restart();

	if (sf::Event event; window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;

		case sf::Event::KeyPressed:
			screen = handleKeyboard();
			break;

		default:
			break;
		}
	}
	update(deltaTime.asSeconds());
	return screen;
}

Screen GameScreen::gamePlay(gameInfo& info)
{
	if (info._newGame)
	{
		game(info);
		m_bar.setBar(40, info); //getLevel Time
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

void GameScreen::update(float deltaTime)
{
	auto otherBear = std::make_pair(sf::Vector2f(), false);
	for (auto& bear : m_bears)
	{
		otherBear = bear.update(deltaTime, otherBear);
	}
	m_bar.update(m_bears.front());
	m_board.update();
}

Screen GameScreen::handleKeyboard()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		return Screen::menu;
	}
	return Screen::game;
}

void GameScreen::draw()
{
	auto& window = m_controller->getWindow();
	window.clear(sf::Color::White);

	for (auto& bear : m_bears)
	{
		bear.drawRopes(window);
		bear.draw(window);
	}
	m_board.draw(window);
	m_bar.draw(window, m_bears.front());

	window.display();
}

void GameScreen::drawSurvival()
{
	auto& window = m_controller->getWindow();
	auto bearLeft = windowWitdh / 2 - bearWitdh / 2 - m_bears.front().getPos().x;
	auto leftViewSize = sf::Vector2f(windowWitdh - (bearLeft > 0 ? bearLeft : 0), windowHieght - barHeight);
	if (m_bears.front().getPos().x <= -windowWitdh / 2 + bearWitdh / 2) leftViewSize.x = 0;
	auto leftViewPos = sf::Vector2f(((bearLeft > 0 ? 0 : m_bears.front().getPos().x + bearWitdh / 2 - windowWitdh / 2)), 0);
	
	auto bearRight = m_bears.front().getPos().x - (3 * windowWitdh - windowWitdh / 2 - bearWitdh / 2);
	auto rightViewSize = sf::Vector2f((bearLeft > 0 ? windowWitdh - leftViewSize.x : windowWitdh - (bearRight > 0 ? bearRight : 0)), windowHieght - barHeight);
	if (m_bears.front().getPos().x >= 3 * windowWitdh - windowWitdh / 2 + bearWitdh / 2) rightViewSize.x = 0;
	auto rightViewPos = sf::Vector2f(m_bears.front().getPos().x + bearWitdh / 2 - windowWitdh / 2 + 3 * windowWitdh, 0);

	auto leftView = sf::View(sf::FloatRect(leftViewPos.x, leftViewPos.y, leftViewSize.x, leftViewSize.y));
	auto rightView = sf::View(sf::FloatRect(rightViewPos.x, rightViewPos.y, rightViewSize.x, rightViewSize.y));

	float windowPortion = (windowHieght - barHeight) / static_cast<float>(windowHieght);
	if (bearLeft > 0)
	{
		rightView.setViewport({ 0.f, 0.f, rightViewSize.x / windowWitdh,  windowPortion });
		leftView.setViewport({ rightViewSize.x / windowWitdh, 0.f, leftViewSize.x / windowWitdh, windowPortion });
	}
	else
	{
		leftView.setViewport({0.f, 0.f, leftViewSize.x / windowWitdh, windowPortion });
		rightView.setViewport({ leftViewSize.x / windowWitdh, 0.f, rightViewSize.x / windowWitdh, windowPortion });
	}

	window.clear(sf::Color::White);

	window.setView(leftView);
	for (auto& bear : m_bears)
	{
		bear.drawRopes(window);
		bear.draw(window);
	}
	m_board.draw(window);
	m_bar.draw(window, m_bears.front());

	window.setView(rightView);
	for (auto& bear : m_bears)
	{
		bear.drawRopes(window);
		bear.draw(window);
	}
	m_board.draw(window);

	auto barView = sf::View(sf::FloatRect(0.f, windowHieght - barHeight, windowWitdh, windowHieght));
	barView.setViewport({ 0, (windowHieght - barHeight) / static_cast<float>(windowHieght), 1, 1 });
	window.setView(barView);
	m_bar.draw(window, m_bears.front());

	window.setView(sf::View(sf::FloatRect(0.f, 0.f, windowWitdh, windowHieght)));
	window.display();
}