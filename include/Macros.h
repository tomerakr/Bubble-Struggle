#pragma once

constexpr int windowHieght = 800;
constexpr int windowWitdh = 1200;
constexpr int barHeight = 100;
constexpr float RATIO = 30.f;			//??
constexpr float UNRATIO = 1 / RATIO;	//??
constexpr int numOfBalls = 9;

//---------------------------------------------------------
constexpr int numOfObjects = 3;
enum class Objects
{
	Ball,
	Bear,
	Button,
	Rope,
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
//---------------------------------------------------------
