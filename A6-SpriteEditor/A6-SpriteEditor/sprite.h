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
    explicit sprite(QObject *parent = 0, int width, int height);
    sprite(const sprite &obj);

    QList<frame> getFrames();
    frame getFrame(int index);
    frame addFrame();
    void removeFrame(int index);

private:
    QList<frame> frames;
    int width;
    int height;

signals:

public slots:

};

#endif // SPRITE_H
