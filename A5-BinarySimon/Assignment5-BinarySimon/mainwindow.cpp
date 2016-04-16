#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    // I think this needs to always be first.
    ui->setupUi(this);

    // Disallow resizing of the window.
    ui->statusBar->setSizeGripEnabled(false);

    // Connect all slots and signals
    connectSignalsAndSlots();

    // Tell the model to start the game.
    gm.gameStart();
}

/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::connectSignalsAndSlots
 */
void MainWindow::connectSignalsAndSlots()
{
    // syntax for default slots is on_NAMEOFTHEWIDGET_NAMEOFTHESIGNAL
    // Manually connect the buttons to the methods:
    connect(ui->pushButton_start, SIGNAL(clicked(bool)), this, SLOT(pushButton_start_clicked()));
    // button pressed
    connect(ui->pushButton_blue, SIGNAL(pressed()), this, SLOT(pushButton_blue_pressed()));
    connect(ui->pushButton_red, SIGNAL(pressed()), this, SLOT(pushButton_red_pressed()));
    connect(ui->pushButton_green, SIGNAL(pressed()), this, SLOT(pushButton_green_pressed()));
    connect(ui->pushButton_yellow, SIGNAL(pressed()), this, SLOT(pushButton_yellow_pressed()));
    // button released
    connect(ui->pushButton_blue, SIGNAL(released()), this, SLOT(pushButton_blue_released()));
    connect(ui->pushButton_red, SIGNAL(released()), this, SLOT(pushButton_red_released()));
    connect(ui->pushButton_green, SIGNAL(released()), this, SLOT(pushButton_green_released()));
    connect(ui->pushButton_yellow, SIGNAL(released()), this, SLOT(pushButton_yellow_released()));

    // Signal that the state has changed.
    connect(&gm, SIGNAL(signalStateChange(int)), this, SLOT(state_changed(int)));

    // Signal for the progress bar to progress.
    connect(&gm, SIGNAL(signalProgressBarUpdate(int)), this, SLOT(updateProgressBar(int)));
}

/**
 * @brief MainWindow::state_changed
 * @param nextState
 */
void MainWindow::state_changed(int nextState)
{
    // Start state
    if (nextState == game_model::gameState::Start)
    {
        // Initialize the buttons
        ui->pushButton_start->setText("Start");
        ui->pushButton_blue->setText("");
        ui->pushButton_red->setText("");
        ui->pushButton_green->setText("");
        ui->pushButton_yellow->setText("");
        ui->pushButton_blue->setDisabled(true);
        ui->pushButton_red->setDisabled(true);
        ui->pushButton_green->setDisabled(true);
        ui->pushButton_yellow->setDisabled(true);
        ui->pushButton_blue->setStyleSheet(BUTTON_BLUE_OFF_STYLE);
        ui->pushButton_red->setStyleSheet(BUTTON_RED_OFF_STYLE);
        ui->pushButton_green->setStyleSheet(BUTTON_GREEN_OFF_STYLE);
        ui->pushButton_yellow->setStyleSheet(BUTTON_YELLOW_OFF_STYLE);

        // Initialize the progress bar to 0.
        ui->progressBar->setValue(0);

        // Initialize the player label.
        ui->label_currentPlayer->setText(QString(""));

        qDebug() << "Start!";

        // Now wait for the start button to be pressed.
        // see pushButton_start_clicked()
    }
    // Displaying state
    else if (nextState == game_model::gameState::DisplaySequence)
    {
        ui->pushButton_start->setText("Reset");

        // State current player
        ui->label_currentPlayer->setText(QString("Computer"));

        // Disable all the buttons
        ui->pushButton_blue->setDisabled(true);
        ui->pushButton_red->setDisabled(true);
        ui->pushButton_green->setDisabled(true);
        ui->pushButton_yellow->setDisabled(true);
        // TODO: Have to do this because we can't interrupt the timer
        ui->pushButton_start->setDisabled(true);

        // Reset the progress bar for this round.
        ui->progressBar->setRange(0, gm.getSequence().size());
        ui->progressBar->setValue(0);

        // Chain the display of the pattern
        highlightNextColorFromPattern();

        // Now wait for the sequence display event to finish
        // see displayPattern()
    }
    // User input state
    else if (nextState == game_model::gameState::UserInput)
    {
        // State current player
        ui->label_currentPlayer->setText(QString("User"));

        // Enable buttons for the user to press.
        ui->pushButton_blue->setEnabled(true);
        ui->pushButton_red->setEnabled(true);
        ui->pushButton_green->setEnabled(true);
        ui->pushButton_yellow->setEnabled(true);

        // TODO: renable the start button
        ui->pushButton_start->setEnabled(true);

        // Now wait for the signal of the user finishing the sequence or makes a mistake.
        // see game_model::checkSequenceNext()
    }
    // User lost state.
    else if (nextState == game_model::gameState::GameOver)
    {
        // Disable all the buttons
        ui->pushButton_blue->setDisabled(true);
        ui->pushButton_red->setDisabled(true);
        ui->pushButton_green->setDisabled(true);
        ui->pushButton_yellow->setDisabled(true);

        // Display game over message
        QMessageBox message;
        message.setText(tr("Game Over!"));
        message.setInformativeText(
                    QString("Total number of rounds achieved: %1\nTotal number of moves: %2\n").arg(
                        gm.getTotalNumberOfRounds()).arg(gm.getTotalMoves()));
        message.addButton(tr("Continue..."), QMessageBox::AcceptRole);
        message.exec();

        // Tell the game model to restart the game.
        gm.nextState(true);
    }
    // Error.
    else
    {
        QMessageBox message;
        message.setText(tr("Error!"));
        message.addButton(tr("Exit"), QMessageBox::AcceptRole);
        message.exec();
        QCoreApplication::exit();
    }
}

/**
 * Chain the time delay calls to the display sequence. Essentially recursive calls to
 * the QTimer::singleShot()
 *
 * @brief MainWindow::highlightNextColorFromPattern
 */
void MainWindow::highlightNextColorFromPattern()
{
    qDebug() << gm.getSequence()[currentPatternIndex];

    if (gm.getSequence()[currentPatternIndex] == QString("blue"))
    {
        ui->pushButton_blue->setStyleSheet(BUTTON_BLUE_LIT_STYLE);
    }
    else if (gm.getSequence()[currentPatternIndex] == QString("red"))
    {
        ui->pushButton_red->setStyleSheet(BUTTON_RED_LIT_STYLE);
    }
    else if (gm.getSequence()[currentPatternIndex] == QString("green"))
    {
        ui->pushButton_green->setStyleSheet(BUTTON_GREEN_LIT_STYLE);
    }
    else if (gm.getSequence()[currentPatternIndex] == QString("yellow"))
    {
        ui->pushButton_yellow->setStyleSheet(BUTTON_YELLOW_LIT_STYLE);
    }

    QTimer::singleShot(gm.getDisplaySequenceDelay(), this, SLOT(unhighlightButtons()));
}

/**
 * @brief MainWindow::updateProgressBar
 */
void MainWindow::updateProgressBar(int value)
{
    ui->progressBar->setValue(value);
}

/**
 * Second part of the QTimer::singleShot() chain where the buttons are placed back
 * into the disabled color that way if a color repeats, it's noticable.
 * This method also checks to see if the program has iterated through the entire
 * sequence. If so, tell the model to move onto the next state.
 *
 * @brief MainWindow::unhighlightButtons
 */
void MainWindow::unhighlightButtons()
{
    ui->pushButton_blue->setStyleSheet(BUTTON_BLUE_OFF_STYLE);
    ui->pushButton_red->setStyleSheet(BUTTON_RED_OFF_STYLE);
    ui->pushButton_green->setStyleSheet(BUTTON_GREEN_OFF_STYLE);
    ui->pushButton_yellow->setStyleSheet(BUTTON_YELLOW_OFF_STYLE);

    ++currentPatternIndex;
    // if we've reached the end of the list
    if (currentPatternIndex == gm.getSequence().size())
    {
        currentPatternIndex = 0;
        gm.nextState();
        return;
    }
    // Otherwise continue displaying the pattern.
    QTimer::singleShot(300, this, SLOT(highlightNextColorFromPattern()));
}

/**
 * @brief MainWindow::pushButton_start_clicked
 */
void MainWindow::pushButton_start_clicked()
{
    if (ui->pushButton_start->text() == "Reset")
    {
        QMessageBox msgBox;
        msgBox.setText("Are you sure you want to restart?");
        msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        int selection = msgBox.exec();

        if (selection == QMessageBox::Ok)
        {   // Restart the game.
            gm.nextState(true);
            return;
        }
        else
        {   // Resume the game
            return;
        }
    }
    gm.nextState();
}

/**
 * @brief MainWindow::pushButton_blue_pressed
 */
void MainWindow::pushButton_blue_pressed()
{
    ui->pushButton_blue->setStyleSheet(BUTTON_BLUE_LIT_STYLE);
}

/**
 * @brief MainWindow::pushButton_red_pressed
 */
void MainWindow::pushButton_red_pressed()
{
    ui->pushButton_red->setStyleSheet(BUTTON_RED_LIT_STYLE);
}

/**
 * @brief MainWindow::pushButton_green_pressed
 */
void MainWindow::pushButton_green_pressed()
{
    ui->pushButton_green->setStyleSheet(BUTTON_GREEN_LIT_STYLE);
}

/**
 * @brief MainWindow::pushButton_yellow_pressed
 */
void MainWindow::pushButton_yellow_pressed()
{
    ui->pushButton_yellow->setStyleSheet(BUTTON_YELLOW_LIT_STYLE);
}

/**
 * @brief MainWindow::pushButton_blue_released
 */
void MainWindow::pushButton_blue_released()
{
    ui->pushButton_blue->setStyleSheet(BUTTON_BLUE_OFF_STYLE);
    gm.checkSequenceNext("blue");
}

/**
 * @brief MainWindow::pushButton_red_released
 */
void MainWindow::pushButton_red_released()
{
    ui->pushButton_red->setStyleSheet(BUTTON_RED_OFF_STYLE);
    gm.checkSequenceNext("red");
}

/**
 * @brief MainWindow::pushButton_green_released
 */
void MainWindow::pushButton_green_released()
{
    ui->pushButton_green->setStyleSheet(BUTTON_GREEN_OFF_STYLE);
    gm.checkSequenceNext("green");
}

/**
 * @brief MainWindow::pushButton_yellow_released
 */
void MainWindow::pushButton_yellow_released()
{
    ui->pushButton_yellow->setStyleSheet(BUTTON_YELLOW_OFF_STYLE);
    gm.checkSequenceNext("yellow");
}

/**
 * I chose to put the checkSequenceNext() calls in the press event because it made more
 * sense to me that keys on the keyboard are registered when they are pressed even when
 * they are not yet released.
 *
 * @brief MainWindow::keyPressEvent
 * @param event
 */
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_B)
    {
        if (ui->pushButton_blue->isEnabled())
        {
            qDebug() << "blue key";
            ui->pushButton_blue->setStyleSheet(BUTTON_BLUE_LIT_STYLE);
            gm.checkSequenceNext("blue");
        }
    }
    else if (event->key() == Qt::Key_R)
    {
        if (ui->pushButton_red->isEnabled())
        {
            qDebug() << "red key";
            ui->pushButton_red->setStyleSheet(BUTTON_RED_LIT_STYLE);
            gm.checkSequenceNext("red");
        }
    }
    else if (event->key() == Qt::Key_G)
    {
        if (ui->pushButton_green->isEnabled())
        {
            qDebug() << "green key";
            ui->pushButton_green->setStyleSheet(BUTTON_GREEN_LIT_STYLE);
            gm.checkSequenceNext("green");
        }
    }
    else if (event->key() == Qt::Key_Y)
    {
        if (ui->pushButton_yellow->isEnabled())
        {
            qDebug() << "yellow key";
            ui->pushButton_yellow->setStyleSheet(BUTTON_YELLOW_LIT_STYLE);
            gm.checkSequenceNext("yellow");
        }
    }
}

/**
 * Just to reset the color back to an unpressed setting.
 *
 * @brief MainWindow::keyReleaseEvent
 * @param event
 */
void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_B)
    {
        if (ui->pushButton_blue->isEnabled())
        {
            ui->pushButton_blue->setStyleSheet(BUTTON_BLUE_OFF_STYLE);
        }
    }
    else if (event->key() == Qt::Key_R)
    {
        if (ui->pushButton_red->isEnabled())
        {
            ui->pushButton_red->setStyleSheet(BUTTON_RED_OFF_STYLE);
        }
    }
    else if (event->key() == Qt::Key_G)
    {
        if (ui->pushButton_green->isEnabled())
        {
            ui->pushButton_green->setStyleSheet(BUTTON_GREEN_OFF_STYLE);
        }
    }
    else if (event->key() == Qt::Key_Y)
    {
        if (ui->pushButton_yellow->isEnabled())
        {
            ui->pushButton_yellow->setStyleSheet(BUTTON_YELLOW_OFF_STYLE);
        }
    }
}
