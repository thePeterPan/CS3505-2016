#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QPoint>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <iostream>
#include <QImage>
#include "frame.h"


class GraphicsScene : public QGraphicsScene
{
    QImage * image;
    QBrush * brush;
    Frame * frame;
    int width, height, pixelSize;
    //Q_OBJECT
public:
    GraphicsScene(QObject *parent = 0);
    GraphicsScene(QObject *parent = 0, int width = 10, int height = 10, int pixelSize = 50);
    ~GraphicsScene();

    void setSceneRect(const QRectF &rect);
    void setSceneRect(int x, int y, int width, int height);
    void setColor(QColor color);

signals:

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    //void wheelEvent(QGraphicsSceneWheelEvent *wheelEvent);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void update(const QRectF &rect);


};

#endif // GRAPHICSSCENE_H
