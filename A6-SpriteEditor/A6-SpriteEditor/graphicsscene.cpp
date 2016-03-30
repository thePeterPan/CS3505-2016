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
GraphicsScene::GraphicsScene(editor_model* editor, QObject *parent, int width, int height, int pixelSize) :
    QGraphicsScene(parent), width(width), height(height), pixelSize(pixelSize), editor(editor)
{
    this->setSceneRect(0,0,width*pixelSize,height*pixelSize);

    //Frame: the object that the colors are stored in inside of a matrix.
    frame = new Frame(this,width,height);

    //Image: does nothing but give a nice background so far.
    //We could make a nice backdrop that shows that nothing has been drawn on this section?
    image = new QImage(width*pixelSize,height*pixelSize,QImage::Format_Alpha8);
    image->fill(Qt::black);
    this->addPixmap(QPixmap::fromImage(*image));

    //Initialize the brush to a value.
    brush = new QBrush(Qt::black);
}

/**
 * @brief GraphicsScene::~GraphicsScene
 *
 */
GraphicsScene::~GraphicsScene()
{
    delete image;
    delete brush;
    delete frame;
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

    paintCommand(x,y);




    /*QRgb value = qRgb(180,20,90);

    image->setColor(1,value);

    image->setPixel(QPoint(x,y),1);*/
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

    paintCommand(x,y);
}

void GraphicsScene::paintCommand(int x, int y){
    if(editor->current_tool == editor->BRUSH){
        drawSquare(x,y,brush->color());
    }else if(editor->current_tool == editor->FILL_BUCKET){
        fillBucket(brush->color());
    }else if(editor->current_tool == editor->MIRROR){
        drawMirror(x,y,brush->color());
    }else if(editor->current_tool == editor->ERASER){

    }
}

/**
 * @brief GraphicsScene::drawSquare
 * Draws a square onto the canvas at the x and y pixel positions.
 * @param x
 * @param y
 */
void GraphicsScene::drawSquare(int x, int y, QColor color)
{
    if(x < 0 | y < 0 | x >= this->width | y >= this->height)
        return;

    frame->setPixelColor(x,y,color);


    this->addRect(pixelSize*x,pixelSize*y,pixelSize,pixelSize,QPen(),*brush);
}

void GraphicsScene::fillBucket(QColor color){
//    std::cout << frame->toString() << std::endl;
//    for(int i = 0; i < width; i++){
//        for(int j = 0; j < height; j++){
//            drawSquare(i,j,color);
//        }
//    }
//    std::cout << frame->toString() << std::endl;
}

void GraphicsScene::drawMirror(int x, int y, QColor color){
    drawSquare(x,y,color);
    drawSquare(width - 1 - x, y,color);
}

/**
 * @brief GraphicsScene::paintEntireFrame
 * Paints the entire frame onto the canvas. Slow algorithm.
 */
void GraphicsScene::paintEntireFrame()
{
    for(int i = 0; i < frame->getFrameWidth(); i++)
        for(int j = 0; j < frame->getFrameHeight(); j++)
            this->addRect(pixelSize*i,pixelSize*j,pixelSize,pixelSize,QPen(),QBrush(frame->getPixelColor(i,j)));
}


/**
 * @brief GraphicsScene::update
 * The underlying update function.
 * So far I don't use it for anything.
 * @param rect
 */
void GraphicsScene::update(const QRectF &rect)
{
    //this->addPixmap(QPixmap::fromImage(*image));

    QGraphicsScene::update(rect);
}

/**
 * @brief GraphicsScene::setColor
 * Sets the brush color.
 * @param color
 */
void GraphicsScene::setColor(QColor color)
{
    this->brush->setColor(color);
}

void GraphicsScene::rotate(bool direction) {
    frame->rotate(direction);
    this->paintEntireFrame();
}
void GraphicsScene::flip(bool vertical) {
    frame->flip(vertical);
    this->paintEntireFrame();
}
void GraphicsScene::invert() {
    frame->invert();
    this->paintEntireFrame();
}
