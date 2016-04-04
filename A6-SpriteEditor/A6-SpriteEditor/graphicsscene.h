#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
// Qt Graphics Objects
#include <QImage>
#include <QGraphicsItem>
#include <QPainter>
// Qt Events
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
// Other Qt Objects
#include <QPoint>

#include "editor_model.h"


class GraphicsScene : public QGraphicsScene
{

public:

    GraphicsScene(editor_model* model, int width, int height, int pixelSize, QObject *parent = 0);
    ~GraphicsScene();

    // Drawing methods:
    void prepareBackground(bool replace);
    void clearScene();
    void redrawScene();
    void paintEntireFrame();
    void drawSquare(int x, int y);

    // Used to resize the scene (allow for zoom in and out)
    void setSceneRect(const QRectF &rect);
    void setSceneRect(int x, int y, int width, int height);

signals:

private:
    // Graphics Objects
    QImage * image;
    QVector<QVector<QGraphicsRectItem*>> pixels;
    int pixelSize;
    int minPixelSize = 5;
    int maxPixelSize = 100;
    int pixelInterval = 5;

    // Model
    editor_model* model;

public slots:
    void zoomIn();
    void zoomOut();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void wheelEvent(QGraphicsSceneWheelEvent *wheelEvent);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);

    void update(const QRectF &rect);


};

#endif // GRAPHICSSCENE_H
