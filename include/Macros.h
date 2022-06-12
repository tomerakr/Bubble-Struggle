#pragma once

#include <vector>
#include <utility>
#include "SFML/Graphics.hpp"

constexpr int windowHeight = 800;
constexpr int windowWidth = 1200;
constexpr int SurvivalWidth = 3 * windowWidth;
constexpr int barHeight = 100;
constexpr int numOfBalls = 9;
constexpr int thickness = 10;
constexpr int ropeWitdh = 20;
constexpr int ropeHeight = 1;
constexpr int bearWitdh = 80;
constexpr int bearHeight = 120;
constexpr int giftTimer = 3;
constexpr int EPSILON = 5;
constexpr int RIGHT = 1;
constexpr int LEFT = -1;

constexpr int BALL_FILTER = -1;					// filter for regular ball
constexpr int ROPE_FILTER = -4;					// filter for regular rope
constexpr int POPPED_BALL_FILTER = -5;
constexpr int BEAR_FILTER = -6;
constexpr int TILE = -7;
//constexpr int CEILING = -14;
constexpr int TOUCH_BEAR = -9;
constexpr int GIFT_FREEZE_FILTER = -10;
constexpr int GIFT_DOUBLE_SHOT_FILTER = -11;
constexpr int GIFT_LIFE_FILTER = -12;
constexpr int GIFT_SHIELD_FILTER = -13;
constexpr int ROPE_TOUCH_WALL = -14;							// filter for frozen rope

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
	SurvivalBackground,
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

enum class Screen
{
	menu,
	game,
	levelCreator,
	MAX
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

enum class Sound
{
	theme,
	click,
	MAX
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

struct gameInput
{
	std::vector<sf::Keyboard::Key> _keys;
	std::pair<sf::Vector2f, bool> _otherBear; //direction, shoot
};