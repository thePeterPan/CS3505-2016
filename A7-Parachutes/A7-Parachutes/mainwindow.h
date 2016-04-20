#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "leveldialog.h"
#include "registrationDialog.h"
#include "sprite.h"
#include "qtimer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    levelDialog level;
    RegistrationDialog registration;
    Sprite sprite;

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void showLevelDialog();
    void showRegistration();
};

#endif // MAINWINDOW_H
