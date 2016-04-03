#include "graphicsscene.h"
#include "editor_model.h"

/**
 * @brief GraphicsScene::GraphicsScene
 * Magic defaults: square, 10x10, size 500
 * @param parent
 */

/**
 * @brief GraphicsScene::GraphicsScene
 * Constructor, gives some optional values.
 * @param parent
 * @param width
 * @param height
 * @param pixelSize
 */
GraphicsScene::GraphicsScene(editor_model* _model, int _width, int _height, int _pixelSize, QObject *parent) :
    QGraphicsScene(parent), width(_width), height(_height), pixelSize(_pixelSize), model(_model)
{
    // Set the size of the drawing area
    this->setSceneRect(0, 0, width*pixelSize, height*pixelSize);
    // Setup the checkered background
    this->prepareBackground(false);


    // Move to mainwindow?
    model->setSprite(new Sprite(width, height));

    // Create the scene with a bunch of "pixels" to draw on.
    clearScene();
}

/**
 * @brief GraphicsScene::~GraphicsScene
 *
 */
GraphicsScene::~GraphicsScene()
{
    delete image;
}

/**
 * @brief GraphicsScene::update
 * The underlying update function.
 * So far I don't use it for anything.
 * @param rect
 */
void GraphicsScene::update(const QRectF &rect)
{
    QGraphicsScene::update(rect);
}

void GraphicsScene::clearScene()
{
    pixels.clear();

    this->width = model->getSprite()->getWidth();
    this->height = model->getSprite()->getHeight();

    this->setSceneRect(0, 0, width * pixelSize, height * pixelSize);
    this->prepareBackground(true);

    for(int i = 0; i < width; i++)
    {
        pixels.append(QVector<QGraphicsRectItem*>(height));
        for(int j = 0; j < height; j++)
        {
            pixels[i][j] = this->addRect(
                        pixelSize * i,
                        pixelSize * j,
                        pixelSize,
                        pixelSize,
                        QPen(Qt::white));
        }
    }
}

/**
 * @brief GraphicsScene::prepareBackground
 * Creates a nice, checkered background to draw on.
 * @param replace - if true, clears the scene first.
 */
void GraphicsScene::prepareBackground(bool replace)
{
    if(replace)
        this->clear();
    image = new QImage(width * pixelSize, height * pixelSize, QImage::Format_ARGB32);
    QPainter painter(image);
    painter.setPen(Qt::white);

    for(int i = 0; i < width * 2; i++)
    {
        for(int j = 0; j < height * 2; j++)
        {
            if((i + j) % 2 == 0)
                painter.setBrush(QBrush(Qt::lightGray));
            else
                painter.setBrush(QBrush(Qt::white));
            painter.drawRect(i * pixelSize / 2, j * pixelSize / 2, pixelSize / 2, pixelSize / 2);
        }
    }

    painter.end();
    this->addPixmap(QPixmap::fromImage(*image));
}

/**
 * @brief GraphicsScene::paintEntireFrame
 * Paints the entire frame onto the canvas. Slow algorithm.
 */
void GraphicsScene::paintEntireFrame()
{
    for(int i = 0; i < model->getSprite()->getWidth(); i++)
        for(int j = 0; j < model->getSprite()->getHeight(); j++)
            pixels[i][j]->setBrush(model->getSprite()->getPixelColorAtCurrentFrame(i, j));
}

/**
 * @brief GraphicsScene::redrawScene
 * Used to update the entire scene if most of the 'squares' were changed.
 */
void GraphicsScene::redrawScene()
{
    clearScene();
    paintEntireFrame();
}

/**
 * @brief GraphicsScene::drawSquare
 * Used to update the scene at the specific pixel so we don't need to update
 * the whole scene if it's not needed.
 * @param x
 * @param y
 */
void GraphicsScene::drawSquare(int x, int y)
{
    pixels[x][y]->setBrush(model->getSprite()->getPixelColorAtCurrentFrame(x, y));
}









/**
 * @brief GraphicsScene::wheelEvent
 * Intended to be a zoom event, but it wasn't quite what I was expecting.
 * @param wheelEvent
 */
void GraphicsScene::wheelEvent(QGraphicsSceneWheelEvent *wheelEvent)
{
    //An interesting scroll idea: what if this zooms when ctrl is also held down?
    //pixelSize += wheelEvent->delta();

    /*

    int newX = this->width() + wheelEvent->delta();
    int newY = this->height() + wheelEvent->delta();

    if(newX < 50 | newY < 50)
    {
        newX = 50;
        newY = 50;
    }
    if(newX > 5000 | newY > 5000)
    {
        newX = 5000;
        newY = 5000;
    }
    this->setSceneRect(0,0,newX, newY);*/
}

void GraphicsScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    return;
}

void GraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    return;
}

/**
 * @brief GraphicsScene::mouseMoveEvent
 * Event for when the user holds down the mouse and moves across the canvas.
 * @param mouseEvent
 */
void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    int x = mouseEvent->scenePos().x()/pixelSize;
    int y = mouseEvent->scenePos().y()/pixelSize;
    if(x >= 0 && x < model->getSprite()->getWidth() && y >= 0 && y < model->getSprite()->getHeight())
        model->paintCommand(x, y);
}

/**
 * @brief GraphicsScene::mousePressEvent
 * Event for when the user clicks the mouse on the canvas.
 * @param mouseEvent
 */
void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    int x = mouseEvent->scenePos().x()/pixelSize;
    int y = mouseEvent->scenePos().y()/pixelSize;

    if(x >= 0 && x < model->getSprite()->getWidth() && y >= 0 && y < model->getSprite()->getHeight())
        model->paintCommand(x, y);
}















void GraphicsScene::zoomIn()
{
    if(pixelSize + pixelInterval <= maxPixelSize)
    {
        pixelSize += pixelInterval;
        redrawScene();
    }
}

void GraphicsScene::zoomOut()
{
    if(pixelSize - pixelInterval >= minPixelSize)
    {
        pixelSize -= pixelInterval;
        redrawScene();
    }
}

/**
 * @brief GraphicsScene::setSceneRect
 * Resizes the scene.
 * @param rect
 */
void GraphicsScene::setSceneRect(const QRectF &rect)
{
    //image->scaled(rect.width(),rect.height());

    //Note: needs to also resize the underlying frame object.

    QGraphicsScene::setSceneRect(rect);
}

/**
 * @brief GraphicsScene::setSceneRect
 * Resizes the scene.
 * @param x
 * @param y
 * @param width
 * @param height
 */
void GraphicsScene::setSceneRect(int x, int y, int width, int height)
{
    //image->scaled(width,height);

    //Note: needs to also resize the underlying frame object.

    QGraphicsScene::setSceneRect(x,y,width,height);
}
