#ifndef WINDOWCONTROLLER_H
#define WINDOWCONTROLLER_H
#include <QObject>
#include "mainwindow.h"
#include "leveldialog.h"
#include "registrationDialog.h"
#include "gamewindow.h"

namespace Ui {
class windowController;
}

class windowController : public QObject
{
    Q_OBJECT

public:
    explicit windowController();
    void start();

private:
    MainWindow main;
    levelDialog level;
    RegistrationDialog registration;
    gameWindow game;

protected:

public slots:
    void openRegistrationDialogue();
    void openLevelDialogue();
    void openGameWindow();
    void gameOverReceived();

signals:

private slots:

};



#endif // WINDOWCONTROLLER_H
