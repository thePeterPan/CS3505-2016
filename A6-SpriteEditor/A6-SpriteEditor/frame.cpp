#include "frame.h"

/**
 * Constructor
 *
 * @brief frame::frame
 * @param parent
 */
frame::frame(QObject *parent) :
    QObject(parent)
{

}

/**
 * Constructor
 *
 * @brief frame::frame
 * @param parent
 * @param width_
 * @param height_
 */
frame::frame(QObject *parent, int width_, int height_) :
    QObject(parent), width(width_), height(height_)
{

}

/**
 * @brief frame::setPixelColor
 * @param x
 * @param y
 * @param color
 */
void frame::setPixelColor(int x, int y, QColor color)
{

}

/**
 * @brief frame::setWholeFrameColor
 * @param color
 */
void frame::setWholeFrameColor(QColor color)
{

}

/**
 * @brief frame::getPixelColor
 * @param x
 * @param y
 * @return
 */
QColor frame::getPixelColor(int x, int y)
{
    return frameMatrix[0][0];
}

/**
 * @brief frame::getFrameWidth
 * @return
 */
int frame::getFrameWidth()
{
    return width;
}

/**
 * @brief frame::getFrameHeight
 * @return
 */
int frame::getFrameHeight()
{
    return height;
}
