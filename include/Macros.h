#pragma once

constexpr int windowHieght = 800;
constexpr int windowWitdh = 1200;
constexpr int barHeight = 100;
constexpr float pToMeter = 0.0002645833f;

float pixelToMeter(const int pixels)
{
	return pixels * pToMeter;
}

enum class Objects
{
	Ball,
	Bear,
	Button,
	Rope,
	Tile,
	GiftFreeze,
	GiftDoubleShot,
	GiftTime,
};