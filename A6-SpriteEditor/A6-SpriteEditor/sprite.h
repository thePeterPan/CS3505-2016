#ifndef SPRITE_H
#define SPRITE_H

#include <QObject>
#include <QList>

#include "frame.h"

class sprite : public QObject
{
    Q_OBJECT
public:
    explicit sprite(QObject *parent = 0);
    explicit sprite(int width, int height, QObject * parent = 0);

    int getAnimationLength();
//    frame getFrame(int index);
//    frame addFrame();
    void removeFrameAt(int index);
    int getWidth();
    int getHeight();

private:
    QList<frame> frames;
    int width_;
    int height_;

signals:

public slots:

};

#endif // SPRITE_H
