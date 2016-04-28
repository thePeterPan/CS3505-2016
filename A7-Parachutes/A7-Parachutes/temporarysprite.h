#ifndef TEMPORARYSPRITE_H
#define TEMPORARYSPRITE_H

#include <QPainter>
#include <QString>
#include <Box2D/Box2D.h>
#include <QDebug>
#include <QPixmap>
#include <QFont>
#include <QTransform>


class TemporarySprite
{

public:
    TemporarySprite(b2Body * body = 0, QString letter = "a", int width = 80);
    void draw(QPainter * painter, int xScale, int yScale, int height);
    QString getLetter();
    b2Body * getBody();
    void setLetter(QString letter);
    void setBody(b2Body*);

private:
    b2Body * body;
    QString letter;
    int width,scale;
    QPixmap * image;
    QFont font;

};

#endif // TEMPORARYSPRITE_H
