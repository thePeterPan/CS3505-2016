#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <QMediaPlayer>
#include <QMessageBox>
#include <QKeyEvent>

#include "Box2D/Box2D.h"

#include "gamelogic.h"
#include "sprite.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent* e);

    void startGame();
    ~GameWindow();

private:
    Ui::GameWindow *ui;

    GameLogic* game;

    QPixmap pm,background;

    int scale;

    void connectSignalsAndSlots();

    void setListWidget(QString word);

    QTimer * timer;

    QMediaPlayer* player;

    bool pause;


protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);

public slots:

    void receiveNewWord(QString word);  // Connected to gameLogic::newWord
    void receiveNewLevel(int level);    // Connected to gameLogic::newLevel
    void receiveFail();                 // Connected to gameLogic::failed
    void receiveVictory();              // Connected to gameLogic::victory
    void actionTimerUpdated(QString message);
    void scoreUpdated(QString score);

signals:
    void letterTyped(QChar letter);
    void newSize(int newWidth,int newHeight);
    void readyToPlay();

    void pauseGame();
    void unPauseGame();
    void showLevelDial();
    //void restart();
private slots:
    void on_actionPause_triggered();
    void on_actionStart_triggered();
    void on_gameOver_triggered();
    void pauseSwitch();
};

#endif // GAMEWINDOW_H
