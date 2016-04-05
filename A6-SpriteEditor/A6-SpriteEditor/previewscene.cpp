#include "previewscene.h"

PreviewScene::PreviewScene(editor_model* _model, QObject* parent, int _width, int _height) :
    QGraphicsScene(parent), model(_model), width(_width), height(_height)
{
    /*if(width!=230 && height!=218)
    {
        if(width > height)
        {
            height = height*218 / width;
            width = 230;
        }
        else
        {
            width = width*230/height;
            height = 218;
        }
    }*/

    updateFrames();
    index = 0;

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()), this, SLOT(updateSprite()));
    timer->start(2001);

    this->setSceneRect(0,0,width,height);
    //this->setBackgroundBrush(QBrush(Qt::white));

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
        index = 0;

    // Time until the next frame. Can use model->getPlaybackSpeed(), but that uses a different metric.
    QTimer::singleShot(500, this, SLOT(showNextImage()));
}

/**
 * @brief PreviewScene::updateSprite
 * Updates the info that it has on the sprite at every timer tick.
 */
void PreviewScene::updateSprite()
{
    updateFrames();
    if(this->index >= this->maxindex)
        this->index = 0;
}
