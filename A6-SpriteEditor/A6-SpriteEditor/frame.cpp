#include "frame.h"

/**
 * Constructor
 *
 * @brief Frame::Frame
 * @param parent
 */
Frame::Frame(QObject *parent) :
    QObject(parent)
{

}

/**
 * Constructor
 *
 * @brief Frame::Frame
 * @param parent
 * @param width_
 * @param height_
 */
Frame::Frame(QObject *parent, int width_, int height_) :
    QObject(parent), width(width_), height(height_)
{
    for(int i = 0; i < width; i++)
    {
        frameMatrix.append(QVector<QColor>(height));
    }
}

Frame::~Frame()
{

}

/**
 * @brief Frame::setPixelColor
 * @param x
 * @param y
 * @param color
 */
void Frame::setPixelColor(int x, int y, QColor color)
{
    frameMatrix[x][y] = color;
}

/**
 * @brief Frame::setWholeFrameColor
 * @param color
 */
void Frame::setWholeFrameColor(QColor color)
{
    for(int i = 0; i < width; i++)
        for(int j=0; j < height; j++)
            frameMatrix[i][j] = color;
}

/**
 * @brief Frame::getPixelColor
 * @param x
 * @param y
 * @return
 */
QColor Frame::getPixelColor(int x, int y)
{
    return frameMatrix[x][y];
}

/**
 * @brief Frame::getFrameWidth
 * @return
 */
int Frame::getFrameWidth()
{
    return width;
}

/**
 * @brief Frame::getFrameHeight
 * @return
 */
int Frame::getFrameHeight()
{
    return height;
}

/**
 * @brief Frame::rotate
 * Rotates the vector of colors in the frame
 * @param direction
 * True: rotates clockwise
 * False: rotates counterclockwise
 */
void Frame::rotate(bool direction)
{

    if(direction)
    {
        if(width == height)
        {
            QVector<QVector<QColor>> temp(frameMatrix);
            for(int x = 0; x < width; x++)
                for(int y = 0; y < height; y++)
                    frameMatrix[x][y] = temp[width-1 - y][x];
        }
    }
}
void Frame::flip(bool vertical)
{
    QVector<QVector<QColor>> temp(frameMatrix);
    if (vertical)
    {
        for(int x = 0; x < width; x++)
            for(int y = 0; y < height; y++)
                frameMatrix[x][y] = temp[x][width - 1 - y];
    }
    else
    {
        for(int x = 0; x < width; x++)
            for(int y = 0; y < height; y++)
                frameMatrix[x][y] = temp[width - x - 1][y];
    }

}

string Frame::toString(){
    string result;
    result += "Frame\n";
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            QColor color = getPixelColor(i,j);
            result += toRgbaString(color);
            result += "\t";
        }
        result += "\n";
    }
    return result;
}

string Frame::toRgbaString(QColor color){
    stringstream ss;
    ss << color.red();
    ss << ",";
    ss << color.blue();
    ss << ",";
    ss << color.green();
    ss << ",";
    ss << color.alpha();
    return ss.str();
}

void Frame::invert()
{
    for(int x = 0; x < width; x++)
        for(int y = 0; y < height; y++)
        {
            QColor invert = frameMatrix[x][y];
            invert.setBlue(255-invert.blue());
            invert.setRed(255-invert.red());
            invert.setGreen(255-invert.green());
            frameMatrix[x][y] = invert;
        }
}
