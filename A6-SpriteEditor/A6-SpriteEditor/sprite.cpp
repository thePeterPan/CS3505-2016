#include "sprite.h"
/**
 * @brief Sprite::Sprite Default constructor for Sprite
 * @param parent
 */
Sprite::Sprite(QObject *parent) :
    QObject(parent), currentFrameIndex(0), width(0), height(0)
{}
/**
 * @brief Sprite::Sprite Add width, height for new Sprite
 * @param width_
 * @param height_
 * @param parent
 */
Sprite::Sprite(int width_, int height_, QObject *parent) :
    QObject(parent), currentFrameIndex(0), width(width_), height(height_)
{
    frames << new Frame(width, height);
}
/**
 * @brief Sprite::~Sprite Destructor for sprite
 */
Sprite::~Sprite() {}


//// Accessor Methods ////

/**
 * @brief Sprite::getAnimationLength
 * @return Returns the number of frames in a sprite
 */
int Sprite::getAnimationLength()
{
    return frames.size();
}

/**
 * @brief Sprite::getWidth
 * @return Width of Sprite (number of columns)
 */
int Sprite::getWidth()
{
    return width;
}
/**
 * @brief Sprite::getHeight
 * @return Height of Sprite (number of rows)
 */
int Sprite::getHeight()
{
    return height;
}


//// Frame Manipulation Methods ////
/**
 * @brief Sprite::addFrameAt Adds a new frame at specified index
 * @param index
 */
void Sprite::addFrameAt(int index)
{
    Frame* newFrame(frames.at(currentFrameIndex)->clone());
    frames.insert(index, newFrame);
    ++currentFrameIndex;
}
/**
 * @brief Sprite::addFrameAfterCurrentIndex Appends new frame after current index
 */
void Sprite::addFrameAfterCurrentIndex()
{
    addFrameAt(currentFrameIndex + 1);
}
/**
 * @brief Sprite::removeFrameAt Removes frame at specified index
 * @param index
 */
void Sprite::removeFrameAt(int index)
{
    if (frames.size() > 1 && index >= 0 && index < frames.size())
    {
        frames.removeAt(index);
        if (--currentFrameIndex < 0)
            currentFrameIndex = 0;
    }
}
/**
 * @brief Sprite::removeCurrentFrame Removes the current frame
 */
void Sprite::removeCurrentFrame()
{
    removeFrameAt(currentFrameIndex);
}
/**
 * @brief Sprite::nextFrame Changes current frame to next frame
 */
void Sprite::nextFrame()
{
    setCurrentFrame(currentFrameIndex + 1);
}
/**
 * @brief Sprite::prevFrame Changes current frame to previous frame
 */
void Sprite::prevFrame()
{
    setCurrentFrame(currentFrameIndex - 1);
}
/**
 * @brief Sprite::setCurrentFrame Sets current frame to frame at specified index
 * @param index
 */
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
/**
 * @brief Sprite::getCurrentFrameIndex Gets the index of the current frame
 * @return
 */
int Sprite::getCurrentFrameIndex()
{
    return currentFrameIndex;
}

//// Drawing Methods ////

/**
 * @brief Sprite::setPixelColorAtCurrentFrame Sets the color for the designated pixel
 * @param x - x coordinate
 * @param y - y coordinate
 * @param color - color to set
 */
void Sprite::setPixelColorAtCurrentFrame(int x, int y, QColor color)
{
    frames.at(currentFrameIndex)->setPixelColor(x, y, color);
}
/**
 * @brief Sprite::getPixelColorAtCurrentFrame
 * @param x - x coordinate
 * @param y - y coordinate
 * @return Returns color of the designated pixel
 */
QColor Sprite::getPixelColorAtCurrentFrame(int x, int y)
{
    return frames.at(currentFrameIndex)->getPixelColor(x, y);
}
/**
 * @brief Sprite::rotateCurrentFrame Rotates the current frame
 * @param direction Rotates clockwise if true, counter-clockwise if false
 */
void Sprite::rotateCurrentFrame(bool direction)
{
    if(width == height)
        frames.at(currentFrameIndex)->rotate(direction);
    else
    {
        for(int i = 0; i < frames.size(); i++)
            frames.at(i)->rotate(direction);
        int temp = height;
        height = width;
        width = temp;
    }
}
/**
 * @brief Sprite::flipCurrentFrameOrientation Flips the frame according to orientation
 * @param orientation Flips vertical if true, horizontal if false
 */
void Sprite::flipCurrentFrameOrientation(bool orientation)
{
    frames.at(currentFrameIndex)->flip(orientation);
}
/**
 * @brief Sprite::invertCurrentFrameColor Inverts the colors of the current frame
 */
void Sprite::invertCurrentFrameColor()
{
    frames.at(currentFrameIndex)->invert();
}

/**
 * @brief Sprite::paintEntireFrame Paints the entire frame a certain color
 * @param color The color to paint the frame
 */
void Sprite::paintEntireFrame(QColor color)
{
    frames.at(currentFrameIndex)->setWholeFrameColor(color);
}


//// Save to file methods ////

/**
 * @brief Sprite::toString
 * @return String of necessary information to save Sprite
 */
QString Sprite::toString()
{
    QString result =
            QString::number(height) + " " + QString::number(width) + "\n" +
            QString::number(frames.size()) + "\n";
    foreach (Frame* frame, frames)
    {
        result += frame->toString();
    }
    return result;
}
/**
 * @brief Sprite::getFramesAsImages
 * @return List of QImages from Sprite's frames
 */
QList<QImage*> Sprite::getFramesAsImages()
{
    QList<QImage*> imageList;

    foreach (Frame* frame, frames)
    {
        imageList << frame->toQImage();
    }

    return imageList;
}
/**
 * @brief Sprite::getFrameAsImage
 * @param index
 * @return QImage from frame at specified index
 */
QImage* Sprite::getFrameAsImage(int index)
{
    QImage* image(frames.at(index)->toQImage());
    return image;
}
