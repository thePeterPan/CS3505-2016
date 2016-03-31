#ifndef SPRITE_H
#define SPRITE_H

// Qt Graphics Objects
#include <QObject>
#include <QList>
// Other Qt Objects
#include <QString>

#include "frame.h"

class Sprite : public QObject
{
    Q_OBJECT
public:
    explicit Sprite(QObject *parent = 0);
    explicit Sprite(int width_, int height_, QString title, QObject * parent = 0);
    int getAnimationLength();
    Frame* getFrame(int index);
    void addFrame(Frame* frame);
    void removeFrameAt(int index);
    int getWidth();
    int getHeight();
    bool getFileSavedStatus();
    void setFileSavedStatus(bool status);
    QString toString();
    QList<Frame*> getFrames();

private:
    QList<Frame*> frames;
    int width;
    int height;

    bool file_saved;
    QString sprite_title;

signals:

public slots:

};

#endif // SPRITE_H
