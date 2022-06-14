#include "ContactListener.h"

void ContactListener::BeginContact(b2Contact* contact)
{
    void* userDataA = contact->GetFixtureA()->GetBody()->GetUserData();
    auto objA = static_cast<GameObject*>(userDataA);

    void* userDataB = contact->GetFixtureB()->GetBody()->GetUserData();
    auto objB = static_cast<GameObject*>(userDataB);

    if (!objA || !objB)
    {
        return;
    }

    CollisionHandler::instance().handleCollision(objA, objB);

////      if rope collided with ball
//    if (fixtureA->GetFilterData().groupIndex == ROPE_FILTER &&
//        fixtureB->GetFilterData().groupIndex == BALL_FILTER ||
//        fixtureA->GetFilterData().groupIndex == ROPE_TOUCH_WALL &&
//        fixtureB->GetFilterData().groupIndex == BALL_FILTER)
//    {
//        b2Filter destroyObjects;
//        destroyObjects.groupIndex = POPPED_BALL_FILTER;
//        fixtureA->SetFilterData(destroyObjects);
//        fixtureB->SetFilterData(destroyObjects);
//    }
//
////      if ball collided with bear
////      A - bear, B - ball
//    else if (fixtureA->GetFilterData().groupIndex == BEAR_FILTER &&
//            fixtureB->GetFilterData().groupIndex == BALL_FILTER)
//    {
//        b2Filter destroyObjects;
//        destroyObjects.groupIndex = POPPED_BALL_FILTER;
//        fixtureA->SetFilterData(destroyObjects);
//    }
//
////      if bear collided with freeze gift
////      A - bear, B - bear
//    else if (fixtureA->GetFilterData().groupIndex == BEAR_FILTER &&
//        fixtureB->GetFilterData().groupIndex == FREEZE_FILTER)
//    {
//        b2Filter freezeGift;
//        freezeGift.groupIndex = FREEZE_FILTER;
//        fixtureA->SetFilterData(freezeGift);
//
//        freezeGift.groupIndex = TOUCH_BEAR;
//        fixtureB->SetFilterData(freezeGift);
//    }
//
////      if bear collided with double-shot gift
////      A - bear, B - bear
//    else if (fixtureA->GetFilterData().groupIndex == BEAR_FILTER &&
//        fixtureB->GetFilterData().groupIndex == DOUBLE_SHOT_FILTER)
//    {
//        b2Filter doubleRopeGift;
//
//        doubleRopeGift.groupIndex = DOUBLE_SHOT_FILTER;
//        fixtureA->SetFilterData(doubleRopeGift);
//
//        doubleRopeGift.groupIndex = TOUCH_BEAR;
//        fixtureB->SetFilterData(doubleRopeGift);
//    }
//
////      if bear collided with life gift
////      A - bear, B - bear
//    else if (fixtureA->GetFilterData().groupIndex == BEAR_FILTER &&
//        fixtureB->GetFilterData().groupIndex == LIFE_FILTER)
//    {
//        b2Filter lifeGift;
//
//        lifeGift.groupIndex = LIFE_FILTER;
//        fixtureA->SetFilterData(lifeGift);
//
//        lifeGift.groupIndex = TOUCH_BEAR;
//        fixtureB->SetFilterData(lifeGift);
//    }
//
////      if bear collided with shield gift
////      A - bear, B - bear
//    else if (fixtureA->GetFilterData().groupIndex == BEAR_FILTER &&
//        fixtureB->GetFilterData().groupIndex == SHIELD_FILTER) 
//    {
//        b2Filter shieldGift;
//
//        shieldGift.groupIndex = SHIELD_FILTER;
//        fixtureA->SetFilterData(shieldGift);
//
//        shieldGift.groupIndex = TOUCH_BEAR;
//        fixtureB->SetFilterData(shieldGift);
//    }
//
////      if rope collided with wall
////      A - wall, B - rope
//    else if (fixtureA->GetFilterData().groupIndex == TILE &&
//        fixtureB->GetFilterData().groupIndex == ROPE_FILTER)
//    {
//        b2Filter destroyObjects;
//        destroyObjects.groupIndex = ROPE_TOUCH_WALL;
//        fixtureB->SetFilterData(destroyObjects);
//    }
//
//
//    else if (fixtureA->GetFilterData().groupIndex == BEAR_FILTER &&
//        fixtureB->GetFilterData().groupIndex == TILE)
//    {
//        b2Filter hitAWall;
//
//        hitAWall.groupIndex = BEAR_HIT_WALL;
//        fixtureA->SetFilterData(hitAWall);
//    }
//
//
//    //      if rope collided with wall
////      A - wall, B - ball
//    else if (fixtureA->GetFilterData().groupIndex == TILE &&
//            fixtureB->GetFilterData().groupIndex == BALL_FILTER)
//    {
//        //b2Filter tileFilter;
//        //tileFilter.groupIndex = TILE;
//        ////  fixtureA->SetFilterData(destroyObjects);
//        //fixtureB->SetFilterData(tileFilter);
//    }
}