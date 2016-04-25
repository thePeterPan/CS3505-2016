#include "gamewindow.h"
#include "ui_gamewindow.h"

gameWindow::gameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gameWindow)
{
    ui->setupUi(this);
    pm.load(":/images/backgrond2.jpg");
}

gameWindow::~gameWindow()
{
    delete ui;
}

void gameWindow::paintEvent(QPaintEvent *pe)
{
QPainter painter(this);
int width = this->ui->centralwidget->width();
int height = this->ui->centralwidget->height();
pm = pm.scaled(width, height, Qt::KeepAspectRatioByExpanding);
painter.drawPixmap(0, 0, pm);
}
