#include "sprite.h"

/**
 * Constructor
 *
 * @brief sprite::sprite
 * @param parent
 */
Sprite::Sprite(QObject *parent) :
    QObject(parent), currentFrame(0), width(0), height(0), file_saved(false)
{

}

Sprite::Sprite(int width_, int height_, QObject *parent) :
    QObject(parent), currentFrame(0), width(width_), height(height_), file_saved(false)
{

}

Sprite::~Sprite() { }

/**
 * Returns the number of frames in the sprite.
 *
 * @brief sprite::getAnimationLength
 * @return
 */
int Sprite::getAnimationLength()
{
    return frames.length();
}

/**
 * @brief sprite::getFrame
 * @param index
 * @return
 */
Frame* Sprite::getFrameAt(int index)
{
    return frames[index];
}

/**
 * @brief Sprite::getFrames
 * @return
 */
QList<Frame*> Sprite::getFrames()
{
    return frames;
}

/**
 * @brief sprite::addFrame
 * @return
 */
void Sprite::addFrame(Frame* f)
{
    frames.push_back(f);
}

/**
 * @brief sprite::removeFrame
 * @param index
 */
void Sprite::removeFrameAt(int index)
{
    if (frames.size() > 1) {
        frames.removeAt(index);
    }

}

void Sprite::setCurrentFrame(int index)
{
    currentFrame = index;
}

int Sprite::getCurrentFrame()
{
    return currentFrame;
}

void Sprite::setPixelColorAtCurrentFrame(int x, int y, QColor color)
{
    frames.at(currentFrame)->setPixelColor(x, y, color);
}

QColor Sprite::getPixelColorAtCurrentFrame(int x, int y)
{
    return frames.at(currentFrame)->getPixelColor(x, y);
}

void Sprite::rotateCurrentFrame(bool direction)
{
    frames.at(currentFrame)->rotate(direction);
}

void Sprite::flipCurrentFrameOrientation(bool orientation)
{
    frames.at(currentFrame)->flip(orientation);
}

void Sprite::invertCurrentFrameColor()
{
    frames.at(currentFrame)->invert();
}

/**
 * @brief sprite::getWidth
 * @return
 */
int Sprite::getWidth()
{
    return width;
}

/**
 * @brief sprite::getHeight
 * @return
 */
int Sprite::getHeight()
{
    return height;
}

/**
 * @brief Sprite::toString
 * Used to output the sprite to a file
 * @return
 */
QString Sprite::toString()
{
    QString result;
    result += QString::number(width);
    result += " ";
    result += QString::number(height);
    result += "\n";
    result += QString::number(frames.size());
    result += "\n";
    foreach(Frame* f, frames){
        result += f->toString();
    }
    return result;
}

