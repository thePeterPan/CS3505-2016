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
    /// File Menu:
    connect(ui->actionNew_File, &QAction::triggered, this, &MainWindow::menuNewFile_triggered);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::menuOpen_triggered);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::menuSave_triggered);
    connect(ui->actionSave_As, &QAction::triggered, this, &MainWindow::menuSaveAs_triggered);
    connect(ui->actionExport_As, &QAction::triggered, this, &MainWindow::menuExportAs_triggered);
    connect(ui->actionImport,  &QAction::triggered, this, &MainWindow::menuImport_triggered);
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::close);

    /// Edit Menu:
    connect(ui->actionRotate_Clockwise, &QAction::triggered, this, &MainWindow::menuRotateClockwise_triggered);
    connect(ui->actionRotate_Counterclockwise, &QAction::triggered, this, &MainWindow::menuRotateCounterClockwise_triggered);
    connect(ui->actionFlip_Vertically, &QAction::triggered, this, &MainWindow::menuFlipV_triggered);
    connect(ui->actionFlip_Horizontally, &QAction::triggered, this, &MainWindow::menuFlipH_triggered);
    connect(ui->actionResize_Canvas, &QAction::triggered, this, &MainWindow::menuResizeCanvas_triggered);

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

void MainWindow::menuNewFile_triggered()
{
    NewFileDialog dialog;
    dialog.exec();
}

void MainWindow::menuOpen_triggered()
{
    QString selfilter = tr("Sprite (*.ssp)");
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open Sprite File"),
                QDir::homePath(),
                tr("All files (*.*);;Sprite (*.ssp)"),
                &selfilter);
    qDebug() << filename;
}

void MainWindow::menuSave_triggered()
{
    qDebug() << "Save";
}

void MainWindow::menuSaveAs_triggered()
{
//    QFileDialog dialog;
//    dialog.setAcceptMode(QFileDialog::AcceptSave);
//    dialog.exec();
    QString selfilter = tr("Sprite (*.ssp)");
    QString filename = QFileDialog::getSaveFileName(
                this,
                tr("Save File As..."),
                QDir::homePath(),
                tr("All files (*.*);;Sprite (*.ssp)"),
                &selfilter);
    filename += ".ssp";
    qDebug() << filename;
}

void MainWindow::menuExportAs_triggered()
{
    qDebug() << "Export As...";
}

void MainWindow::menuImport_triggered()
{
    qDebug() << "Import";
}

void MainWindow::menuRotateClockwise_triggered()
{
    qDebug() << "Rotate Clockwise";
}

void MainWindow::menuRotateCounterClockwise_triggered()
{
    qDebug() << "Rotate Counterclockwise";
}

void MainWindow::menuFlipV_triggered()
{
    qDebug() << "Flip Vertically";
}

void MainWindow::menuFlipH_triggered()
{
    qDebug() << "Flip Horizontally";
}

void MainWindow::menuResizeCanvas_triggered()
{
    qDebug() << "Resize Canvas";
}

void MainWindow::menuHelp_triggered()
{
    qDebug() << "Help!";
}

void MainWindow::colorWheel_colorChanged(QColor color)
{
    ui->colorPreview_widget->setColor(color);
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




void MainWindow::on_brush_pushButton_clicked()
{
    model.setTool(model.BRUSH);
}

void MainWindow::on_fillBucket_pushButton_clicked()
{
    model.setTool(model.FILL_BUCKET);
}

void MainWindow::on_eraser_pushButton_clicked()
{
    model.setTool(model.ERASER);
}

void MainWindow::on_rotate_pushButton_clicked()
{
    scene->rotate(true);
}

void MainWindow::on_pushButton_clicked()
{
    model.setTool(model.PAN);
}

void MainWindow::on_symmetricalTool_pushButton_clicked()
{
    model.setTool(model.MIRROR);
}

void MainWindow::on_flipV_pushButton_clicked()
{
    scene->flip(true);
}

void MainWindow::on_flipH_pushButton_clicked()
{
    scene->flip(false);
}
