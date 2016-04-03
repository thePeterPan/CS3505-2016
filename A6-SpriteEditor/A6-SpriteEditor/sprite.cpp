#include "sprite.h"

Sprite::Sprite(QObject *parent) :
    QObject(parent), currentFrameIndex(0), width(0), height(0), file_saved(false)
{

}

Sprite::Sprite(int width_, int height_, QObject *parent) :
    QObject(parent), currentFrameIndex(0), width(width_), height(height_), file_saved(false)
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

Frame* Sprite::getFrameAt(int index)
{
    return frames[index];
}

QList<Frame*> Sprite::getFrames()
{
    return frames;
}

void Sprite::addFrameAt(int index)
{
    Frame* newFrame(frames.at(currentFrameIndex));
    frames.insert(index, newFrame);
    ++currentFrameIndex;
}

void Sprite::addFrameAfterCurrentIndex()
{
    Frame* newFrame(frames.at(currentFrameIndex));
    frames.insert(++currentFrameIndex, newFrame);
}

void Sprite::removeFrameAt(int index)
{
    if (frames.size() > 1)
    {
        frames.removeAt(index);
        --currentFrameIndex;
    }
}

void Sprite::removeCurrentFrame()
{
    if (frames.size() > 1)
    {
        frames.removeAt(currentFrameIndex);
        --currentFrameIndex;
    }
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
}

void Sprite::nextFrame()
{
    if (++currentFrameIndex >= frames.size())
    {
        currentFrameIndex = frames.size() - 1;
    }
}

void Sprite::prevFrame()
{
    if (--currentFrameIndex < 0)
    {
        currentFrameIndex = 0;
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
    frames.at(currentFrameIndex)->rotate(direction);
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
            QString::number(width) + " " +
            QString::number(height) + "\n" +
            QString::number(frames.size()) + "\n";
    foreach(Frame* f, frames)
    {
        result += f->toString();
    }
    return result;
}

