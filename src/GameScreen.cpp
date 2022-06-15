#include "GameScreen.h"
#include "Controller.h"
#include "Bear.h"
#include <time.h>

GameScreen::GameScreen(Controller* ctrl)
	: m_controller(ctrl), m_board()
{
	srand(time(NULL));
	Resources::instance().playSound(Sound::theme);

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
	m_points.second = SurvivalWidth - m_points.first;
}

Screen GameScreen::gamePlay(gameInfo& info)
{
	if (info._newGame)
	{
		game(info);
		m_bar.setBar(90, info); //getLevel Time
		info._newGame = false;
	}
	auto screen = Screen::game;
	switch (info._mode)
	{
	case gameMode::Normal:
		screen = playNormal(info);
		break;

	case gameMode::Survival:
		screen = playSurvival();
		break;

	default:
		break;
	}

	return screen;
}

void GameScreen::game(const gameInfo& info)
{
	clear();

	auto xPos = windowWidth / (info._numOfPlayers + 1);
	auto yPos = windowHeight - barHeight - bearHeight - thickness;
	auto textureIndex = info._skinIndex;

	m_bears.emplace_back(Bear{ sf::Vector2f(xPos * info._numOfPlayers, yPos), &m_board, receiveInfo::Solo, textureIndex++ % static_cast<int>(bearTypes::MAX) });
	m_bears.back().setKeys(&m_keys[(info._numOfPlayers - info._numOfPlayers) % m_keys.size()]);
	
	m_board.pickLevel(info._level);
	m_bar.setLevel(info._level);
	
	for (int i = info._numOfPlayers - 1; i > 0; --i)
	{
		m_bears.emplace_back(Bear{sf::Vector2f(xPos * i, yPos), &m_board, info._receive, textureIndex++ % static_cast<int>(bearTypes::MAX) });
		m_bears.back().setKeys(&m_keys[(info._numOfPlayers - i) % m_keys.size()]);
	}
	if (info._host) m_bears.back().setHost();
	textureIndex = info._skinIndex;

	auto textureSize = sf::Vector2u();

	switch (info._mode)
	{
	case gameMode::Normal:

		m_background.setTexture(Resources::instance().getObjectTexture(Objects::GameBackground));
		m_background.setSize(sf::Vector2f(windowWidth, windowHeight));
		textureSize = m_background.getTexture()->getSize();
		m_background.setTextureRect(sf::IntRect((textureSize.x / numOfGameBackgrounds) * (rand() % numOfGameBackgrounds), 0,
			textureSize.x / numOfGameBackgrounds, textureSize.y));

		m_board.createNormal();
		m_board.setLevel();
		break;

	case gameMode::Survival:
	{
		//createSuvival();
		m_background.setTexture(Resources::instance().getObjectTexture(Objects::SurvivalBackground));
		m_background.setSize(sf::Vector2f(SurvivalWidth, windowHeight));

		for (int i = info._numOfPlayers; i > 0; --i)
		{
			m_dummyBears.emplace_back(Bear{ sf::Vector2f(xPos * i + SurvivalWidth, yPos), &m_board, info._receive, textureIndex++ % static_cast<int>(bearTypes::MAX) });
			m_dummyBears.back().setKeys(&m_keys[(info._numOfPlayers - i) % m_keys.size()]);
		}

		m_mainBear = &m_bears.front();
		m_board.createSurvival();
		break;
	}

	default:
		break;
	}
}

Screen GameScreen::playNormal(gameInfo& info)
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
	screen = update(deltaTime.asSeconds(), info);

	return screen;
}

Screen GameScreen::update(float deltaTime, gameInfo& info)
{
	auto scores = std::vector<int>();
	auto otherBear = std::make_pair(sf::Vector2f(), false);
	for (auto& bear : m_bears)
	{
		otherBear = bear.update(deltaTime, otherBear, this);
		scores.push_back(bear.getScore());
	}
	m_bar.update(scores);
	m_board.update();

	//if no balls left, proceed to next level
	if (m_board.getNumBalls() == 0)
	{
		m_isWon = true;
	}
	if (m_bar.timeEnded())
	{
		m_board.resetLevel();
		for (auto& bear : m_bears)
		{
			bear.decLives();
		}
	}
	if (allBearsDead())
	{
		clear();
		info._newGame = true;
		m_isLost = true;
		return Screen::menu;
	}
	return Screen::game;
}

bool GameScreen::allBearsDead()
{
	for (auto& bear : m_bears)
	{
		if (bear.getNumOfLives() != 0)
		{
			return false;
		}
	}

	return true;
}

void GameScreen::drawNormal()
{
	auto lives = std::vector<int>();
	auto& window = m_controller->getWindow();
	window.clear(sf::Color::White);
	window.draw(m_background);

	for (auto& bear : m_bears)
	{
		bear.drawRopes(window);
		bear.draw(window);
		lives.push_back(bear.getNumOfLives());
	}
	m_board.draw(window);
	m_bar.draw(window, lives);

	window.display();
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

void GameScreen::updateSurvival(float deltaTime)
{
	auto scores = std::vector<int>();
	auto otherBear = std::make_pair(sf::Vector2f(), false);
	for (auto& bear : m_bears)
	{
		otherBear = bear.update(deltaTime, otherBear, this);
		scores.push_back(bear.getScore());
	}
	for (auto& bear : m_dummyBears)
	{
		bear.update(deltaTime, otherBear, this);
	}

	updateBearSurvivalPosition();
	updateBallSurvivalPosition();
	addBallsSurvival(deltaTime);
	m_bar.update(scores);
	m_board.update();
}

void GameScreen::addBallsSurvival(float deltaTime)
{
	m_totalTime += deltaTime;

	if (m_totalTime >= m_addBallSpaceTime)
	{
		m_totalTime -= m_addBallSpaceTime;

		auto pos = sf::Vector2f(rand() % SurvivalWidth, 100);
		auto force = b2Vec2((rand() % 2 == 0 ? -1 : 1) * 20, -30); // 50 - 50 for each direction
		auto index = rand() % numOfBalls;
		m_board.addBall(pos, force, index);
	}
}

void GameScreen::updateBearSurvivalPosition()
{
	auto bearPos = m_bears.front().getPos();
	auto dummyBearPos = m_dummyBears.front().getPos();
	if (bearPos.x > 0 && bearPos.x < SurvivalWidth)
	{
		m_mainBear = &m_bears.front();
		m_dummyBears.front().setPos(sf::Vector2f(bearPos.x + ((bearPos.x > m_points.second ? -1 : 1)) * SurvivalWidth, bearPos.y));
	}
	else
	{
		m_mainBear = &m_dummyBears.front();
		m_bears.front().setPos(sf::Vector2f(dummyBearPos.x + (dummyBearPos.x > m_points.second ? -1 : 1) * SurvivalWidth, dummyBearPos.y));
	}
}

void GameScreen::updateBallSurvivalPosition()
{
	auto balls = m_board.getBalls();

	for (int i = 0; i < balls.isEnd(); balls.next())
	{
		auto pos = balls.value().getPos();
		auto radius = balls.value().getRaidus();
		auto direction = balls.value().getCurrDirection();
		if (!balls.value().hadChild() && pos.x <= radius + EPSILON && direction == LEFT)
		{
			m_board.addBall(balls.value(), SurvivalWidth);
			balls.value().creatingNewBall();
		}
		else if (pos.x <= -(radius + EPSILON) && direction == LEFT)
		{
			balls.value().destroy();
		}
		if (!balls.value().hadChild() && pos.x >= SurvivalWidth - (radius + EPSILON) && direction == RIGHT)
		{
			m_board.addBall(balls.value(), -(SurvivalWidth));
			balls.value().creatingNewBall();
		}
		else if (pos.x >= SurvivalWidth + radius + EPSILON && direction == RIGHT)
		{
			balls.value().destroy();
		}
	}
}

Screen GameScreen::handleKeyboard()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		return Screen::menu;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (m_isWon)
		{
			m_board.nextLevel();
			auto textureSize = m_background.getTexture()->getSize();
			m_background.setTextureRect(sf::IntRect((textureSize.x / numOfGameBackgrounds) * rand() % numOfGameBackgrounds, 0,
				textureSize.x / numOfGameBackgrounds, textureSize.y));
			m_isWon = false;
		}

		if (m_isLost)
		{
			m_board.pickLevel(1);
			//	how to return to the menu?
			return Screen::menu;
		}
	}

	return Screen::game;
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

	auto lives = std::vector<int>();
	for (auto& bear : m_bears)
	{
		lives.push_back(bear.getNumOfLives());
	}
	m_bar.draw(window, lives);

	//================ M I N I - M A P ================
	//auto miniMapView = sf::View(sf::FloatRect(-SurvivalWidth, 0, SurvivalWidth * 3, windowHeight - barHeight));
	//miniMapView.setViewport({ 0.2f, barHeight / static_cast<float>(windowHeight), 0.6, 0.3 });
	//draw(window, miniMapView);
	//=================================================

	window.setView(sf::View(sf::FloatRect(0.f, 0.f, windowWidth, windowHeight)));
	window.display();
}

void GameScreen::setViews(sf::View& leftView, sf::View& rightView)
{
	auto bearX = m_mainBear->getPos().x;

	auto bearLeft = m_points.first - bearX;
	auto bearRight = bearX - m_points.second;

	auto leftViewSize = sf::Vector2f(windowWidth - (bearLeft > 0 ? bearLeft : 0), windowHeight - barHeight);
	auto leftViewPos = sf::Vector2f(((bearLeft > 0 || bearRight > 0 ? 0 : bearX - m_points.first)), 0);

	auto rightViewSize = sf::Vector2f((bearLeft > 0 ? windowWidth - leftViewSize.x : windowWidth - (bearRight > 0 ? bearRight : 0)), windowHeight - barHeight);
	auto rightViewPos = sf::Vector2f(bearX + (bearLeft > 0 ? m_points.second : -m_points.first), 0);

	if (bearRight > 0) leftViewSize.x = windowWidth - rightViewSize.x;

	leftView = sf::View(sf::FloatRect(leftViewPos.x, leftViewPos.y, leftViewSize.x, leftViewSize.y));
	rightView = sf::View(sf::FloatRect(rightViewPos.x, rightViewPos.y, rightViewSize.x, rightViewSize.y));

	float windowPortion = (windowHeight - barHeight) / static_cast<float>(windowHeight);

	auto firstSizeX = ((bearLeft > 0 || bearRight > 0) ? rightViewSize.x : leftViewSize.x);
	auto secondSizeX = ((bearLeft > 0 || bearRight > 0) ? leftViewSize.x : rightViewSize.x);

	rightView.setViewport({ 0.f, 0.f, firstSizeX / windowWidth,  windowPortion });
	leftView.setViewport({ firstSizeX / windowWidth, 0.f, secondSizeX / windowWidth, windowPortion });

}

void GameScreen::addTime()
{
	m_bar.addTime();
}

void GameScreen::draw(sf::RenderWindow& window, sf::View& view)
{
	auto lives = std::vector<int>();
	window.setView(view);
	for (auto& bear : m_bears)
	{
		bear.drawRopes(window);
		bear.draw(window);
		lives.push_back(bear.getNumOfLives());
	}
	for (auto& bear : m_dummyBears)
	{
		bear.drawRopes(window);
		bear.draw(window);
	}
	m_board.draw(window);
	m_bar.draw(window, lives);
}

void GameScreen::clear()
{
	for (auto& bear : m_bears)
	{
		bear.destroyBody();
	}
	for (auto& bear : m_dummyBears)
	{
		bear.destroyBody();
	}
	m_bears.clear();
	m_dummyBears.clear();
	m_board.clear();
}