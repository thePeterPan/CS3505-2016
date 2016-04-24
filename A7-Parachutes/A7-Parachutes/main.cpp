#include "mainwindow.h"
#include <QApplication>

// 3rd party libraries
#include "Box2D/helloworld.h"   // runBox2DHelloWorld

// Application internals
#include "networking.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.show();

    // Get settings from config file:
    QString configFile = ":/A7-Parachutes.ini";

    // For testing Box2D purposes:
    //runBox2DHelloWorld();


    // Turns out putting this in a method was deleting the client object when the method returned,
    // therefore creating a pointer for it is better.
    //Networking* client = new Networking(configFile, &app);
    // If the connection closes:
    //QObject::connect(client, &Networking::closed, &app, &QCoreApplication::quit);

    return app.exec();
}
