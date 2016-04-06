#include "previewscene.h"

/**
 * @brief PreviewScene::PreviewScene Creates a new preview window.
 * @param _model: The model that controls this window.
 * @param parent: The Ui that this window is displayed in.
 * @param _width: Optional. Default value is 230, which is the size of the space in the Ui
 * @param _height: Optional. Default value is 218, which is the size of the space in the Ui
 */
PreviewScene::PreviewScene(EditorModel* _model, QObject* parent, int _width, int _height) :
    QGraphicsScene(parent), model(_model), sceneWidth(_width), sceneHeight(_height)
{
    updateFrames();
    imageIndex = 0;

    this->setSceneRect(0,0,sceneWidth,sceneHeight);

    QTimer::singleShot(500, this, SLOT(showNextImage()));
}

/**
 * @brief PreviewScene::updateFrames
 * Gets all of the frames from the model as QImages.
 * This method refreshes the images that the preview window shows.
 */
void PreviewScene::updateFrames()
{
    this->frames = model->getSprite()->getFramesAsImages();
    this->maxindex = frames.size();
}

/**
 * @brief PreviewScene::showNextImage
 * Clears off the last image and shows the next image in the sprite.
 * Once all images have been shown, the window refreshes the list of images
 * and starts over from the beginning.
 */
void PreviewScene::showNextImage()
{
    this->clear();
    this->addPixmap(QPixmap::fromImage(frames.at(imageIndex)->scaled(sceneWidth,sceneHeight,Qt::KeepAspectRatio)));

    imageIndex++;
    if(imageIndex >= maxindex)
    {
        QTimer::singleShot(1,this,SLOT(updateFromSprite()));
        imageIndex = 0;
    }

    QTimer::singleShot(1000/model->getPlaybackSpeed(), this, SLOT(showNextImage()));
}

/**
 * @brief PreviewScene::updateSprite
 * Timer slot. This method is called when the image list needs to be refreshed.
 */
void PreviewScene::updateFromSprite()
{
    updateFrames();
}
