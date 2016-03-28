#include "sprite.h"

/**
 * Constructor
 *
 * @brief sprite::sprite
 * @param parent
 */
sprite::sprite(QObject *parent) :
    QObject(parent), width(0), height(0)
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
    return width;
}

/**
 * @brief sprite::getHeight
 * @return
 */
int sprite::getHeight()
{
    return height;
}
