#include "graphicsscene.h"
GraphicsScene::GraphicsScene( QObject *parent ) :
    QGraphicsScene( parent )
{
}

void GraphicsScene::mousePressEvent( QGraphicsSceneMouseEvent * mouseEvent )
{
    int x = mouseEvent->scenePos().x();
    int y = mouseEvent->scenePos().y();
    std::cout << "x " << x << std::endl;
    std::cout << "y " << y << std::endl;
}
