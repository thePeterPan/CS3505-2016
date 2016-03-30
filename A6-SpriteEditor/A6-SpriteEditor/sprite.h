#ifndef SPRITE_H
#define SPRITE_H

#include <QObject>
#include <QList>
#include <QString>


#include "frame.h"

class sprite : public QObject
{
    Q_OBJECT
public:
    explicit sprite(QObject *parent = 0);
    explicit sprite(int width_, int height_, QObject * parent = 0);

    int getAnimationLength();
//    frame getFrame(int index);
//    frame addFrame();
    void removeFrameAt(int index);
    int getWidth();
    int getHeight();
    void save(QString path);
    string toString();

private:
    QList<Frame*> frames;
    int width;
    int height;

signals:

public slots:

};

#endif // SPRITE_H
