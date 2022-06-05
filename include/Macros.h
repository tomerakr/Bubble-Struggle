#pragma once

constexpr int windowHeight = 800;
constexpr int windowWidth = 1200;
constexpr int barHeight = 100;
constexpr int numOfBalls = 9;
constexpr int thickness = 10;
constexpr int ropeWitdh = 20;
constexpr int ropeHeight = 0;
constexpr int bearWitdh = 80;
constexpr int bearheight = 120;
constexpr int giftTimer = 3;
constexpr int EPSILON = 5;
constexpr int RIGHT = 1;
constexpr int LEFT = -1;

//constexpr sf::Vector2f left = sf::Vector2f(-1, 0);
//constexpr sf::Vector2f right = sf::Vector2f(1, 0);

constexpr int BALL_FILTER = -1;
//constexpr int FLOOR = -2;
//constexpr int WALL = -3;
constexpr int ROPE_FILTER = -4;
const int POPPED_BALL_FILTER = -5;
const int BEAR_FILTER = -6;
constexpr int TILE = -7;
const int TOUCH_WALL = -8;
const int TOUCH_BEAR = -9;
const int GIFT_FREEZE_FILTER = -10;
const int GIFT_DOUBLE_SHOT_FILTER = -11;
const int GIFT_LIFE_FILTER = -12;
const int GIFT_SHIELD_FILTER = -13;


//---------------------------------------------------------
enum class Objects
{
	Bears,
	Ropes,
	Ball,
	Floor,
	Wall,
	Button,
	Arrow,
	EraseButton,
	ClearButton,
	SaveButton,
	Backgrounds,
	BearsHeads,
	Gifts,
	BarBackground,
	TextBackground,
	MAX
};

enum class giftTypes
{
	Freeze,
	DoubleShot,
	Time,
	Life,
	Shield,
	MAX
};

enum class bearTypes
{
	REGULAR,
	PANDA,
	POLAR,
	POOH,
	MAX
};

constexpr int numOfScreens = 3;
enum class Screen
{
	menu,
	game,
	levelCreator
};

enum class gameMode
{
	Normal,
	Survival
};

enum class receiveInfo
{
	Solo,
	Online,
	SamePc
};

enum class Keys
{
	Left,
	Right,
	Shoot
};
//---------------------------------------------------------

struct gameInfo
{
	Screen _screen;
	gameMode _mode;
	unsigned int _numOfPlayers;
	receiveInfo _receive;
	bool _newGame;
	int _skinIndex;
};

#include <vector>
#include <utility>
#include "SFML/Graphics.hpp"

struct gameInput
{
	std::vector<sf::Keyboard::Key> _keys;
	std::pair<sf::Vector2f, bool> _otherBear; //direction, shoot
};