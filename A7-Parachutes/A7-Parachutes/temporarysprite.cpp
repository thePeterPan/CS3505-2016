#include "temporarysprite.h"

TemporarySprite::TemporarySprite()
{

}

TemporarySprite::TemporarySprite(b2Body *body, QString letter, int width) : body(body), letter(letter), width(width)
{
    image = new QPixmap(":/images/crate_sprite.svg");
    image2 = new QPixmap(image->scaled(width, width,Qt::KeepAspectRatio));
    font = QFont("Helvetica",20);
    font.setCapitalization(QFont::AllUppercase);
    /*x = 0;
    y = 0;
    size = width;*/
}

void TemporarySprite::draw(QPainter *painter)
{
    painter->drawPixmap(x-size/2,y-size/2,size,size,image2->transformed(transform));
    painter->setFont(font);
    painter->drawText(x-10,y-10,50,50,0,letter);
}

QString TemporarySprite::getLetter()
{
    return letter;
}

b2Body* TemporarySprite::getBody()
{
    return body;
}

void TemporarySprite::resize(int sizeScale)
{
    (*image2) = image->scaled(width*sizeScale/100, width*sizeScale/100,Qt::KeepAspectRatio);
}

void TemporarySprite::update(int xScale, int yScale, int height)
{
    x = body->GetPosition().x * xScale;
    y = height - body->GetPosition().y * yScale;
    float angle = body->GetAngle();
    font.setPointSize(15+5*xScale / 100);
    QTransform trans;
    trans.rotateRadians(angle);
    transform = trans;
    size = width * abs(sin(angle) * cos(angle))/ sqrt(2);
    size += width;
    size *= xScale / 100;
}
