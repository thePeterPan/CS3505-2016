#include "gameLogic.h"
#include "Box2D/Box2D.h"
#include <QDebug>


gameLogic::gameLogic(QObject *parent) : QObject(parent)
{
    setUpBox2D();
    SCALE = 30.0f;
}

void gameLogic::setUpBox2D()
{
    /** Prepare the world */
        Gravity = b2Vec2(0.f, 9.8f);
        bool doSleep = true;

        World = new b2World(Gravity);
        //World(Gravity);

        CreateGround(*World, 400.f, 500.f);
        CreateBox(*World, 0, 0);


}

void gameLogic::CreateGround(b2World& World, float X, float Y)
{
        b2BodyDef BodyDef;
        BodyDef.position = b2Vec2(X/30.f, Y/30.f);
        BodyDef.type = b2_staticBody;
        b2Body* Body = World.CreateBody(&BodyDef);
        b2PolygonShape Shape;
        Shape.SetAsBox((800.f/2)/SCALE, (16.f/2)/SCALE); // Creates a box shape. Divide your desired width and height by 2.
        b2FixtureDef FixtureDef;
        FixtureDef.density = 0.f;  // Sets the density of the body
        FixtureDef.shape = &Shape; // Sets the shape
        Body->CreateFixture(&FixtureDef); // Apply the fixture definition
}

void gameLogic::CreateBox(b2World& World, int MouseX, int MouseY)
{
        b2BodyDef BodyDef;
        BodyDef.type = b2_dynamicBody;
        BodyDef.position = b2Vec2(13.0f, MouseY/SCALE);
        b2Body* Body = World.CreateBody(&BodyDef);

        b2PolygonShape Shape;
        Shape.SetAsBox(100.f,100.f);
        b2FixtureDef FixtureDef;
        FixtureDef.density = 1.0f;
        FixtureDef.friction = 0.7f;
        FixtureDef.shape = &Shape;
        Body->CreateFixture(&FixtureDef);
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
