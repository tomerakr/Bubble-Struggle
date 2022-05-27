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

constexpr int BALL_FILTER = -1;
constexpr int FLOOR = -2;
constexpr int WALL = -3;
constexpr int ROPE_FILTER = -4;
const int POPPED_BALL_FILTER = -5;
const int BEAR_FILTER = -6;

constexpr float RATIO = 30.f;			//??
constexpr float METERS_PER_PIXLE = 1 / RATIO;	//??

//---------------------------------------------------------
constexpr int numOfObjects = 14;
enum class Objects
{
	Ball,
	Bear,
	Panda,
	Polar,
	HoneyRope, 
	BambooRope,
	PolarRope,
	Floor,
	Wall,
	Button,
	UndoButton,
	EraseButton,
	ClearButton,
	SaveButton,
	GiftFreeze,
	GiftDoubleShot,
	GiftTime
};

constexpr int numOfBackgrounds = 3;
enum class Backgrounds
{
	BearMenu,
	PandaMenu,
	PolarMenu,
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
constexpr int numOfSkins = 3;

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
