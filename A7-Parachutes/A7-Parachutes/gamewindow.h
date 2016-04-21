#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <sprite.h>
#include <QPainter>
#include <QTimer>
#include "gameLogic.h"
#include "Box2D/Box2D.h"
#include <QDebug>


namespace Ui {
class gameWindow;
}

class gameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit gameWindow(QWidget *parent = 0);
    ~gameWindow();

private:
    Ui::gameWindow *ui;

    Sprite sprite,groundSprite;

    gameLogic* game;

    void connectSignalsAndSlots();

    void setListWidget(QString word);

protected:
    void paintEvent(QPaintEvent *);

public slots:
    void receiveNewWord(QString word); //Connected to gameLogic::newWord
    void receiveNewLevel(int level);//Connected to gameLogic::newLevel
    void receiveFail();//Connected to gameLogic::failed
    void receiveVictory();//Connected to gameLogic::victory

signals:
    void letterTyped(char letter);
};

#endif // GAMEWINDOW_H
