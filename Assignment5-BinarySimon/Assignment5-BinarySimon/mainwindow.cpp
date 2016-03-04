#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    // I think this should always be first.
    ui->setupUi(this);

    // Disallow resizing of the window.
    ui->statusBar->setSizeGripEnabled(false);

    // Connect everything
    connectSignalsAndSlots();

    // Tell the model to start the game.
    gm.gameStart();
}

MainWindow::~MainWindow()
{
    delete ui;
//    delete timer;
//    delete timer_thread;
}

void MainWindow::connectSignalsAndSlots()
{
    // syntax for default slots is on_NAMEOFTHEWIDGET_NAMEOFTHESIGNAL
    // Manually connect the buttons to the methods:
    connect(ui->pushButton_start, SIGNAL(clicked(bool)), this, SLOT(pushButton_start_clicked()));
    connect(ui->pushButton_blue, SIGNAL(clicked(bool)), this, SLOT(pushButton_blue_clicked()));
    connect(ui->pushButton_red, SIGNAL(clicked(bool)), this, SLOT(pushButton_red_clicked()));
    connect(ui->pushButton_green, SIGNAL(clicked(bool)), this, SLOT(pushButton_green_clicked()));
    connect(ui->pushButton_yellow, SIGNAL(clicked(bool)), this, SLOT(pushButton_yellow_clicked()));

    // Signal that the state has changed.
    connect(&gm, SIGNAL(signalStateChange(int)), this, SLOT(state_changed(int)));

    // Signal for the progress bar to progress.
    connect(&gm, SIGNAL(signalProgressBarUpdate(int)), this, SLOT(updateProgressBar(int)));

    // Signal that the user has successfully completed the pattern.
//    connect(&gm, SIGNAL(signalSequenceComplete()), &gm, SLOT(nextRound()));

    // Signal that the player has made a mistake, game over
//    connect(&gm, SIGNAL(signalGameOver()), &gm, SLOT(nextState(bool)));
}

/**
 * @brief MainWindow::pushButton_start_clicked
 */
void MainWindow::pushButton_start_clicked()
{
    if (ui->pushButton_start->text() == "Reset")
    {
//        if (timer_thread->isRunning())
//        {
//            // TODO: timers cannot be stopped from another thread
//            timer->stop();
//        }
        QMessageBox msgBox;
        msgBox.setText("Are you sure you want to restart?");
        msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        int selection = msgBox.exec();

        if (selection == QMessageBox::Ok)
        {   // Restart the game.
            // kill the thread if it's running the timer.
//            timer_thread->exit(0);
            gm.nextState(true);
            return;
        }
        else
        {   // Resume the game
            // this resets the timer, but whatever.
//            timer->start();
            return;
        }
    }
    gm.nextState();
}

/**
 * @brief MainWindow::pushButton_blue_clicked
 */
void MainWindow::pushButton_blue_clicked()
{
    gm.checkSequenceNext("blue");
}

/**
 * @brief MainWindow::pushButton_red_clicked
 */
void MainWindow::pushButton_red_clicked()
{
    gm.checkSequenceNext("red");
}

/**
 * @brief MainWindow::pushButton_green_clicked
 */
void MainWindow::pushButton_green_clicked()
{
    gm.checkSequenceNext("green");
}

/**
 * @brief MainWindow::pushButton_yellow_clicked
 */
void MainWindow::pushButton_yellow_clicked()
{
    gm.checkSequenceNext("yellow");
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
        ui->pushButton_blue->setText("Blue (b)");
        ui->pushButton_blue->setDisabled(true);
        ui->pushButton_red->setText("Red (r)");
        ui->pushButton_red->setDisabled(true);
        ui->pushButton_green->setText("Green (g)");
        ui->pushButton_green->setDisabled(true);
        ui->pushButton_yellow->setText("Yellow (y)");
        ui->pushButton_yellow->setDisabled(true);

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
        ui->label_currentPlayer->setText(QString("Computer"));

        ui->pushButton_blue->setDisabled(true);
        ui->pushButton_red->setDisabled(true);
        ui->pushButton_green->setDisabled(true);
        ui->pushButton_yellow->setDisabled(true);

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
        ui->pushButton_blue->setEnabled(true);
        ui->pushButton_red->setEnabled(true);
        ui->pushButton_green->setEnabled(true);
        ui->pushButton_yellow->setEnabled(true);

        ui->label_currentPlayer->setText(QString("User"));

        // Now wait for as signal of the user finishing the sequence or make a mistake.
        // see game_model::checkSequenceNext()
    }
    // User lost state.
    else if (nextState == game_model::gameState::GameOver)
    {
        ui->pushButton_blue->setDisabled(true);
        ui->pushButton_red->setDisabled(true);
        ui->pushButton_green->setDisabled(true);
        ui->pushButton_yellow->setDisabled(true);

        QMessageBox message;
        message.setText(tr("Game Over!"));
        message.setInformativeText(
                    QString("Total number of rounds achieved: %1\nTotal number of moves: %2\n").arg(
                        gm.getTotalNumberOfRounds()).arg(gm.getTotalMoves()));
        message.addButton(tr("Continue..."), QMessageBox::AcceptRole);
        message.exec();

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
 * @brief MainWindow::highlightNextColorFromPattern
 */
void MainWindow::highlightNextColorFromPattern()
{
    qDebug() << gm.getSequence()[currentPatternIndex];

    QTimer::singleShot(gm.getDisplaySequenceDelay(), this, SLOT(unhighlightButtons()));
}

/**
 * @brief MainWindow::unhighlightButtons
 */
void MainWindow::unhighlightButtons()
{
    qDebug() << "Unhighlight all buttons.";

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
 * @brief MainWindow::updateProgressBar
 */
void MainWindow::updateProgressBar(int value)
{
    ui->progressBar->setValue(value);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_R)
    {
        if (ui->pushButton_red->isEnabled())
        {
            qDebug() << "red key";
            pushButton_red_clicked();
        }
    }
    else if (event->key() == Qt::Key_B)
    {
        if (ui->pushButton_blue->isEnabled())
        {
            qDebug() << "blue key";
            pushButton_blue_clicked();
        }
    }
    else if (event->key() == Qt::Key_G)
    {
        if (ui->pushButton_green->isEnabled())
        {
            qDebug() << "green key";
            pushButton_green_clicked();
        }
    }
    else if (event->key() == Qt::Key_Y)
    {
        if (ui->pushButton_yellow->isEnabled())
        {
            qDebug() << "yellow key";
            pushButton_yellow_clicked();
        }
    }
}

