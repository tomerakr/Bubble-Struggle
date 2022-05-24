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
//constexpr sf::Vector2f left = sf::Vector2f(-1, 0);
//constexpr sf::Vector2f right = sf::Vector2f(1, 0);

constexpr int FLOOR = -2;
constexpr int WALL = -3;
constexpr int ROPE_FILTER = -4;

constexpr float RATIO = 30.f;			//??
constexpr float METERS_PER_PIXLE = 1 / RATIO;	//??

//---------------------------------------------------------
constexpr int numOfObjects = 6;
enum class Objects
{
	Ball,
	Bear,
	Panda,
	Button,
	HoneyRope, 
	BambooRope, 
	Floor,
	Wall,
	GiftFreeze,
	GiftDoubleShot,
	GiftTime
};

constexpr int numOfBackgrounds = 1;
enum class Backgrounds
{
	Menu,
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
};