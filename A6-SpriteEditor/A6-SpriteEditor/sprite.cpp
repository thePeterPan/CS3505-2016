#include "sprite.h"

/**
 * Constructor
 *
 * @brief sprite::sprite
 * @param parent
 */
sprite::sprite(QObject *parent) :
    QObject(parent), width(0), height(0), file_saved(false), sprite_title("New Sprite")
{

}

sprite::sprite(int width_, int height_, QString title_, QObject *parent) :
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

string sprite::toString(){
    string result;

    result += "Sprite:";
    result += width;
    result += ",";
    result += height;
    result += "\n";// + "," + height + "\n";

    foreach(Frame* f, frames){
        result += f->toString();
    }

    return result;
}

void sprite::save(string path)
{

}
