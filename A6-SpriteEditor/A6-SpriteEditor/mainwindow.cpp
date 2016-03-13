#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connectSignalsAndSlots();

    initializeUIDefaults();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * Connects all respective signals and slots.
 *
 * @brief MainWindow::connectSignalsAndSlots
 */
void MainWindow::connectSignalsAndSlots()
{
    /// Menubar:
//    connect(ui->actionNew_File, SIGNAL(triggered(bool)), this, SLOT());
//    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT());
//    connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT());
//    connect(ui->actionSave_As, SIGNAL(triggered(bool)), this, SLOT());
//    connect(ui->actionExport_As, SIGNAL(triggered(bool)), this, SLOT());
//    connect(ui->actionImport,  SIGNAL(triggered(bool)), this, SLOT());
    connect(ui->actionQuit, SIGNAL(triggered(bool)), this, SLOT(close()));

    /// Speed Slider
    connect(ui->playbackSpeed_horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(playbackSpeed_hSlider_moved(int)));
}

void MainWindow::initializeUIDefaults()
{
    /// Speed Slider
    ui->playbackSpeed_horizontalSlider->setMinimum(1);
    ui->playbackSpeed_horizontalSlider->setMaximum(10);
    ui->playbackSpeed_label->setText("Playback speed: " + QString::number(ui->playbackSpeed_horizontalSlider->value()));
}

void MainWindow::playbackSpeed_hSlider_moved(int value)
{
    ui->playbackSpeed_label->setText("Playback speed: " + QString::number(value));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // http://stackoverflow.com/questions/25454648/qmainwindow-close-signal-not-emitted
    event->ignore();
    // Perform checks.
    event->accept();
}
