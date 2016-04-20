#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "gameLogic.h"

gameWindow::gameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gameWindow)
{
    ui->setupUi(this);

    sprite = Sprite();

    QTimer::singleShot(100,this,SLOT(update()));

    gameLogic game;

}

gameWindow::~gameWindow()
{
    delete ui;
}

void gameWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    sprite.setX(sprite.getX() + 1);
    sprite.setY(sprite.getY() + 1);
    sprite.draw(&painter);

    QTimer::singleShot(100,this,SLOT(update()));
}


