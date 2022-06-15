#pragma once

#include "box2d/box2d.h"

class ContactListener : public b2ContactListener
{
private:
    void BeginContact(b2Contact* contact);
};