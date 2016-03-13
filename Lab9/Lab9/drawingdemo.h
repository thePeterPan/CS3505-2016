#ifndef DRAWINGDEMO_H
#define DRAWINGDEMO_H

#include <QMainWindow>

#include <QPainter>
#include <QPen>

namespace Ui {
class DrawingDemo;
}

class DrawingDemo : public QMainWindow
{
    Q_OBJECT

public:
    explicit DrawingDemo(QWidget *parent = 0);
    ~DrawingDemo();

public slots:
    void valuesChanged();

private:
    Ui::DrawingDemo *ui;

protected:
    void paintEvent(QPaintEvent *);
};

#endif // DRAWINGDEMO_H
