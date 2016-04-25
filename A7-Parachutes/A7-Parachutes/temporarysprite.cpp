#include "temporarysprite.h"

TemporarySprite::TemporarySprite()
{

}

TemporarySprite::TemporarySprite(b2Body *body, QString letter, int width) : body(body), letter(letter), width(width)
{
    //ok
    image = new QPixmap(":/images/crate_sprite.svg");
    (*image) = image->scaled(width, width);
    font = QFont("Helvetica",20);
    font.setCapitalization(QFont::AllUppercase);
}

void TemporarySprite::draw(QPainter *painter)
{
    // Need to make these things global parameters:::
    int height = 635;
    int scale = 100;
    //-----

    int x = body->GetPosition().x * scale;
    int y = height - body->GetPosition().y * scale;

    painter->drawPixmap(x-width/2,y-width/2,width,width,*image);
    painter->setFont(font);
    painter->drawText(x-9,y,50,50,0,letter);
    //painter->rotate(body->GetAngle());
}

QString TemporarySprite::getLetter()
{
    return letter;
}

b2Body* TemporarySprite::getBody()
{
    return body;
}
