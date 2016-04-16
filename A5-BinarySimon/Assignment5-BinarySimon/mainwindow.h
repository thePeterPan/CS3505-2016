#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QProgressBar>
#include <QLabel>
#include <QMessageBox>

#include <QStringList>      // QString, QStringList
#include <QTimer>           // QTimer
#include <QDebug>           // qDebug()
#include <QKeyEvent>        // QKeyEvent

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
    QPushButton *pushButton_green;
    QPushButton *pushButton_yellow;

    QProgressBar *progressBar;

    QLabel label_currentPlayer;

    // The game model and logic container.
    game_model gm;

    // Used to keep track of the progress bar.
    int currentPatternIndex = 0;

    void connectSignalsAndSlots();

    const QString BUTTON_BLUE_LIT_STYLE = "background-color: #0000FF;";
    const QString BUTTON_RED_LIT_STYLE = "background-color: #FF0000;";
    const QString BUTTON_GREEN_LIT_STYLE = "background-color: #00FF00;";
    const QString BUTTON_YELLOW_LIT_STYLE = "background-color: #FFFF00;";

    const QString BUTTON_BLUE_OFF_STYLE = "background-color: #0000CC;";
    const QString BUTTON_RED_OFF_STYLE = "background-color: #CC0000;";
    const QString BUTTON_GREEN_OFF_STYLE = "background-color: #00CC00;";
    const QString BUTTON_YELLOW_OFF_STYLE = "background-color: #CCCC00;";

private slots:
    void pushButton_start_clicked();

    void pushButton_blue_pressed();
    void pushButton_red_pressed();
    void pushButton_green_pressed();
    void pushButton_yellow_pressed();

    void pushButton_blue_released();
    void pushButton_red_released();
    void pushButton_green_released();
    void pushButton_yellow_released();

    void updateProgressBar(int value);
    void highlightNextColorFromPattern();
    void unhighlightButtons();

    void state_changed(int state);

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
