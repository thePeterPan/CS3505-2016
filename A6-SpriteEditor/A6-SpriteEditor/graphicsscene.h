#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <iostream>
class GraphicsScene : public QGraphicsScene
{
public:
    GraphicsScene( QObject *parent = 0);

protected:
    void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent );
};
#endif // GRAPHICSSCENE_H
