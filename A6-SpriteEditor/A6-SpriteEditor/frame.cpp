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
frame::frame(int width, int height, QObject *parent) :
    QObject(parent), width_(width), height_(height)
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
    frameMatrix[x][y] = color;
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
    return width_;
}

/**
 * @brief frame::getFrameHeight
 * @return
 */
int frame::getFrameHeight()
{
    return height_;
}
