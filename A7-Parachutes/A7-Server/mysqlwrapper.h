#ifndef MYSQLWRAPPER_H
#define MYSQLWRAPPER_H

#include <QObject>
#include <QDebug>
#include <QList>
//MySQL Connector libraries
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

//Name=neverland-db
//Server=us-cdbr-azure-west-c.cloudapp.net
//Login=b485a4f4f7fcea
//Password=fd0282b9

class MySQLWrapper : public QObject
{
    Q_OBJECT
public:
    explicit MySQLWrapper(QObject *parent = 0);

    void setHost(QString _hostPath, int _port = 3306);
    void setUsername(QString _username);
    void setPassword(QString _password);
    void setDatabaseName(QString _name);

    QList<QString> getTeacherWordsByLevel(QString teacher, int level);
    bool loginAvailable(QString login);
    bool isTeacher(QString login);
    void insertNewStudent(QString login, QString first, QString last, QString password, QString teacher);
    void insertNewTeacher(QString login, QString first, QString last, QString password);
    int getUserCurrentLevel(QString login);

    void updateUserScore(QString login, int score);
    void updateUserLevel(QString login, int level);

    void addTeacherWordsByLevel(QList<QString> words, QString login, int level);


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
