#include "gamewindow.h"
#include "ui_gamewindow.h"

gameWindow::gameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gameWindow)
{
    ui->setupUi(this);

    scale = 100;

    game = new gameLogic(this,(float)scale);
    sprite = Sprite();
    //groundSprite = Sprite();
    connectSignalsAndSlots();
    //QTimer::singleShot(100,this,SLOT(update()));
    game->testSignals();

    testBox2D();

}

gameWindow::~gameWindow()
{
    delete ui;
}

void gameWindow::connectSignalsAndSlots()
{
    qDebug() << "connecting signals and slots";
    //connect(ui->loginButton, SIGNAL(clicked()), this, SLOT(showLevelDialog()));
    //connect(ui->createAccountButton, SIGNAL(clicked()), this, SLOT(showRegistration()));
    connect(this->game, &gameLogic::newWord, this, &gameWindow::receiveNewWord);
    connect(this->game, &gameLogic::newLevel, this, &gameWindow::receiveNewLevel);
    connect(this->game, &gameLogic::failed, this, &gameWindow::receiveFail);
    connect(this->game, &gameLogic::victory, this, &gameWindow::receiveVictory);
}

void gameWindow::paintEvent(QPaintEvent *)
{
    game->World->Step(1.f/60.f, 8, 3);
    QPainter painter(this);

    //b2World* world = World;
    for (b2Body* BodyIterator = game->World->GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
       {
            if (BodyIterator->GetType() == b2_dynamicBody)
            {
                //sf::Sprite Sprite;
                //Sprite.SetTexture(BoxTexture);
                //Sprite.SetOrigin(16.f, 16.f);
                //Sprite.SetPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
                sprite.setX(BodyIterator->GetPosition().x*scale);
                sprite.setY(this->height() - BodyIterator->GetPosition().y * scale);
                //Sprite.SetRotation(BodyIterator->GetAngle() * 180/b2_pi);
                //Window.Draw(Sprite);
                sprite.draw(&painter);
                qDebug("%4.2f %4.2f \n",BodyIterator->GetPosition().x,BodyIterator->GetPosition().y);


            }
            else
            {
                painter.setBrush(Qt::blue);
                painter.drawRect(BodyIterator->GetPosition().x * scale,this->height() - BodyIterator->GetPosition().y * scale,400,20);
                //GroundSprite.SetTexture(GroundTexture);
                //GroundSprite.SetOrigin(400.f, 8.f);
                //GroundSprite.SetPosition(BodyIterator->GetPosition().x * SCALE, BodyIterator->GetPosition().y * SCALE);
                //groundSprite.setX(BodyIterator->GetPosition().x * 30.0f);
                //groundSprite.setY(BodyIterator->GetPosition().y * 30.0f);
                //GroundSprite.SetRotation(180/b2_pi * BodyIterator->GetAngle());
                //Window.Draw(GroundSprite);
                //groundSprite.draw(&painter);

            }

        }
    //QPainter painter(this);
    //float32 xPos = game->getXPos();
    //float32 yPos = game->getYPos();
    //sprite.setX(xPos);
    //sprite.setY(yPos);
    //sprite.setX(sprite.getX() + 1);
    //sprite.setY(sprite.getY() + 1);
    //sprite.draw(&painter);

    QTimer::singleShot(100,this,SLOT(update()));
}

void gameWindow::testBox2D()
{
    b2Vec2 Gravity(0.0f, -10.f);

    b2World World(Gravity);

    int SCALE =1.0f;

    float width = 100.f;
    float height = 20.f;

    b2BodyDef bodyDef;
    bodyDef.position.Set(0.0f, -10.f);
    //bodyDef.type = b2_staticBody; // Static by default
    b2Body* body = World.CreateBody(&bodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox((width/2.0f)/SCALE, (height/2.0f)/SCALE); // Creates a box shape. Divide your desired width and height by 2.
    //b2FixtureDef FixtureDef;
    //FixtureDef.density = 0.f;  // Sets the density of the body
    //FixtureDef.shape = &groundBox; // Sets the shape
    body->CreateFixture(&groundBox,0.0f); // Apply the fixture definition

    b2BodyDef bodyDef2;
    bodyDef2.type = b2_dynamicBody;
    bodyDef2.position.Set(0.0f, 40.0f);
    b2Body* body2 = World.CreateBody(&bodyDef2);

    b2PolygonShape shape;
    shape.SetAsBox(1.0f,1.0f);//2mx2m box
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 10.0f;
    fixtureDef.friction = 0.2f;
    body2->CreateFixture(&fixtureDef);

    for (int32 i = 0; i < 600; ++i)
    {   World.Step(1.0f / 60.0f, 6, 2);
        b2Vec2 position = body2->GetPosition();
        float32 angle = body2->GetAngle();
        qDebug("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
    }

    qDebug()<<this->height();

    /*
    // Define the gravity vector.
    b2Vec2 gravity(0.0f, -10.0f);

    // Construct a world object, which will hold and simulate the rigid bodies.
    b2World world(gravity);

    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    // Define the ground box shape.
    b2PolygonShape groundBox;

    // The extents are the half-widths of the box.
    groundBox.SetAsBox(50.0f, 10.0f);

    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);
    b2Body* body = world.CreateBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    // Override the default friction.
    fixtureDef.friction = 0.3f;

    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);

    // Prepare for simulation. Typically we use a time step of 1/60 of a
    // second (60Hz) and 10 iterations. This provides a high quality simulation
    // in most game scenarios.
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    // This is our little game loop.
    for (int32 i = 0; i < 60; ++i)
    {
            // Instruct the world to perform a single step of simulation.
            // It is generally best to keep the time step and iterations fixed.
            world.Step(timeStep, velocityIterations, positionIterations);

            // Now print the position and angle of the body.
            b2Vec2 position = body->GetPosition();
            float32 angle = body->GetAngle();

            qDebug("%4.2f %4.2f %4.2f", position.x, position.y, angle);
    }*/
}

void gameWindow::setListWidget(QString word)
{
    for(auto i = 0; i < word.length(); i++)
    {
        ui->listWidget->item(i)->setText(word.at(i));
    }
}

void gameWindow::receiveNewWord(QString word)
{
    qDebug() << "received " << word;
}

void gameWindow::receiveNewLevel(int level)
{
    qDebug() << "received " << level;
}

void gameWindow::receiveFail()
{
    qDebug() << "received fail";

}

void gameWindow::receiveVictory()
{
    qDebug() << "received victory";
}
