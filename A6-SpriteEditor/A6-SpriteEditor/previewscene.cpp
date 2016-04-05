#include "previewscene.h"

PreviewScene::PreviewScene(EditorModel* _model, QObject* parent, int _width, int _height) :
    QGraphicsScene(parent), model(_model), width(_width), height(_height)
{
    updateFrames();
    index = 0;

    this->setSceneRect(0,0,width,height);

    QTimer::singleShot(500, this, SLOT(showNextImage()));
}

void PreviewScene::updateFrames()
{
    this->frames = model->getSprite()->getFramesAsImages();
    this->maxindex = frames.size();
}

void PreviewScene::showNextImage()
{
    this->clear();
    this->addPixmap(QPixmap::fromImage(frames.at(index)->scaled(width,height,Qt::KeepAspectRatio)));

    index++;
    if(index >= maxindex)
    {
        //At the end of the animation, so refresh the images and then start again.
        QTimer::singleShot(1,this,SLOT(updateSprite()));
        index = 0;
    }

    QTimer::singleShot(1000/model->getPlaybackSpeed(), this, SLOT(showNextImage()));
}

/**
 * @brief PreviewScene::updateSprite
 * Updates the info that it has on the sprite at every timer tick.
 */
void PreviewScene::updateSprite()
{
    updateFrames();
}
