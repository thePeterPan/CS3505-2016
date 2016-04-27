#include "windowcontroller.h"

windowController::windowController() {

    main.show();
    connect(&main, &MainWindow::showRegistrationSignal, this, &windowController::openRegistrationDialogue);
    connect(&main, &MainWindow::showLevelDialogSignal, this, &windowController::openLevelDialogue);
    connect(&level, &levelDialog::showGameWindowSignal, this, &windowController::openGameWindow);
    connect(&game, &gameWindow::showLevelDial, this, &windowController::gameOverReceived);
}

void windowController::start(){
    main.show();
}

void windowController::openRegistrationDialogue() {
    registration.show();
}

void windowController::openLevelDialogue() {
    level.show();
    main.close();
}

void windowController::openGameWindow() {
    game.show();
    game.setFocus();
    game.startGame();
    level.close();
}

void windowController::gameOverReceived() {
    level.show();
    game.close();
}
