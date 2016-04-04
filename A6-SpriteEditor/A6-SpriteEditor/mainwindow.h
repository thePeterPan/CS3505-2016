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
// from Qt-Color-Widgets library
#include <ColorDialog>
#include <ColorWheel>

#include "graphicsscene.h"
#include "editor_model.h"
#include "newfiledialog.h"

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
    Ui::MainWindow *ui;
    GraphicsScene* scene;
    editor_model* model;

    void connectSignalsAndSlots();
    void initializeUIDefaults();

    void setNewGraphicsScene();

signals:

public slots:

private slots:
    // File Menu:
    void menuNewFile_triggered();
    void menuOpen_triggered();
    void menuSave_triggered();
    void menuSaveAs_triggered();
    void menuExportAs_triggered();
    void menuImport_triggered();

    // Edit Menu:
    void menuRotateClockwise_triggered();
    void menuRotateCounterClockwise_triggered();
    void menuFlipV_triggered();
    void menuFlipH_triggered();
    void menuResizeCanvas_triggered();
//    void zoomToFit_triggered();

    // Help Menu:
    void menuHelp_triggered();

    // State properties:
    void playbackSpeed_hSlider_moved(int value);
    void colorWheel_colorChanged(QColor color);
    void alphaSlider_valueChanged(int value);

    // Toolbar buttons:
    void brush_pushButton_clicked();
    void fillBucket_pushButton_clicked();
    void eraser_pushButton_clicked();
    void rotateCCW_pushButton_clicked();
    void rotateCW_pushButton_clicked();
    void panPushButton_clicked();
    void symmetricalTool_pushButton_clicked();
    void flipV_pushButton_clicked();
    void flipH_pushButton_clicked();
    void invertColors_pushButton_clicked();
    void toolUpdated(editor_model::Tool new_tool);

    // Playback buttons:
    void play_pushButton_clicked();

    // Frames:
    void update_currentFrameStatus(int currentFrame, int numOfFrames);

protected:
    virtual void closeEvent(QCloseEvent *event);



};

#endif // MAINWINDOW_H
