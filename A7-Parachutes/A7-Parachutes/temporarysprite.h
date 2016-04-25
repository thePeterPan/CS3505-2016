#ifndef TEMPORARYSPRITE_H
#define TEMPORARYSPRITE_H

#include <QPainter>
#include <QString>
#include <Box2D/Box2D.h>
#include <QDebug>
#include <QPixmap>
#include <QFont>


class TemporarySprite
{

public:
    TemporarySprite();
    TemporarySprite(b2Body * body, QString letter, int width);
    void draw(QPainter * painter, bool typed);
    QString getLetter();
    b2Body * getBody();

private:
    b2Body * body;
    QString letter;
    int width;
    QPixmap * image;
    QFont font;

};

#endif // TEMPORARYSPRITE_H
