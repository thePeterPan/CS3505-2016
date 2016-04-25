#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "QMessageBox"
#include "QKeyEvent"

gameWindow::gameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gameWindow)
{
    ui->setupUi(this);

    scale = 100;

    game = new gameLogic(this,(float)scale);
    connectSignalsAndSlots();
    game->testSignals();
    pm.load(":/images/backgrond2.jpg");



}

gameWindow::~gameWindow()
{
    delete ui;
}

void gameWindow::connectSignalsAndSlots()
{
    //connect(ui->loginButton, SIGNAL(clicked()), this, SLOT(showLevelDialog()));
    //connect(ui->createAccountButton, SIGNAL(clicked()), this, SLOT(showRegistration()));
    //connect(ui->)
    connect(this->game, &gameLogic::newWord, this, &gameWindow::receiveNewWord);
    connect(this->game, &gameLogic::newLevel, this, &gameWindow::receiveNewLevel);
    connect(this->game, &gameLogic::failed, this, &gameWindow::receiveFail);
    connect(this->game, &gameLogic::victory, this, &gameWindow::receiveVictory);
    connect(this, &gameWindow::letterTyped, this->game, &gameLogic::newLetterTyped);

}

void gameWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    int width = this->ui->centralwidget->width();
    int height = this->ui->centralwidget->height();
    pm = pm.scaled(width, height, Qt::KeepAspectRatioByExpanding);
    painter.drawPixmap(0, 0, pm);
    game->paintWorld(&painter);
    QTimer::singleShot(30,this,SLOT(update()));
}

void gameWindow::keyPressEvent(QKeyEvent *e) {
    QChar letter = e->text()[0].toUpper();
    if (letter >= 'A' && letter <= 'Z'){
       // ui->listWidget->addItem(QString(letter));
        //ONLY SEND THIS if the box corresponding to
        //the letter they typed is in the target zone
        emit letterTyped(letter);
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
