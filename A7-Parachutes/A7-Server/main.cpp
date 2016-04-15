#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
//#include "echoserver.h"

// From 3rd party libraries
#include "tcpserver.h"
#include "httplistener.h"

// Application internals
#include "webrequesthandler.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QCommandLineParser parser;

    QCommandLineOption dbgOption(QStringList() << "d" << "debug",
            QCoreApplication::translate("main", "Debug output [default: off]."));
    parser.addOption(dbgOption);

    QCommandLineOption portOption(QStringList() << "p" << "port",
            QCoreApplication::translate("main", "Port for echoserver [default: 1234]."),
            QCoreApplication::translate("main", "port"), QLatin1Literal("1234"));
    parser.addOption(portOption);

    parser.process(app);

    bool debug = parser.isSet(dbgOption);
    int port = parser.value(portOption).toInt();

//    EchoServer *server = new EchoServer(port, debug);
//    QObject::connect(server, &EchoServer::closed, &a, &QCoreApplication::quit);

    // Create a TcpListener using QtTcpSocket:
//    TcpServer tcpServer;

    // QtWebApp:
//    QSettings* settings = new QSettings("configfile.ini", QSettings::IniFormat, &app);
    QSettings* settings = new QSettings(&app);
    settings->setValue("port", parser.value(portOption));
    WebRequestHandler* handler = new WebRequestHandler(&app);
    HttpListener* listener = new HttpListener(settings, handler, &app);

    return app.exec();
}
