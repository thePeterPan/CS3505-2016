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

    PreviewScene(EditorModel* model, QObject *parent = 0, int width = 230, int height=218);

private:

    // Model
    EditorModel* model;

    //Parameters
    int width, height;
    int index, maxindex;
    QList<QImage*> frames;

    void updateFrames();

protected slots:

    void updateSprite();
    void showNextImage();
};


#endif // PREVIEWSCENE_H
