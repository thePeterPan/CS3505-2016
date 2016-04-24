#include "temporarysprite.h"

TemporarySprite::TemporarySprite()
{

}

TemporarySprite::TemporarySprite(b2Body *body, QString letter) : body(body), letter(letter)
{
    //ok
}

void TemporarySprite::draw(QPainter *painter)
{
    // Need to make these things global parameters:::
    int height = 645;
    int scale = 100;
    //-----

    int x = body->GetPosition().x * scale;
    int y = height - body->GetPosition().y * scale;

    painter->setBrush(Qt::cyan);

    painter->drawRect(x-50,y-50,100,100);
    painter->drawText(x-25,y-25,50,50,1,letter);
}

QString TemporarySprite::getLetter()
{
    return letter;
}
