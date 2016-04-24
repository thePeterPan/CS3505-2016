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
                //sprite.setX(BodyIterator->GetPosition().x*scale);
                //sprite.setY(this->height() - BodyIterator->GetPosition().y * scale);
                //Sprite.SetRotation(BodyIterator->GetAngle() * 180/b2_pi);
                //Window.Draw(Sprite);
                //sprite.draw(&painter);
                painter.setBrush(Qt::red);
                painter.drawRect(BodyIterator->GetPosition().x * scale, this->height() - BodyIterator->GetPosition().y * scale,100,100);
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
