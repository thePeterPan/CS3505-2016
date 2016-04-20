#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <sprite.h>
#include <QPainter>
#include <QTimer>

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

    Sprite sprite;

protected:
    void paintEvent(QPaintEvent *);
private slots:

};

#endif // GAMEWINDOW_H
