#include "temporarysprite.h"

TemporarySprite::TemporarySprite(b2Body *body, QString letter, int width) : body(body), letter(letter), width(width)
{
    image = new QPixmap(":/images/crate_sprite.svg");
    (*image) = image->scaled(width, width,Qt::KeepAspectRatio);
    font = QFont("Helvetica",20);
    font.setCapitalization(QFont::AllUppercase);
}

void TemporarySprite::draw(QPainter *painter, int xScale, int yScale, int height)
{
    int x = body->GetPosition().x * xScale;
    int y = height - body->GetPosition().y * yScale;
    float angle = body->GetAngle();
    font.setPointSize(15+5*xScale / 100);

    QTransform transform;
    transform.rotateRadians(angle);
    float size = width * abs(sin(angle) * cos(angle))/ sqrt(2);
    size += width;
    size *= xScale / 100;

    painter->drawPixmap(x-size/2,y-size/2,size,size,image->transformed(transform));
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

void TemporarySprite::setLetter(QString letter)
{
    this->letter = letter;
}

void TemporarySprite::setBody(b2Body * newBody)
{
    this->body = newBody;
}
