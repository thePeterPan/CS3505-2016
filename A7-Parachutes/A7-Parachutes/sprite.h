#ifndef SPRITE_H
#define SPRITE_H

#include <QPainter>

class Sprite
{
public:
    Sprite();

    void draw(QPainter * painter);

    void setX();
    void setY();
    void nextFrame();

private:

    QPixmap * image;
    int currentFrame;
    int x;
    int y;

};

#endif // SPRITE_H
