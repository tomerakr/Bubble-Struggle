#include "ContactListener.h"

#include "Macros.h"

#include <iostream>

void ContactListener::BeginContact(b2Contact* contact)
{   
    auto fixtureA = contact->GetFixtureA();
    auto fixtureB = contact->GetFixtureB();

    if (fixtureA == nullptr || fixtureB == nullptr)
    {
        return;
    }

    if (fixtureA->GetBody() == nullptr || fixtureB->GetBody() == nullptr)
    {
        return;
    }

//      if rope collided with ball
    if (fixtureA->GetFilterData().groupIndex == BALL_FILTER &&
        fixtureB->GetFilterData().groupIndex == ROPE_FILTER ||
        fixtureA->GetFilterData().groupIndex == ROPE_FILTER &&
        fixtureB->GetFilterData().groupIndex == BALL_FILTER)
    {
        b2Filter destroyObjects;
        destroyObjects.groupIndex = POPPED_BALL_FILTER;
        fixtureA->SetFilterData(destroyObjects);
        fixtureB->SetFilterData(destroyObjects);
    }

//      if ball collided with bear
    else if (fixtureA->GetFilterData().groupIndex == BEAR_FILTER &&
        fixtureB->GetFilterData().groupIndex == BALL_FILTER ||
        fixtureA->GetFilterData().groupIndex == BALL_FILTER &&
        fixtureB->GetFilterData().groupIndex == BEAR_FILTER)
    {
        b2Filter destroyObjects;
        destroyObjects.groupIndex = POPPED_BALL_FILTER;
        fixtureA->SetFilterData(destroyObjects);
    }

//      if rope collided with ceiling
    else if (fixtureA->GetFilterData().groupIndex == FLOOR &&
        fixtureB->GetFilterData().groupIndex == ROPE_FILTER ||
        fixtureA->GetFilterData().groupIndex == ROPE_FILTER &&
        fixtureB->GetFilterData().groupIndex == FLOOR)
    {
        b2Filter destroyObjects;
        destroyObjects.groupIndex = TOUCH_WALL;
        fixtureA->SetFilterData(destroyObjects);
    }

//      if ball collided with ceiling
    //else if (fixtureA->GetFilterData().groupIndex == FLOOR &&
    //    fixtureB->GetFilterData().groupIndex == BALL_FILTER ||
    //    fixtureA->GetFilterData().groupIndex == BALL_FILTER &&
    //    fixtureB->GetFilterData().groupIndex == FLOOR)
    //{
    //    b2Filter destroyObjects;
    //    destroyObjects.groupIndex = POPPED_BALL_FILTER;
    //    fixtureB->SetFilterData(destroyObjects);
    //}
}