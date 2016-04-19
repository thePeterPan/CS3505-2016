#ifndef MYSQLWRAPPER_H
#define MYSQLWRAPPER_H

#include <QObject>
#include <QDebug>

//MySQL Connector libraries
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

class MySQLWrapper : public QObject
{
    Q_OBJECT
public:
    explicit MySQLWrapper(QObject *parent = 0);

    void setHost(QString _hostPath, int _port = 3306);
    void setUsername(QString _username);
    void setPassword(QString _password);
    void setDatabaseName(QString _name);

    bool open();
    bool close();

    bool exec();

signals:

public slots:

private:
    QString hostPath;
    int port;
    QString username;
    QString password;
    QString databaseName;

    // Do these need to be deleted?
    sql::Driver *driver;
    sql::Connection *connection;
    sql::Statement *statement;
    sql::ResultSet *resultSet;
};

#endif // MYSQLWRAPPER_H
