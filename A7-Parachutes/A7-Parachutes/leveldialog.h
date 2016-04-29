#ifndef LEVELDIALOG_H
#define LEVELDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <QDebug>

#include "gamewindow.h"
#include "temporarysprite.h"
#include "networking.h"

namespace Ui {
class LevelSelectionDialog;
}

class LevelSelectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LevelSelectionDialog(Networking *client_, QWidget *parent = 0);
    ~LevelSelectionDialog();

private:
    Ui::LevelSelectionDialog *ui;
    Networking* client;

signals:
    void showGameWindowSignal();
    void addWordsFromFile(QStringList);

private slots:
    void showGameWindow();
    void openFile();
};

#endif // LEVELDIALOG_H
