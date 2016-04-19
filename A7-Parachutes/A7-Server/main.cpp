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
#include "echoserver.h"         // EchoServer
#include "webrequesthandler.h"  // WebRequestHandler
#include "mysqlwrapper.h"

QString searchConfigFile()
{
    // ini config file must share the name of the app
    QString binDir = QCoreApplication::applicationDirPath();
    QString appName = QCoreApplication::applicationName();
    QString fileName(appName + ".ini");

    QStringList searchList;
    searchList.append(binDir);
    searchList.append(binDir + "/etc");
    searchList.append(binDir + "/../etc");
    searchList.append(binDir + "/../../etc"); // for development without shadow build
    searchList.append(binDir + "/../" + appName + "/etc"); // for development with shadow build
    searchList.append(binDir + "/../../" + appName + "/etc"); // for development with shadow build
    searchList.append(binDir + "/../../../" + appName + "/etc"); // for development with shadow build
    searchList.append(binDir + "/../../../../" + appName + "/etc"); // for development with shadow build
    searchList.append(binDir + "/../../../../../" + appName + "/etc"); // for development with shadow build
    searchList.append(QDir::rootPath() + "etc/opt");
    searchList.append(QDir::rootPath() + "etc");

    foreach (QString dir, searchList)
    {
        QFile file(dir + "/" + fileName);
        if (file.exists())
        {
            // file is found
            fileName = QDir(file.fileName()).canonicalPath();
            qDebug("Using config file %s", qPrintable(fileName));
            return fileName;
        }
    }

    // if the file is not found
    foreach (QString dir, searchList)
    {
        qWarning("%s/%s not found", qPrintable(dir), qPrintable(fileName));
    }
    qFatal("Cannot find config file %s", qPrintable(fileName));

    return 0;
}

void launchWebServer(QCommandLineParser* parser, QObject* parent = 0)
{
    // QtWebApp:
    // Get settings from the config file
    QString configFile = searchConfigFile();
    QSettings* listenerSettings = new QSettings(configFile, QSettings::IniFormat, parent);


    listenerSettings->beginGroup("docroot");
    StaticFileController* staticFC = new StaticFileController(listenerSettings, parent);
    listenerSettings->beginGroup("listener");
    listenerSettings->setValue("port", "8080");
    new HttpListener(listenerSettings, staticFC, parent);

    // Create a web request handler and start listening.
//    listenerSettings->beginGroup("listener");
//    new HttpListener(listenerSettings, new WebRequestHandler(parent), parent);
}

void launchSocketListener(int port, bool debug, QObject* parent = 0)
{
        EchoServer *server = new EchoServer(port, debug);
        QObject::connect(server, &EchoServer::closed, parent, &QCoreApplication::quit);

        // Create a TcpListener using QtTcpSocket:
    //    TcpServer tcpServer;
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

    bool debug = parser.isSet(dbgOption);
    int port = parser.value(portOption).toInt();

    launchWebServer(&parser, &app);

    launchSocketListener(port, debug, &app);

    return app.exec();
}
