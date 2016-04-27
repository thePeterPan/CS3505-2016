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

    if(checkLogin()){
     //level.show();
     emit showLevelDialogSignal();
     //this->close();
    }

}

bool MainWindow::checkLogin(){
    if(ui->inputPassword->text().count() ==0 || ui->inputUsername->text().count() ==0){

        ui->warningLabel->setText("User Name or Password CANNOT BE EMPTY");
        return false;
    }
    //else{
        //check login data from sever.

    return true;
}


void MainWindow::showRegistration() {
    emit showRegistrationSignal();
}
