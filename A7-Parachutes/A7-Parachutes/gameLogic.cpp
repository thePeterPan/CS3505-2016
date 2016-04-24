#include "gameLogic.h"
#include "Box2D/Box2D.h"
#include <QDebug>

gameLogic::gameLogic(QObject *parent, float scale) : QObject(parent), SCALE(scale)
{
    setUpBox2D();
}

void gameLogic::setUpBox2D()
{
    /** Prepare the world */
    Gravity = b2Vec2(0.0f, -9.8f);
    bool doSleep = true;

    World = new b2World(Gravity);
    //World(Gravity);

    CreateGround(400.0f, 20.0f);
    CreateBox(80.0f, 600.0f, 100.0f, 100.0f, 0.2f,1.2f);
    CreateBox(150.0f, 600.0f, 100.0f, 100.0f, 0.35f,1.2f);
    CreateBox(220.0f, 600.0f, 100.0f, 100.0f, 0.4f,1.2f);
    CreateBox(290.0f, 600.0f, 100.0f, 100.0f, 0.55f,1.2f);
    CreateBox(360.0f, 600.0f, 100.0f, 100.0f, 0.7f,1.2f);
    CreateBox(430.0f, 600.0f, 100.0f, 100.0f, 0.85f,1.2f);

}

void gameLogic::CreateGround(float width, float height)
{

    b2BodyDef groundDef;
    groundDef.position.Set(0.0f, -10.f);
    //bodyDef.type = b2_staticBody; // Static by default
    b2Body* ground = World->CreateBody(&groundDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox((width/2.0f), (height/2.0f)); // Creates a box shape. Divide your desired width and height by 2.
    //b2FixtureDef FixtureDef;
    //FixtureDef.density = 0.f;  // Sets the density of the body
    //FixtureDef.shape = &groundBox; // Sets the shape
    ground->CreateFixture(&groundBox,0.0f); // Apply the fixture definition
}

void gameLogic::CreateBox(float x, float y, float width, float height, float friction, float density)
{
    b2BodyDef boxDef;
    boxDef.type = b2_dynamicBody;
    boxDef.position.Set(x/SCALE, y/SCALE);
    b2Body* box = World->CreateBody(&boxDef);

    b2PolygonShape shape;
    shape.SetAsBox(width/SCALE,height/SCALE);//2mx2m box
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    box->CreateFixture(&fixtureDef);
    /*
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(1.0f, 4.0f);
        b2Body* body = World->CreateBody(&bodyDef);

        b2PolygonShape shape;
        shape.SetAsBox(1.0f,1.0f);//2mx2m box
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.7f;
        body->CreateFixture(&fixtureDef);
        */
}

b2World* gameLogic::getWorld()
{
    return World;
}

void gameLogic::newLetterTyped(char letter)
{
    // If the new letter is incorrect || the position of the lowest sprite on GUI is bad:
    //      emit failed();
    // If that's the end of the word, but the QQueue is not empty:
    //      emit newWord on the next word
    // If that's the end of the word and the QQueue is empty;
    //      emit newLevel to update GUI and Database
    //      If any levels left:
    //          get next words from database
    //          send first word to gui
    //      otherwise
    //          you won, game over.
    // Otherwise,
    //      Word isn't over, do nothing and wait for next letter typed
}

void gameLogic::testSignals()
{
    qDebug() << "emitting signals";
    emit newWord("tanner");
    emit newLevel(1);
    emit failed();
    emit victory();
}
