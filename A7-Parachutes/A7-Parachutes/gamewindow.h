#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <sprite.h>
#include <QPainter>
#include <QTimer>
#include "gameLogic.h"
#include "Box2D/Box2D.h"
#include <QDebug>
#include <QKeyEvent>


namespace Ui {
class gameWindow;
}

class gameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit gameWindow(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent* e);
    ~gameWindow();

private:
    Ui::gameWindow *ui;

    gameLogic* game;

    QPixmap pm;

    int scale;

    void connectSignalsAndSlots();

    void setListWidget(QString word);

    QTimer * timer;

protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);

public slots:
    void receiveNewWord(QString word); //Connected to gameLogic::newWord
    void receiveNewLevel(int level);//Connected to gameLogic::newLevel
    void receiveFail();//Connected to gameLogic::failed
    void receiveVictory();//Connected to gameLogic::victory

signals:
    void letterTyped(QChar letter);
    void newHeight(int);
    void newWidth(int);
};

#endif // GAMEWINDOW_H
