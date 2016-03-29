#ifndef WIDGET_H
#define WIDGET_H
#include <iostream>
#include <QWidget>
#include <QPainter>


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0, Qt::WindowFlags f = 0) :
        QWidget(parent, f), screen_image_(256, 240, QImage::Format_RGB32) {

    }

    void draw_frame(void *data) {
        // render data into screen_image_
        // I am using fill here, but in the real thing I am rendering
        // on a pixel by pixel basis
        screen_image_.fill(rand());
    }

    void start_frame() {
        // do any pre-rendering prep work that needs to be done before
        // each frame
    }

    void end_frame() {
        //update(); // force a paint event
        repaint();
    }

    void paintEvent(QPaintEvent *) {
        std::cout << "painting" << std::endl;
        QImage image = QImage(this->size(),QImage::Format_ARGB32);
        image.allGray();
        QPainter p(&image);
        p.setPen(Qt::green);
        p.drawText(10,10,"hello tanner");
/*
        QImage image = QImage(100,100,QImage::Format_ARGB32);
        QPainter p(&image);
        //p.setPen(Qt::green);
        p.drawText(100,100,"hello");
        //p.drawImage(rect(), screen_image_, screen_image_.rect());*/
    }

    QImage screen_image_;
};
#endif // WIDGET_H
