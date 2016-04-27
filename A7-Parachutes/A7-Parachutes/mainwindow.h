#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "leveldialog.h"
#include "registrationdialog.h"

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
    bool checkLogin();

signals:
    void showRegistrationSignal();
    void showLevelDialogSignal();

private slots:
    void showRegistration();
    void showLevelDialog();
};

#endif // MAINWINDOW_H
