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
    ui->alphaSlider_widget->setValue(255);
    ui->alphaSlider_widget->setFirstColor(QColor::fromRgba(qRgba(0,0,0,0)));
    ui->alphaSlider_widget->setLastColor(QColor::fromRgba(qRgba(0,0,0,255)));
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
    model.loadSpriteFromFile(filename);
    qDebug() << filename;
}

void MainWindow::menuSave_triggered()
{
    if (model.getFilePath() == "")
    {
        menuSaveAs_triggered();
        return;
    }

    model.saveSpriteToFile(model.getFilePath());

    qDebug() << "Save";
}

void MainWindow::menuSaveAs_triggered()
{
    QString selfilter = tr("Sprite (*.ssp)");
    QString filename = QFileDialog::getSaveFileName(
                this,
                tr("Save File As..."),
                QDir::homePath(),
                tr("All files (*.*);;Sprite (*.ssp)"),
                &selfilter);
    if (!filename.endsWith(".ssp", Qt::CaseInsensitive))
    {
        filename += ".ssp";
    }

    QFileInfo checkFile(filename);
    if (checkFile.exists() && checkFile.isFile()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("File Exists."), tr("File already exists. Overwrite?"),
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::No) {
            return;
        }
    }

    model.saveSpriteToFile(filename);

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
    QColor color = ui->colorWheel_widget->color();
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
    scene = new GraphicsScene(&model, ui->graphicsView,2,2,60);
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
