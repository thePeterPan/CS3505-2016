#ifndef SPRITE_H
#define SPRITE_H

// Qt Graphics Objects
#include <QObject>
#include <QList>
#include <QImage>
// Other Qt Objects
#include <QString>
#include <QList>

#include "frame.h"

class Sprite : public QObject
{
    Q_OBJECT

public:
    explicit Sprite(QObject *parent = 0);
    explicit Sprite(int width_, int height_, QObject * parent = 0);
    ~Sprite();

    // Accessor methods
    int getAnimationLength();
    int getWidth();
    int getHeight();

    // Frame Methods
    void addFrameAt(int index);
    void addFrameAfterCurrentIndex();
    void removeFrameAt(int index);
    void removeCurrentFrame();
    int getCurrentFrameIndex();
    void nextFrame();
    void prevFrame();
    void setCurrentFrame(int index);

    // Current Frame Drawing methods:
    void setPixelColorAtCurrentFrame(int x, int y, QColor color);
    QColor getPixelColorAtCurrentFrame(int x, int y);
    void rotateCurrentFrame(bool direction);
    void flipCurrentFrameOrientation(bool orientation);
    void invertCurrentFrameColor();
    void paintEntireFrame(QColor color);


    // Save to file method
    QString toString();
    QList<QImage*> getFramesAsImages();
    QImage* getFrameAsImage(int index);

private:
    QList<Frame*> frames;
    int currentFrameIndex;
    int width;
    int height;
};

#endif // SPRITE_H
