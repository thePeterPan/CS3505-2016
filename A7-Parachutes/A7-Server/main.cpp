#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
//#include "echoserver.h"

#include "tcpserver.h"
#include "httplistener.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("QtWebSockets example: echoserver");
    parser.addHelpOption();

    QCommandLineOption dbgOption(QStringList() << "d" << "debug",
            QCoreApplication::translate("main", "Debug output [default: off]."));
    parser.addOption(dbgOption);

    QCommandLineOption portOption(QStringList() << "p" << "port",
            QCoreApplication::translate("main", "Port for echoserver [default: 1234]."),
            QCoreApplication::translate("main", "port"), QLatin1Literal("1234"));
    parser.addOption(portOption);

    parser.process(a);

    bool debug = parser.isSet(dbgOption);
    int port = parser.value(portOption).toInt();

//    EchoServer *server = new EchoServer(port, debug);
//    QObject::connect(server, &EchoServer::closed, &a, &QCoreApplication::quit);

    // TcpServer:
    TcpServer tcpServer;

    // QtWebApp:
    QSettings* settings = new QSettings("configfile.ini", QSettings::IniFormat, &a);
//    MyRequestHandler* handler = new MyRequestHandler(app);
//    HttpListener* listener = new HttpListener(settings, handler, app);

    return a.exec();
}
