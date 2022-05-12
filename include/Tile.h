#pragma once

#include "StaticObject.h"

class Tile : public StaticObject
{
public:
	using StaticObject::StaticObject;

private:
	bool m_vertical;
};

