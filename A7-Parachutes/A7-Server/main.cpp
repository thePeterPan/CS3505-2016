#include <QDebug>
#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include <QDir>
#include <QString>

// From 3rd party libraries
#include "tcpserver.h"          // TcpServer
#include "staticfilecontroller.h"
#include "httplistener.h"       // HttpListener

// Application internals
#include "networking.h"
#include "webrequesthandler.h"  // WebRequestHandler
#include "mysqlwrapper.h"

void launchWebServer(QString configFile, QObject* parent = 0)
{
    // QtWebApp:
        QSettings* docrootSettings = new QSettings(configFile, QSettings::IniFormat);
        docrootSettings->beginGroup("docroot");
        StaticFileController* staticFC = new StaticFileController(docrootSettings, parent);
        QSettings* listenerSettings = new QSettings(configFile, QSettings::IniFormat);
        listenerSettings->beginGroup("listener");
        new HttpListener(listenerSettings, staticFC, parent);

        // Create a web request handler and start listening.
    //    listenerSettings->beginGroup("listener");
    //    new HttpListener(listenerSettings, new WebRequestHandler(parent), parent);
}

void launchSocketListener(QString configFile, QObject* parent = 0)
{
    Networking *server = new Networking(configFile, parent);
    QObject::connect(server, &Networking::closed, parent, &QCoreApplication::quit);
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // Parse the command line for any options:
    QCommandLineParser parser;
    QCommandLineOption dbgOption(QStringList() << "d" << "debug",
            QCoreApplication::translate("main", "Debug output [default: off]."));
    parser.addOption(dbgOption);
    QCommandLineOption portOption(QStringList() << "p" << "port",
            QCoreApplication::translate("main", "Port for echoserver [default: 1234]."),
            QCoreApplication::translate("main", "port"), QLatin1Literal("1234"));
    parser.addOption(portOption);
    parser.process(app);
    // parser.value(portOption)
    // bool debug = parser.isSet(dbgOption);
    // int port = parser.value(portOption).toInt();

    // Get Settings from the config file:
    QString configfile = ":/A7-Server.ini";
    launchWebServer(configfile, &app);
    launchSocketListener(configfile, &app);

    return app.exec();
}
