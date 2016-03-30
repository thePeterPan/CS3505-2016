#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    graphics();

    connectSignalsAndSlots();
    initializeUIDefaults();


    std::cout <<"hello world"<<std::endl;
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
    /// Alpha Slider
    connect(ui->alphaSlider_widget, &color_widgets::GradientSlider::valueChanged, this, &MainWindow::alphaSlider_valueChanged);

    /// Tool Buttons:
    connect(ui->brush_pushButton, &QToolButton::clicked, this, &MainWindow::brush_pushButton_clicked);
    connect(ui->fillBucket_pushButton, &QToolButton::clicked, this, &MainWindow::fillBucket_pushButton_clicked);
    connect(ui->eraser_pushButton, &QToolButton::clicked, this, &MainWindow::eraser_pushButton_clicked);
    connect(ui->rotate_pushButton, &QToolButton::clicked, this, &MainWindow::rotate_pushButton_clicked);
    connect(ui->pushButton, &QToolButton::clicked, this, &MainWindow::pushButton_clicked);
    connect(ui->symmetricalTool_pushButton, &QToolButton::clicked, this, &MainWindow::symmetricalTool_pushButton_clicked);
    connect(ui->flipV_pushButton, &QToolButton::clicked, this, &MainWindow::flipV_pushButton_clicked);
    connect(ui->flipH_pushButton, &QToolButton::clicked, this, &MainWindow::flipH_pushButton_clicked);
    connect(ui->invertColors_pushButton, &QToolButton::clicked, this, &MainWindow::invertColors_pushButton_clicked);

}

void MainWindow::initializeUIDefaults()
{
    /// Speed Slider
    ui->playbackSpeed_horizontalSlider->setMinimum(1);
    ui->playbackSpeed_horizontalSlider->setMaximum(10);
    ui->playbackSpeedCurrent_label->setText(QString::number(ui->playbackSpeed_horizontalSlider->value()));

    /// Alpha Slider
    ui->alphaSlider_widget->setMinimum(0);
    ui->alphaSlider_widget->setMaximum(255);
    ui->alphaSlider_widget->setFirstColor(QColor::fromRgba(qRgba(0,0,0,0)));
    ui->alphaSlider_widget->setLastColor(QColor::fromRgba(qRgba(0,0,0,255)));
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
    QColor alpha_color = color;
    alpha_color.setAlpha(0);
    ui->alphaSlider_widget->setFirstColor(alpha_color);
    alpha_color.setAlpha(255);
    ui->alphaSlider_widget->setLastColor(alpha_color);

    alpha_color.setAlpha(ui->alphaSlider_widget->value());

    scene->setColor(alpha_color);
}

void MainWindow::alphaSlider_valueChanged(int value)
{
<<<<<<< HEAD
    QColor color = ui->colorWheel_widget->value();
    value = value * 255 / 100;
=======
    QColor color = ui->colorWheel_widget->color();
>>>>>>> origin/neverland-dev
    color.setAlpha(value);

    scene->setColor(color);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // http://stackoverflow.com/questions/25454648/qmainwindow-close-signal-not-emitted
    event->ignore();
    // Perform checks.
    event->accept();
}

void MainWindow::graphics()
{
    //scene = new GraphicsScene(ui->graphicsView);
    scene = new GraphicsScene(&model, ui->graphicsView,20,20,30);
    scene->setColor(ui->colorWheel_widget->color());
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}




void MainWindow::brush_pushButton_clicked()
{
    model.setTool(model.BRUSH);
}

void MainWindow::fillBucket_pushButton_clicked()
{
    model.setTool(model.FILL_BUCKET);
}

void MainWindow::eraser_pushButton_clicked()
{
    model.setTool(model.ERASER);
}

void MainWindow::rotate_pushButton_clicked()
{
    scene->rotate(true);
}

void MainWindow::pushButton_clicked()
{
    model.setTool(model.PAN);
}

void MainWindow::symmetricalTool_pushButton_clicked()
{
    model.setTool(model.MIRROR);
}

void MainWindow::flipV_pushButton_clicked()
{
    scene->flip(true);
}

void MainWindow::flipH_pushButton_clicked()
{
    scene->flip(false);
}

void MainWindow::invertColors_pushButton_clicked()
{
    scene->invert();
}
