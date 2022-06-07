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

	m_points.first = windowWidth / 2.f;
	m_points.second = 3 * windowWidth - m_points.first;
}

void GameScreen::game(const gameInfo& info)
{
	m_bears.clear();
	auto xPos = windowWidth / (info._numOfPlayers + 1);
	auto yPos = windowHeight - barHeight - bearheight - thickness;
	auto textureIndex = info._skinIndex;
	for (int i = info._numOfPlayers; i > 0; --i)
	{
		m_bears.emplace_back(Bear{sf::Vector2f(xPos * i, yPos), &m_board, info._receive, textureIndex });
		m_bears.back().setKeys(&m_keys[(info._numOfPlayers - i) % m_keys.size()]);

		m_dummyBears.emplace_back(Bear{ sf::Vector2f(xPos * i, yPos), &m_board, info._receive, textureIndex++ % static_cast<int>(bearTypes::MAX) });
		m_dummyBears.back().setKeys(&m_keys[(info._numOfPlayers - i) % m_keys.size()]);
	}

	switch (info._mode)
	{
	case gameMode::Normal:
		m_board.createNormal();
		break;

	case gameMode::Survival:
	{
		m_background.setTexture(Resources::instance().getObjectTexture(Objects::SurvivalBackground));
		m_background.setSize(sf::Vector2f(3 * windowWidth, windowHeight));

		auto pos = m_bears.front().getPos();
		m_dummyBears.front().setPos(sf::Vector2f(pos.x + 3 * windowWidth, pos.y));
		m_mainBear = &m_bears.front();
		m_board.createSurvival();
		break;
	}

	default:
		break;
	}
}

Screen GameScreen::playNormal()
{
	auto screen = Screen::game;
	sf::Clock clock;
	auto& window = m_controller->getWindow();

	drawNormal();
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
	auto deltaTime = clock.restart().asSeconds();

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
	updateSurvival(deltaTime);

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

void GameScreen::updateSurvival(float deltaTime)
{
	auto otherBear = std::make_pair(sf::Vector2f(), false);
	for (auto& bear : m_bears)
	{
		otherBear = bear.update(deltaTime, otherBear);
	}
	for (auto& bear : m_dummyBears)
	{
		bear.update(deltaTime, otherBear);
	}

	updateBearSurvivalPosition();
	updateBallSurvivalPosition();

	m_bar.update(m_bears.front());
	m_board.update();
}

void GameScreen::updateBearSurvivalPosition()
{
	auto bearPos = m_bears.front().getPos();
	auto dummyBearPos = m_dummyBears.front().getPos();
	if (bearPos.x > 0 && bearPos.x < 3 * windowWidth)
	{
		m_mainBear = &m_bears.front();
		m_dummyBears.front().setPos(sf::Vector2f(bearPos.x + ((bearPos.x > m_points.second ? -1 : 1)) * 3 * windowWidth, bearPos.y));
	}
	else
	{
		m_mainBear = &m_dummyBears.front();
		m_bears.front().setPos(sf::Vector2f(dummyBearPos.x + (dummyBearPos.x > m_points.second ? -1 : 1) * 3 * windowWidth, dummyBearPos.y));
	}
}

void GameScreen::updateBallSurvivalPosition()
{
	//auto balls = m_board.getBalls();
	//for (auto& ball : *balls)
	//{
	//	auto pos = ball.getPos();
	//	auto radius = ball.getRaidus();
	//	auto direction = ball.getCurrDirection();
	//	if (!ball.hadChild() && pos.x <= radius + EPSILON && direction == LEFT)
	//	{
	//		m_board.addBall(ball, 3 * windowWidth);
	//		ball.creatingNewBall();
	//	}
	//	else if (pos.x <= -(radius + EPSILON) && direction == LEFT)
	//	{
	//		ball.destroy();
	//	}
	//	if (!ball.hadChild() && pos.x >= 3 * windowWidth - (radius + EPSILON) && direction == RIGHT)
	//	{
	//		m_board.addBall(ball, -(3 * windowWidth));
	//		ball.creatingNewBall();
	//	}
	//	else if (pos.x >= 3 * windowWidth + radius + EPSILON && direction == RIGHT)
	//	{
	//		ball.destroy();
	//	}
	//}
}

Screen GameScreen::handleKeyboard()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		return Screen::menu;
	}
	return Screen::game;
}

void GameScreen::drawNormal()
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
	auto leftView = sf::View(), rightView = sf::View();
	setViews(leftView, rightView);
	
	window.clear(sf::Color::White);
	window.draw(m_background);

	draw(window, leftView);
	draw(window, rightView);

	auto barView = sf::View(sf::FloatRect(0.f, windowHeight - barHeight, windowWidth, windowHeight));
	barView.setViewport({ 0, (windowHeight - barHeight) / static_cast<float>(windowHeight), 1, 1 });
	window.setView(barView);
	m_bar.draw(window, m_bears.front());

	//================ M I N I - M A P ================
	//auto miniMapView = sf::View(sf::FloatRect(0, 0, windowWidth * 4, windowHeight - barHeight));
	//miniMapView.setViewport({ 0.4f, barHeight / static_cast<float>(windowHeight), 0.6, 0.3 });
	//draw(window, miniMapView);
	//=================================================

	window.setView(sf::View(sf::FloatRect(0.f, 0.f, windowWidth, windowHeight)));
	window.display();
}

void GameScreen::draw(sf::RenderWindow& window, sf::View& view)
{
	window.setView(view);
	for (auto& bear : m_bears)
	{
		bear.drawRopes(window);
		bear.draw(window);
	}
	for (auto& bear : m_dummyBears)
	{
		bear.drawRopes(window);
		bear.draw(window);
	}
	m_board.draw(window);
	m_bar.draw(window, m_bears.front());
}

void GameScreen::setViews(sf::View& leftView, sf::View& rightView)
{
	auto bearX = m_mainBear->getPos().x;

	auto bearLeft = m_points.first - bearX;
	auto bearRight = bearX - m_points.second;

	auto leftViewSize = sf::Vector2f(windowWidth - (bearLeft > 0 ? bearLeft : 0), windowHeight - barHeight);
	//if (bearX <= -windowWidth / 2 + bearWitdh / 2) 
	//	leftViewSize.x = 0;
	auto leftViewPos = sf::Vector2f(((bearLeft > 0 || bearRight > 0 ? 0 : bearX - m_points.first)), 0);

	auto rightViewSize = sf::Vector2f((bearLeft > 0 ? windowWidth - leftViewSize.x : windowWidth - (bearRight > 0 ? bearRight : 0)), windowHeight - barHeight);
	//if (bearX >= 3 * windowWidth + windowWidth / 2 - bearWitdh / 2)
	//	rightViewSize.x = 0;
	auto rightViewPos = sf::Vector2f(bearX + (bearLeft > 0 ? m_points.second : -m_points.first), 0);

	if (bearRight > 0) leftViewSize.x = windowWidth - rightViewSize.x;

	leftView = sf::View(sf::FloatRect(leftViewPos.x, leftViewPos.y, leftViewSize.x, leftViewSize.y));
	rightView = sf::View(sf::FloatRect(rightViewPos.x, rightViewPos.y, rightViewSize.x, rightViewSize.y));

	float windowPortion = (windowHeight - barHeight) / static_cast<float>(windowHeight);
	if (bearLeft > 0 || bearRight > 0)
	{
		rightView.setViewport({ 0.f, 0.f, rightViewSize.x / windowWidth,  windowPortion });
		leftView.setViewport({ rightViewSize.x / windowWidth, 0.f, leftViewSize.x / windowWidth, windowPortion });
	}
	else
	{
		leftView.setViewport({ 0.f, 0.f, leftViewSize.x / windowWidth, windowPortion });
		rightView.setViewport({ leftViewSize.x / windowWidth, 0.f, rightViewSize.x / windowWidth, windowPortion });
	}
}