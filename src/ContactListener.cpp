#include "ContactListener.h"


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
}