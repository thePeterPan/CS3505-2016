#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "leveldialog.h"
#include "registrationdialog.h"
#include "networking.h"
#include "ui_mainwindow.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Networking *client_, QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    bool checkLogin();
    QPixmap pm;
    void paintEvent(QPaintEvent *);
    Networking *client;
    bool loginAnswer;

signals:
    void showRegistrationSignal();
    void showLevelDialogSignal();
    void checkLoginDataSignal(QString, QString);

private slots:
    void showRegistration();
    void showLevelDialog();

public slots:
    void loginAnswerReceived(bool);

};

#endif // MAINWINDOW_H
