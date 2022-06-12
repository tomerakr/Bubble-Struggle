#include "ContactListener.h"
#include "Macros.h"
#include <iostream>

void ContactListener::BeginContact(b2Contact* contact)
{   
    auto fixtureA = contact->GetFixtureA();
    auto fixtureB = contact->GetFixtureB();

    if ((!fixtureA || !fixtureB) || (!fixtureA->GetBody() || !fixtureB->GetBody()))
    {
        return;
    }

//      if rope collided with ball
    if (fixtureA->GetFilterData().groupIndex == ROPE_FILTER &&
        fixtureB->GetFilterData().groupIndex == BALL_FILTER ||
        fixtureA->GetFilterData().groupIndex == ROPE_TOUCH_WALL &&
        fixtureB->GetFilterData().groupIndex == BALL_FILTER)
    {
        b2Filter destroyObjects;
        destroyObjects.groupIndex = POPPED_BALL_FILTER;
        fixtureA->SetFilterData(destroyObjects);
        fixtureB->SetFilterData(destroyObjects);
    }

//      if ball collided with bear
//      A - bear, B - rope
    else if (fixtureA->GetFilterData().groupIndex == BEAR_FILTER &&
            fixtureB->GetFilterData().groupIndex == BALL_FILTER)
    {
        b2Filter destroyObjects;
        destroyObjects.groupIndex = POPPED_BALL_FILTER;
        fixtureA->SetFilterData(destroyObjects);
    }

//      if bear collided with freeze gift
//      A - gift, B - bear
    else if (fixtureA->GetFilterData().groupIndex == GIFT_FREEZE_FILTER &&
            fixtureB->GetFilterData().groupIndex == BEAR_FILTER)
    {
        b2Filter freezeGift;
        freezeGift.groupIndex = GIFT_FREEZE_FILTER;
        fixtureB->SetFilterData(freezeGift);

        freezeGift.groupIndex = TOUCH_BEAR;
        fixtureA->SetFilterData(freezeGift);
    }

//      if bear collided with double-shot gift
//      A - gift, B - bear
    else if (fixtureA->GetFilterData().groupIndex == GIFT_DOUBLE_SHOT_FILTER &&
            fixtureB->GetFilterData().groupIndex == BEAR_FILTER)
    {
        b2Filter doubleRopeGift;

        doubleRopeGift.groupIndex = GIFT_DOUBLE_SHOT_FILTER;
        fixtureB->SetFilterData(doubleRopeGift);

        doubleRopeGift.groupIndex = TOUCH_BEAR;
        fixtureA->SetFilterData(doubleRopeGift);
    }

//      if bear collided with life gift
//      A - gift, B - bear
    else if (fixtureA->GetFilterData().groupIndex == GIFT_LIFE_FILTER &&
        fixtureB->GetFilterData().groupIndex == BEAR_FILTER)
    {
        b2Filter lifeGift;

        lifeGift.groupIndex = GIFT_LIFE_FILTER;
        fixtureB->SetFilterData(lifeGift);

        lifeGift.groupIndex = TOUCH_BEAR;
        fixtureA->SetFilterData(lifeGift);
    }

//      if bear collided with shield gift
//      A - gift, B - bear
    else if (fixtureA->GetFilterData().groupIndex == GIFT_SHIELD_FILTER &&
        fixtureB->GetFilterData().groupIndex == BEAR_FILTER)
    {
        b2Filter shieldGift;

        shieldGift.groupIndex = GIFT_SHIELD_FILTER;
        fixtureB->SetFilterData(shieldGift);

        shieldGift.groupIndex = TOUCH_BEAR;
        fixtureA->SetFilterData(shieldGift);
    }

//      if rope collided with wall
//      A - wall, B - rope
    else if (fixtureA->GetFilterData().groupIndex == TILE &&
        fixtureB->GetFilterData().groupIndex == ROPE_FILTER)
    {
        b2Filter destroyObjects;
        destroyObjects.groupIndex = ROPE_TOUCH_WALL;
      //  fixtureA->SetFilterData(destroyObjects);
        fixtureB->SetFilterData(destroyObjects);
    }

    //      if rope collided with wall
//      A - wall, B - ball
    else if (fixtureA->GetFilterData().groupIndex == TILE &&
            fixtureB->GetFilterData().groupIndex == BALL_FILTER)
    {
        b2Filter tileFilter;
        tileFilter.groupIndex = TILE;
        //  fixtureA->SetFilterData(destroyObjects);
        fixtureB->SetFilterData(tileFilter);
    }
}