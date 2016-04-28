#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    pause = false;
    scale = 100;

    game = new GameLogic(this,this->width(),this->height());
    connectSignalsAndSlots();

    //game->testSignals();
    pm.load(":/images/nightBackground.jpg");
    int width = this->width();
    int height = this->height() - ui->toolBar->height();
    background = pm.scaled(width, height, Qt::KeepAspectRatioByExpanding);

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()), this, SLOT(update()));

    player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/images/bgm.mp3"));
    player->setVolume(50);
    player->play();

}

GameWindow::~GameWindow()
{
    delete ui;
    delete timer;
    delete game;
    delete player;
}

void GameWindow::startGame()
{
    emit readyToPlay();
    timer->start(30);
    pause = false;
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
    connect(this,       &GameWindow::newSize,           this->game, &GameLogic::changeSize);
    connect(this,       &GameWindow::readyToPlay,       this->game, &GameLogic::startGame);
    connect(this,       &GameWindow::pauseGame,         this->game, &GameLogic::pause);
    connect(this,       &GameWindow::pauseGame,         this,       &GameWindow::pauseSwitch);
    connect(this,       &GameWindow::unPauseGame,       this->game, &GameLogic::unPause);
    connect(this,       &GameWindow::unPauseGame,       this,       &GameWindow::pauseSwitch);
    connect(this->game, &GameLogic::gameOver,           this,       &GameWindow::on_gameOver_triggered);
}

void GameWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, ui->toolBar->height(), background);
    game->paintWorld(&painter);
}

void GameWindow::keyPressEvent(QKeyEvent *e)
{
    if(!pause){
    QChar letter = e->text()[0].toUpper();
        if (letter >= 'A' && letter <= 'Z')
        {
            emit letterTyped(letter);
        }
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
    int width = this->width();
    int height = this->height();
    background = pm.scaled(width, height, Qt::KeepAspectRatioByExpanding);
    emit newSize(width, height);
    this->update();
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
    emit showLevelDial();
}

void GameWindow::pauseSwitch()
{
    pause = !pause;
}

