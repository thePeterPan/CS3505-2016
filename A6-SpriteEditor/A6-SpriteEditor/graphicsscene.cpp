#include "graphicsscene.h"

GraphicsScene::GraphicsScene(QObject *parent) : QGraphicsScene(parent)
{

    image = new QImage(500,500,QImage::Format_Alpha8);
    frame = new Frame(this,10,10);
    image->fill(Qt::white);
    this->addPixmap(QPixmap::fromImage(*image));
    brush = new QBrush(Qt::black);
}

GraphicsScene::GraphicsScene(QObject *parent, int width, int height, int pixelSize) : QGraphicsScene(parent), width(width), height(height), pixelSize(pixelSize)
{
    this->setSceneRect(0,0,width*pixelSize,height*pixelSize);


    image = new QImage(width*pixelSize,height*pixelSize,QImage::Format_Alpha8);
    frame = new Frame(this,width,height);
    image->fill(Qt::white);
    this->addPixmap(QPixmap::fromImage(*image));
    brush = new QBrush(Qt::black);
}

GraphicsScene::~GraphicsScene()
{
    delete image;
    delete brush;
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

    int x = mouseEvent->scenePos().x()/50;
    int y = mouseEvent->scenePos().y()/50;

    if(x < 0 | y < 0 | x >= this->width | y >= this->height)
        return;

    frame->setPixelColor(x,y,brush->color());

    this->addRect(50*x,50*y,50,50,QPen(),*brush);

    std::cout << "X " << x << std::endl;
    std::cout << "Y " << y << std::endl;

}


/*void GraphicsScene::wheelEvent(QGraphicsSceneWheelEvent *wheelEvent)
{
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
    this->setSceneRect(0,0,newX, newY);
}*/

void GraphicsScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{

}

void GraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

}

void GraphicsScene::setSceneRect(const QRectF &rect)
{
    //image->scaled(rect.width(),rect.height());
    QGraphicsScene::setSceneRect(rect);
}

void GraphicsScene::setSceneRect(int x, int y, int width, int height)
{
    //image->scaled(width,height);
    QGraphicsScene::setSceneRect(x,y,width,height);
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    int x = mouseEvent->scenePos().x()/50;
    int y = mouseEvent->scenePos().y()/50;

    if(x < 0 | y < 0 | x >= this->width | y >= this->height)
        return;

    frame->setPixelColor(x,y,brush->color());

    this->addRect(50*x,50*y,50,50,QPen(),*brush);

    /*QRgb value = qRgb(180,20,90);

    image->setColor(1,value);

    image->setPixel(QPoint(x,y),1);*/
}

void GraphicsScene::update(const QRectF &rect)
{
    //this->addPixmap(QPixmap::fromImage(*image));
    QGraphicsScene::update(rect);
}

void GraphicsScene::setColor(QColor color)
{
    this->brush->setColor(color);
}
