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
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::close);
    connect(ui->menuHelp, &QMenu::triggered, this, &MainWindow::menuHelp_triggered);

    /// Speed Slider
    connect(ui->playbackSpeed_horizontalSlider, &QSlider::valueChanged, this, &MainWindow::playbackSpeed_hSlider_moved);

    /// Color Wheel
    connect(ui->colorWheel_widget, &color_widgets::ColorWheel::colorChanged, this, &MainWindow::colorWheel_colorChanged);
}

void MainWindow::initializeUIDefaults()
{
    /// Speed Slider
    ui->playbackSpeed_horizontalSlider->setMinimum(1);
    ui->playbackSpeed_horizontalSlider->setMaximum(10);
    ui->playbackSpeedCurrent_label->setText(QString::number(ui->playbackSpeed_horizontalSlider->value()));

    /// Color Preview
    ui->colorPreview_widget->setColor(QColor::fromRgb(0,0,0));
}

void MainWindow::playbackSpeed_hSlider_moved(int value)
{
    ui->playbackSpeedCurrent_label->setText(QString::number(value));
}

void MainWindow::menuHelp_triggered()
{

}

void MainWindow::colorWheel_colorChanged(QColor color)
{
    ui->colorPreview_widget->setColor(color);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // http://stackoverflow.com/questions/25454648/qmainwindow-close-signal-not-emitted
    event->ignore();
    // Perform checks.
    event->accept();
}
