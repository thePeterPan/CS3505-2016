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
    Q_OBJECT

public:

    GraphicsScene(EditorModel* model, int width, int height, int pixelSize, QObject *parent = 0);
    ~GraphicsScene();

    // Drawing methods:
    void prepareBackground(bool replace);
    void clearScene();
    void redrawScene();
    void paintEntireFrame();
    void drawSquare(int x, int y);

signals:

private:
    // Graphics Objects
    QImage * image;
    QVector<QVector<QGraphicsRectItem*>> pixels;
    int pixelSize;
    int minPixelSize = 1;
    int maxPixelSize = 1000;
    int pixelInterval = 5;

    // Model
    EditorModel* model;

public slots:
    void zoomIn();
    void zoomOut();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void update(const QRectF &rect);

};

#endif // GRAPHICSSCENE_H
