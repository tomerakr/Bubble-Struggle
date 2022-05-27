#pragma once

#include <SFML/Graphics.hpp>
#include "MovingObject.h"
#include "Macros.h"
#include "Gun.h"
#include "Rope.h"
#include <vector>
#include "Input.h"

class Board;
//class Input;

class Bear : public MovingObject
{
public:
	Bear(sf::Vector2f pos, Board* board, receiveInfo readInput, int textureIndex);
	void jump();
	void setKeys(std::vector<sf::Keyboard::Key>* keys) { m_keys = *keys; }
	const sf::Vector2f getPos() const;
	void update(float deltaTime);
	void drawRopes(sf::RenderWindow& window);

private:
	std::unique_ptr<Input> m_getInput = nullptr;
	bool m_online;
	int m_ropeTexture; //must be before gun
	Gun m_gun;
	std::vector<sf::Keyboard::Key> m_keys;

	b2Body* m_box2DBear = nullptr;
	Board* m_board = nullptr;
};

