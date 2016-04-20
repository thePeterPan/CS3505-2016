#include "mainwindow.h"
#include <QApplication>

// 3rd party libraries
#include "Box2D/helloworld.h"   // runBox2DHelloWorld

// Application internals
#include "echoclient.h"

void echoclient_test(QObject* parent = 0)
{
    EchoClient client(QUrl(QStringLiteral("ws://localhost:1234")), true);
    QObject::connect(&client, &EchoClient::closed, parent, &QCoreApplication::quit);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // For testing Box2D purposes:
    //runBox2DHelloWorld();

    // For testing QtWebSockets:
    echoclient_test(&a);

    return a.exec();
}
