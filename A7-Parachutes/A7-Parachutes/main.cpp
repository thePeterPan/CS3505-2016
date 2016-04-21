#include "mainwindow.h"
#include <QApplication>
#include <QSettings>

// 3rd party libraries
#include "Box2D/helloworld.h"   // runBox2DHelloWorld

// Application internals
#include "echoclient.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
//    MainWindow w;
//    w.show();

    // Get settings from config file:
    QString configFile = ":/A7-Parachutes.ini";

    // For testing Box2D purposes:
    runBox2DHelloWorld();

    // QtWebSockets:
    QSettings* socketSettings = new QSettings(configFile, QSettings::IniFormat);
    socketSettings->beginGroup("socket");
    // Get the settings from the ini file.
    QString scheme = socketSettings->value("scheme", QString("ws")).toString();
    QString host = socketSettings->value("host", QString("localhost")).toString();
    int port = socketSettings->value("port", 8081).toInt();
    // Set the url to connect to
    QUrl* url = new QUrl();
    url->setScheme(scheme);
    url->setHost(host);
    url->setPort(port);

    // Turns out putting this in a method was deleting the client object when the method returned,
    // therefore creating a pointer for it is better.
    EchoClient* client = new EchoClient(*url, true);
    // If the connection closes:
    QObject::connect(client, &EchoClient::closed, &app, &QCoreApplication::quit);

    return app.exec();
}
