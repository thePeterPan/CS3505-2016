#include "drawingdemo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DrawingDemo w;
    w.show();

    return a.exec();
}
