void pushBallUP();
void Ball::pushBallUP()
{
    m_body->ApplyLinearImpulseToCenter(b2Vec2(0, m_body->GetMass() * -40), true);
}

void collision(Board* b);
void Ball::collision(Board* b)
{
    for (b2ContactEdge* edge = m_body->GetContactList(); edge; edge = edge->next)
    {
        auto angle = edge->contact->GetFixtureB()->GetBody()->GetAngle();  // ball angle

        if (edge->contact->GetFixtureA()->GetFilterData().groupIndex == -3) // If the ball touches the wall
        {
            edge->contact->GetFixtureB()->SetFriction(0);
            edge->contact->GetFixtureB()->GetBody()->SetAngularVelocity(0);
            b->colorBalll();

            //if (edge->contact->GetFixtureA()->GetFilterData().groupIndex == -2) // // If the ball touches the floor
            //{
            //    edge->contact->GetFixtureB()->GetBody()->ApplyLinearImpulseToCenter(b2Vec2(cos(angle)*2, sin(angle)*100), true);
            //}
        }
    }
}