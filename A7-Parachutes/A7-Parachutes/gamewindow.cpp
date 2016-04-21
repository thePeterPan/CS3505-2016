#include "gamewindow.h"
#include "ui_gamewindow.h"

gameWindow::gameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gameWindow)
{
    ui->setupUi(this);

    sprite = Sprite();

    QTimer::singleShot(100,this,SLOT(update()));

}

gameWindow::~gameWindow()
{
    delete ui;
}

void gameWindow::paintEvent(QPaintEvent *)
{
    game.World->Step(1/60.f, 8, 3);
    //b2World* world = World;
    for (b2Body* BodyIterator = game.World->GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
       {
            if (BodyIterator->GetType() == b2_dynamicBody)
            {
                QPainter painter(this);
                //sf::Sprite Sprite;
                //Sprite.SetTexture(BoxTexture);
                //Sprite.SetOrigin(16.f, 16.f);
                //Sprite.SetPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
                sprite.setX(30.0f * BodyIterator->GetPosition().x);
                sprite.setY(30.0f * BodyIterator->GetPosition().y);
                //Sprite.SetRotation(BodyIterator->GetAngle() * 180/b2_pi);
                //Window.Draw(Sprite);
                sprite.draw(&painter);

            }
            else
            {
                QPainter painter(this);
                Sprite GroundSprite;
                //GroundSprite.SetTexture(GroundTexture);
                //GroundSprite.SetOrigin(400.f, 8.f);
                //GroundSprite.SetPosition(BodyIterator->GetPosition().x * SCALE, BodyIterator->GetPosition().y * SCALE);
                GroundSprite.setX(BodyIterator->GetPosition().x * 30.0f);
                GroundSprite.setY(BodyIterator->GetPosition().y * 30.0f);
                //GroundSprite.SetRotation(180/b2_pi * BodyIterator->GetAngle());
                //Window.Draw(GroundSprite);
                GroundSprite.draw(&painter);

            }
        }
    //QPainter painter(this);
    //float32 xPos = game.getXPos();
    //float32 yPos = game.getYPos();
    //sprite.setX(xPos);
    //sprite.setY(yPos);
    //sprite.setX(sprite.getX() + 1);
    //sprite.setY(sprite.getY() + 1);
    //sprite.draw(&painter);

    QTimer::singleShot(100,this,SLOT(update()));
}


