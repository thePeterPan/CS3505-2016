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
    TemporarySprite();
    TemporarySprite(b2Body * body, QString letter, int width);
    void draw(QPainter * painter);
    QString getLetter();
    b2Body * getBody();
    void update(int xScale, int yScale, int height);
    void resize(int sizeScale);

private:
    b2Body * body;
    QString letter;
    int width,scale,x,y;
    QPixmap * image;
    QPixmap * image2;
    QFont font;
    QTransform transform;
    float size;

};

#endif // TEMPORARYSPRITE_H
