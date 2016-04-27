#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    scale = 100;

    game = new GameLogic(this,this->width(),this->height());
    connectSignalsAndSlots();

    //game->testSignals();
    pm.load(":/images/nightBackground.jpg");

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()), this, SLOT(update()));
    timer->start(30);

    player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/images/bgm.mp3"));
    player->setVolume(50);
    player->play();

}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::startGame()
{

    emit readyToPlay();
}

void GameWindow::connectSignalsAndSlots()
{
    connect(this->game, &GameLogic::newWord,            this,       &GameWindow::receiveNewWord);
    connect(this->game, &GameLogic::newLevel,           this,       &GameWindow::receiveNewLevel);
    connect(this->game, &GameLogic::failed,             this,       &GameWindow::receiveFail);
    connect(this->game, &GameLogic::victory,            this,       &GameWindow::receiveVictory);
    connect(this->game, &GameLogic::updateActionTimer,  this,       &GameWindow::actionTimerUpdated);
    connect(this->game, &GameLogic::updateScore,        this,       &GameWindow::scoreUpdated);
    connect(this,       &GameWindow::letterTyped,       this->game, &GameLogic::newLetterTyped);
//    connect(this, SIGNAL(newHeight(int)), this->game, SLOT(changeHeight(int)));
    connect(this,       &GameWindow::newHeight,         this->game, &GameLogic::changeHeight);
//    connect(this, SIGNAL(newWidth(int)), this->game, SLOT(changeWidth(int)));
    connect(this,       &GameWindow::newWidth,          this->game, &GameLogic::changeWidth);
    connect(this,       &GameWindow::readyToPlay,       this->game, &GameLogic::startGame);
//    connect(this, SIGNAL(pauseGame()), this->game, SLOT(pause()));
    connect(this,       &GameWindow::pauseGame,         this->game, &GameLogic::pause);
//    connect(this, SIGNAL(unPauseGame()), this->game, SLOT(unPause()));
    connect(this,       &GameWindow::unPauseGame,       this->game, &GameLogic::unPause);
    connect(this->game, &GameLogic::gameOver,           this,       &GameWindow::on_gameOver_triggered);
}

void GameWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    int width = this->ui->centralwidget->width();
    int height = this->ui->centralwidget->height();
    pm = pm.scaled(width, height, Qt::KeepAspectRatioByExpanding);
    painter.drawPixmap(0, 0, pm);
    game->paintWorld(&painter);
}

void GameWindow::keyPressEvent(QKeyEvent *e)
{
    QChar letter = e->text()[0].toUpper();
    if (letter >= 'A' && letter <= 'Z')
    {
        emit letterTyped(letter);
    }
}

void GameWindow::receiveNewWord(QString word)
{
    qDebug() << "received " << word;
}

void GameWindow::receiveNewLevel(int level)
{
    qDebug() << "received " << level;
}

void GameWindow::receiveFail()
{
    qDebug() << "received fail";
}

void GameWindow::receiveVictory()
{
    qDebug() << "received victory";
}


void GameWindow::resizeEvent(QResizeEvent *)
{
    emit newHeight( ui->centralwidget->height());
    emit newWidth( ui->centralwidget->width());
}

void GameWindow::actionTimerUpdated(QString message)
{
    ui->actionTimer->setText(message);
}

void GameWindow::scoreUpdated(QString score)
{
    ui->actionScore->setText(score);
}

void GameWindow::on_actionPause_triggered()
{
    timer->stop();
    emit pauseGame();
}

void GameWindow::on_actionStart_triggered()
{
    if(timer->isActive())
        return;
    timer->start(30);
    emit unPauseGame();
}

void GameWindow::on_gameOver_triggered()
{
    timer->stop();
    emit pauseGame();
    QMessageBox msgBox;
    msgBox.setText("Game over! You Lose!");
    msgBox.exec();
    //show the level dialog
    //leveldial.show();
    //this is just to freeze the screen
    emit unPauseGame();
    emit showLevelDial();
}


