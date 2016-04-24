#include "gameLogic.h"
#include "Box2D/Box2D.h"
#include <QDebug>

gameLogic::gameLogic(QObject *parent, float scale) : QObject(parent), SCALE(scale)
{
    sprites = QList<TemporarySprite>();
    setUpBox2D();
}

void gameLogic::setUpBox2D()
{
    /** Prepare the world */
    Gravity = b2Vec2(0.0f, -9.8f);
    bool doSleep = true;

    World = new b2World(Gravity);
    //World(Gravity);

    CreateGround(0.0f, 0.0f,2000.0f, 1.0f);
    CreateGround(0.0f,0.0f,1.0f,1200.0f);
    CreateGround(800.0f,0.0f,1.0f,1200.0f);
    CreateGround(0.0f,615.0f,2000.0f,1.0f);

    CreateBox("t",80.0f, 600.0f, 100.0f, 100.0f, 0.1f,1.0f);
    CreateBox("i",150.0f, 550.0f, 100.0f, 100.0f, 0.1f,1.0f);
    CreateBox("r",220.0f, 600.0f, 100.0f, 100.0f, 0.1f,1.0f);
    CreateBox("e",290.0f, 400.0f, 100.0f, 100.0f, 0.1f,1.0f);
    CreateBox("d",360.0f, 250.0f, 100.0f, 100.0f, 0.1f,1.0f);
    CreateBox("!",430.0f, 600.0f, 100.0f, 100.0f, 0.05f,1.0f);

}

void gameLogic::CreateGround(float x, float y, float width, float height)
{

    b2BodyDef groundDef;
    groundDef.position.Set(x/SCALE, y/SCALE);
    //bodyDef.type = b2_staticBody; // Static by default
    b2Body* ground = World->CreateBody(&groundDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox((width/2.0f)/SCALE, (height/2.0f)/SCALE); // Creates a box shape. Divide your desired width and height by 2.
    ground->CreateFixture(&groundBox,10.0f); // Apply the fixture definition
}

void gameLogic::CreateBox(QString letter, float x, float y, float width, float height, float friction, float restitution, float density)
{
    b2BodyDef boxDef;
    boxDef.type = b2_dynamicBody;
    boxDef.position.Set(x/SCALE, y/SCALE);
    b2Body* box = World->CreateBody(&boxDef);

    b2PolygonShape shape;
    shape.SetAsBox((width/2.0f)/SCALE,(height/2.0f)/SCALE);//2mx2m box
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    fixtureDef.restitution = restitution;
    box->CreateFixture(&fixtureDef);

    TemporarySprite sprite(box,letter);
    sprites.append(sprite);
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

void gameLogic::paintWorld(QPainter *painter)
{
    World->Step(1.f/120.f, 8, 3);

    for(int i = 0; i < sprites.length(); i++)
    {
        sprites[i].draw(painter);
    }
}
