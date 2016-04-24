#include "temporarysprite.h"

TemporarySprite::TemporarySprite()
{

}

TemporarySprite::TemporarySprite(b2Body *body, QString letter, int width) : body(body), letter(letter), width(width)
{
    //ok
}

void TemporarySprite::draw(QPainter *painter)
{
    // Need to make these things global parameters:::
    int height = 635;
    int scale = 100;
    //-----

    int x = body->GetPosition().x * scale;
    int y = height - body->GetPosition().y * scale;
    
    painter->setBrush(Qt::cyan);

    painter->drawRect(x-width/2,y-width/2,width,width);
    painter->drawText(x,y,50,50,1,letter);
}

QString TemporarySprite::getLetter()
{
    return letter;
}
