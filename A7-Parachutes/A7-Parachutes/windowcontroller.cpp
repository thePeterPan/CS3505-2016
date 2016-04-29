#include "windowcontroller.h"

WindowController::WindowController(Networking *client_, QWidget *parent)
    : client(client_), game(client_), level(client_), registration(client_), main(client_)
{
    start();
    connect(&main,  &MainWindow::showRegistrationSignal, this, &WindowController::openRegistrationDialogue);
    connect(&main,  &MainWindow::showLevelDialogSignal, this, &WindowController::openLevelDialogue);
    connect(&level, &LevelSelectionDialog::showGameWindowSignal, this, &WindowController::openGameWindow);
    connect(&game,  &GameWindow::showLevelDial, this, &WindowController::gameOverReceived);
    connect(&level, &LevelSelectionDialog::addWordsFromFile,&game,&GameWindow::catchAddWordsFromLevel);
}

void WindowController::start()
{
    main.show();
}

void WindowController::openRegistrationDialogue()
{
    registration.show();
}

void WindowController::openLevelDialogue()
{
    level.show();
    main.close();
}

void WindowController::openGameWindow()
{
    game.show();
    game.setFocus();
    game.startGame();
    level.close();
}

void WindowController::gameOverReceived()
{
    level.show();
    game.close();
}
