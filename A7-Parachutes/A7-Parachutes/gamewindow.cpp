#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "Box2D/Box2D.h"

gameWindow::gameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gameWindow)
{
    ui->setupUi(this);

}

gameWindow::~gameWindow()
{
    delete ui;
}
