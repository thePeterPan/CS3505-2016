#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QDialog>

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
};

#endif // GAMEWINDOW_H
