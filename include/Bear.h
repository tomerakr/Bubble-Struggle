#pragma once

#include <SFML/Graphics.hpp>
#include "MovingObject.h" //do we need this class? for what reason
#include "Animation.h"
#include "Macros.h"
#include "Gun.h"
#include "Rope.h"
#include <vector>
#include "Input.h"

constexpr int MAX_LIFE = 4;
constexpr int START_LIFE = 3;

class Board;

class Bear : public MovingObject
{
public:
	Bear(const sf::Vector2f& pos, Board* board, const receiveInfo& readInput, int textureIndex);

	void setPos(const sf::Vector2f& pos);
	void setKeys(std::vector<sf::Keyboard::Key>* keys) { m_keys = *keys; }
	const sf::Vector2f& getPos() const;
	void destroyBody();
	std::pair<const sf::Vector2f&, bool> update(float deltaTime, std::pair<sf::Vector2f, bool> otherBear);
	void drawRopes(sf::RenderWindow& window);
	unsigned int getNumOfLives(){ return m_lives; }
	unsigned int getScore()		{ return m_score; }
	void setHost()				{ m_host = true; }
	void resetPowers();
	void decLives()				{ --m_lives; }

private:
	void defineBear2d(const sf::Vector2f&);
	void resetFilter();

	std::unique_ptr<Input> m_getInput = nullptr;
	std::vector<sf::Keyboard::Key> m_keys;

	Gun m_gun;
	b2Body* m_box2DBear = nullptr;
	Board* m_board = nullptr;
	Animation m_animation;
	sf::Vector2f m_pos;

	unsigned int m_score;
	unsigned int m_lives;

	bool m_shield = false;
	bool m_freezeRope = false;
	bool m_host = false;
	float m_speedPerSecond = 200.f;
};
