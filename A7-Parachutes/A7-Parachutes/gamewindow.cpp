#include "gamewindow.h"
#include "ui_gamewindow.h"

gameWindow::gameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gameWindow)
{
    ui->setupUi(this);

    scale = 100;

    game = new gameLogic(this,(float)scale);
    sprite = Sprite();
    //groundSprite = Sprite();
    connectSignalsAndSlots();
    //QTimer::singleShot(100,this,SLOT(update()));
    game->testSignals();


}

gameWindow::~gameWindow()
{
    delete ui;
}

void gameWindow::connectSignalsAndSlots()
{
    qDebug() << "connecting signals and slots";
    //connect(ui->loginButton, SIGNAL(clicked()), this, SLOT(showLevelDialog()));
    //connect(ui->createAccountButton, SIGNAL(clicked()), this, SLOT(showRegistration()));
    connect(this->game, &gameLogic::newWord, this, &gameWindow::receiveNewWord);
    connect(this->game, &gameLogic::newLevel, this, &gameWindow::receiveNewLevel);
    connect(this->game, &gameLogic::failed, this, &gameWindow::receiveFail);
    connect(this->game, &gameLogic::victory, this, &gameWindow::receiveVictory);
}

void gameWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    game->paintWorld(&painter);
    QTimer::singleShot(30,this,SLOT(update()));
}

void gameWindow::setListWidget(QString word)
{
    for(auto i = 0; i < word.length(); i++)
    {
        ui->listWidget->item(i)->setText(word.at(i));
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
