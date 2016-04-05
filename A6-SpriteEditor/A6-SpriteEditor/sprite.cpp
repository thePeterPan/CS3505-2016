#include "sprite.h"

Sprite::Sprite(QObject *parent) :
    QObject(parent), currentFrameIndex(0), width(0), height(0)
{

}

Sprite::Sprite(int width_, int height_, QObject *parent) :
    QObject(parent), currentFrameIndex(0), width(width_), height(height_)
{
    frames << new Frame(width, height);
}

Sprite::~Sprite() { }


//// Accessor Methods ////

int Sprite::getAnimationLength()
{
    return frames.size();
}

int Sprite::getWidth()
{
    return width;
}

int Sprite::getHeight()
{
    return height;
}


//// Frame Manipulation Methods ////

//Frame* Sprite::getFrameAt(int index)
//{
//    return frames[index];
//}

//QList<Frame*> Sprite::getFrames()
//{
//    return frames;
//}

void Sprite::addFrameAt(int index)
{
    Frame* newFrame(frames.at(currentFrameIndex)->clone());
    frames.insert(index, newFrame);
    ++currentFrameIndex;
}

void Sprite::addFrameAfterCurrentIndex()
{
    addFrameAt(currentFrameIndex + 1);
}

void Sprite::removeFrameAt(int index)
{
    if (frames.size() > 1 && index >= 0 && index < frames.size())
    {
        frames.removeAt(index);
        if (--currentFrameIndex < 0)
            currentFrameIndex = 0;
    }
}

void Sprite::removeCurrentFrame()
{
    removeFrameAt(currentFrameIndex);
}

void Sprite::nextFrame()
{
    setCurrentFrame(currentFrameIndex + 1);
}

void Sprite::prevFrame()
{
    setCurrentFrame(currentFrameIndex - 1);
}

void Sprite::setCurrentFrame(int index)
{
    if (index < 0)
    {
        currentFrameIndex = 0;
    }
    else if (index >= frames.size())
    {
        currentFrameIndex = frames.size() - 1;
    }
    else
    {
        currentFrameIndex = index;
    }
}

int Sprite::getCurrentFrameIndex()
{
    return currentFrameIndex;
}



//// Drawing Methods ////

void Sprite::setPixelColorAtCurrentFrame(int x, int y, QColor color)
{
    frames.at(currentFrameIndex)->setPixelColor(x, y, color);
}

QColor Sprite::getPixelColorAtCurrentFrame(int x, int y)
{
    return frames.at(currentFrameIndex)->getPixelColor(x, y);
}

void Sprite::rotateCurrentFrame(bool direction)
{
    if(width == height)
        frames.at(currentFrameIndex)->rotate(direction);
    else{
        for(int i = 0; i < frames.size(); i++)
            frames.at(i)->rotate(direction);
        int temp = height;
        height = width;
        width = temp;
        //TODO: change height, width, etc.
    }
}

void Sprite::flipCurrentFrameOrientation(bool orientation)
{
    frames.at(currentFrameIndex)->flip(orientation);
}

void Sprite::invertCurrentFrameColor()
{
    frames.at(currentFrameIndex)->invert();
}


//// Save to file methods ////

QString Sprite::toString()
{
    QString result =
            QString::number(width) + " " + QString::number(height) + "\n" +
            QString::number(frames.size()) + "\n";
    foreach (Frame* frame, frames)
    {
        result += frame->toString();
    }
    return result;
}

QList<QImage*> Sprite::getFramesAsImages()
{
    QList<QImage*> imageList;

    foreach (Frame* frame, frames)
    {
        imageList << frame->toQImage();
    }

    return imageList;
}

QImage* Sprite::getFrameAsImage(int index)
{
    QImage* image(frames.at(index)->toQImage());
    return image;
}
