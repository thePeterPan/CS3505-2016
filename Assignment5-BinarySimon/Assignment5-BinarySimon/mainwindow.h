#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QProgressBar>
#include <QMessageBox>

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

    game_model gm;

    // Used to keep track of the progress bar.
    int clickCount;

    void connectSignalsAndSlots();

private slots:
    void pushButton_start_clicked();
    void pushButton_blue_clicked();
    void pushButton_red_clicked();

    void state_changed(int state);

    void pattern_complete();
};

#endif // MAINWINDOW_H
