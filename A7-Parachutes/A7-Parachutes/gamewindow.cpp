#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    pause = false;
    scale = 100;

    connectSignalsAndSlots();

    pm.load(":/images/nightBackground.jpg");
    int width = this->width();
    int height = this->height() - ui->toolBar->height();
    background = pm.scaledToHeight(height);

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
    connect(this,  &GameWindow::unPauseGame, this,  &GameWindow::pauseSwitch);
    connect(this,  &GameWindow::pauseGame,   this,  &GameWindow::pauseSwitch);

}

// ===== EVENTS ===== //

void GameWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, ui->toolBar->height(), background);
    emit paintWorld(&painter);
}

void GameWindow::resizeEvent(QResizeEvent *)
{
    int width = this->width();
    int height = this->height();
    background = pm.scaledToHeight(height);
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

void GameWindow::on_actionPause_triggered()
{
    if(!pause)
    {
        timer->stop();
        emit pauseGame();
    }

}

void GameWindow::on_actionStart_triggered()
{
    if(pause)
    {
        if(timer->isActive())
            return;
        timer->start(30);
        emit unPauseGame();
    }
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
    if(level > 0)
    {
        timer->stop();
        emit pauseGame();
        QMessageBox msgBox;
        msgBox.setMinimumSize(150,75);
        QString s = "Congratulations! You beat level " + QString::number(level) + "!";
        msgBox.setText(s);
        msgBox.exec();
        emit showLevelDial();
    }
}

void GameWindow::pauseSwitch()
{
    pause = !pause;
}

void GameWindow::setOldScore(QString username, int level, int highscore){

    QString s = QString::number(highscore);
    QString l = QString::number(level);
    ui->actionOldScore->setText("Old Score: "+s);
    ui->actionLevel->setText("Level:"+l);
}
