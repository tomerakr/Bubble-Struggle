#include "Ball.h"
#include "Board.h"
#include <time.h>
#include <math.h>

float pixelToMeter(const int pixels) { return pixels * pToMeter; }

Ball::Ball(Board* board, int direction, float radius, sf::Color color, sf::Vector2f pos)
	:m_board(board)
{
	m_ball.setPosition(sf::Vector2f(pos));
	m_ball.setRadius(radius);
	m_ball.setFillColor(color);

    //set up dynamic body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.x, pos.y);
    bodyDef.angularVelocity = direction; // set with true? can we +a and -a?
    //bodyDef.linearVelocity.y = 7;
    m_body = m_board->getWorld()->CreateBody(&bodyDef);

    //add circle fixture
    m_ball2D.m_p.Set(1.f, 1.f);
    m_ball2D.m_radius = pixelToMeter(radius); //needs convert
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &m_ball2D;
    fixtureDef.density = 1.f;
    fixtureDef.friction = 0.4f;
    fixtureDef.restitution = 1.f;
    fixtureDef.filter.groupIndex = -1;
 
    m_body->CreateFixture(&fixtureDef);
}

void Ball::split()
{
    m_board->getWorld()->DestroyBody(m_body); //why here
    m_board->addBalls(m_ball.getRadius() / 2, sf::Color::Magenta, m_ball.getPosition());
}

void Ball::updatePos()
{
    auto pos = m_body->GetPosition();
    m_ball.setPosition(pos.x, pos.y);
}

void Ball::colorBall() //for DEBUG
{
    srand(time(NULL));

    m_ball.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
}

void Ball::collision(Board* board)
{
    for (b2ContactEdge* edge = m_body->GetContactList(); edge; edge = edge->next)
    {
        //auto angle = edge->contact->GetFixtureB()->GetBody()->GetAngle();  // ball angle

        if (edge->contact->GetFixtureA()->GetFilterData().groupIndex == -3) // If the ball touches the wall
        {
            edge->contact->GetFixtureB()->SetFriction(0);
            edge->contact->GetFixtureB()->GetBody()->SetAngularVelocity(0);
            board->colorBalll();

            //if (edge->contact->GetFixtureA()->GetFilterData().groupIndex == -2) // // If the ball touches the floor
            //{
            //    edge->contact->GetFixtureB()->GetBody()->ApplyLinearImpulseToCenter(b2Vec2(cos(angle)*2, sin(angle)*100), true);
            //}
        }
    }
}

void Ball::pushBallUP()
{
    m_body->ApplyLinearImpulseToCenter(b2Vec2(0, m_body->GetMass()*-40), true);
}

//Ball::~Ball()
//{
//    m_board->getWorld()->DestroyBody(m_body);
//}