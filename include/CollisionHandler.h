#pragma once

#include "GameObject.h"
#include "HashHandler.h"
#include <utility>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>

class CollisionHandler
{
public:
	using colliderFunc = void (CollisionHandler::*)(GameObject*, GameObject*);
	using key = std::pair<std::type_index, std::type_index>;
	using colliderFuncMap = std::unordered_map<key, colliderFunc, PairKeysHash, KeyEqual>;

	static CollisionHandler& instance();
	~CollisionHandler() { }
	void handleCollision(GameObject*, GameObject*);

private:
	colliderFuncMap m_colliderMap;

	CollisionHandler();
	CollisionHandler(const CollisionHandler&) = default;
	CollisionHandler& operator=(const CollisionHandler&) = default;

	void initializeMap();

	void ballHitBear(GameObject*, GameObject*);
	void bearHitBall(GameObject* A, GameObject* B) { ballHitBear(B, A); }

	void ballHitRope(GameObject*, GameObject*);
	void ropeHitBall(GameObject* A, GameObject* B) { ballHitRope(B, A); }

	void ropeHitTile(GameObject*, GameObject*);
	void tileHitRope(GameObject* A, GameObject* B) { ropeHitTile(B, A); }

	void giftHitBear(GameObject*, GameObject*);
	void bearHitGift(GameObject* A, GameObject* B) { giftHitBear(B, A); }

	void bearHitTile(GameObject*, GameObject*);
	void tileHitBear(GameObject* A, GameObject* B) { bearHitTile(B, A); }
};