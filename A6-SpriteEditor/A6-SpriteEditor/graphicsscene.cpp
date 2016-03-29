#include "graphicsscene.h"

GraphicsScene::GraphicsScene(QObject *parent) : QGraphicsScene(parent)
{

    image = new QImage(500,500,QImage::Format_Alpha8);
    image->fill(Qt::white);
    this->addPixmap(QPixmap::fromImage(*image));
}

GraphicsScene::~GraphicsScene()
{
    delete image;
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

    int x = mouseEvent->scenePos().x();
    int y = mouseEvent->scenePos().y();

    std::cout << "X " << x << std::endl;
    std::cout << "y " << y << std::endl;

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
    image->scaled(rect.width(),rect.height());
    QGraphicsScene::setSceneRect(rect);
}

void GraphicsScene::setSceneRect(int x, int y, int width, int height)
{
    image->scaled(width,height);
    QGraphicsScene::setSceneRect(x,y,width,height);
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    int x = mouseEvent->scenePos().x();
    int y = mouseEvent->scenePos().y();

    std::cout << "X " << x << std::endl;
    std::cout << "y " << y << std::endl;

    this->addRect(50*(x/50),50*(y/50),50,50,QPen(Qt::white),QBrush(Qt::gray));

    /*QRgb value = qRgb(180,20,90);

    image->setColor(1,value);

    image->setPixel(QPoint(x,y),1);*/
}

void GraphicsScene::update(const QRectF &rect)
{
    this->addPixmap(QPixmap::fromImage(*image));
    QGraphicsScene::update(rect);
}
