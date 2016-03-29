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
#include <QGraphicsProxyWidget>
#include <QGraphicsItem>
#include <QGraphicsScene>

#include "editor_model.h"
#include "widget.h"

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
    editor_model model;
    Widget* widget;
    void connectSignalsAndSlots();
    void initializeUIDefaults();

private slots:
    void playbackSpeed_hSlider_moved(int value);
    void menuHelp_triggered();
    void colorWheel_colorChanged(QColor color);

protected:
    virtual void closeEvent(QCloseEvent *event);

};

#endif // MAINWINDOW_H