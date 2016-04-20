#include "mainwindow.h"
#include <QApplication>

// 3rd party libraries
#include "Box2D/helloworld.h"   // runBox2DHelloWorld

// Application internals
#include "echoclient.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
//    MainWindow w;
//    w.show();

    // For testing Box2D purposes:
    runBox2DHelloWorld();

    // For testing QtWebSockets:
    // Turns out putting this in a method was deleting the client object when the method returned,
    // therefore creating a pointer for it is better.
    EchoClient* client = new EchoClient(QUrl(QStringLiteral("ws://127.0.0.1:8081")), true);
    QObject::connect(client, &EchoClient::closed, &app, &QCoreApplication::quit);

    return app.exec();
}
