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

public:
    QImage * image;
    QBrush * brush;
    Sprite * sprite;
    Frame * currentFrame;
    int currentFrameIndex;
    QVector<QVector<QGraphicsRectItem*>> pixels;
    editor_model* editor;
    int width, height, pixelSize;

    int minPixelSize = 5;
    int maxPixelSize = 100;
    int pixelInterval = 5;

    void paintCommand(int x, int y);
    void drawSquare(int x, int y, QColor color);
    void fillBucket(int x, int y, QColor color);
    void paintEntireFrame();
    void drawMirror(int x, int y, QColor color);
    void erase(int x, int y);
    void prepareBackground(bool replace);


    GraphicsScene(editor_model* editor, int width, int height, int pixelSize, QObject *parent = 0);
    ~GraphicsScene();

    void setSceneRect(const QRectF &rect);
    void setSceneRect(int x, int y, int width, int height);
    void setBrushColor(QColor color);
    void rotateScene(bool direction);
    void flipSceneOrientation(bool orientation);
    void invertSceneColors();
    void addFrame();
    void removeFrame();
    void previousFrame();
    void nextFrame();
    void redrawScene(Sprite* sprite);

signals:
    void frameUpdated(int currentFrameIndex, int totalFrames);

private:


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
