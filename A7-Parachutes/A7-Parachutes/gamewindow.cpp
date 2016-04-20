#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "Box2D/Box2D.h"

gameWindow::gameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gameWindow)
{
    ui->setupUi(this);
<<<<<<< HEAD

=======
    sprite = Sprite();

    QTimer::singleShot(100,this,SLOT(update()));
>>>>>>> 429e69cac09facdc4850cd8907c9072041f011dc
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
