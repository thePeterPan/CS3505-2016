#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QPainter>

namespace Ui {
class gameWindow;
}

class gameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit gameWindow(QWidget *parent = 0);
    ~gameWindow();
    void paintEvent(QPaintEvent *);

private:
    Ui::gameWindow *ui;
    QPixmap pm;
};

#endif // GAMEWINDOW_H
