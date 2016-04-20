#include "gamewindow.h"
#include "ui_gamewindow.h"

gameWindow::gameWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gameWindow)
{
    ui->setupUi(this);


    QTimer::singleShot(100,this,SLOT(update()));
    Sprite sprite();
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
