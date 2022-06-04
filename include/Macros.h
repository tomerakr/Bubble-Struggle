#pragma once

constexpr int windowHieght = 800;
constexpr int windowWitdh = 1200;
constexpr int barHeight = 100;
constexpr int numOfBalls = 9;
constexpr int thickness = 10;
constexpr int ropeWitdh = 20;
constexpr int ropeHeight = 0;
constexpr int bearWitdh = 80;
constexpr int bearHieght = 120;
constexpr int giftTimer = 3;

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
constexpr int numOfObjects = 16;
enum class Objects
{
	Ball,
	Bear,
	Panda,
	Polar,
	Pooh,
	Rope,
	BambooRope,
	PolarRope,
	HoneyRope, 
	Floor,
	Wall,
	Button,
	Arrow,
	EraseButton,
	ClearButton,
	SaveButton,
	GiftFreeze,
	GiftDoubleShot,
	GiftTime,
	GiftLife,
	GiftShield
};

constexpr int numOfBackgrounds = 4;
enum class Backgrounds
{
	BearMenu,
	PandaMenu,
	PolarMenu,
	PoohMenu,
	//GameBackground,
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

struct Skin
{
	Objects _bear;
	Objects _rope;
	Backgrounds _background;
};
constexpr int numOfSkins = 4;

struct gameInfo
{
	Screen _screen;
	gameMode _mode;
	unsigned int _numOfPlayers;
	receiveInfo _receive;
	bool _newGame;
	Skin _skin;
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