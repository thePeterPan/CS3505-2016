#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QPoint>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <iostream>
#include <QImage>
#include "frame.h"
#include "sprite.h"
#include "editor_model.h"
#include <QGraphicsItem>
#include <QPainter>


class GraphicsScene : public QGraphicsScene
{
    QImage * image;
    QBrush * brush;
    Sprite * sprite;
    Frame * currentFrame;
    QVector<QVector</*QGraphicsObject*/QGraphicsRectItem*>> pixels;
    editor_model* editor;
    int width, height, pixelSize;

    void paintCommand(int x, int y);
    void drawSquare(int x, int y, QColor color);
    void fillBucket(int x, int y, QColor color);
    void paintEntireFrame();
    void drawMirror(int x, int y, QColor color);
    void erase(int x, int y);
    void prepareBackground();

    //Q_OBJECT
public:
    //GraphicsScene(QObject *parent); // Not needed.
    GraphicsScene(editor_model* editor, int width, int height, int pixelSize, QObject *parent = 0);
    GraphicsScene(editor_model *editor, Sprite* sprite, int pixelSize, QObject *parent = 0);
    ~GraphicsScene();

    void setSceneRect(const QRectF &rect);
    void setSceneRect(int x, int y, int width, int height);
    void setColor(QColor color);
    void rotate(bool direction);
    void flip(bool vertical);
    void invert();

private:
    bool colorEquals(QColor color1, QColor color2);

signals:

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void wheelEvent(QGraphicsSceneWheelEvent *wheelEvent);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void update(const QRectF &rect);


};

#endif // GRAPHICSSCENE_H
