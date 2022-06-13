#pragma once

#include "GameObject.h"
#include <unorderd_map>
#include <utility>
#include <typeinfo>
#include <typeindex>

class CollisionHandler
{
public:

	using colliderFunc = void (CollisionHandler::*)(GameObject*, GameObject*);
	using key = std::pair<std::type_index, std::type_index>;
	using colliderFuncMap = std::unorderd_map<key, colliderFunc, keyEqual>;

	static CollisionHandler& instance();
	~CollisionHandler() = default;
	void handleCollision(GameObject*, GameObject*);

private:
	std::unorderd_map<key, colliderFunc, keyEqual> m_colliderMap;

	CollisionHandler() = default;
	CollisionHandler(const CollisionHandler&) = default;
	CollisionHandler& operator=(const CollisionHandler&) = default;

	initializeMap();

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