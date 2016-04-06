#ifndef PREVIEWSCENE_H
#define PREVIEWSCENE_H

#include <QGraphicsScene>
#include <QImage>
#include <QList>
#include <QTimer>

#include "editor_model.h"
#include "sprite.h"


class PreviewScene : public QGraphicsScene
{
    Q_OBJECT

public:
    PreviewScene(EditorModel* model, QObject *parent = 0, int sceneWidth = 230, int sceneHeight=218);

private:
    // Model
    EditorModel* model;

    // Parameters
    int sceneWidth, sceneHeight;
    int imageIndex, maxindex;
    QList<QImage*> frames;

    // Methods
    void updateFrames();

protected slots:
    void updateFromSprite();
    void showNextImage();
};

#endif // PREVIEWSCENE_H
