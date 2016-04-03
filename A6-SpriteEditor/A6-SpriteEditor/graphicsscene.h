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
    void setBrushColor(QColor color);
    void paintCommand(int x, int y);
    void drawSquare(int x, int y, QColor color);
    void fillBucket(int x, int y, QColor color);
    void drawMirror(int x, int y, QColor color);
    void paintEntireFrame();
    void erase(int x, int y);
    void redrawScene(Sprite* sprite);

    // Used to resize the scene (allow for zoom in and out)
    void setSceneRect(const QRectF &rect);
    void setSceneRect(int x, int y, int width, int height);

    // Scene manipulation
    void rotateScene(bool direction);
    void flipSceneOrientation(bool orientation);
    void invertSceneColors();

    // Move to Model
    void addFrame();
    void removeFrame();
    void previousFrame();
    void nextFrame();

signals:
    void frameUpdated(int currentFrameIndex, int totalFrames);

private:
    // Graphics Objects
    QImage * image;
    QBrush * brush;
    QVector<QVector<QGraphicsRectItem*>> pixels;
    int width, height, pixelSize;
    int minPixelSize = 5;
    int maxPixelSize = 100;
    int pixelInterval = 5;

    // Model
    editor_model* model;

    // Move to model
    int currentFrameIndex;


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
