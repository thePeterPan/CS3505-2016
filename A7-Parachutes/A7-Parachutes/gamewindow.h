#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <sprite.h>
#include <QPainter>
#include <QTimer>
#include "gameLogic.h"
#include "Box2D/Box2D.h"


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

    gameLogic game;

protected:
    void paintEvent(QPaintEvent *);
};

#endif // GAMEWINDOW_H
