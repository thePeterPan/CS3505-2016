#ifndef TEMPORARYSPRITE_H
#define TEMPORARYSPRITE_H

#include <QPainter>
#include <QString>
#include <Box2D/Box2D.h>
#include <QDebug>


class TemporarySprite
{

public:
    TemporarySprite();
    TemporarySprite(b2Body * body, QString letter, int width);
    void draw(QPainter * painter);
    QString getLetter();

private:
    b2Body * body;
    QString letter;
    int width;

};

#endif // TEMPORARYSPRITE_H
