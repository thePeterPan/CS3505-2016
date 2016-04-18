#include <QDebug>
#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include <QDir>
#include <QString>
//#include <QtSql/QSql>
//#include <QtSql/QSqlDatabase>
#include <QtSql>
#include <QtSql/QSqlDriver>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

// From 3rd party libraries
#include "tcpserver.h"          // TcpServer
#include "staticfilecontroller.h"
#include "httplistener.h"       // HttpListener

// Application internals
#include "echoserver.h"         // EchoServer
#include "webrequesthandler.h"  // WebRequestHandler

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

void initializeSQLConnection()
{
//    qDebug() << QCoreApplication::libraryPaths();
//    qDebug() << QSqlDatabase::drivers();
//    qDebug() << QSqlDatabase::isDriverAvailable("QMYSQL");
//    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
//    db.setHostName("us-cdbr-azure-west-c.cloudapp.net");
//    db.setDatabaseName("neverland-db");
//    db.setUserName("b485a4f4f7fcea");
//    db.setPassword("fd0282b9");
//    if (!db.open())
//    {
//        qDebug() << "Database error.";
//    }


    /// Source: https://dev.mysql.com/doc/connector-cpp/en/connector-cpp-examples-complete-example-1.html
    try {
      sql::Driver *driver;
      sql::Connection *con;
      sql::Statement *stmt;
      sql::ResultSet *res;

      /* Create a connection */
      driver = get_driver_instance();
      con = driver->connect("us-cdbr-azure-west-c.cloudapp.net:3306", "b485a4f4f7fcea", "fd0282b9");
      /* Connect to the MySQL test database */
      con->setSchema("neverland-db");

      stmt = con->createStatement();
      res = stmt->executeQuery("SELECT first FROM user");
      while (res->next()) {
        qDebug() << "\t... MySQL replies: ";
        /* Access column data by alias or column name */
//        qDebug() << QObject::tr(res->getString("_message").asStdString());
        qDebug() << "\t... MySQL says it again: ";
        /* Access column fata by numeric offset, 1 is the first column */
//        qDebug() << QObject::tr(res->getString(1));
      }
      delete res;
      delete stmt;
      delete con;

    } catch (sql::SQLException &e) {
//      qDebug() << "# ERR: SQLException in " << __FILE__;
//      qDebug() << "(" << __FUNCTION__ << ") on line " << __LINE__ ;
      qDebug() << "# ERR: " << e.what();
      qDebug() << " (MySQL error code: " << QString::number(e.getErrorCode());
//      qDebug() << ", SQLState: " << QObject::tr(e.getSQLState()) << " )";
    }
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

    QPluginLoader plug("libqsqlmysql.so");
    plug.load();
    qDebug() << plug.errorString();
    qDebug() << "mysql plugin loaded: " << plug.isLoaded();

    initializeSQLConnection();

    return app.exec();
}
