#include "mysqlwrapper.h"

MySQLWrapper::MySQLWrapper(QObject *parent)
    : QObject(parent), hostPath(""), port(3306),
      username(""), password(""), databaseName("")
{

}

void MySQLWrapper::setHost(QString _hostPath, int _port)
{
    hostPath = _hostPath;
    port = _port;
}

void MySQLWrapper::setUsername(QString _username)
{
    username = _username;
}

void MySQLWrapper::setPassword(QString _password)
{
    password = _password;
}

void MySQLWrapper::setDatabaseName(QString _name)
{
    databaseName = _name;
}

bool MySQLWrapper::open()
{
    if (hostPath == "" || username == "" || password == "")
        return false;

    try
    {
        // Create a connection:
        driver = get_driver_instance(); // Not threadsafe
        std::string completeHost = hostPath.toStdString() + ":"  + std::to_string(port);
        connection = driver->connect(completeHost, username.toStdString(), password.toStdString());
        connection->setSchema(databaseName.toStdString());
    }
    catch (sql::SQLException &e) {
//      qDebug() << "# ERR: SQLException in " << __FILE__;
//      qDebug() << "(" << __FUNCTION__ << ") on line " << __LINE__ ;
      qDebug() << "# ERR: " << e.what();
      qDebug() << " (MySQL error code: " << QString::number(e.getErrorCode());
//      qDebug() << ", SQLState: " << QObject::tr(e.getSQLState()) << " )";
        return false;
    }
}

bool MySQLWrapper::close()
{
    // Do not explicitly free driver, the connector object. Connector/C++ takes care of freeing that.
    delete resultSet;
    delete statement;
    delete connection;
}

bool MySQLWrapper::exec()
{
    /// Source: https://dev.mysql.com/doc/connector-cpp/en/connector-cpp-examples-complete-example-1.html
    statement = connection->createStatement();
    resultSet = statement->executeQuery("SELECT first FROM user");
    while (resultSet->next()) {
      qDebug() << "\t... MySQL replies: ";
      /* Access column data by alias or column name */
//        qDebug() << QObject::tr(res->getString("_message").asStdString());
      qDebug() << "\t... MySQL says it again: ";
      /* Access column fata by numeric offset, 1 is the first column */
//        qDebug() << QObject::tr(res->getString(1));
    }
    return true;
}
