#ifndef FRAME_H
#define FRAME_H

#include <QObject>
#include <QList>
#include <QColor>

class frame : public QObject
{
    Q_OBJECT
public:
    explicit frame(QObject *parent = 0);
    explicit frame(int width, int height, QObject *parent = 0);

    void setPixelColor(int x, int y, QColor color);
    void setWholeFrameColor(QColor color);
    QColor getPixelColor(int x, int y);
    int getFrameWidth();
    int getFrameHeight();

private:
    QList<QList<QColor> > frameMatrix;
    int width_;
    int height_;

signals:

public slots:

};

#endif // FRAME_H
