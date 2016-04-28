#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "leveldialog.h"
#include "registrationdialog.h"
#include "networking.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Networking *client, QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    bool checkLogin();
     QPixmap pm;
     void paintEvent(QPaintEvent *);
     Networking* client;

signals:
    void showRegistrationSignal();
    void showLevelDialogSignal();

private slots:
    void showRegistration();
    void showLevelDialog();
};

#endif // MAINWINDOW_H
