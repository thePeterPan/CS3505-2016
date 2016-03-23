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
 * @brief sprite::sprite
 * @param parent
 * @param width_
 * @param height_
 */
sprite::sprite(QObject *parent, int width_, int height_) :
    QObjct(parent), width(width_), height(height_)
{

}

/**
 * Copy Constructor
 *
 * @brief sprite::sprite
 * @param obj
 */
sprite::sprite(const sprite &obj)
{

}

/**
 * Constructor
 *
 * @brief sprite::~sprite
 */
sprite::~sprite()
{

}

/**
 * @brief sprite::getFrames
 * @return
 */
QList<frame> sprite::getFrames()
{

}

/**
 * @brief sprite::getFrame
 * @param index
 * @return
 */
frame sprite::getFrame(int index)
{

}

/**
 * @brief sprite::addFrame
 * @return
 */
frame sprite::addFrame()
{

}

/**
 * @brief sprite::removeFrame
 * @param index
 */
void sprite::removeFrame(int index)
{

}
