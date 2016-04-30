#include "windowcontroller.h"

WindowController::WindowController(Networking *client_, QWidget *parent)
    : client(client_), game(), level(), registration(client_), main(client_), logic(this,game.width(),game.height())
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


    connect(&level, &LevelSelectionDialog::addWordsFromFile,    &logic,&GameLogic::addWordsFromFile);

    connect(&main, &MainWindow::checkLoginDataSignal,           client,&Networking::requestLogin);
    connect(client, &Networking::loginSuccessSignal,            &main, &MainWindow::loginAnswerReceived);
    connect(&main, &MainWindow::requestUserInfo,                client,&Networking::requestUserInfo);
    connect(client, &Networking::sendUsernameAvailable,         &registration, &RegistrationDialog::getNameAvailable);
    connect(client, &Networking::sendIsTeacher,                 &registration, &RegistrationDialog::getIsTeacher);
    connect(client, &Networking::sendIsTeacher,                 &main, &MainWindow::getUserType);
    connect(client, &Networking::sendRegisterSuccess,           &registration, &RegistrationDialog::getRegisterSuccess);

    // NETWORK AND GAME LOGIC COMMUNICATION //

    connect(client, &Networking::newList,                       &logic,&GameLogic::receivedWordList);
    connect(&logic, &GameLogic::requestWordList,                client,&Networking::requestNextList);
    connect(client, &Networking::sendUserInfo,                  &logic,&GameLogic::receiveUserInfo);
    connect(&logic, &GameLogic::sendScore,                      client,&Networking::requestWriteNewScore);

    // GAME WINDOW AND GAME LOGIC COMMUNICATION //

    // GameLogic to GameWindow //
    connect(&logic,     &GameLogic::newWord,            &game,      &GameWindow::receiveNewWord);
    connect(&logic,     &GameLogic::newLevel,           &game,      &GameWindow::receiveNewLevel);
    connect(&logic,     &GameLogic::failed,             &game,      &GameWindow::receiveFail);
    connect(&logic,     &GameLogic::victory,            &game,      &GameWindow::receiveVictory);
    connect(&logic,     &GameLogic::updateActionTimer,  &game,      &GameWindow::actionTimerUpdated);
    connect(&logic,     &GameLogic::updateScore,        &game,      &GameWindow::scoreUpdated);
    connect(&logic,     &GameLogic::gameOver,           &game,      &GameWindow::gameOver);
    connect(&logic,     &GameLogic::levelCompleted,     &game,      &GameWindow::levelCompleted);

    //Networking and GameWindow
    connect(client,     &Networking::sendCurrentScore,  &game,      &GameWindow::setOldScore);
    connect(&main,      &MainWindow::setOldScore,       client,     &Networking::requestCurrentHighScore);

    // GameWindow to GameLogic //
    connect(&game,      &GameWindow::letterTyped,       &logic,     &GameLogic::newLetterTyped);
    connect(&game,      &GameWindow::newSize,           &logic,     &GameLogic::changeSize);
    connect(&game,      &GameWindow::readyToPlay,       &logic,     &GameLogic::startGame);
    connect(&game,      &GameWindow::pauseGame,         &logic,     &GameLogic::pause);
    connect(&game,      &GameWindow::unPauseGame,       &logic,     &GameLogic::unPause);
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



