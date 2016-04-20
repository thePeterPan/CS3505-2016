#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QDialog>
#include "sprite.h"
#include "qtimer.h"

namespace Ui {
class gameWindow;
}

class gameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit gameWindow(QWidget *parent = 0);
    ~gameWindow();

private:
    Ui::gameWindow *ui;

    Sprite sprite;

protected:
    void paintEvent(QPaintEvent *);
};

#endif // GAMEWINDOW_H
