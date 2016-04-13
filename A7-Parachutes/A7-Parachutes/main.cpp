#include "mainwindow.h"
#include <QApplication>

/// Echo Client Example:
#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include "echoclient.h"
/// End

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    /// Echo Client Example:
//    QCoreApplication a(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("QtWebSockets example: echoclient");
    parser.addHelpOption();

    QCommandLineOption dbgOption(QStringList() << "d" << "debug",
           QCoreApplication::translate("main", "Debug output [default: off]."));
    parser.addOption(dbgOption);
    parser.process(a);
    bool debug = parser.isSet(dbgOption);

    EchoClient client(QUrl(QStringLiteral("ws://localhost:1234")), debug);
    QObject::connect(&client, &EchoClient::closed, &a, &QCoreApplication::quit);
    /// End

    return a.exec();
}
