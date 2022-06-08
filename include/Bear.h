#pragma once

#include <SFML/Graphics.hpp>
#include "MovingObject.h" //do we need this class? for what reason
#include "Macros.h"
#include "Gun.h"
#include "Rope.h"
#include <vector>
#include "Input.h"

class Board;

class Bear : public MovingObject
{
public:
	Bear(const sf::Vector2f& pos, Board* board, const receiveInfo& readInput, int textureIndex);

	//Bear& operator=(Bear&& other) noexcept
	//{
	//	std::ranges::swap(m_score, other.m_score);
	//	std::ranges::swap(m_lives, other.m_lives);
	//	std::ranges::swap(m_board, other.m_board);
	//	std::ranges::swap(m_box2DBear, other.m_box2DBear);
	//	std::ranges::swap(m_gun, other.m_gun);
	//	std::ranges::swap(m_keys, other.m_keys);
	//	std::ranges::swap(m_getInput, other.m_getInput);
	//	return *this;
	//}
	void setPos(const sf::Vector2f& pos) { m_icon.setPosition(pos); }
	void jump();
	void setKeys(std::vector<sf::Keyboard::Key>* keys) { m_keys = *keys; }
	const sf::Vector2f& getPos() const;
	std::pair<const sf::Vector2f&, bool> update(float deltaTime, std::pair<sf::Vector2f, bool> otherBear);
	void drawRopes(sf::RenderWindow& window);
	unsigned int getNumOfLives(){ return m_lives; }
	unsigned int getScore()		{ return m_score; }

private:
	void defineBear2d(const sf::Vector2f&);

	void resetFilter();

	std::unique_ptr<Input> m_getInput = nullptr;
	std::vector<sf::Keyboard::Key> m_keys;

	Gun m_gun;
	b2Body* m_box2DBear = nullptr;
	Board* m_board = nullptr;

	unsigned int m_score;
	unsigned int m_lives;
	const unsigned int m_Maxlives = m_lives;

	bool m_hasShield = false;
	bool m_freezeRope = false;

	
};
