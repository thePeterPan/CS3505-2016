#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new editor_model();

    setNewGraphicsScene();

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

    /// Toolbar Buttons:
    connect(ui->brush_pushButton, &QToolButton::clicked, this, &MainWindow::brush_pushButton_clicked);
    connect(ui->fillBucket_pushButton, &QToolButton::clicked, this, &MainWindow::fillBucket_pushButton_clicked);
    connect(ui->eraser_pushButton, &QToolButton::clicked, this, &MainWindow::eraser_pushButton_clicked);
    connect(ui->rotateCCW_pushButton, &QToolButton::clicked, this, &MainWindow::rotateCCW_pushButton_clicked);
    connect(ui->rotateCW_pushButton, &QToolButton::clicked, this, &MainWindow::rotateCW_pushButton_clicked);
    connect(ui->pan_pushButton, &QToolButton::clicked, this, &MainWindow::pushButton_clicked);
    connect(ui->symmetricalTool_pushButton, &QToolButton::clicked, this, &MainWindow::symmetricalTool_pushButton_clicked);
    connect(ui->flipV_pushButton, &QToolButton::clicked, this, &MainWindow::flipV_pushButton_clicked);
    connect(ui->flipH_pushButton, &QToolButton::clicked, this, &MainWindow::flipH_pushButton_clicked);
    connect(ui->invertColors_pushButton, &QToolButton::clicked, this, &MainWindow::invertColors_pushButton_clicked);
    connect(ui->zoomIn_pushButton, &QPushButton::clicked, this->scene, &GraphicsScene::zoomIn);
    connect(ui->zoomOut_pushButton, &QPushButton::clicked, this->scene, &GraphicsScene::zoomOut);
    connect(ui->addFrame_pushButton, &QPushButton::clicked, this, &MainWindow::addFrame_pushButton_clicked);
    connect(ui->removeFrame_pushButton, &QPushButton::clicked, this, &MainWindow::removeFrame_pushButton_clicked);

    /// Playback buttons:
    connect(ui->prevFrame_pushButton, &QPushButton::clicked, this, &MainWindow::prevFrame_pushButton_clicked);
    connect(ui->nextFrame_pushButton, &QPushButton::clicked, this, &MainWindow::nextFrame_pushButton_clicked);
    connect(ui->play_pushButton, &QPushButton::clicked, this, &MainWindow::play_pushButton_clicked);

    /// Open file:
    connect(this->model,&editor_model::modelUpdated,this,&MainWindow::updateModel);

    /// Frame Index Label
    //connect(this->scene,&GraphicsScene::frameUpdated,this,&MainWindow::updateFrame);
    //connect(this->scene,SIGNAL(frameUpdated(int, int)),this,SLOT(updateFrame(int, int)));
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

void MainWindow::updateModel(Sprite* sprite)
{
    scene->redrawScene(sprite);
}

void MainWindow::updateCurrentFrameIndex(int currentFrame, int totalFrames)
{
    ui->currentFrameIndex_label->setText(QString::number(currentFrame) + " / " + QString::number(totalFrames));
}

void MainWindow::playbackSpeed_hSlider_moved(int value)
{
    ui->playbackSpeedCurrent_label->setText(QString::number(value));
}

void MainWindow::menuNewFile_triggered()
{
    NewFileDialog dialog;

    if(dialog.exec() == QDialog::Accepted)
    {
        int width = dialog.getWidth();
        int height = dialog.getHeight();
        Sprite* s = new Sprite(width,height,dialog.getTitle());
        Frame* f = new Frame(width,height);
        s->addFrame(f);
        model->setSprite(s);
        scene->redrawScene(s);
    }
}

void MainWindow::menuOpen_triggered()
{
    qDebug() << "Open:";
    QFileDialog openDialog(this,
                           tr("Open File..."),
                           QDir::homePath(),
                           tr("Sprite (*.ssp);;All files (*.*)"));
    openDialog.setAcceptMode(QFileDialog::AcceptOpen);
    openDialog.setFileMode(QFileDialog::ExistingFile);

    if (openDialog.exec())
    {
        // Get the selected file
        QString filename = openDialog.selectedFiles().at(0);

        // Load and open the selected file
        model->loadSpriteFromFile(filename);
    }
}

void MainWindow::menuSave_triggered()
{
    if (model->getFilePath() == "")
    {
        menuSaveAs_triggered();
        return;
    }

    model->saveSpriteToFile(model->getFilePath());
}

void MainWindow::menuSaveAs_triggered()
{
    QFileDialog saveAsDialog(this,
                             tr("Save File As..."),
                             QDir::homePath(),
                             tr("Sprite (*.ssp);;All files (*.*)"));
    saveAsDialog.setAcceptMode(QFileDialog::AcceptSave);
    if (saveAsDialog.exec())
    {
        // Get the file name input by the user
        QString filename = saveAsDialog.selectedFiles().at(0);

        // Check to see if the user appended an extension, add if they didn't
        if (!filename.endsWith(".ssp", Qt::CaseInsensitive))
            filename += ".ssp";

        model->saveSpriteToFile(filename);
    }
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
    scene->rotateScene(false);
}

void MainWindow::menuRotateCounterClockwise_triggered()
{
    qDebug() << "Rotate Counterclockwise";
    scene->rotateScene(true);
}

void MainWindow::menuFlipV_triggered()
{
    qDebug() << "Flip Vertically";
    scene->flipSceneOrientation(true);
}

void MainWindow::menuFlipH_triggered()
{
    qDebug() << "Flip Horizontally";
    scene->flipSceneOrientation(false);
}

void MainWindow::menuResizeCanvas_triggered()
{
    qDebug() << "Resize Canvas";
}

void MainWindow::zoomToFit_triggered()
{
    qDebug() << "Zoom To Fit";
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

    scene->setBrushColor(alpha_color);
}

void MainWindow::alphaSlider_valueChanged(int value)
{
    QColor color = ui->colorWheel_widget->color();
    color.setAlpha(value);

    scene->setBrushColor(color);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // http://stackoverflow.com/questions/25454648/qmainwindow-close-signal-not-emitted
    event->ignore();
    // Perform checks.
    event->accept();
}

void MainWindow::setNewGraphicsScene()
{
    scene = new GraphicsScene(model, 20,20,20, ui->graphicsView);
    scene->setBrushColor(ui->colorWheel_widget->color());
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}


void MainWindow::brush_pushButton_clicked()
{
    model->setCurrentTool(editor_model::BRUSH);
}

void MainWindow::fillBucket_pushButton_clicked()
{
    model->setCurrentTool(editor_model::FILL_BUCKET);
}

void MainWindow::eraser_pushButton_clicked()
{
    model->setCurrentTool(editor_model::ERASER);
}

void MainWindow::rotateCCW_pushButton_clicked()
{
    scene->rotateScene(true);
}

void MainWindow::rotateCW_pushButton_clicked()
{
    scene->rotateScene(false);
}

void MainWindow::pushButton_clicked()
{
    model->setCurrentTool(editor_model::PAN);
}

void MainWindow::symmetricalTool_pushButton_clicked()
{
    model->setCurrentTool(editor_model::MIRROR);
}

void MainWindow::flipV_pushButton_clicked()
{
    scene->flipSceneOrientation(true);
}

void MainWindow::flipH_pushButton_clicked()
{
    scene->flipSceneOrientation(false);
}

void MainWindow::invertColors_pushButton_clicked()
{
    scene->invertSceneColors();
}

void MainWindow::addFrame_pushButton_clicked()
{
    scene->addFrame();
}

void MainWindow::removeFrame_pushButton_clicked()
{
    scene->removeFrame();
}

void MainWindow::prevFrame_pushButton_clicked()
{
    scene->previousFrame();
}

void MainWindow::nextFrame_pushButton_clicked()
{
    scene->nextFrame();
}

void MainWindow::play_pushButton_clicked()
{

}
