#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Box2D/Box2D.h"

MainWindow::MainWindow(Networking *client_, QWidget *parent)
    : client(client_), QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pm.load(":/images/backgrond2.jpg");
    loginAnswer = false;

    connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::showLevelDialog);
    connect(ui->createAccountButton, &QPushButton::clicked, this, &MainWindow::showRegistration);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showLevelDialog()
{
    if(checkLogin()){

        client->requestIsTeacher(ui->inputUsername->text());
    }
}

bool MainWindow::checkLogin()
{
    if(ui->inputPassword->text().count() ==0 || ui->inputUsername->text().count() ==0){

        ui->warningLabel->setText("User Name or Password CANNOT BE EMPTY");
        return false;
    }
    else{

        //check login data from sever.
        emit checkLoginDataSignal(ui->inputUsername->text(), ui->inputPassword->text());
        emit requestUserInfo(ui->inputUsername->text());
        emit setOldScore(ui->inputUsername->text());
//        return loginAnswer;
    }
}

void MainWindow::getUserType(bool teacher)
{
    if(teacher)
    {
        qDebug() << "got teacher";
        //system("firefox localhost:8080");
    }
    else
    {
        //emit showLevelDialogSignal();

    }
}


void MainWindow::showRegistration()
{
    emit showRegistrationSignal();
}

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    int width = this->centralWidget()->width();
    int height = this->centralWidget()->height();
    pm = pm.scaled(width, height, Qt::KeepAspectRatioByExpanding);
    painter.drawPixmap(0,0,pm);
}

void MainWindow::loginAnswerReceived(QString username, bool answer, bool teacher)
{
    loginAnswer = answer;
    if(loginAnswer)
    {
        if(teacher)
            system("firefox localhost:8080");
        else
        {
            client->requestCurrentHighScore(username);
            emit showLevelDialogSignal();
        }

    }
    else
        ui->warningLabel->setText("Username and/or password is incorrect, please try again");

}
