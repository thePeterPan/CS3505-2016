#include "sprite.h"

/**
 * Constructor
 *
 * @brief sprite::sprite
 * @param parent
 */
Sprite::Sprite(QObject *parent) :
    QObject(parent), width(0), height(0), file_saved(false), sprite_title("New Sprite")
{

}

Sprite::Sprite(int width_, int height_, QString title_, QObject *parent) :
    QObject(parent), width(width_), height(height_), file_saved(false),
    sprite_title(title_)
{

}

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
Frame* Sprite::getFrame(int index)
{
    return frames[index];
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
//    frames.removeAt(index);
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

QString Sprite::toString(){
    QString result;

    result += "Sprite:";
    result += QString::number(width);
    result += ",";
    result += QString::number(height);
    result += "\n";// + "," + height + "\n";

    foreach(Frame* f, frames){
        result += f->toString();
    }

    return result;
}
