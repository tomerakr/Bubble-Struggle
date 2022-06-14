#pragma once

#include "box2d/box2d.h"
//#include "Macros.h"
#include "CollisionHandler.h"
#include "GameObject.h"

class ContactListener : public b2ContactListener
{
public:
    //ContactListener() {}
    //~ContactListener() {}
    void BeginContact(b2Contact* contact);
    //void EndContact(b2Contact* contact) {}

};