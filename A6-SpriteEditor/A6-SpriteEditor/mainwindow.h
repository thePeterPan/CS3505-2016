#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
// Qt Graphics objects
#include <QPushButton>
#include <QToolButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSlider>
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFileDialog>
// Other Qt Objects
#include <QCloseEvent>
#include <QString>
#include <QDebug>
#include <QFileInfo>
// from Qt-Color-Widgets library
#include <ColorDialog>
#include <ColorWheel>
#include <QDesktopServices>

#include "graphicsscene.h"
#include "editor_model.h"
#include "newfiledialog.h"
#include "previewscene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget * parent = 0);
    ~MainWindow();

public slots:

private:
    Ui::MainWindow* ui;
    GraphicsScene* scene;
    EditorModel* model;
    PreviewScene* preview;

    void connectSignalsAndSlots();
    void initializeUIDefaults();

    void setNewGraphicsScene();
    void setNewPreviewScene();

signals:

public slots:

private slots:
    // File Menu:
    void menuNewFile_triggered();
    void menuOpen_triggered();
    void menuSave_triggered();
    void menuSaveAs_triggered();
    void menuExportAs_triggered();

    // Edit Menu:
    void menuRotateClockwise_triggered();
    void menuRotateCounterClockwise_triggered();
    void menuFlipV_triggered();
    void menuFlipH_triggered();

    // Help Menu:
    void menuHelp_triggered();

    // State properties:
    void colorWheel_colorChanged(QColor color);
    void alphaSlider_valueChanged(int value);

    // Toolbar buttons:
    void brush_pushButton_clicked();
    void fillBucket_pushButton_clicked();
    void eraser_pushButton_clicked();
    void rotateCCW_pushButton_clicked();
    void rotateCW_pushButton_clicked();
    void symmetricalTool_pushButton_clicked();
    void flipV_pushButton_clicked();
    void flipH_pushButton_clicked();
    void invertColors_pushButton_clicked();
    void toolUpdated(EditorModel::Tool new_tool);

    // Playback buttons:
    void play_pushButton_clicked();
    void playbackSpeed_horizontalSlider_valueChanged(int value);
//    void playbackSpeed_hSlider_moved(int value);

    // Frames:
    void update_currentFrameStatus(int currentFrame, int numOfFrames);

    // Window Title:
    // true if file was just saved, false if file has been modified.
    void fileSavedEvent(bool status);
protected:
    virtual void closeEvent(QCloseEvent *event);

};

#endif // MAINWINDOW_H
