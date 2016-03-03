#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), clickCount(0)
{
    // I think this should always be first.
    ui->setupUi(this);

    // Disallow resizing of the window.
    ui->statusBar->setSizeGripEnabled(false);

    // Disable buttons:
    ui->pushButton_blue->setEnabled(false);
    ui->pushButton_red->setEnabled(false);

    // http://stackoverflow.com/questions/14230265/what-is-the-proper-way-to-set-qprogressbar-to-update-from-the-logic-layer
    // Initialize the progress bar.
    // TODO: better way of initializing this?
    ui->progressBar->setRange(0,2);
    ui->progressBar->setValue(0);

    connectSignalsAndSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectSignalsAndSlots()
{
    // syntax for default slots is on_NAMEOFTHEWIDGET_NAMEOFTHESIGNAL
    // Manually connect the buttons to the methods:
    connect(ui->pushButton_start, SIGNAL(clicked(bool)), this, SLOT(pushButton_start_clicked()));
    connect(ui->pushButton_blue, SIGNAL(clicked(bool)), this, SLOT(pushButton_blue_clicked()));
    connect(ui->pushButton_red, SIGNAL(clicked(bool)), this, SLOT(pushButton_red_clicked()));

    // Signal that the state has changed.
    connect(&gm, SIGNAL(signalStateChange(int)), this, SLOT(state_changed(int)));

    // Signal that the size of the pattern has changed, update the progress bar.
    connect(&gm, SIGNAL(signalPatternSizeChange(int)), this, SLOT(patternSize_changed(int)));

    // Signal to display the pattern to the user.
    connect(&gm, SIGNAL(signalDisplayPattern(std::vector<char>)), this, SLOT(displayPattern(std::vector<char>)));
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
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        int selection = msgBox.exec();

        if (selection == QMessageBox::Ok)
        {
            // Restart the game.
            gm.nextState(true);
            return;
        }
        else
        {
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
    gm.checkPattern('b');
    ++clickCount;
    ui->progressBar->setValue(clickCount);

    qDebug() << clickCount;
}

/**
 * @brief MainWindow::pushButton_red_clicked
 */
void MainWindow::pushButton_red_clicked()
{
    gm.checkPattern('r');
    ++clickCount;
    ui->progressBar->setValue(clickCount);

    qDebug() << clickCount;
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
        ui->pushButton_start->setText("Start");
        ui->pushButton_blue->setDisabled(true);
        ui->pushButton_red->setDisabled(true);
    }
    // Displaying state
    else if (nextState == game_model::gameState::DisplayPattern)
    {
        ui->pushButton_start->setText("Reset");

    }
    // User input state
    else if (nextState == game_model::gameState::UserInput)
    {
        ui->pushButton_blue->setDisabled(false);
        ui->pushButton_red->setDisabled(false);
    }
    // User lost state.
    else if (nextState == game_model::gameState::GameOver)
    {
        QMessageBox message;
        message.setText(tr("Game Over!"));
        message.setInformativeText(
                    QString("Total number of rounds achieved: %1\nTotal number of moves: %2\n").arg(
                        gm.getTotalNumberOfRounds(), gm.getTotalMoves()));
        message.addButton(tr("Continue..."), QMessageBox::AcceptRole);
        message.exec();
    }
    // Error.
    else
    {
        QMessageBox message;
        message.setText(tr("Error!"));
        message.addButton(tr("Exit"), QMessageBox::AcceptRole);
        message.exec();
        // TODO: quit program
    }
}

/**
 * @brief MainWindow::patternSize_changed
 * @param patternSize
 */
void MainWindow::patternSize_changed(int patternSize)
{
    ui->progressBar->setRange(0, patternSize);
    ui->progressBar->setValue(0);
}

/**
 * @brief MainWindow::displayPattern
 */
void MainWindow::displayPattern(std::vector<char> thePattern)
{
    for (auto const& value : thePattern)
    {
        qDebug() << tr(value);
    }
    gm.nextState();
}
