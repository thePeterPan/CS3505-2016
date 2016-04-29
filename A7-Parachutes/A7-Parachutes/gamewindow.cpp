#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(Networking *client_, QWidget *parent)
    : client(client_), QMainWindow(parent), ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    pause = false;
    scale = 100;

    game = new GameLogic(this,this->width(),this->height());
    connectSignalsAndSlots();

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
    connect(this->game, &GameLogic::gameOver,           this,       &GameWindow::gameOver);
    connect(this,       &GameWindow::addWordsFromFile,  this->game, &GameLogic::addWordsFromFile);
    connect(this->game, &GameLogic::levelCompleted,     this,       &GameWindow::levelCompleted);

}

// ===== EVENTS ===== //

void GameWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, ui->toolBar->height(), background);
    game->paintWorld(&painter);
}

void GameWindow::resizeEvent(QResizeEvent *)
{
    int width = this->width();
    int height = this->height();
    background = pm.scaled(width, height, Qt::KeepAspectRatioByExpanding);
    emit newSize(width, height);
    this->update();
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

// ===== SLOTS ===== //

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

void GameWindow::actionTimerUpdated(QString message)
{
    ui->actionTimer->setText(message);
}

void GameWindow::scoreUpdated(QString score)
{
    ui->actionScore->setText(score);
}

void GameWindow::catchAddWordsFromLevel(QStringList list)
{
  emit addWordsFromFile(list);
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

void GameWindow::gameOver(int level, int score)
{
    timer->stop();
    emit pauseGame();
    QMessageBox msgBox;
    msgBox.setMinimumSize(150,75);
    QString s = "Game over! You Lose! Score: " + QString::number(score);
    qDebug() << s;
    msgBox.setText(s);
    msgBox.setInformativeText("You beat level: " + QString::number(level));
    msgBox.exec();
    emit showLevelDial();
}

void GameWindow::levelCompleted(int level, int score)
{
    timer->stop();
    emit pauseGame();
    QMessageBox msgBox;
    msgBox.setMinimumSize(150,75);
    QString s = "Congratulations! You beat level " + QString::number(level) + "! \n Score: " + QString::number(score);
    msgBox.setText(s);
    msgBox.exec();
    emit showLevelDial();
}

void GameWindow::pauseSwitch()
{
    pause = !pause;
}


