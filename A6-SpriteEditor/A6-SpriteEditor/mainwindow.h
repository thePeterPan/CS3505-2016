#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
// Graphics objects
#include <QPushButton>
#include <QToolButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSlider>
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsScene>
// Other Qt Objects
#include <QCloseEvent>
#include <QString>
// from Qt-Color-Widgets library
#include <ColorDialog>
#include <ColorWheel>

#include <QGraphicsSceneMouseEvent>
#include <iostream>

#include "graphicsscene.h"
#include "editor_model.h"

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
    editor_model model;

    void connectSignalsAndSlots();
    void initializeUIDefaults();

    void graphics();

private slots:
    void playbackSpeed_hSlider_moved(int value);
    void menuHelp_triggered();
    void colorWheel_colorChanged(QColor color);


    void on_brush_pushButton_clicked();

    void on_fillBucket_pushButton_clicked();

    void on_eraser_pushButton_clicked();

    void on_rotate_pushButton_clicked();

    void on_pushButton_clicked();

    void on_symmetricalTool_pushButton_clicked();

protected:
    virtual void closeEvent(QCloseEvent *event);



};

#endif // MAINWINDOW_H
