#include "windowcontroller.h"

WindowController::WindowController(Networking *client_, QWidget *parent)
    : client(client_), game(client_), level(client_), registration(client_), main(client_), logic(this,game.width(),game.height())
{

    connectSignalsAndSlots();
    start();
}

void WindowController::connectSignalsAndSlots()
{
    connect(&main,  &MainWindow::showRegistrationSignal,        this, &WindowController::openRegistrationDialogue);
    connect(&main,  &MainWindow::showLevelDialogSignal,         this, &WindowController::openLevelDialogue);
    connect(&level, &LevelSelectionDialog::showGameWindowSignal,this, &WindowController::openGameWindow);
    connect(&game,  &GameWindow::showLevelDial,                 this, &WindowController::gameOverReceived);
    connect(&level, &LevelSelectionDialog::addWordsFromFile,    &game,&GameWindow::catchAddWordsFromLevel);
    connect(client, &Networking::newList,                       &game,&GameWindow::receivedWordList);



    // GAME WINDOW AND GAME LOGIC COMMUNICATION //

    // GameLogic to GameWindow
    connect(&logic,     &GameLogic::newWord,            &game,      &GameWindow::receiveNewWord);
    connect(&logic,     &GameLogic::newLevel,           &game,      &GameWindow::receiveNewLevel);
    connect(&logic,     &GameLogic::failed,             &game,      &GameWindow::receiveFail);
    connect(&logic,     &GameLogic::victory,            &game,      &GameWindow::receiveVictory);
    connect(&logic,     &GameLogic::updateActionTimer,  &game,      &GameWindow::actionTimerUpdated);
    connect(&logic,     &GameLogic::updateScore,        &game,      &GameWindow::scoreUpdated);
    connect(&logic,     &GameLogic::gameOver,           &game,      &GameWindow::gameOver);
    connect(&logic,     &GameLogic::levelCompleted,     &game,      &GameWindow::levelCompleted);


    connect(&game,      &GameWindow::letterTyped,       &logic,     &GameLogic::newLetterTyped);
    connect(&game,      &GameWindow::newSize,           &logic,     &GameLogic::changeSize);
    connect(&game,      &GameWindow::readyToPlay,       &logic,     &GameLogic::startGame);
    connect(&game,      &GameWindow::pauseGame,         &logic,     &GameLogic::pause);
    connect(&game,      &GameWindow::pauseGame,         &game,      &GameWindow::pauseSwitch);
    connect(&game,      &GameWindow::unPauseGame,       &logic,     &GameLogic::unPause);
    connect(&game,      &GameWindow::unPauseGame,       &game,      &GameWindow::pauseSwitch);
    connect(&game,      &GameWindow::addWordsFromFile,  &logic,     &GameLogic::addWordsFromFile);
    connect(&game,      &GameWindow::paintWorld,        &logic,     &GameLogic::paintWorld);
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
