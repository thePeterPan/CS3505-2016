#ifndef LEVELDIALOG_H
#define LEVELDIALOG_H

#include <QDialog>

#include "gamewindow.h"
#include "temporarysprite.h"

namespace Ui {
class LevelSelectionDialog;
}

class LevelSelectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LevelSelectionDialog(QWidget *parent = 0);
    ~LevelSelectionDialog();

private:
    Ui::LevelSelectionDialog *ui;

signals:
    void showGameWindowSignal();

private slots:
    void showGameWindow();
};

#endif // LEVELDIALOG_H
