#ifndef MYSQLWRAPPER_H
#define MYSQLWRAPPER_H

#include <QObject>
#include <QDebug>
#include <QList>

// MySQL Connector libraries
#include "mysql_connection.h"
#include "cppconn/driver.h"
#include "cppconn/exception.h"
#include "cppconn/resultset.h"
#include "cppconn/statement.h"
#include "cppconn/prepared_statement.h"

//Name=neverland-db
//Server=us-cdbr-azure-west-c.cloudapp.net
//Login=b485a4f4f7fcea
//Password=fd0282b9

//Database Schema: user(login,first,last,password,is_teacher)
//login is PK
//current_level(login,level)
//login is PK
//class(student,teacher)
//student is PK
//list(level,teacher)
//level,teacher is superkey
//words(teacher,level,word)
//teacher,level,word is superkey

class MySQLWrapper : public QObject
{
    Q_OBJECT
public:
    explicit MySQLWrapper(QObject *parent = 0);
    ~MySQLWrapper();

    //////////// Database Control
    void setHost(QString _hostPath, int _port = 3306);
    void setUsername(QString _username);
    void setPassword(QString _password);
    void setDatabaseName(QString _name);
    bool open();
    bool close();

    /////////// Getters
    QList<QString> getTeacherWordsByLevel(QString teacher, int level);
    int getUserCurrentLevel(QString login);
    int getUserScore(QString login);
    QString getTeacher(QString student);
    QList<QString> getStudents(QString teacher);
    QList<QList<QString>> getTeacherStats(QString teacher);
    QList<QString> getFirstAndLastName(QString login);

    /////////// Verification
    bool usernameAvailable(QString login);
    bool loginCorrect(QString login, QString password);
    bool isTeacher(QString login);

    /////////// Inserts
    void insertNewStudent(QString login, QString first, QString last, QString password, QString teacher);
    void insertNewTeacher(QString login, QString first, QString last, QString password);
    void addTeacherWordsByLevel(QList<QString> words, QString login, int level);
    void addNewTeacherWordByLevel(QString word, QString login, int level);

    /////////// Deletions
    void deleteTeacherWordsByLevel(QString login, int level);
    void deleteTeacherWordByLevel(QString word, QString login, int level);

    /////////// Updates
    void updateUserScore(QString login, int score);
    void updateUserLevel(QString login, int level);
    void updateUserLevelAndScore(QString login, int level, int score);
    void incrementUserLevel(QString login);

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
    sql::PreparedStatement *statement;
    sql::ResultSet *resultSet;
};

#endif // MYSQLWRAPPER_H
