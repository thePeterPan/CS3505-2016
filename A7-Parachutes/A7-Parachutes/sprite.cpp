#include "sprite.h"

Sprite::Sprite()
{
    x = 50;
    y = 50;
    currentFrame = 0;
    image = new QPixmap("images/crate_sprite.png");
    (*image) = image->scaled(100,100,Qt::KeepAspectRatioByExpanding);
}

void Sprite::draw(QPainter *painter)
{
    painter->drawPixmap(x,y,*image,currentFrame,0,100,100);
    nextFrame();
}

void Sprite::nextFrame()
{
    currentFrame += 100;
    if(currentFrame > 2350)
        currentFrame = 0;
}
