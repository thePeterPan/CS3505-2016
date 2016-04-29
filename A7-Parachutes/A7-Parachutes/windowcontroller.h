#ifndef WINDOWCONTROLLER_H
#define WINDOWCONTROLLER_H

#include <QObject>

#include "mainwindow.h"
#include "leveldialog.h"
#include "registrationdialog.h"
#include "gamewindow.h"
#include "networking.h"

namespace Ui {
class WindowController;
}

class WindowController : public QObject
{
    Q_OBJECT

public:
    explicit WindowController(Networking *client_, QWidget *parent = 0);
    void start();

private:
    Networking *client;
    MainWindow main;
    LevelSelectionDialog level;
    RegistrationDialog registration;
    GameWindow game;

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
