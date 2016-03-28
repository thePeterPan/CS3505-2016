#include "sprite.h"

/**
 * Constructor
 *
 * @brief sprite::sprite
 * @param parent
 */
sprite::sprite(QObject *parent) :
    QObject(parent), width_(0), height_(0)
{

}

sprite::sprite(int width, int height, QObject *parent) :
    QObject(parent), width_(width), height_(height)
{

}

/**
 * Returns the number of frames in the sprite.
 *
 * @brief sprite::getAnimationLength
 * @return
 */
int sprite::getAnimationLength()
{
    return frames.length();
}

///**
// * @brief sprite::getFrame
// * @param index
// * @return
// */
//frame sprite::getFrame(int index)
//{

//}

///**
// * @brief sprite::addFrame
// * @return
// */
//frame sprite::addFrame()
//{

//}

/**
 * @brief sprite::removeFrame
 * @param index
 */
void sprite::removeFrameAt(int index)
{
//    frames.removeAt(index);
}

/**
 * @brief sprite::getWidth
 * @return
 */
int sprite::getWidth()
{
    return width_;
}

/**
 * @brief sprite::getHeight
 * @return
 */
int sprite::getHeight()
{
    return height_;
}
