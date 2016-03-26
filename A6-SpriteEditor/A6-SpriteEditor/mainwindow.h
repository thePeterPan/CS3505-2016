#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QPushButton>
#include <QToolButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSlider>
#include <QLabel>
#include <QGraphicsView>

#include <QCloseEvent>
#include <QString>

#include <ColorDialog>
#include <ColorWheel>

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

    /// UI Elements
    QGridLayout * leftSidebar_GLayout;
        QPushButton * colorPicker_pushButton;
        // Line* line_3;
        QSlider * playbackSpeed_horizontalSlider;
	    QLabel *playbackSpeed_label;
        QGraphicsView * preview_graphicsView;
        QPushButton * shapes_pushButton;
        QPushButton * tools_pushButton;
        // Spacer * verticalSpacer_2;
    QVBoxLayout * imageView_VLayout;
        QHBoxLayout * mainEditor_HLayout;
            QPushButton * nextFrame_pushButton;
            QPushButton * play_pushButton;
            QPushButton * prevFrame_pushButton;
        QGraphicsView * graphicsView;
    QVBoxLayout * rightSidebar_VLayout;
        QToolButton * placeholder1;
        QToolButton * placeholder2;
        QToolButton * placeholder3;
        QToolButton * placeholder4;
        // Spacer * verticalSpacer;
    // Line line;
    // Line line_2;

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
