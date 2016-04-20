#ifndef SPRITE_H
#define SPRITE_H

#include <QPainter>
#include <QString>

class Sprite
{
public:
    Sprite();
    Sprite(int x, int y, int width, int height, int numFrames, QString filepath);
    ~Sprite();

    void draw(QPainter * painter);

    void setX(int newX);
    int getX();
    void setY(int newY);
    int getY();
    void nextFrame();

private:

    QPixmap * image;
    int currentFrame, numFrames;
    int x, y, width, height;

};

#endif // SPRITE_H
