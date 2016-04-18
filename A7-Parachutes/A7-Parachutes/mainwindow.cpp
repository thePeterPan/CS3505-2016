#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    level.show();
    this->close();
}
