#include "temporarysprite.h"

TemporarySprite::TemporarySprite()
{

}

TemporarySprite::TemporarySprite(b2Body *body, QString letter, int width) : body(body), letter(letter), width(width)
{
    image = new QPixmap(":/images/crate_sprite.svg");
    (*image) = image->scaled(width, width,Qt::KeepAspectRatio);
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
    float angle = body->GetAngle();

    QTransform transform;
    transform.rotateRadians(angle);
    float size = width * abs(sin(angle) * cos(angle))/ sqrt(2);

    painter->drawPixmap(x-width/2,y-width/2,width+size,width+size,image->transformed(transform));
    painter->setFont(font);
    painter->drawText(x-10,y,50,50,0,letter);
}

QString TemporarySprite::getLetter()
{
    return letter;
}

b2Body* TemporarySprite::getBody()
{
    return body;
}
