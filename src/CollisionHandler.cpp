#include "CollisionHandler.h"

#include "Bear.h"
#include "Ball.h"
#include "Rope.h"
#include "Tile.h"
#include "Gift.h"
#include <iostream>

CollisionHandler::CollisionHandler()
{
	initializeMap();
}

CollisionHandler& CollisionHandler::instance()
{
	static CollisionHandler inst;
	return inst;
}

void CollisionHandler::handleCollision(GameObject* a, GameObject* b)
{
	
	auto mapEntry = m_colliderMap.find(key(typeid(*a), typeid(*b)));

	if (mapEntry != m_colliderMap.end())
	{
		auto func = mapEntry->second;
		(this->*(func))(a, b);
	}
}

void CollisionHandler::initializeMap()
{
	m_colliderMap[key(typeid(Ball), typeid(Bear))] = &CollisionHandler::ballHitBear;
	m_colliderMap[key(typeid(Bear), typeid(Ball))] = &CollisionHandler::bearHitBall;

	m_colliderMap[key(typeid(Ball), typeid(Rope))] = &CollisionHandler::ballHitRope;
	m_colliderMap[key(typeid(Rope), typeid(Ball))] = &CollisionHandler::ropeHitBall;

	m_colliderMap[key(typeid(Rope), typeid(Tile))] = &CollisionHandler::ropeHitTile;
	m_colliderMap[key(typeid(Tile), typeid(Rope))] = &CollisionHandler::tileHitRope;

	m_colliderMap[key(typeid(Gift), typeid(Bear))] = &CollisionHandler::giftHitBear;
	m_colliderMap[key(typeid(Bear), typeid(Gift))] = &CollisionHandler::bearHitGift;

	m_colliderMap[key(typeid(Bear), typeid(Tile))] = &CollisionHandler::bearHitTile;
	m_colliderMap[key(typeid(Tile), typeid(Bear))] = &CollisionHandler::tileHitBear;
}

void CollisionHandler::ballHitBear(GameObject* ball, GameObject* bear)
{
	//Ball* ballPtr = static_cast<Ball*>(ball);
	Bear* bearPtr = static_cast<Bear*>(bear);

	bearPtr->reduceLife();
}

void CollisionHandler::ballHitRope(GameObject* ball, GameObject* rope)
{
	Ball* ballPtr = static_cast<Ball*>(ball);
	Rope* ropePtr = static_cast<Rope*>(rope);

	ballPtr->pop();
	ropePtr->poppedABall();
}

void CollisionHandler::ropeHitTile(GameObject* rope, GameObject* tile)
{
	Rope* ropePtr = static_cast<Rope*>(rope);
	//Tile* tilePtr = static_cast<Tile*>(tile);

	ropePtr->hitAWall();
}

void CollisionHandler::giftHitBear(GameObject* gift, GameObject* bear)
{
	Gift* giftPtr = static_cast<Gift*>(gift);
	Bear* bearPtr = static_cast<Bear*>(bear);

	giftPtr->taken();
	bearPtr->addLife();
}

void CollisionHandler::bearHitTile(GameObject* bear, GameObject* tile)
{
	Bear* bearPtr = static_cast<Bear*>(bear);
	//Tile* tilePtr = static_cast<Tile*>(tile);

	bearPtr->hitedAWall();
}