#pragma once

#include "MovingObject.h"

class Rope : public MovingObject
{
public:
	using MovingObject::GameObject;
	void checkHit();
	void setFreeze();

private:
	bool m_freeze = false;
};

