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

};