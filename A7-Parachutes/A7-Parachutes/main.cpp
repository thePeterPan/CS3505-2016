#include "mainwindow.h"
#include <QApplication>

#include "Box2D/helloworld.h" // runBox2DHelloWorld

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // For testing Box2D purposes:
    runBox2DHelloWorld();

    return a.exec();
}
