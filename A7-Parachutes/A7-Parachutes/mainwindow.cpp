#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Box2D/Box2D.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->loginButton, SIGNAL(clicked()), this, SLOT(showLevelDialog()));
    connect(ui->createAccountButton, SIGNAL(clicked()), this, SLOT(showRegistration()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showLevelDialog() {

    if(ui->inputPassword->text().count()!=0&&ui->inputUsername->text().count()!=0){
    level.show();
    this->close();
}
}

void MainWindow::showRegistration() {
    registration.show();
}

