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

    model->setSprite(new Sprite(width, height));

    currentFrameIndex = 0;

    // Frame: the object that the colors are stored in inside of a matrix.
//    currentFrame = new Frame(width, height, this);
    model->getSprite()->addFrame(new Frame(width, height, this));

    // Initialize the brush to a value.
    brush = new QBrush(QColor(0, 0, 0, 0));

    // Create the scene with a bunch of "pixels" to draw on.
    for(int i = 0; i < width; i++)
    {
        pixels.append(QVector<QGraphicsRectItem*>(height));
        for(int j = 0; j < height; j++)
        {
            pixels[i][j] = this->addRect(pixelSize*i, pixelSize*j, pixelSize, pixelSize, QPen(Qt::white), *brush);
        }
    }
}

/**
 * @brief GraphicsScene::redrawScene
 * @param sprite
 */
void GraphicsScene::redrawScene(Sprite *sprite)
{
    pixels.clear();

    this->width = sprite->getWidth();
    this->height = sprite->getHeight();

    this->setSceneRect(0, 0, width * pixelSize, height * pixelSize);
    this->prepareBackground(true);
    model->setSprite(sprite);
//    currentFrame = sprite->getFrameAt(currentFrameIndex);

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
                        QPen(Qt::white),
                        *brush);
        }
    }
    paintEntireFrame();
}


/**
 * @brief GraphicsScene::prepareBackground
 * Creates a nice, checkered background to draw on.
 * @param replace - if true clears the scene first.
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
 * @brief GraphicsScene::~GraphicsScene
 *
 */
GraphicsScene::~GraphicsScene()
{
    delete image;
    delete brush;
//    delete currentFrame;
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

void GraphicsScene::zoomIn()
{
    if(pixelSize + pixelInterval <= maxPixelSize)
    {
        pixelSize += pixelInterval;
        redrawScene(model->getSprite());
    }
}

void GraphicsScene::zoomOut()
{
    if(pixelSize - pixelInterval >= minPixelSize)
    {
        pixelSize -= pixelInterval;
        redrawScene(model->getSprite());
    }
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
        paintCommand(x,y);
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
        paintCommand(x,y);
}

/**
 * @brief GraphicsScene::paintCommand
 * @param x
 * @param y
 */
void GraphicsScene::paintCommand(int x, int y)
{
    if(model->getCurrentTool() == editor_model::BRUSH) {
        drawSquare(x,y,brush->color());
    } else if (model->getCurrentTool() == editor_model::FILL_BUCKET) {
        fillBucket(x,y,brush->color());
    } else if (model->getCurrentTool() == editor_model::MIRROR) {
        drawMirror(x,y,brush->color());
    } else if (model->getCurrentTool() == editor_model::ERASER) {
        erase(x,y);
    }
}

/**
 * @brief GraphicsScene::drawSquare
 * Draws a square onto the canvas at the x and y pixel positions.
 * Aka. for the paint brush tool.
 * @param x
 * @param y
 */
void GraphicsScene::drawSquare(int x, int y, QColor color)
{
    if((x < 0) | (y < 0) | (x >= this->width) | (y >= this->height))
        return;

    model->getSprite()->setPixelColorAtCurrentFrame(x, y, color);

    pixels[x][y]->setBrush(QBrush(color));
}

/**
 * @brief GraphicsScene::fillBucket
 * Used for the fill bucket tool.
 * @param x
 * @param y
 * @param color
 */
void GraphicsScene::fillBucket(int x, int y, QColor color)
{

    QColor prev = model->getSprite()->getPixelColorAtCurrentFrame(x, y);

    if(prev == color)
        return;

    drawSquare(x,y,color);

    int x1 = x - 1;
    int x2 = x + 1;
    int y1 = y - 1;
    int y2 = y + 1;
    if(x1 >= 0 && model->getSprite()->getPixelColorAtCurrentFrame(x1, y) == prev)
            fillBucket(x1,y,color);
    if(x2 < width && model->getSprite()->getPixelColorAtCurrentFrame(x2, y) == prev)
            fillBucket(x2,y,color);
    if(y1 >= 0 && model->getSprite()->getPixelColorAtCurrentFrame(x, y1) == prev)
            fillBucket(x,y1,color);
    if(y2 < height && model->getSprite()->getPixelColorAtCurrentFrame(x, y2) == prev)
            fillBucket(x,y2,color);
}

void GraphicsScene::drawMirror(int x, int y, QColor color)
{
    drawSquare(x,y,color);
    drawSquare(width - 1 - x, y,color);
}

void GraphicsScene::erase(int x, int y)
{
    drawSquare(x, y, QColor(0, 0, 0, 0));
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
 * @brief GraphicsScene::update
 * The underlying update function.
 * So far I don't use it for anything.
 * @param rect
 */
void GraphicsScene::update(const QRectF &rect)
{
    QGraphicsScene::update(rect);
}

/**
 * @brief GraphicsScene::setBrushColor
 * Sets the brush color.
 * @param color
 */
void GraphicsScene::setBrushColor(QColor color)
{
    this->brush->setColor(color);
}

/**
 * @brief GraphicsScene::rotateScene
 * @param direction
 */
void GraphicsScene::rotateScene(bool direction)
{
    model->getSprite()->rotateCurrentFrame(direction);
    this->paintEntireFrame();
}

/**
 * @brief GraphicsScene::flipSceneOrientation
 * @param vertical
 */
void GraphicsScene::flipSceneOrientation(bool orientation)
{
    model->getSprite()->flipCurrentFrameOrientation(orientation);
    this->paintEntireFrame();
}

/**
 * @brief GraphicsScene::invertSceneColors
 */
void GraphicsScene::invertSceneColors()
{
    model->getSprite()->invertCurrentFrameColor();
    this->paintEntireFrame();
}

/**
 * @brief GraphicsScene::addFrame
 */
void GraphicsScene::addFrame()
{
    model->getSprite()->addFrame(new Frame(width, height, this));
    currentFrameIndex = model->getSprite()->getFrames().size() - 1;
//    currentFrame = model->getSprite()->getFrameAt(currentFrameIndex);
    this->paintEntireFrame();
}

/**
 * @brief GraphicsScene::removeFrame
 */
void GraphicsScene::removeFrame()
{

    if (model->getSprite()->getFrames().size() > 1)
    {
        model->getSprite()->removeFrameAt(currentFrameIndex);
        if (currentFrameIndex == model->getSprite()->getFrames().size())
            currentFrameIndex--;
//        currentFrame = model->getSprite()->getFrameAt(currentFrameIndex);
        this->paintEntireFrame();
        //emit frameUpdated(currentFrameIndex + 1, sprite->getFrames().size());
    }
}

/**
 * @brief GraphicsScene::previousFrame
 */
void GraphicsScene::previousFrame()
{
    if (currentFrameIndex > 0)
    {
        currentFrameIndex--;
//        currentFrame = model->getSprite()->getFrameAt(currentFrameIndex);
        //emit frameUpdated(currentFrameIndex + 1, sprite->getFrames().size());
    }
    this->paintEntireFrame();

}

/**
 * @brief GraphicsScene::nextFrame
 */
void GraphicsScene::nextFrame()
{
    if (currentFrameIndex < model->getSprite()->getFrames().size() - 1)
    {
        currentFrameIndex++;
//        currentFrame = model->getSprite()->getFrameAt(currentFrameIndex);
        //emit frameUpdated(currentFrameIndex - 1, sprite->getFrames().size());
    }
    this->paintEntireFrame();
}
