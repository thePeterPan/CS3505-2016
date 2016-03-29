#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QPoint>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <iostream>
#include <QImage>


class GraphicsScene : public QGraphicsScene
{
    QImage * image;
    //Q_OBJECT
public:
    GraphicsScene(QObject *parent = 0);
    ~GraphicsScene();

    void setSceneRect(const QRectF &rect);
    void setSceneRect(int x, int y, int width, int height);

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
