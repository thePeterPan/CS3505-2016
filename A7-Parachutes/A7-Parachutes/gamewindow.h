#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <QMediaPlayer>
#include <QMessageBox>

#include "Box2D/Box2D.h"

#include "sprite.h"
#include "networking.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();

    void startGame();
    void keyPressEvent(QKeyEvent* e);

private:
    Ui::GameWindow * ui;

    QPixmap pm,background;
    int scale;

    QTimer *timer;
    QMediaPlayer *player;

    bool pause;

    void connectSignalsAndSlots();

protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);

public slots:
    void receiveNewWord(QString word);      // Connected to GameLogic::newWord
    void receiveNewLevel(int level);        // Connected to GameLogic::newLevel
    void receiveFail();                     // Connected to GameLogic::failed
    void receiveVictory();                  // Connected to GameLogic::victory
    void actionTimerUpdated(QString message);   // Signal from GameLogic::updateActionTimer
    void scoreUpdated(QString score);           // Signal from GameLogic::updateScore

    void gameOver(int level, int score); // Signal from GameLogic::gameOver
    void levelCompleted(int level, int score);
    void pauseSwitch();
    void setOldScore(QString username, int level, int highscore);


signals:
    void letterTyped(QChar letter);             // Connected to GameLogic::newLetterTyped
    void newSize(int newWidth,int newHeight);   // Connected to GameLogic::changeSize
    void readyToPlay();                         // Connected to GameLogic::startGame
    void pauseGame();                           // Connected to GameLogic::pause
    void unPauseGame();                         // Connected to GameLogic::unPause and GameWindow::pauseSwitch
    void showLevelDial();                       // Connected to WindowController::gameOverReceived
    void addWordsFromFile(QStringList);         // Connected to GameLogic::addWordsFromFile
    //void restart();
    void paintWorld(QPainter * painter);

private slots:
    void on_actionPause_triggered();        // Signal from pause button
    void on_actionStart_triggered();        // Signal from start button                   // Signal from GameWindow::pauseGame

};

#endif // GAMEWINDOW_H
