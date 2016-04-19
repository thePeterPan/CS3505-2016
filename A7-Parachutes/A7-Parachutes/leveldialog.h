#ifndef LEVELDIALOG_H
#define LEVELDIALOG_H

#include <QDialog>
#include "gamewindow.h"

namespace Ui {
class levelDialog;
}

class levelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit levelDialog(QWidget *parent = 0);
    ~levelDialog();

private:
    Ui::levelDialog *ui;
    gameWindow game;

private slots:
    void showGameWindow();
};

#endif // LEVELDIALOG_H
