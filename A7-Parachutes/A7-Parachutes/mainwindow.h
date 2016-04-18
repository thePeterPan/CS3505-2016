#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "leveldialog.h"
#include "registrationDialog.h"

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

private slots:
    void showLevelDialog();
};

#endif // MAINWINDOW_H
