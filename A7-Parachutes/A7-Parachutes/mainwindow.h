#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUrl>
#include <QDesktopServices>
#include <QProcess>
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
    bool loginAnswer;
    Networking *client;

signals:
    void showRegistrationSignal();
    void showLevelDialogSignal();
    void checkLoginDataSignal(QString, QString);
    void requestUserInfo(QString);
    void checkStudentOrTeacher(QString);
    void setOldScore(QString username);

private slots:
    void showRegistration();
    void showLevelDialog();

public slots:
    void loginAnswerReceived(QString,bool,bool);
    void getUserType(bool);

};

#endif // MAINWINDOW_H
