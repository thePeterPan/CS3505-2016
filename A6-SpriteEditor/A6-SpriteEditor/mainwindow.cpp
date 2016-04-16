#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * @brief MainWindow::MainWindow creates a new MainWindow object
 * @param parent pointer to parent object to construct
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new EditorModel();
    update_currentFrameStatus(0,1);


    setNewGraphicsScene();
    setNewPreviewScene();

    connectSignalsAndSlots();
    initializeUIDefaults();
}

/**
 * @brief MainWindow::~MainWindow destructor that deletes the ui object
 */
MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    delete model;
    delete preview;
}

/**
 * @brief creates a default graphicsscene for our sprite editor for the user to manipulate
 */
void MainWindow::setNewGraphicsScene()
{
    scene = new GraphicsScene(model, 20, 20, 20, ui->graphicsView);
    model->setBrushColor(ui->colorWheel_widget->color());
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}

/**
 * @brief creates a new preview scene object for us to preview the user's sprite
 */
void MainWindow::setNewPreviewScene()
{
    preview = new PreviewScene(model, ui->graphicsView);
    ui->preview_graphicsView->setScene(preview);
    ui->preview_graphicsView->show();
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
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::close);

    /// Edit Menu:
    connect(ui->actionRotate_Clockwise, &QAction::triggered, this, &MainWindow::menuRotateClockwise_triggered);
    connect(ui->actionRotate_Counterclockwise, &QAction::triggered, this, &MainWindow::menuRotateCounterClockwise_triggered);
    connect(ui->actionFlip_Vertically, &QAction::triggered, this, &MainWindow::menuFlipV_triggered);
    connect(ui->actionFlip_Horizontally, &QAction::triggered, this, &MainWindow::menuFlipH_triggered);

    /// Help Menu:
    connect(ui->viewTutorialItem, &QAction::triggered, this, &MainWindow::menuHelp_triggered);

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
    connect(ui->symmetricalTool_pushButton, &QToolButton::clicked, this, &MainWindow::symmetricalTool_pushButton_clicked);
    connect(ui->flipV_pushButton, &QToolButton::clicked, this, &MainWindow::flipV_pushButton_clicked);
    connect(ui->flipH_pushButton, &QToolButton::clicked, this, &MainWindow::flipH_pushButton_clicked);
    connect(ui->invertColors_pushButton, &QToolButton::clicked, this, &MainWindow::invertColors_pushButton_clicked);
    connect(ui->zoomIn_pushButton, &QPushButton::clicked, scene, &GraphicsScene::zoomIn);
    connect(ui->zoomOut_pushButton, &QPushButton::clicked, scene, &GraphicsScene::zoomOut);
    connect(model, &EditorModel::toolChanged, this, &MainWindow::toolUpdated);

    /// Frame Controls
    connect(ui->addFrame_pushButton, &QPushButton::clicked, model, &EditorModel::addFrame);
    connect(ui->removeFrame_pushButton, &QPushButton::clicked, model, &EditorModel::removeFrame);
    /// Frame Slider
    connect(ui->currentFrame_horizontalSlider, &QSlider::valueChanged, model, &EditorModel::setCurrentFrame);

    /// Playback Controls:
    connect(ui->prevFrame_pushButton, &QPushButton::clicked, model, &EditorModel::prevFrame);
    connect(ui->nextFrame_pushButton, &QPushButton::clicked, model, &EditorModel::nextFrame);
    connect(ui->play_pushButton, &QPushButton::clicked, this, &MainWindow::play_pushButton_clicked);
    connect(ui->playbackSpeed_horizontalSlider, &QSlider::valueChanged, this, &MainWindow::playbackSpeed_horizontalSlider_valueChanged);

    /// Connections from the model
    connect(model, &EditorModel::sceneUpdated, scene, &GraphicsScene::redrawScene);
    connect(model, &EditorModel::squareUpdated, scene, &GraphicsScene::drawSquare);
    connect(model, &EditorModel::frameUpdated, this, &MainWindow::update_currentFrameStatus);
    connect(model, &EditorModel::fileSaved, this, &MainWindow::fileSavedEvent);
}

/**
 * @brief Initializes the defaults of our GUI
 */
void MainWindow::initializeUIDefaults()
{
    // Main Window:
    setWindowTitle("Sprite Editor - New Sprite");

    /// Speed Slider
    ui->playbackSpeed_horizontalSlider->setMinimum(1);
    ui->playbackSpeed_horizontalSlider->setMaximum(25);
    ui->playbackSpeedCurrent_label->setText(QString::number(ui->playbackSpeed_horizontalSlider->value()));

    /// Alpha Slider
    ui->alphaSlider_widget->setMinimum(0);
    ui->alphaSlider_widget->setMaximum(255);
    ui->alphaSlider_widget->setValue(255);
    ui->alphaSlider_widget->setFirstColor(QColor::fromRgba(qRgba(0,0,0,0)));
    ui->alphaSlider_widget->setLastColor(QColor::fromRgba(qRgba(0,0,0,255)));

    /// Frame Slider
    ui->currentFrame_horizontalSlider->setMinimum(0);
    ui->currentFrame_horizontalSlider->setMaximum(0);
    ui->currentFrame_horizontalSlider->setValue(0);
    ui->currentFrame_horizontalSlider->setSingleStep(1);
    ui->currentFrame_horizontalSlider->setPageStep(1);
    update_currentFrameStatus(0,1);

    /// Toolbar buttons
    brush_pushButton_clicked();
}

/**
 * @brief Triggered when the user selects File->New File
 */
void MainWindow::menuNewFile_triggered()
{
    NewFileDialog dialog;

    if(dialog.exec() == QDialog::Accepted)
    {
        Sprite* s = new Sprite(dialog.getWidth(), dialog.getHeight());
        model->setSprite(s);
        model->newSprite();

        if(dialog.hasBgColor())
        {
            model->getSprite()->paintEntireFrame(dialog.getBgColor());
        }

        scene->redrawScene();
        update_currentFrameStatus(0,1);

        setWindowTitle("Sprite Editor - " + dialog.getTitle());
    }
}

/**
 * @brief Triggered when the user selects File->Open
 */
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

/**
 * @brief Triggered when the user selects File->Save
 */
void MainWindow::menuSave_triggered()
{
    if (model->getFilePath() == "")
    {
        menuSaveAs_triggered();
        return;
    }

    model->saveToFile(model->getFilePath());
}

/**
 * @brief Triggered when the user selects File->Save As...
 */
void MainWindow::menuSaveAs_triggered()
{
    QFileDialog saveAsDialog(this,
                             tr("Save File As..."),
                             QDir::homePath(),
                             tr("Sprite (*.ssp);;All files (*.*)"));
    saveAsDialog.setAcceptMode(QFileDialog::AcceptSave);
    // If user did not hit cancel:
    if (saveAsDialog.exec())
    {
        // Get the file name input by the user
        QString filename = saveAsDialog.selectedFiles().at(0);

        // Check to see if the user appended an extension, add if they didn't
        if (!filename.endsWith(".ssp", Qt::CaseInsensitive))
            filename += ".ssp";

        model->saveToFile(filename);
    }
}

/**
 * @brief Triggered when the user selects File->Export as GIF
 */
void MainWindow::menuExportAs_triggered()
{
    QFileDialog exportAsDialog(this,
                               tr("Export as GIF"),
                               QDir::homePath(),
                               tr("GIF (*.gif);;All files (*.*)"));
    exportAsDialog.setAcceptMode(QFileDialog::AcceptSave);
    exportAsDialog.setLabelText(QFileDialog::Accept, "Export");
    // If user did not hit cancel:
    if (exportAsDialog.exec())
    {
        // Get the file name input by the user
        QString filename = exportAsDialog.selectedFiles().at(0);

        // Check to see if the user appended an extension, add if they didn't
        if (!filename.endsWith(".gif", Qt::CaseInsensitive))
            filename += ".gif";

        model->exportSpriteAsGIF(filename);
    }
}

/**
 * @brief rotates the current frame clockwise
 */
void MainWindow::menuRotateClockwise_triggered()
{
    model->rotateScene(false);
}

/**
 * @brief rotates the current frame counterclockwise
 */
void MainWindow::menuRotateCounterClockwise_triggered()
{
    model->rotateScene(true);
}

/**
 * @brief flips the current frame over the vertical axis
 */
void MainWindow::menuFlipV_triggered()
{
    model->flipSceneOrientation(true);
}

/**
 * @brief flips the current frame over the horizontal axis
 */
void MainWindow::menuFlipH_triggered()
{
    model->flipSceneOrientation(false);
}

/**
 * @brief Opens up the help menu
 */
void MainWindow::menuHelp_triggered()
{

    QString link = "https://drive.google.com/file/d/0B_Xk7ipNEG4bOThJT3FuY1NJcDQ/view?ts=57044168";
    QDesktopServices::openUrl(QUrl(link));
}

/**
 * @brief Slot that is triggered when the user selects a new color from the color wheel
 * @param color new color selected
 */
void MainWindow::colorWheel_colorChanged(QColor color)
{
    QColor alpha_color = color;
    alpha_color.setAlpha(0);
    ui->alphaSlider_widget->setFirstColor(alpha_color);
    alpha_color.setAlpha(255);
    ui->alphaSlider_widget->setLastColor(alpha_color);

    alpha_color.setAlpha(ui->alphaSlider_widget->value());

    model->setBrushColor(alpha_color);
}

/**
 * @brief Slot triggered by selection of current transparency value
 * @param value new alpha value
 */
void MainWindow::alphaSlider_valueChanged(int value)
{
    QColor color = ui->colorWheel_widget->color();
    color.setAlpha(value);

    model->setBrushColor(color);
}

/**
 * @brief erroneous
 * @param event sent
 */
void MainWindow::closeEvent(QCloseEvent *event)
{
    // http://stackoverflow.com/questions/25454648/qmainwindow-close-signal-not-emitted
    event->ignore();
    // Perform checks.
    event->accept();
}


//// Scene Drawing Events/Slots/Methods ////

/**
 * @brief user selects the brush tool to use
 */
void MainWindow::brush_pushButton_clicked()
{
    model->setCurrentTool(EditorModel::BRUSH);
}

/**
 * @brief user selects the fill bucket tool to use
 */
void MainWindow::fillBucket_pushButton_clicked()
{
    model->setCurrentTool(EditorModel::FILL_BUCKET);
}

/**
 * @brief user selects the eraser tool to use
 */
void MainWindow::eraser_pushButton_clicked()
{
    model->setCurrentTool(EditorModel::ERASER);
}

/**
 * @brief user selects the rotate counter clockwise tool to use
 */
void MainWindow::rotateCCW_pushButton_clicked()
{
    model->rotateScene(true);
}

/**
 * @brief user selects the rotate clockwise tool to use
 */
void MainWindow::rotateCW_pushButton_clicked()
{
    model->rotateScene(false);
}

/**
 * @brief user selects the mirror tool to use
 */
void MainWindow::symmetricalTool_pushButton_clicked()
{
    model->setCurrentTool(EditorModel::MIRROR);
}

/**
 * @brief user clicks the flip over the vertical axis button
 */
void MainWindow::flipV_pushButton_clicked()
{
    model->flipSceneOrientation(true);
}

/**
 * @brief user clicks the flip over the horizontal axis button
 */
void MainWindow::flipH_pushButton_clicked()
{
    model->flipSceneOrientation(false);
}

/**
 * @brief inverts the colors on the screen
 */
void MainWindow::invertColors_pushButton_clicked()
{
    model->invertSceneColors();
}

/**
 * @brief if the tool the user wants to use is changed
 * @param new_tool the new tool the user wants to use
 */
void MainWindow::toolUpdated(EditorModel::Tool new_tool)
{
    // Enable all tools:
    ui->brush_pushButton->setEnabled(true);
    ui->brush_pushButton->setChecked(false);
    ui->fillBucket_pushButton->setEnabled(true);
    ui->fillBucket_pushButton->setChecked(false);
    ui->eraser_pushButton->setEnabled(true);
    ui->eraser_pushButton->setChecked(false);
    ui->symmetricalTool_pushButton->setEnabled(true);
    ui->symmetricalTool_pushButton->setChecked(false);

    // Figure out which one to disable:
    switch(new_tool)
    {
    case EditorModel::BRUSH:
        ui->brush_pushButton->setEnabled(false);
        ui->brush_pushButton->setChecked(true);
        break;
    case EditorModel::FILL_BUCKET:
        ui->fillBucket_pushButton->setEnabled(false);
        ui->fillBucket_pushButton->setChecked(true);
        break;
    case EditorModel::ERASER:
        ui->eraser_pushButton->setEnabled(false);
        ui->eraser_pushButton->setChecked(true);
        break;
    case EditorModel::MIRROR:
        ui->symmetricalTool_pushButton->setEnabled(false);
        ui->symmetricalTool_pushButton->setChecked(true);
        break;
    default:
        qDebug() << "Invalid tool.";
        break;
    }
}

//// Playback ////

/**
 * @brief User presses play to iterate through all the frames
 */
void MainWindow::play_pushButton_clicked()
{
    model->iterateThroughFrames();
}

/**
 * @brief playback speed is changed
 * @param value of new playback speed
 */
void MainWindow::playbackSpeed_horizontalSlider_valueChanged(int value)
{
    ui->playbackSpeedCurrent_label->setText(QString::number(value));
    model->setPlaybackSpeed(value);
}

/**
 * @brief Update the labels for what frame we're on / how many frames there are
 * @param currentFrame index of the current frame you're on
 * @param numOfFrames the total number of frames in your animation
 */
void MainWindow::update_currentFrameStatus(int currentFrame, int numOfFrames)
{
    ui->currentFrame_horizontalSlider->setMinimum(0);
    ui->currentFrame_horizontalSlider->setMaximum(numOfFrames-1);
    ui->currentFrame_horizontalSlider->setValue(currentFrame);

    ui->currentFrameIndex_label->setText(QString::number(currentFrame + 1) + " / " + QString::number(numOfFrames));
}

//// Window Title ////

/**
 * @brief MainWindow::fileSavedEvent
 * true if file was just saved, false if file has been modified
 * @param status
 */
void MainWindow::fileSavedEvent(bool status)
{
    QFileInfo fileInfo(model->getFilePath());
    QString name;
    if (fileInfo.filePath() == "")
    {
        name = "New Sprite";
    }
    else
    {
        name = fileInfo.fileName();
    }

    if (status)
    {
        setWindowTitle("Sprite Editor - " + name);
    }
    else
    {
        setWindowTitle("* Sprite Editor - " + name);
    }
}
