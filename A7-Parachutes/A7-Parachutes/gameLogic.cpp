#include "gameLogic.h"
#include "Box2D/Box2D.h"
#include <QDebug>

gameLogic::gameLogic(QObject *parent, float scale) : QObject(parent), SCALE(scale)
{
    sprites = QList<TemporarySprite>();
    setUpBox2D();
    SCALE = 100.0f;
    currentLevel = 1;
    getWordsFromDatabase(currentLevel);
}

void gameLogic::setUpBox2D()
{
    /** Prepare the world */
    b2Vec2 gravity = b2Vec2(0.0f, -9.8f);
    bool doSleep = true;

    World = new b2World(gravity);

    CreateGround(0.0f, 0.0f,2000.0f, 1.0f);
    CreateGround(0.0f,0.0f,1.0f,1400.0f);
    CreateGround(800.0f,0.0f,1.0f,1400.0f);
    CreateGround(0.0f,650.0f,2000.0f,1.0f);

}

void gameLogic::addWordToWorld()
{
    for(int i = 0; i < sprites.length(); i++)
    {
        World->DestroyBody(sprites[i].getBody());
    }
    sprites.clear();
    //NEEDS TO BE A GLOBAL:: WIDTH, HEIGHT
    float width = 800.0f;
    float height = 635.0f;
    float itemWidth = 80.0f;
    int spacing = width / currentWord.length();
    for(int i = 0; i < currentWord.length(); i++)
    {
        CreateBox(""+currentWord[i],i*spacing, height-itemWidth/2 + (rand() % 30),itemWidth,itemWidth, 0.1f,1.0f);
    }
}

/**
 * @brief gameLogic::CreateGround
 * @param x
 * @param y
 * @param width
 * @param height
 */
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

/**
 * NOTE: Box2D can only reliably simulate objects with size dimensions less than 10m.
 * Therefore, a large scaling number is needed in order to scale down or up from pixel size.
 * @brief gameLogic::CreateBox
 * @param letter
 * @param x
 * @param y
 * @param width
 * @param height
 * @param friction
 * @param restitution
 * @param density
 */
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

    TemporarySprite sprite(box,letter,(int)width);
    sprites.append(sprite);
}

b2World* gameLogic::getWorld()
{
    return World;
}

void gameLogic::getWordsFromDatabase(int level)
{
    words.clear();

    //test data
    if(level == 1)
    {
        words.append("parachuting");
        words.append("rainbow");
        words.append("cloudy");
        words.append("raindrop");
        words.append("parachute");
        words.append("snowflake");
        words.append("fantastic");
        words.append("airplane");
        words.append("sunlight");
        words.append("bumblebee");
        words.append("butterfly");
    }
    else if(level == 2)
    {
        words.append("flower");
        words.append("cucumber");
        words.append("tomato");
        words.append("icecream");
        words.append("pumpernickle");
        words.append("sesameseed");
        words.append("wind");
        words.append("sky");
        words.append("downpour");
        words.append("inkpot");
    }
    else if(level == 3)
    {
        words.append("feather");
        words.append("falcon");
        words.append("nest");
        words.append("caterpillar");
        words.append("frolic");
        words.append("dandelion");
        words.append("hyper");
        words.append("cartwheel");
        words.append("somersault");
        words.append("foursquare");
        words.append("blissful");
        words.append("delicious");
    }
    currentWord = words.first();
    currentWordIndex = 0;
    words.removeFirst();
    qDebug() << currentWord;
    addWordToWorld();
}

void gameLogic::newLetterTyped(QChar letter)
{
    if(letter == currentWord.at(currentWordIndex).toUpper())
    {
        qDebug() << letter << " was correct";
        if(currentWordIndex == currentWord.length() - 1)
        {
            if(words.isEmpty())
            {
                getWordsFromDatabase(++currentLevel);
                emit newLevel(currentLevel);
            }
            else
            {
                currentWord = words.first();
                currentWordIndex = 0;
                words.removeFirst();
                qDebug() << "new word: " << currentWord;
                addWordToWorld();

            }
        }
        else
        {
            currentWordIndex++;
        }
    }
    else
    {

       emit failed();
    }
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
    World->Step(1.0f/60.0f, 8, 3);

    for(int i = 0; i < sprites.length(); i++)
    {
        (currentWordIndex > i) ? painter->setPen(Qt::red) : painter->setPen(Qt::white);

        sprites[i].draw(painter);
    }
}
