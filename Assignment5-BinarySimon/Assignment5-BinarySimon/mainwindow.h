#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QProgressBar>
#include <QLabel>
#include <QMessageBox>

#include <QStringList>
#include <QThread>
#include <QTimer>
#include <QDebug>

#include "game_model.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:


private:
    Ui::MainWindow *ui;

    QPushButton *pushButton_start;
    QPushButton *pushButton_red;
    QPushButton *pushButton_blue;

    QProgressBar *progressBar;

    QLabel label_currentPlayer;

    game_model gm;

    // Used to keep track of the progress bar.
    int clickCount;
    int currentPatternIndex = 0;
    void connectSignalsAndSlots();

private slots:
    void pushButton_start_clicked();
    void pushButton_blue_clicked();
    void pushButton_red_clicked();

    void state_changed(int state);

    void displayPattern();
    void updateProgressBar(int value);
    void pattern_complete();
};

#endif // MAINWINDOW_H
