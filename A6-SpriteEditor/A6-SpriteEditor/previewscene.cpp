#include "previewscene.h"

//Dimensions: 232x220

PreviewScene::PreviewScene(editor_model* _model, QObject* parent, int _width, int _height) :
    QGraphicsScene(parent), model(_model), width(_width), height(_height)
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()), this, SLOT(updateSprite()));
    timer->start(2001);

    this->setSceneRect(0,0,width,height);

    //QTimer::singleShot(model->getPlaybackSpeed(), this, SLOT(showNextImage()));
}
/*
void PreviewScene::showNextImage()
{
    this->clear();
    this->addPixmap(QPixmap::fromImage(frames.at(index)->scaled(width,height)));

    index++;
    if(index >= maxindex)
        index = 0;

    QTimer::singleShot(model->getPlaybackSpeed(), this, SLOT(showNextImage()));
}*/

/**
 * @brief PreviewScene::updateSprite
 * Updates the info that it has on the sprite at every timer tick.
 */
void PreviewScene::updateSprite()
{
    this->frames = model->getSprite()->getFramesAsImages();
    this->maxindex = frames.size();
    if(this->index >= this->maxindex)
        this->index = 0;
}
