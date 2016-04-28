#include "sprite.h"

Sprite::Sprite()
{
    x = 50;
    y = 50;
    width = 100;
    height = 100;
    currentFrame = 0;
    numFrames = 24;
    image = new QPixmap(":/images/crate_sprite.png");
    (*image) = image->scaled(width, height,Qt::KeepAspectRatioByExpanding);
}

/**
 * @brief Sprite::Sprite
 * @param x
 * @param y
 * @param width ### NEEDS TO BE THE SCALED WIDTH OF THE SPRITE ### do some math.
 * @param height
 * @param numFrames
 * @param filepath
 */
Sprite::Sprite(int x, int y, int width, int height, int numFrames, QString letter) :
    x(x),y(y),width(width),height(height),numFrames(numFrames)
{
    image = new QPixmap(":/images/crate_sprites/" + letter + ".png");
    (*image) = image->scaled(width,height,Qt::KeepAspectRatioByExpanding);
    currentFrame = 0;
}

/*
//{
//   delete image;
//}
Sprite::~Sprite()
{
    delete image;
}
*/

void Sprite::setX(int newX)
{
    x = newX;
}

int Sprite::getX()
{
    return x;
}

void Sprite::setY(int newY)
{
    y = newY;
}

int Sprite::getY()
{
    return y;
}

/**
 * @brief Sprite::draw Centers the sprite on the x,y coordinates given.
 * @param painter
 */
void Sprite::draw(QPainter *painter)
{
    painter->drawPixmap(x - (width/2),y - (height/2),*image,currentFrame * width, 0, width, height);
    nextFrame();
}

void Sprite::nextFrame()
{
    currentFrame += 1;
    if(currentFrame > numFrames-1)
        currentFrame = 0;
}
