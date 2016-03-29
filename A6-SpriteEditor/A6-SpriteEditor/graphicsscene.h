#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QPoint>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <iostream>


class GraphicsScene : public QGraphicsScene
{
    //Q_OBJECT
public:
    GraphicsScene(QObject *parent = 0);
    //~GraphicsScene();

signals:

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // GRAPHICSSCENE_H
